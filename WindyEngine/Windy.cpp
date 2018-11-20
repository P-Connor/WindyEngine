#include "Windy.h"
#include "Window.h"
#include <iostream>

int WINAPI wWinMain(HINSTANCE currentInstanceH, HINSTANCE prevInstaceH, PWSTR pCommandLine, int nCmdShow)
{
	Windy windy(L"Windy Game Engine", 960, 540);

	ShowWindow(windy.GetMainWindow().GetWindowH(), nCmdShow);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		windy.Loop();
	}

	return 0;
}

Windy::Windy() : mainWin(L"Windy", CS_OWNDC | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
{
	Begin();
}

Windy::Windy(LPCWSTR displayT, int w, int h) : mainWin( displayT, 
														CS_OWNDC | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
														0, 5, 35,
														w, h)
{
	Begin();
}

void Windy::Loop() {
	static Timer framerateTimer;
	static long frames = 0;
	static double elapsedT = 0;
	
	HDC hdc = GetDC(mainWin.GetWindowH());
	mainWin.Draw(hdc, gameObjects);
	ReleaseDC(mainWin.GetWindowH(), hdc);
	
	WInput.UpdateKeys();
	Update();

	frames++;
	deltaTime = framerateTimer.GetValue() / 100000000.0;
	elapsedT += deltaTime;
	framerateTimer.ResetTimer();
	if (elapsedT > 1) {
		WinDebug.Log(frames);
		frames = 0;
		elapsedT -= 1;
	}
}

MainWindow& Windy::GetMainWindow() {
	return mainWin;
}

void Windy::AddGameObject(GameObject& gObj)
{
	gameObjects.push_back(gObj);
}

unsigned int Windy::FrameRate()
{
	return frameRate;
}

double Windy::DeltaTime()
{
	return deltaTime;
}
