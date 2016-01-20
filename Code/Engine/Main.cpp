#include "../Common/Engine.h"
#include "../Common/Game.h"
#include "../Common/Audio.h"
#include <cstdlib>
#include <ctime>
#include "Font.h"
#include "Sound.h"
#include "Stopwatch.h"


LPDIRECT3DDEVICE9	g_pD3DDevice;
LPD3DXSPRITE		g_pSprites;

Font* g_pFont;

long int g_nFrameID = 0;


namespace
{
	LPDIRECT3D9			pD3D;
	LPDIRECT3DSURFACE9	pBackBuffer;

	bool bAppWindowDestroyed;

	int nClientToWindowWidthDelta;
	int nClientToWindowHeightDelta;

	HWND g_hWnd;


	//////////////////////////////////////////////////////////////////////////
	
	void ClearScene()
	{
		g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.f, 0);
	}


	bool InitEngine()
	{
		pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (!pD3D)
			return false;

		D3DDISPLAYMODE displayMode;
		if (pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode) != D3D_OK)
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

		if ((pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			g_hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice) != D3D_OK) || !g_pD3DDevice)
		{
			return false;
		}

		ClearScene();

		g_pD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE,	TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE,	D3DFILL_SOLID);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING,	TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_AMBIENT,	D3DCOLOR_XRGB(0, 0, 0));

		if (D3DXCreateSprite(g_pD3DDevice, &g_pSprites) != D3D_OK)
			return false;

		if (!Audio::Init())
			return false;

		Game::Init();

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
		g_pD3DDevice->SetMaterial(&material);

		g_pFont = new Font("Font.bmp", 8, 8, 16);
		if (!g_pFont->IsOK())
			return false;

		return true;
	}


	void RenderFrame()
	{
		g_pD3DDevice->BeginScene();

		ClearScene();

		D3DXMATRIX matrixWorld;
		D3DXMatrixIdentity(&matrixWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matrixWorld);

		{
			g_pSprites->Begin(D3DXSPRITE_ALPHABLEND);
			Game::Render();
			g_pSprites->End();
		}

		g_pD3DDevice->EndScene();
		g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
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
		delete g_pFont;

		Game::ShutDown();

		Audio::ShutDown();

		g_pSprites->Release();
		g_pD3DDevice->Release();
		pD3D->Release();
	}

}	// namespace


LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		Game::KeyPressed(char(wParam));
		break;

	case WM_SIZING:
	{
		RECT* pRect = reinterpret_cast<RECT*>(lParam);
		int nNewWindowWidth  = pRect->right  - pRect->left;
		int nNewWindowHeight = pRect->bottom - pRect->top;

		int nNewClientWidth  = nNewWindowWidth  - nClientToWindowWidthDelta;
		int nNewClientHeight = nNewWindowHeight - nClientToWindowHeightDelta;

		int nNewCorrectedClientWidth  = nNewClientHeight * Engine::eScreenWidthInChars  / Engine::eScreenHeightInChars;
		int nNewCorrectedClientHeight = nNewClientWidth  * Engine::eScreenHeightInChars / Engine::eScreenWidthInChars;

		// Keep ZX Spectrum display aspect ratio
		switch (wParam)
		{
		case WMSZ_TOP:
		case WMSZ_BOTTOM:
			pRect->right = pRect->left + (nNewCorrectedClientWidth + nClientToWindowWidthDelta);
			break;

		case WMSZ_LEFT:
		case WMSZ_RIGHT:
			pRect->bottom = pRect->top + (nNewCorrectedClientHeight + nClientToWindowHeightDelta);
			break;

		case WMSZ_BOTTOMLEFT:
			if (nNewCorrectedClientWidth < nNewClientWidth)
			{
				pRect->left = pRect->right - (nNewCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->bottom = pRect->top + (nNewCorrectedClientHeight + nClientToWindowHeightDelta);
			}
			break;

		case WMSZ_BOTTOMRIGHT:
			if (nNewCorrectedClientWidth < nNewClientWidth)
			{
				pRect->right = pRect->left + (nNewCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->bottom = pRect->top + (nNewCorrectedClientHeight + nClientToWindowHeightDelta);
			}
			break;

		case WMSZ_TOPLEFT:
			if (nNewCorrectedClientWidth < nNewClientWidth)
			{
				pRect->left = pRect->right - (nNewCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->top = pRect->bottom - (nNewCorrectedClientHeight - nClientToWindowHeightDelta);
			}
			break;

		case WMSZ_TOPRIGHT:
			if (nNewCorrectedClientWidth < nNewClientWidth)
			{
				pRect->right = pRect->left + (nNewCorrectedClientWidth + nClientToWindowWidthDelta);
			}
			else
			{
				pRect->top = pRect->bottom - (nNewCorrectedClientHeight + nClientToWindowHeightDelta);
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


bool HasFocus()
{
	return (GetFocus() == g_hWnd);
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(static_cast<unsigned int>(time(NULL)));

	const char* szWindowCaption = Game::GetName();

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
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szWindowCaption;
	wc.hIconSm       = LoadIcon(hInstance, "IDI_JET_STORY");
	
	if (!RegisterClassEx(&wc))
	{
		Engine::LogError("Error registering window class.");
		return 0;
	}

	const DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	const DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	int nClientWidth  = Engine::eScreenScale * Engine::eScreenWidthInPixels;
	int nClientHeight = Engine::eScreenScale * Engine::eScreenHeightInPixels;

	RECT windowRect = { 0, 0, nClientWidth, nClientHeight };
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
	int nWindowWidth  = windowRect.right  - windowRect.left;
	int nWindowHeight = windowRect.bottom - windowRect.top;

	nClientToWindowWidthDelta  = nWindowWidth - nClientWidth;
	nClientToWindowHeightDelta = nWindowHeight - nClientHeight;

	HWND hWnd = CreateWindowEx(
		0,
		szWindowCaption,		// window class
		szWindowCaption,		// title bar
		dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,	// window style
		(GetSystemMetrics(SM_CXSCREEN) - nWindowWidth)  / 2,	// x coordinate
		(GetSystemMetrics(SM_CYSCREEN) - nWindowHeight) / 2,	// y coordinate
		nWindowWidth,			// width of the window
		nWindowHeight,			// height of the window
		NULL,					// parent window
		NULL,					// menu
		hInstance,
		NULL					// window parameters
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
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

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


void ExitEngine()
{
	DestroyWindow(g_hWnd);
}
