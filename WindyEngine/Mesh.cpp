#include "Mesh.h"

Mesh::Mesh()
	: vertices(0), triangles(0), vertCount(0), triCount(0)
{}

Mesh::~Mesh()
{
	if (vertices != 0) {
		delete[] vertices;
	}
	if (triangles != 0) {
		delete[] triangles;
	}
}

Mesh::Mesh(const Mesh& mesh)
{
	vertCount = mesh.vertCount;
	triCount = mesh.triCount;

	vertices = new Vertex3[mesh.vertCount];
	for (int i = 0; i < mesh.vertCount; i++) {
		vertices[i] = mesh.vertices[i];
	}

	triangles = new Vector3<size_t>[mesh.triCount];
	for (int i = 0; i < mesh.triCount; i++) {
		triangles[i] = mesh.triangles[i];
	}
}

Mesh& Mesh::operator=(const Mesh& mesh)
{
	vertCount = mesh.vertCount;
	triCount = mesh.triCount;

	vertices = new Vertex3[mesh.vertCount];
	for (int i = 0; i < mesh.vertCount; i++) {
		vertices[i] = mesh.vertices[i];
	}

	triangles = new Vector3<size_t>[mesh.triCount];
	for (int i = 0; i < mesh.triCount; i++) {
		triangles[i] = mesh.triangles[i];
	}
	
	return *this;
}

