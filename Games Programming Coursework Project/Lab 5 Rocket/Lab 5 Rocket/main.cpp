/*
=================
main.cpp
Main entry point for the Card application
=================
*/

#include "GameConstants.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cSprite.h"

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();
	
float rot = 0.0f;
D3DXVECTOR2 rocketTrans = D3DXVECTOR2(350,400);
D3DXVECTOR2 rocketScale = D3DXVECTOR2(0.5f,0.5f);
float dt;
bool MoveLeft = false;
bool MoveRight = false;
bool MoveUp  = false;
bool MoveDown = false;


	

/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue
	switch (message)
	{
		case WM_KEYDOWN:
			{
				if (wParam =='A')
				{
					MoveLeft = true;
					return 0;
					//rocketTrans.x -=(5.0f);
					//return 0;
				}
				if (wParam =='S')
				{
					MoveDown = true;
					//rocketTrans.y +=(5.0f);
					return 0;
				}
				if (wParam =='D')
				{
					MoveRight = true;
					//rocketTrans.x +=(5.0f);
					return 0;
				}
				if (wParam =='W')
				{
					MoveUp = true;
					//rocketTrans.y -=(5.0f);
					return 0;
				}

					return 0;
				}
		case WM_KEYUP:
			{
				if(wParam=='A')
				{
					MoveLeft  = false;
					return 0;
				}
				if(wParam=='S')
				{
					MoveDown = false;
					return 0;
				}
				if(wParam=='D')
				{
					MoveRight = false;
					return 0;
				}
				if(wParam=='W')
				{
					MoveUp  = false;
					return 0;
				}
				return 0;
			}

			
		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
				 return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,"plant.ico"); // icon to associate with the application
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "SpaceRockets"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,"plant.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("SpaceRockets",			// the window class to use
							 "Space Rockets",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							800, // the pixel width of the window
							600, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{

	float fpsRate = 1.0f/60.0f;
	float numFrames = 0.0f;
	float timeElapsed = 0.0f;
	__int64 currentTime = 0;
	__int64 previousTime = 0;
	__int64 freq = 0;				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;

	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;

	LPDIRECT3DSURFACE9 aSurface;				// the Direct3D surface
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer
	
	// Initial starting position for Rocket
	D3DXVECTOR3 rocketPos = D3DXVECTOR3(300,300,0);
	cSprite theRocket(rocketPos,d3dMgr->getTheD3DDevice(),"Images\\rocketSprite.png");

	theRocket.SetTranslation(D3DXVECTOR2(5.0f,0.0f));

	//IMPORTANT MATRIX HERE!!!!!!!!!!!!!!!!
	D3DXMATRIX transformMatrix;

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Create the background surface
	aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\GameBackground.png");

	QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);
	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
			dt = (currentTime - previousTime)*sPC;

			// Accumulate how much time has passed.
			timeElapsed += dt;
			// Game code goes here
			
			if(MoveRight == true)
			{
				if(rocketTrans.x + theRocket.getSpriteCentre().x >= 830)
				{
					rocketTrans.x+=0;
				}
				else
				{
				rocketTrans.x+=(100.0f*dt);
				}
			}

			if(MoveLeft == true)
			{
				if(rocketTrans.x <= 0)
				{
					rocketTrans.x-=0;
				}

				else
				{
					rocketTrans.x-=(100.0f*dt);
				}
			}
			if(MoveUp == true)
			{
				if(rocketTrans.y <= 0)
				{
					rocketTrans.y-=0;
				}
				else
				{
					rocketTrans.y-=(100.0f*dt);
				}
			}
			if(MoveDown == true)
			{
				if(rocketTrans.y + theRocket.getSpriteCentre().y >= 570)
				{
					rocketTrans.y+=0;
				}

				else
				{
				rocketTrans.y+=(100.0f*dt);
				}
			}
			
			if (timeElapsed > fpsRate)
			{
			rocketPos = D3DXVECTOR3(rocketTrans.x,rocketTrans.y,0);
			theRocket.setSpritePos(rocketPos);

			D3DXMatrixTransformation2D(&transformMatrix,NULL,0.0f,&rocketScale,&(theRocket.getSpriteCentre()),rot,&rocketTrans);


			
			d3dMgr->beginRender();
			theBackbuffer = d3dMgr->getTheBackBuffer();
			d3dMgr->updateTheSurface(aSurface, theBackbuffer);
			d3dMgr->releaseTheBackbuffer(theBackbuffer);
			

			d3dxSRMgr->beginDraw();
			d3dxSRMgr ->setTheTransform(transformMatrix);
			d3dxSRMgr->drawSprite(theRocket.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			d3dxSRMgr->endDraw();
			d3dMgr->endRender();
			}
			previousTime = currentTime;
			}
		}
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;


	
}


