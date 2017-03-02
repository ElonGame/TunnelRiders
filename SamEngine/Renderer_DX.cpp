#pragma once
#if BUILD_DIRECTX
#include "Renderer_DX.h"
#include <iostream>
#include "GL\GLM\gtc\matrix_inverse.hpp"

Renderer_DX::Renderer_DX(HWND hWnd)
	: _hWnd(hWnd)
{
}

Renderer_DX::~Renderer_DX()
{
}

void Renderer_DX::ClearScreen()
{
	_context->ClearRenderTargetView(_backbuffer, D3DXCOLOR(_clearColour.r, _clearColour.g, _clearColour.b, _clearColour.a));
	_context->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer_DX::Destroy()
{
	_swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

	// close and release all existing COM objects
	_layout->Release();
	_vertexShader->Release();
	_pixelShader->Release();
	_swapchain->Release();
	_backbuffer->Release();
	_device->Release();
	_context->Release();
	_depthStencilView->Release();
	_depthStencilState->Release();
	_depthDisabledStencilState->Release();
	_depthStencilBuffer->Release();
	_rasterState->Release();
	_alphaBlendingState->Release();

	_sampleState->Release();

	if (_uniformBuffer)
	{
		_uniformBuffer->Release();
	}
}

void Renderer_DX::Draw(const Mesh* mesh, const Texture* texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 PM, const glm::vec4 colour)
{
	Texture_DX* texture_dx = (Texture_DX*)texture;
	ID3D11ShaderResourceView* textureResource = texture_dx->GetTexture();
	_context->PSSetShaderResources(0, 1, &textureResource);

	//glm::mat4 MVP = PM * VM * MM;
	//MVP = glm::transpose(MVP);

	glm::mat4 MVMInv = VM * MM;
	MVMInv = (glm::inverseTranspose(MVMInv));
	
	UniformBuffer uniforms;
	memcpy(&uniforms.MM, &MM[0][0], sizeof(DirectX::XMFLOAT4X4));
	memcpy(&uniforms.VM, &VM[0][0], sizeof(DirectX::XMFLOAT4X4));
	memcpy(&uniforms.PM, &PM[0][0], sizeof(DirectX::XMFLOAT4X4));
	memcpy(&uniforms.NM, &MVMInv[0][0], sizeof(DirectX::XMFLOAT4X4));
	memcpy(&uniforms.globalColour, &colour[0], sizeof(DirectX::XMFLOAT4));

	// Need to update uniform buffer here
	D3D11_MAPPED_SUBRESOURCE ms;
	_context->Map(_uniformBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);		// map the buffer
	memcpy(ms.pData, &uniforms, sizeof(UniformBuffer));								// copy the data
	_context->Unmap(_uniformBuffer, NULL);											// unmap the buffer
	_context->VSSetConstantBuffers(0, 1, &_uniformBuffer);
	_context->PSSetConstantBuffers(0, 1, &_uniformBuffer);

	VBO* vbo = mesh->GetVBO();
	if (vbo != NULL)
		vbo->Draw(this);
}

void Renderer_DX::Draw2D(const Mesh * mesh, const Texture * texture, glm::mat4 MM, glm::mat4 VM, glm::mat4 OM, glm::vec4 colour)
{
	// turn off depth buffer
	EnableDepthBuffering(false);

	glm::vec4 light = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	Draw(mesh, texture, MM, VM, OM, light);

	EnableDepthBuffering(true);
}

void Renderer_DX::Initialise(int width, int height)
{
	HRESULT result;
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                   // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
	scd.BufferDesc.Width = width;							// set the back buffer width
	scd.BufferDesc.Height = height;						 // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
	scd.OutputWindow = _hWnd;                              // the window to be used
	scd.SampleDesc.Count = 1;                              // how many multisamples
	scd.Windowed = TRUE;                                   // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

	D3D_FEATURE_LEVEL feature = D3D_FEATURE_LEVEL_11_0;

														   // create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		&feature,
		1,
		D3D11_SDK_VERSION,
		&scd,
		&_swapchain,
		&_device,
		NULL,
		&_context);

	// get the address of the back buffer
	ID3D11Texture2D *p_backbuffer;
	_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_backbuffer);

	// use the back buffer address to create the render target
	result = _device->CreateRenderTargetView(p_backbuffer, NULL, &_backbuffer);
	if (FAILED(result))
	{
		std::cout << "Failed to create backbuffer" << std::endl;
	}
	p_backbuffer->Release();
	p_backbuffer = 0;

	// Initialize the description of the depth buffer.
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_DESC depthDisableStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = width;
	depthBufferDesc.Height = height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = _device->CreateTexture2D(&depthBufferDesc, NULL, &_depthStencilBuffer);
	if (FAILED(result))
	{
		std::cout << "Failed to create depth buffer" << std::endl;
	}
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = _device->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);
	if (FAILED(result))
	{
		std::cout << "Failed to create depth stenicl state" << std::endl;
	}
	_context->OMSetDepthStencilState(_depthStencilState, 1);

	// DEPTH DISABLED STATE
	ZeroMemory(&depthDisableStencilDesc, sizeof(depthDisableStencilDesc));

	depthDisableStencilDesc.DepthEnable = false;
	depthDisableStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisableStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisableStencilDesc.StencilEnable = true;
	depthDisableStencilDesc.StencilReadMask = 0xFF;
	depthDisableStencilDesc.StencilWriteMask = 0xFF;
	depthDisableStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisableStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisableStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisableStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = _device->CreateDepthStencilState(&depthDisableStencilDesc, &_depthDisabledStencilState);
	if (FAILED(result))
	{
		std::cout << "Failed to create depth disabled stenicl state" << std::endl;
	}

	// Initialize the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = depthBufferDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = _device->CreateDepthStencilView(_depthStencilBuffer, NULL, &_depthStencilView);
	if (FAILED(result))
	{
		std::cout << "Failed to create depth stencil view" << std::endl;
	}
	_context->OMSetRenderTargets(1, &_backbuffer, _depthStencilView);

	// Setup rasterizer state
	D3D11_RASTERIZER_DESC raster;
	raster.AntialiasedLineEnable = false;
	raster.CullMode = D3D11_CULL_BACK;
	raster.DepthBias = 0;
	raster.DepthBiasClamp = 0.0f;
	raster.DepthClipEnable = true;
	raster.FillMode = D3D11_FILL_SOLID;
	raster.FrontCounterClockwise = false;
	raster.MultisampleEnable = false;
	raster.ScissorEnable = false;
	raster.SlopeScaledDepthBias = 0.0f;

	result = _device->CreateRasterizerState(&raster, &_rasterState);
	if (FAILED(result))
	{
		std::cout << "Failed to create rasterizer state" << std::endl;
	}
	_context->RSSetState(_rasterState);

	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	_context->RSSetViewports(1, &viewport);

	// Clear the blend state description.
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	// Create an alpha enabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	//blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	// Create the blend state using the description.
	result = _device->CreateBlendState(&blendStateDescription, &_alphaBlendingState);
	if (FAILED(result))
	{
		std::cout << "Failed to create blend state" << std::endl;
	}
	float blendFactor[4];
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;
	_context->OMSetBlendState(_alphaBlendingState, blendFactor, 0xffffffff);

	// Initialise shaders
	InitialiseShaders();
}

