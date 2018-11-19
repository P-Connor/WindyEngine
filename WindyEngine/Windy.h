#pragma once
#include <Windows.h>
#include "Window.h"
#include "Debug.h"
#include "GameObject.h"
#include <vector>
class Windy {

public:	
	Windy();
	Windy(	LPCWSTR displayT,
			int w = CW_USEDEFAULT, int h = CW_USEDEFAULT);
	
	void Loop();
	void Begin();
	void Update();
	
	MainWindow& GetMainWindow();
	void AddGameObject(GameObject&);

private:
	LPCWSTR appName = L"WindyEngine";
	LPCWSTR displayName = L"Windy";
	MainWindow mainWin;

	std::vector<GameObject> gameObjects;
};