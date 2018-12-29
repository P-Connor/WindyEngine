#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"

template<class C>
void GameObject::AddComponent()
{
	//C component = C();
	//components.push_back(component);
}

GameObject::GameObject()
	: mesh(Cube())
{
	//AddComponent<Transform>();
}
