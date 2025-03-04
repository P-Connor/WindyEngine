#include "Window.h"
#include "Graphics.h"
#include "Debug.h"
#include "Matrix4.h"
#include <stdexcept>

//Registers and creates a new window with inputed properties
//Returns 0 if successful
template <class WINDOW_TYPE> 
int Window<WINDOW_TYPE>::Open (
	LPCWSTR lpWindowName,
	DWORD wndStyle,
	DWORD exWndStyle,
	int x, int y,
	int w, int h,
	HWND hWndParent,
	HMENU hMenu)
{	
	//Adjust the coordinates of the window for the exact resolution
	LPRECT windowRect = &RECT();
	windowRect->left = x;
	windowRect->top = y;
	windowRect->right = x + w + 1;
	windowRect->bottom = y + h + 1;
	AdjustWindowRectEx(windowRect, wndStyle, false, exWndStyle);
	
	WNDCLASSEXW winClass = { 0 };

	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.lpfnWndProc = WINDOW_TYPE::WindowProcedure;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = GetModuleHandle(NULL);
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = NULL;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = lpWindowName;
	winClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (RegisterClassExW(&winClass) == 0) {
		return GetLastError();
	}

	if (CreateWindowExW(
		exWndStyle, 
		lpWindowName, 
		lpWindowName, 
		wndStyle,
		windowRect->left, windowRect->top, 
		windowRect->right - windowRect->left, windowRect->bottom - windowRect->top,
		hWndParent, 
		hMenu, 
		GetModuleHandleW(NULL), 
		this
	) == NULL) {
		return 1;
	}

	return 0;
}

template<class WINDOW_TYPE>
LRESULT CALLBACK Window<WINDOW_TYPE>::WindowProcedure(HWND windowH, UINT message, WPARAM wParam, LPARAM lParam)
{
	WINDOW_TYPE* windowPtr;

	if (message == WM_NCCREATE) {
		CREATESTRUCTW* pCreate = (CREATESTRUCTW*)lParam;
		windowPtr = (WINDOW_TYPE*)pCreate->lpCreateParams;
		SetWindowLongPtrW(windowH, GWLP_USERDATA, (LONG_PTR)windowPtr);

		windowPtr->windowH = windowH;

		//SetTimer(windowH, IDT_TIMER1, 1, (TIMERPROC)NULL);
	}
	else {
		windowPtr = (WINDOW_TYPE*)GetWindowLongPtrW(windowH, GWLP_USERDATA);
	}

	if (windowPtr) {
		return windowPtr->HandleMessage(message, wParam, lParam);
	}
	else {
		return DefWindowProcW(windowH, message, wParam, lParam);
	}

}

MainWindow::MainWindow()
{
	int ret = Open(L"default", CS_OWNDC | WS_OVERLAPPEDWINDOW, 0, CW_DEFAULT, CW_DEFAULT, CW_DEFAULT, CW_DEFAULT, NULL, NULL);
	if (ret != 0) {
		std::runtime_error("Error! Failed to open window! Code:" + ret);
	}
	resolution = Vector2<int>(CW_USEDEFAULT, CW_USEDEFAULT);
	camera = Camera(resolution);
	graphics = new Graphics(hdc, resolution);
}

MainWindow::MainWindow(
	LPCWSTR lpWindowName,
	DWORD wndStyle,
	DWORD exWndStyle,
	int x, int y,
	int w, int h,
	HWND hWndParent,
	HMENU hMenu)
{
	int ret = Open(lpWindowName, wndStyle, exWndStyle, x, y, w, h, hWndParent, hMenu);
	if (ret != 0) {
		std::runtime_error("Error! Failed to open window! Code:" + ret);
	}
	resolution = Vector2<int>(w, h);
	camera = Camera(resolution);
	//camera.SetMode(ORTHOGRAPHIC);
	//camera.SetFov(90);
	graphics = new Graphics(hdc, resolution);
}

MainWindow::~MainWindow()
{
	delete graphics;
}

void MainWindow::Draw(HDC hdc, const std::vector<GameObject>& gameObjects) {	
	Timer total;
	unsigned last;

	for (int obj = 0; obj < gameObjects.size(); obj++) {
		Vertex3 *modifiedVerts = new Vertex3[gameObjects[obj].mesh.vertCount];

		last = total.Value();
		//WinDebug.Log(std::to_string(last) + "\t-allocated");
		
		Matrix4 rotMatrix = Matrix4::RotationDeg(gameObjects[obj].transform.rotation);

		for (int i = 0; i < gameObjects[obj].mesh.vertCount; i++) {
			modifiedVerts[i] = gameObjects[obj].mesh.vertices[i];
			modifiedVerts[i].position *= gameObjects[obj].transform.scale;
			modifiedVerts[i].position = rotMatrix * modifiedVerts[i].position;
			modifiedVerts[i].position.Translate(gameObjects[obj].transform.position);
			camera.WorldToScreen(modifiedVerts[i]);
		}
		
		//WinDebug.Log(std::to_string(total.Value()-last) + "\t-modified");
		last = total.Value();

		for (int i = 0; i < gameObjects[obj].mesh.triCount; i++) {
			graphics->DrawTriangle(	modifiedVerts[gameObjects[obj].mesh.triangles[i].X], 
									modifiedVerts[gameObjects[obj].mesh.triangles[i].Y],
									modifiedVerts[gameObjects[obj].mesh.triangles[i].Z]);
		}
		
		//WinDebug.Log(std::to_string(total.Value()-last) + "\t-drew triangles");
		last = total.Value();
		
		delete[] modifiedVerts;
		//WinDebug.Log(std::to_string(total.Value() - last) + "\t-deleted");
	}

	BitBlt(hdc, 0, 0, resolution.X, resolution.Y, graphics->GetMemoryHDC(), 0, 0, SRCCOPY);
	
	//WinDebug.Log(std::to_string(total.Value() - last) + "\t-flipped buffer");
	//last = total.Value();
	
	graphics->ClearBuffer();

	//WinDebug.Log(std::to_string(total.Value()-last) + "\t-cleared old buffer");
}

LRESULT MainWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message) {

	case WM_NCCREATE: {
		return DefWindowProcW(windowH, message, wParam, lParam);
	}

	case WM_CLOSE: {
		DestroyWindow(windowH);
		return 0;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}

	default: {
		return DefWindowProcW(windowH, message, wParam, lParam);
	}
	}
}