void Renderer_DX::SwapBuffers()
{
	_swapchain->Present(0, 0);
}

void Renderer_DX::InitialiseShaders()
{
	// load and compile the two shaders
	ID3D10Blob *VS, *PS;
	D3DX11CompileFromFile(L"shaders.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile(L"shaders.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	// encapsulate both shaders into shader objects
	_device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &_vertexShader);
	_device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &_pixelShader);

	// set the shader objects
	_context->VSSetShader(_vertexShader, 0, 0);
	_context->PSSetShader(_pixelShader, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	_device->CreateInputLayout(ied, 3, VS->GetBufferPointer(), VS->GetBufferSize(), &_layout);
	_context->IASetInputLayout(_layout);

	// Create uniform buffer
	UniformBuffer uniforms;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(uniforms);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &uniforms;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the buffer.
	_device->CreateBuffer(&cbDesc, &InitData, &_uniformBuffer);

	// Create a texture sampler state description.
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	_device->CreateSamplerState(&samplerDesc, &_sampleState);
}

void Renderer_DX::EnableDepthBuffering(bool enable)
{
	if (enable = true)
	{
		// turn on
		_context->OMSetDepthStencilState(_depthStencilState, 1);
	}
	else
	{
		// turn off
		_context->OMSetDepthStencilState(_depthDisabledStencilState, 1);
	}
}

#endif
