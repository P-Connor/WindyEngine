#include "Input.h"
#include <Windows.h>

//Returns the singular instace of the WindyInput class
WindyInput* WindyInput::GetInstance()
{
	static WindyInput instance;
	return &instance;
}

//Retrieves a pointer to a key object at the specified index
Key* WindyInput::GetKey(const unsigned int& k)
{
	return &(keys[k]);
}

//Updates the keyboard input
void WindyInput::UpdateKeys()
{
	for (int i = 0; i < keyCount; i++) {
		if ((GetAsyncKeyState(i+1) & (short)65535) != 0){		//if the current key is being pressed		
			
			if (keys[i].isDown) {		//if the key was held down last frame
				keys[i].isDown = false;
				keys[i].isHeld = true;
			}
			else if (keys[i].isHeld == false) {	//if the key was not held last frame
				keys[i].isDown = true;
			}

			if (keys[i].isUp) {			//if the key was released last frame
				keys[i].isUp = false;	//update it to not be released anymore
			}

		}
		else {	//if the key was not pressed this frame
			if (keys[i].isHeld || keys[i].isDown) {	//if the key was pressed or held last frame
				keys[i].isUp = true;
			}
			else {	//if the key was not pressed
				keys[i].isUp = false;
			}
			keys[i].isDown = false;	//Since the key is not being pressed during this frame
			keys[i].isHeld = false;	//set the other two states to false
		}
	}
}

//Initializes the keyboard input buffer 
//(assuming that no keys are pressed)
WindyInput::WindyInput()
{
	for (int i = 0; i < keyCount; i++) {
		keys[i].isDown = false;
		keys[i].isHeld = false;
		keys[i].isUp = false;
	}
}
