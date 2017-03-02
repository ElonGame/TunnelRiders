#pragma once
#if BUILD_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "VBO.h"


class VBO_DX
	: public VBO
{
public:
	VBO_DX();
	virtual ~VBO_DX();

	virtual void Create(Renderer* renderer, Vertex vertices[], int numVertices);
	virtual void Draw(Renderer* renderer);

protected:
	ID3D11Buffer* _vbo;
};
#endif
