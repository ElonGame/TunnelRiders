#pragma once
#if BUILD_DIRECTX
#include "Texture_DX.h"
#include "Game.h"
#include "Renderer_DX.h"


Texture_DX::Texture_DX() : m_texture(0)
{
}

Texture_DX::Texture_DX(const Texture_DX & other)
{
}


Texture_DX::~Texture_DX()
{
	Shutdown();
}

bool Texture_DX::Initialisze(WCHAR * fileName)
{
	Renderer_DX* renderer = (Renderer_DX*)Game::TheGame->GetRenderer();
	ID3D11Device* device = renderer->GetDevice();

	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(device, fileName, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void Texture_DX::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}

ID3D11ShaderResourceView * Texture_DX::GetTexture()
{
	return m_texture;
}
#endif