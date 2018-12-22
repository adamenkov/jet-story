#include "../Shared/Engine.h"
#include "../Shared/Game.h"
#include <cstdlib>
#include <ctime>
#include "Audio.h"
#include "Font.h"
#include "Sound.h"
#include "Stopwatch.h"


LPDIRECT3DDEVICE9	g_pDirect3DDevice;		// the video card
LPD3DXSPRITE		g_pDirect3DXSprite;

std::unique_ptr<Font> g_pFont;

long int g_nFrameID = 0;


namespace
{
	LPDIRECT3D9			pDirect3D;
	LPDIRECT3DSURFACE9	pBackBuffer;

	bool bAppWindowDestroyed;

	int nClientToWindowWidthDelta;
	int nClientToWindowHeightDelta;

	HWND g_hWnd;


	//////////////////////////////////////////////////////////////////////////
	
	void ClearScene()
	{
		g_pDirect3DDevice->Clear(
			0,			// no rectangles
			nullptr,	// rectangles
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,		// Clear the render target surface and the depth (z) buffer
			D3DCOLOR_XRGB(0, 0, 0),					// Clear with the black color
			1.f,		// new Z-buffer value
			0			// new stencil buffer value
		);
	}


	bool InitEngine()
	{
		pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (pDirect3D == nullptr)
			return false;

		D3DDISPLAYMODE displayMode;
		if (pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode) != D3D_OK)
			return false;

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof d3dpp);

		d3dpp.BackBufferWidth			= Engine::eScreenWidthInPixels;
		d3dpp.BackBufferHeight			= Engine::eScreenHeightInPixels;
		d3dpp.BackBufferFormat			= displayMode.Format;
		d3dpp.BackBufferCount			= 1;
		d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow				= g_hWnd;
		d3dpp.Windowed					= true;
		d3dpp.EnableAutoDepthStencil	= TRUE;
		d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
		d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

		if ((pDirect3D->CreateDevice(
				D3DADAPTER_DEFAULT,	// use the default video card
				D3DDEVTYPE_HAL,		// use the hardware renderer
				g_hWnd,				// use the main window
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pDirect3DDevice) != D3D_OK)
			|| !g_pDirect3DDevice)
		{
			return false;
		}

		ClearScene();

		g_pDirect3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

		g_pDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		g_pDirect3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		g_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		g_pDirect3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(0, 0, 0));

		if (D3DXCreateSprite(g_pDirect3DDevice, &g_pDirect3DXSprite) != D3D_OK)
		{
			return false;
		}

		if (!Audio::Init())
		{
			return false;
		}

		if (!Game::Init())
		{
			return false;
		}

		D3DMATERIAL9 material;
		ZeroMemory(&material, sizeof material);
		material.Diffuse.r = 0.f;
		material.Diffuse.g = 0.f;
		material.Diffuse.b = 0.f;
		material.Diffuse.a = 1.f;

		material.Ambient.r = 0.f;
		material.Ambient.g = 0.f;
		material.Ambient.b = 0.f;
		material.Ambient.a = 1.f;
		g_pDirect3DDevice->SetMaterial(&material);

		g_pFont = std::make_unique<Font>("Font.bmp", 8, 8, 16);
		if (g_pFont->IsEmpty())
		{
			return false;
		}

		return true;
	}


	void RenderFrame()
	{
		g_pDirect3DDevice->BeginScene();

		ClearScene();

		D3DXMATRIX matrixWorld;
		D3DXMatrixIdentity(&matrixWorld);
		g_pDirect3DDevice->SetTransform(D3DTS_WORLD, &matrixWorld);

		{
			g_pDirect3DXSprite->Begin(D3DXSPRITE_ALPHABLEND);
			Game::Render();
			g_pDirect3DXSprite->End();
		}

		g_pDirect3DDevice->EndScene();
		g_pDirect3DDevice->Present(nullptr, nullptr, NULL, nullptr);
	}


	void UpdateEngine()
	{
		static Stopwatch timedUpdate;

		if (timedUpdate(1000 / Engine::eFPS))
		{
			Game::Update();

			Audio::Update();

			RenderFrame();

			++g_nFrameID;
		}
	}


	void ShutDownEngine()
	{
		Game::ShutDown();

		Audio::ShutDown();

		if (g_pDirect3DXSprite != nullptr)
		{
			g_pDirect3DXSprite->Release();
		}

		if (g_pDirect3DDevice != nullptr)
		{
			g_pDirect3DDevice->Release();
		}

		if (pDirect3D != nullptr)
		{
			pDirect3D->Release();
		}
	}

}	// namespace


