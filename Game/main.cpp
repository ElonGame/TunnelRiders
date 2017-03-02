#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "TunnelGame.h"

#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "Window_DX.h"

#include <stdlib.h> 
#include <time.h>  

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;


// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; };

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// Create the Game object
	TunnelGame game;

	// Create a Window object
	Window_DX application(&game, SCREEN_WIDTH, SCREEN_HEIGHT, hInstance, nCmdShow);

	srand(time(NULL));

	application.Initialise();
}