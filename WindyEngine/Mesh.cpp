#include "Mesh.h"
#include "Debug.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

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

Mesh::Mesh(std::string filename)
{
	std::ifstream fin;
	fin.open(filename);

	if (fin.fail()) {
		throw 1;
		return;
	}

	std::vector<Vertex3> verts;
	std::vector<Vector3<size_t>> tris;

	while (!fin.eof()) {
		std::string s;
		double x, y, z;

		getline(fin, s);
		std::istringstream sin(s);

		sin >> s;

		if (s == "v") {
			sin >> x;
			sin >> y;
			sin >> z;
			z = -z;
			verts.push_back(Vertex3(Vector3<double>(x, y, z), COLORREF(RGB(200, (x+4.5)*30, (y+2)*50))));
			//WinDebug.Log("v " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z));
		}
		else if (s == "f") {
			unsigned _verts[3], _tcs[3], _norms[3];

			for (int i = 0; i < 3; i++) {
				std::string vert, tc, norm;
				std::istringstream num;

				getline(sin, vert, '/');
				num = std::istringstream(vert);
				num >> _verts[i];

				getline(sin, tc, '/');
				num = std::istringstream(vert);
				num >> _tcs[i];

				getline(sin, norm, ' ');
				num = std::istringstream(vert);
				num >> _norms[i];
			}

			tris.push_back(Vector3<size_t>(_verts[0]-1, _verts[1]-1, _verts[2]-1));

			//WinDebug.Log("f " + std::to_string(_verts[0]-1) + ", " + std::to_string(_verts[1]-1) + ", " + std::to_string(_verts[2]-1));
		}
	}

	vertCount = verts.size();
	triCount = tris.size();
	vertices = new Vertex3[vertCount];
	triangles = new Vector3<size_t>[triCount];

	for (int i = 0; i < vertCount; i++) {
		vertices[i] = verts.at(i);
	}
	for (int i = 0; i < triCount; i++) {
		triangles[i] = tris.at(i);
	}

	fin.close();
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

