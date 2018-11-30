#pragma once
#include <Windows.h>
#include <vector>
#include "Vector2.h"
#include "Graphics.h"
#include "Camera.h"
#include "GameObject.h"
#include "Input.h"


template <class WINDOW_TYPE>
class Window {

public:
	Window() : windowH(NULL) { }

	int Open (
		LPCWSTR lpWindowName,
		DWORD wndStyle,
		DWORD exWndStyle,
		int x, int y,
		int w, int h,
		HWND hWndParent,
		HMENU hMenu
	);

	static LRESULT CALLBACK WindowProcedure(HWND windowH, UINT message, WPARAM wParam, LPARAM lParam);
	HWND GetWindowH() const { return windowH; }
	virtual void Draw(HDC, const std::vector<GameObject>&) = 0;

protected:
	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	
	Vector2<int> resolution;
	Graphics *graphics;
	Camera camera;
	HWND windowH;
	HDC hdc;
};

class MainWindow : public Window<MainWindow>{
public:
	MainWindow();
	MainWindow(
		LPCWSTR lpWindowName,
		DWORD wndStyle = CS_OWNDC | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		DWORD exWndStyle = 0,
		int x = 50, int y = 50,
		int w = 50, int h = 50,
		HWND hWndParent = 0,
		HMENU hMenu = 0);
	~MainWindow();

//protected:
	LPCWSTR winName = L"MainWindow";
	LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	void Draw(HDC, const std::vector<GameObject>&);

};
