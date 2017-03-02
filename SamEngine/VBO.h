#pragma once
#include "Vertex.h"

// Forward Declarations
class Renderer;

class VBO
{
public:
	VBO();
	virtual ~VBO();

	virtual void Create(Renderer* rendeer, Vertex vertices[], int numVerticies) = 0;
	virtual void Draw(Renderer* renderer) = 0;

protected:
	int _numVertices;
};

