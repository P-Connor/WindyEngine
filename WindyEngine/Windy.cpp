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

//Constructs the engine by default
Windy::Windy() : mainWin(L"Windy", CS_OWNDC | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)
{
	gameObjects.reserve(100);
	Begin();
}

//Constructs the engine with more control over parameters such as window width and height
Windy::Windy(LPCWSTR displayT, int w, int h) : mainWin( displayT, 
														CS_OWNDC | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
														0, 5, 35,
														w, h)
{
	gameObjects.reserve(100);
	Begin();
}

//The main update loop of the engine, called once per frame
//Not to be confused with Update(), Loop() handles all of the "low level" events of the engine per frame
void Windy::Loop() {
	static Timer framerateTimer, secondsTimer;
	static unsigned frames = 0;
	
	HDC hdc = GetDC(mainWin.GetWindowH());
	mainWin.Draw(hdc, gameObjects);
	ReleaseDC(mainWin.GetWindowH(), hdc);
	
	WInput.UpdateKeys();
	Update();

	frames++;
	deltaTime = framerateTimer.Value() / 100000000.0;
	if (secondsTimer.Value() > 1000000000) {
		frameRate = frames;

		// TODO - Remove log
		WinDebug.Log(frameRate);

		frames = 0;
		secondsTimer.Reset();
	}
	framerateTimer.Reset();
}

//Returns a reference to the main window of the engine
MainWindow& Windy::GetMainWindow() {
	return mainWin;
}

//Adds a gameobject to the scene by copying
void Windy::AddGameObject(const GameObject& gObj)
{
	gameObjects.push_back(gObj);
}

//Returns the current framerate
//Note: framerate is only updated once per second
unsigned int Windy::FrameRate()
{
	return frameRate;
}

//Returns the time in seconds that the last frame took to execute
double Windy::DeltaTime()
{
	return deltaTime;
}
