#pragma once
#include <vector>
#include "VBO.h"
#include "Vertex.h"
#include "ObjImporter.h"

// Forward Declarations
class Renderer;

class Mesh
{
public:
	Mesh();
	~Mesh();

	VBO* GetVBO() const { return _vbo; }
	int NumVertices() const { return (int)_vertices.size(); }
	Vertex GetVertex(int i) const { return _vertices[i]; }
	Vertex& GetVertexRef(int i) { return _vertices[i]; }

	VBO* CreateVBO(Renderer* renderer);
	bool AddVertex(Vertex v);
	bool Clear();
	bool DeleteVertex(int i);

	bool ImportFromObj(const char * fileName);
	
	void Reset();
	float CalcuateMaxSize();

private:
	bool _locked;
	VBO* _vbo;
	std::vector<Vertex> _vertices;
};

