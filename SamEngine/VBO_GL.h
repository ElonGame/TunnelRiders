#pragma once
#if BUILD_GL
#include "VBO.h"
class VBO_GL :
	public VBO
{
public:
	VBO_GL();
	virtual ~VBO_GL();

	virtual void Create(Renderer* renderer, Vertex vertices[], int numVertices) {}
	virtual void Draw(Renderer* renderer) {}
};
#endif

