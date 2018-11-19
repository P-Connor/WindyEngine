#pragma once

enum KeyCode {	KC_A = 0x41, KC_B = 0x42, 
				KC_C = 0x43, KC_D = 0x44, 
				KC_E = 0x45, KC_F = 0x46, 
				KC_G = 0x47, KC_H = 0x48, 
				KC_I = 0x49, KC_J = 0x4A, 
				KC_K = 0x4B, KC_L = 0x4C, 
				KC_M = 0x4D, KC_N = 0x4E,
				KC_O = 0x4F, KC_P = 0x50,
				KC_Q = 0x51, KC_R = 0x52,
				KC_S = 0x53, KC_T = 0x54,
				KC_U = 0x55, KC_V = 0x56,
				KC_W = 0x57, KC_X = 0x58,
				KC_Y = 0x59, KC_Z = 0x5A};

struct Key {
	bool isDown = false, isHeld = false, isUp = false;
};

/*	Singleton class for handling keyboard and mouse input.
	Access using "Winput" */
class WindyInput {

public:
	static WindyInput* GetInstance();

	inline bool KeyDown(const unsigned int& k) { return keys[k - 1].isDown; }
	inline bool KeyHeld(const unsigned int& k) { return keys[k - 1].isHeld; }
	inline bool KeyUp(	const unsigned int& k) { return keys[k - 1].isUp; }

	Key* GetKey(const unsigned int&);
	void UpdateKeys();

private:
	WindyInput();
	const size_t keyCount = 254;
	Key keys[254];

};

#define WInput (*WindyInput::GetInstance())