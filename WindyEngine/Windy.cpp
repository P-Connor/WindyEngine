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
	static Timer framerateTimer, secondsTimer;
	static long frames = 0;
	
	HDC hdc = GetDC(mainWin.GetWindowH());
	mainWin.Draw(hdc, gameObjects);
	ReleaseDC(mainWin.GetWindowH(), hdc);
	
	WInput.UpdateKeys();
	Update();


	//WinDebug.Log("Seconds: " + std::to_string(secondsTimer.Value() / 1000000000.0));
	frames++;
	deltaTime = framerateTimer.Value() / 100000000.0;
	if (secondsTimer.Value() > 1000000000) {
		frameRate = frames;
		frames = 0;
		secondsTimer.Reset();
	}
	WinDebug.Log(frameRate);
	framerateTimer.Reset();
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
