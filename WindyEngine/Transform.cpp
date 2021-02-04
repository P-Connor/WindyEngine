#include "Transform.h"

Transform::Transform() {

	position = Vector3<double>(0, 0, 0);
	rotation = Vector3<double>(0, 0, 0);
	scale = Vector3<double>(1, 1, 1);

}

void Transform::Translate(double x, double y, double z) {
	Translate(Vector3<double>(x, y, z));
}
void Transform::Translate(Vector3<double> vec) {
	position += Matrix4::RotationDeg(rotation) * vec;
}

void Transform::TranslateWorld(double x, double y, double z) {
	position.X += x;
	position.Y += y;
	position.Z += z;
}
void Transform::TranslateWorld(Vector3<double> vec) {
	position += vec;
}

void Transform::Rotate(double x, double y, double z) {
	rotation.X += x;
	if (rotation.X > 360)
		rotation.X -= (int)(rotation.X / 360) * 360;
	if (rotation.X < 0)
		rotation.X += ((int)(-rotation.X / 360) + 1) * 360;

	rotation.Y += y;
	if (rotation.Y > 360)
		rotation.Y -= (int)(rotation.Y / 360) * 360;
	if (rotation.Y < 0)
		rotation.Y += ((int)(-rotation.Y / 360) + 1) * 360;

	rotation.Z += z;
	if (rotation.Z > 360)
		rotation.Z -= (int)(rotation.Z / 360) * 360;
	if (rotation.Z < 0)
		rotation.Z += ((int)(-rotation.Z / 360) + 1) * 360;
}
void Transform::Rotate(Vector3<double> vec) {
	Rotate(vec.X, vec.Y, vec.Z);
}

void Transform::Scale(double x, double y, double z) {
	scale.X += x;
	scale.Y += y;
	scale.Z += z;
}
void Transform::Scale(Vector3<double> vec) {
	scale += vec;
}