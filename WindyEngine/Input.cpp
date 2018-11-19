#include "Input.h"
#include <Windows.h>

WindyInput* WindyInput::GetInstance()
{
	static WindyInput instance;
	return &instance;
}

/*
inline bool WindyInput::KeyDown(const unsigned int& k)
{
	return keys[k - 1].isDown;
}


inline bool WindyInput::KeyHeld(const unsigned int& k)
{
	return keys[k - 1].isHeld;
}

inline bool WindyInput::KeyUp(const unsigned int& k)
{
	return keys[k - 1].isUp;
}
*/

Key* WindyInput::GetKey(const unsigned int& k)
{
	return &(keys[k]);
}

void WindyInput::UpdateKeys()
{
	for (int i = 0; i < keyCount; i++) {
		if ((GetAsyncKeyState(i+1) & (short)65535) != 0){			
			
			if (keys[i].isDown) {
				keys[i].isDown = false;
				keys[i].isHeld = true;
			}
			else if (keys[i].isHeld == false) {
				keys[i].isDown = true;
			}

			if (keys[i].isUp) {
				keys[i].isUp = false;
			}

		}
		else {
			if (keys[i].isHeld || keys[i].isDown) {
				keys[i].isUp = true;
			}
			else {
				keys[i].isUp = false;
			}
			keys[i].isDown = false;
			keys[i].isHeld = false;
		}
	}
}

WindyInput::WindyInput()
{
	for (int i = 0; i < keyCount; i++) {
		keys[i].isDown = false;
		keys[i].isHeld = false;
		keys[i].isUp = false;
	}
}
