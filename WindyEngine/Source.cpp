#include "Windy.h"
//#include "Input.h"

void Windy::Begin() {
	GameObject cube1, cube2;
	cube1.transform.position = Vector3<double>(0, 0, 4);
	cube2.transform.position = Vector3<double>(5, 2, 10);
	AddGameObject(cube1);
	AddGameObject(cube2);
}
	
void Windy::Update() {
	WinLog.StartTimer(0);
	
	static double angle[] = { 0,0,0 }, angleInc = .2;

	for (int axis = 0; axis < 3; axis++) {
		if (angle[axis] > 360) {
			angle[axis] -= 360;
		}
		if (angle[axis] < 0) {
			angle[axis] += 360;
		}
	}
	if (WInput.KeyHeld(KC_W) || WInput.KeyDown(KC_W)) {
		angle[0] += angleInc;
		gameObjects[1].transform.position.Y += angleInc / 10;
	}
	if (WInput.KeyHeld(KC_S) || WInput.KeyDown(KC_S)) {
		angle[0] -= angleInc;
		gameObjects[1].transform.position.Y -= angleInc / 10;
	}
	if (WInput.KeyHeld(KC_D) || WInput.KeyDown(KC_D)) {
		angle[1] += angleInc;
		gameObjects[1].transform.position.X += angleInc / 10;
	}
	if (WInput.KeyHeld(KC_A) || WInput.KeyDown(KC_A)) {
		angle[1] -= angleInc;
		gameObjects[1].transform.position.X -= angleInc / 10;
	}
	if (WInput.KeyHeld(KC_E) || WInput.KeyDown(KC_E)) {
		angle[2] += angleInc;
		gameObjects[1].transform.position.Z += angleInc / 10;
	}
	if (WInput.KeyHeld(KC_Q) || WInput.KeyDown(KC_Q)) {
		angle[2] -= angleInc;
		gameObjects[1].transform.position.Z -= angleInc / 10;
	}
	
	if (WInput.KeyUp(KC_R)) {
		angle[0] = 0;
		angle[1] = 0;
		angle[2] = 0;
		gameObjects[1].transform.position = Vector3<double>(5, 2, 10);
	}
	
	gameObjects[0].transform.rotation = Vector3<double>(angle[0], angle[1], angle[2]);

	WinLog.EndTimer(0);
}