// The window event callback function
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		Game::KeyPressed(static_cast<char>(wParam));
		break;

	case WM_SIZE:
	{
		RECT rect;
		GetWindowRect(hWnd, &rect);
		int nWindowWidth = rect.right - rect.left;
		int nWindowHeight = rect.bottom - rect.top;

		int nMinClientWidth = GetSystemMetrics(SM_CXMIN) - nClientToWindowWidthDelta;	// SM_CXMIN - minimum window width
		int nMinClientHeight = nMinClientWidth * Engine::eScreenHeightInCharacters / Engine::eScreenWidthInCharacters;

		bool sizeNeedsCorrection = false;

		int nClientHeight = nWindowHeight - nClientToWindowHeightDelta;
		if (nClientHeight < nMinClientHeight)
		{
			rect.bottom = rect.top + (nMinClientHeight + nClientToWindowHeightDelta);
			sizeNeedsCorrection = true;
		}
		else
		{
			int nClientWidth = nWindowWidth - nClientToWindowWidthDelta;
			int nCorrectedClientHeight = nClientWidth  * Engine::eScreenHeightInCharacters / Engine::eScreenWidthInCharacters;
			if (nClientHeight > nCorrectedClientHeight)
			{
				rect.bottom = rect.top + (nCorrectedClientHeight + nClientToWindowHeightDelta);
				sizeNeedsCorrection = true;
			}
			else
			{
				int nCorrectedClientWidth = nClientHeight * Engine::eScreenWidthInCharacters / Engine::eScreenHeightInCharacters;
				if (nClientWidth > nCorrectedClientWidth)
				{
					rect.right = rect.left + (nCorrectedClientWidth + nClientToWindowWidthDelta);
					sizeNeedsCorrection = true;
				}
			}
		}
		
		if (sizeNeedsCorrection)
		{
			MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
		}

		break;
	}

	case WM_SIZING:
	{
		RECT* pRect = reinterpret_cast<RECT*>(lParam);
		int nNewWindowWidth  = pRect->right  - pRect->left;
		int nNewWindowHeight = pRect->bottom - pRect->top;

		int nNewClientWidth  = nNewWindowWidth  - nClientToWindowWidthDelta;
		int nNewClientHeight = nNewWindowHeight - nClientToWindowHeightDelta;

		int nPossibleCorrectedClientWidth  = nNewClientHeight * Engine::eScreenWidthInCharacters  / Engine::eScreenHeightInCharacters;
		int nPossibleCorrectedClientHeight = nNewClientWidth  * Engine::eScreenHeightInCharacters / Engine::eScreenWidthInCharacters;

		// Keep ZX Spectrum display aspect ratio
		switch (wParam)
		{
		case WMSZ_TOP:
		case WMSZ_BOTTOM:
			pRect->right = pRect->left + (nPossibleCorrectedClientWidth + nClientToWindowWidthDelta);
			break;

		case WMSZ_LEFT:
		case WMSZ_RIGHT:
			pRect->bottom = pRect->top + (nPossibleCorrectedClientHeight + nClientToWindowHeightDelta);
			break;

		case WMSZ_BOTTOMLEFT:
			if (nPossibleCorrectedClientWidth < nNewClientWidth)
			{
				pRect->left = pRect->right - (nPossibleCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->bottom = pRect->top + (nPossibleCorrectedClientHeight + nClientToWindowHeightDelta);
			}
			break;

		case WMSZ_BOTTOMRIGHT:
			if (nPossibleCorrectedClientWidth < nNewClientWidth)
			{
				pRect->right = pRect->left + (nPossibleCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->bottom = pRect->top + (nPossibleCorrectedClientHeight + nClientToWindowHeightDelta);
			}
			break;

		case WMSZ_TOPLEFT:
			if (nPossibleCorrectedClientWidth < nNewClientWidth)
			{
				pRect->left = pRect->right - (nPossibleCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->top = pRect->bottom - (nPossibleCorrectedClientHeight + nClientToWindowHeightDelta);
			}
			break;

		case WMSZ_TOPRIGHT:
			if (nPossibleCorrectedClientWidth < nNewClientWidth)
			{
				pRect->right = pRect->left + (nPossibleCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->top = pRect->bottom - (nPossibleCorrectedClientHeight + nClientToWindowHeightDelta);
			}
			break;
		}

		RenderFrame();
		break;
	}

	case WM_DESTROY:
		bAppWindowDestroyed = true;
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}


bool ApplicationWindowHasFocus()
{
	return (GetFocus() == g_hWnd);
}


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE UNUSED_PARAM(hPrevInstance),
	LPSTR UNUSED_PARAM(lpszCmdLine),
	int nCmdShow)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	const char* szWindowCaption = Game::GetName();

	// Register the class of the main window

	WNDCLASSEX wc;
	wc.cbSize        = sizeof wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WinProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(hInstance, "IDI_JET_STORY");
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = nullptr;
	wc.lpszClassName = szWindowCaption;
	wc.hIconSm       = wc.hIcon;
	
	if (!RegisterClassEx(&wc))
	{
		Engine::LogError("Error registering window class.");
		return 0;
	}

	// Create the main window

	const DWORD dwStyle = WS_OVERLAPPEDWINDOW;		// i.e. not dialog or child
	const DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;		// a border with a raised edge

	int nClientWidth  = Engine::eScreenScale * Engine::eScreenWidthInPixels;
	int nClientHeight = Engine::eScreenScale * Engine::eScreenHeightInPixels;

	RECT windowRect = { 0, 0, nClientWidth, nClientHeight };
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
	int nWindowWidth  = windowRect.right  - windowRect.left;
	int nWindowHeight = windowRect.bottom - windowRect.top;

	nClientToWindowWidthDelta  = nWindowWidth - nClientWidth;
	nClientToWindowHeightDelta = nWindowHeight - nClientHeight;

	HWND hWnd = CreateWindowEx(
		0,						// extended style
		szWindowCaption,		// window class
		szWindowCaption,		// title bar
		dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,	// window style

		// Center the main window
		(GetSystemMetrics(SM_CXSCREEN) - nWindowWidth)  / 2,	// x coordinate
		(GetSystemMetrics(SM_CYSCREEN) - nWindowHeight) / 2,	// y coordinate

		nWindowWidth,			// width of the window
		nWindowHeight,			// height of the window
		NULL,					// parent window
		NULL,					// menu
		hInstance,
		nullptr					// window parameters
	);

	if (!hWnd)
	{
		Engine::LogError("Error creating main window.");
		return 0; 
	}

	g_hWnd = hWnd;

	if (!InitEngine())
	{
		Engine::LogError("Error initializing Engine.");
		ShutDownEngine();
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop
	MSG msg;
	while (!bAppWindowDestroyed)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	
		UpdateEngine();
	}
	
	ShutDownEngine();

	return 1;
}


void DestroyWindow()
{
	DestroyWindow(g_hWnd);
}
