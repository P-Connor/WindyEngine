#pragma once
#include <Windows.h>

class Window 
{

public:
	Window(LPSTR name, );
	Window() = delete;
	~Window();

private:
	HWND handle;

};

