#include "Windy.h"
#include "Face.h"
#include <cstdlib>

//Called once at startup, used to initialize objects and scenes
void Windy::Begin() {

	//GetMainWindow().camera.UpdProjection(ORTHOGRAPHIC);

	GameObject anvil;
	anvil.mesh = Mesh("./Resources/Anvil2.obj");
	anvil.transform.position = Vector3<double>(0.0, 0.0, 20.0);
	anvil.transform.rotation = Vector3<double>(0, 0, 0);
	AddGameObject(anvil);

	GetMainWindow().GetCamera().GetTransform().Rotate(0, 180, 0);
}
	
//Called once per frame
void Windy::Update() {
	static double angle[] = { 0,180,0 }, angleInc = 1;
	Vector3<double> camVelocity = Vector3<double>(0, 0, 0);
	Vector3<double> camRotationVelocity = Vector3<double>(0, 0, 0);
	double tSpeed = 0.5, rSpeed = 5;

	for (int axis = 0; axis < 3; axis++) {
		if (angle[axis] > 360) {
			angle[axis] -= 360;
		}
		if (angle[axis] < 0) {
			angle[axis] += 360;
		}
	}
	if (WInput.KeyHeld(KC_W) || WInput.KeyDown(KC_W)) {
		//angle[2] += angleInc * deltaTime * 10;
		camVelocity.Z = tSpeed * deltaTime;
		//gameObjects[0].transform.position.Y += angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_S) || WInput.KeyDown(KC_S)) {
		//angle[2] -= angleInc * deltaTime * 10;
		camVelocity.Z = -tSpeed * deltaTime;
		//gameObjects[0].transform.position.Y -= angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_D) || WInput.KeyDown(KC_D)) {
		//angle[1] += angleInc * deltaTime * 10;
		camVelocity.X = tSpeed * deltaTime;
		//gameObjects[0].transform.position.X += angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_A) || WInput.KeyDown(KC_A)) {
		//angle[1] -= angleInc * deltaTime * 10;
		camVelocity.X = -tSpeed * deltaTime;
		//gameObjects[0].transform.position.X -= angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_E) || WInput.KeyDown(KC_E)) {
		//angle[0] -= angleInc * deltaTime * 10;
		camVelocity.Y = -tSpeed * deltaTime;
		//gameObjects[0].transform.position.Z += angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_Q) || WInput.KeyDown(KC_Q)) {
		//angle[0] += angleInc * deltaTime * 10;
		camVelocity.Y = tSpeed * deltaTime;
		//gameObjects[0].transform.position.Z -= angleInc  * deltaTime;
	}

	//----------------------------------------------------------------------------------------------
	
	if (WInput.KeyHeld(KC_I) || WInput.KeyDown(KC_I)) {
		camRotationVelocity.X = rSpeed * deltaTime;
	}
	if (WInput.KeyHeld(KC_K) || WInput.KeyDown(KC_K)) {
		camRotationVelocity.X = -rSpeed * deltaTime;
	}
	if (WInput.KeyHeld(KC_L) || WInput.KeyDown(KC_L)) {
		camRotationVelocity.Y = rSpeed * deltaTime;
	}
	if (WInput.KeyHeld(KC_J) || WInput.KeyDown(KC_J)) {
		camRotationVelocity.Y = -rSpeed * deltaTime;
	}
	if (WInput.KeyHeld(KC_O) || WInput.KeyDown(KC_O)) {
		camRotationVelocity.Z = -rSpeed * deltaTime;
	}
	if (WInput.KeyHeld(KC_U) || WInput.KeyDown(KC_U)) {
		camRotationVelocity.Z = rSpeed * deltaTime;
	}
	
	if (WInput.KeyUp(KC_R)) {
		
		angle[0] = 0;
		angle[1] = 180;
		angle[2] = 0;
		
		
		//gameObjects[0].transform.position = Vector3<double>(5, 2, 10);
	}
	
	gameObjects[0].transform.rotation = Vector3<double>(angle[0], angle[1], angle[2]);
	Camera& c = GetMainWindow().GetCamera();
	Transform& t = c.GetTransform();
	WinDebug.Log(std::to_string(t.rotation.X) + " " + std::to_string(t.rotation.Y) + " " + std::to_string(t.rotation.Z));
	t.Translate(camVelocity);
	t.Rotate(camRotationVelocity);
	c.UpdViewMatrix();
}

