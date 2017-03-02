#pragma once
#if BUILD_DIRECTX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "Texture.h"

class Texture_DX :
	public Texture
{
public:
	Texture_DX();
	Texture_DX(const Texture_DX&);
	virtual ~Texture_DX();

	bool Initialisze(WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* m_texture;
};
#endif