#pragma once
#if BUILD_DIRECTX
#include <d3d11.h>
#include <D3DX11.h>
#include <d3dx10.h>
#include <DirectXMath.h>
#include "Renderer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Texture_DX.h"

typedef struct UniformBuffer
{
	DirectX::XMFLOAT4X4 MM;
	DirectX::XMFLOAT4X4 VM;
	DirectX::XMFLOAT4X4 PM;
	DirectX::XMFLOAT4X4 NM;
	DirectX::XMFLOAT4 globalColour;
} UniformBuffer;

class Renderer_DX :
	public Renderer
{
public:
	Renderer_DX(HWND hWnd);
	virtual ~Renderer_DX();

	ID3D11Device* GetDevice() const { return _device; }
	void SetDevice(ID3D11Device* v) { _device = v; }

	ID3D11DeviceContext* GetContext() const { return _context; }
	void SetContext(ID3D11DeviceContext* v) { _context = v; }

	virtual void ClearScreen();
	virtual void Destroy();
	virtual void Draw(const Mesh* mesh, const Texture* texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 PM, glm::vec4 colour);
	virtual void Draw2D(const Mesh* mesh, const Texture* texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 OM, glm::vec4 colour);
	virtual void Initialise(int width, int height);
	virtual void SwapBuffers();
	void InitialiseShaders();


protected:
	IDXGISwapChain*	_swapchain;             // the pointer to the swap chain interface
	ID3D11Device*	_device;                // the pointer to our Direct3D device interface
	ID3D11DeviceContext* _context;				// the pointer to our Direct3D device context
	ID3D11RenderTargetView* _backbuffer;			// the pointer to our back buffer
	ID3D11Texture2D* _depthStencilBuffer;

	ID3D11DepthStencilState* _depthStencilState;
	ID3D11DepthStencilState* _depthDisabledStencilState;

	ID3D11DepthStencilView* _depthStencilView;
	ID3D11RasterizerState* _rasterState;

	ID3D11InputLayout* _layout;				// the pointer to the input layout
	ID3D11VertexShader*	_vertexShader;			// the pointer to the vertex shader
	ID3D11PixelShader* _pixelShader;			// the pointer to the pixel shader
	ID3D11Buffer* _uniformBuffer;			// Stores the MVM and colour
	ID3D11SamplerState* _sampleState;
	ID3D11BlendState* _alphaBlendingState;

	HWND _hWnd;	// Window handle

	void EnableDepthBuffering(bool enable);
};
#endif
