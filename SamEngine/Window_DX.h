#pragma once
#if BUILD_DIRECTX
#include "Window.h"

// include Windows and Direct3D headers
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <DirectXMath.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class Window_DX :
	public Window
{

public:
	Window_DX(Game* game, int width, int height, HINSTANCE hInstance, int nCmdShow);
	virtual ~Window_DX();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void Initialise();

private:
	HWND _hWnd;
};
#endif
