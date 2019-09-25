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

	/*GameObject target;
	target.mesh = Mesh("C:\\Users\\Colloquiem\\Desktop\\Shape.obj");
	target.transform.position = Vector3<double>(-5, 0, 10);
	target.transform.scale = Vector3<double>(.1, .1, .1);
	AddGameObject(target);*/

	/*
	GameObject cube2, cube3, cube4, cube5;;

	cube2.transform.position = Vector3<double>(4, 2, 10);
	cube3.transform.position = Vector3<double>(4, -2, 10);
	cube4.transform.position = Vector3<double>(-4, 2, 10);
	cube5.transform.position = Vector3<double>(-4, -2, 10);
	
	AddGameObject(cube2);
	AddGameObject(cube3);
	AddGameObject(cube4);
	AddGameObject(cube5);
	*/

	/*
	GameObject cube;
	for (int x = -3; x < 3; x++) {
		for (int y = -3; y < 3; y++) {
			for (int z = -3; z < 3; z++) {
				cube.transform.position = Vector3<double>(x * 2, y * 2, (z * 2) + 50 );
				AddGameObject(cube);
			}
		}
	}
	*/
}
	
//Called once per frame
void Windy::Update() {
	static double angle[] = { 0,180,0 }, angleInc = 1;

	/*if (gameObjects[0].transform.position.X - gameObjects[1].transform.position.X < 1
		&& gameObjects[0].transform.position.Y - gameObjects[1].transform.position.Y < 1
		&& gameObjects[0].transform.position.Z - gameObjects[1].transform.position.Z < 1) 
	{
		gameObjects[1].transform.position = Vector3<double>((rand() % 5) - 2.5, (rand() % 20) - 5, (rand() % 10) + 10);
	}*/

	/*
	for (int i = 1; i < gameObjects.size(); i++) {
		gameObjects[i].transform.position.X *= 1.01;
		gameObjects[i].transform.position.Y *= 1.01;
	}
	*/

	for (int axis = 0; axis < 3; axis++) {
		if (angle[axis] > 360) {
			angle[axis] -= 360;
		}
		if (angle[axis] < 0) {
			angle[axis] += 360;
		}
	}
	if (WInput.KeyHeld(KC_W) || WInput.KeyDown(KC_W)) {
		angle[2] += angleInc * deltaTime * 10;
		gameObjects[0].transform.position.Y += angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_S) || WInput.KeyDown(KC_S)) {
		angle[2] -= angleInc * deltaTime * 10;
		gameObjects[0].transform.position.Y -= angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_D) || WInput.KeyDown(KC_D)) {
		angle[1] += angleInc * deltaTime * 10;
		//gameObjects[0].transform.position.X += angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_A) || WInput.KeyDown(KC_A)) {
		angle[1] -= angleInc * deltaTime * 10;
		//gameObjects[0].transform.position.X -= angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_E) || WInput.KeyDown(KC_E)) {
		angle[0] -= angleInc * deltaTime * 10;
		//gameObjects[0].transform.position.Z += angleInc * deltaTime;
	}
	if (WInput.KeyHeld(KC_Q) || WInput.KeyDown(KC_Q)) {
		angle[0] += angleInc * deltaTime * 10;
		//gameObjects[0].transform.position.Z -= angleInc  * deltaTime;
	}
	
	if (WInput.KeyUp(KC_R)) {
		
		angle[0] = 0;
		angle[1] = 180;
		angle[2] = 0;
		
		
		//gameObjects[0].transform.position = Vector3<double>(5, 2, 10);
	}
	
	gameObjects[0].transform.rotation = Vector3<double>(angle[0], angle[1], angle[2]);
}

