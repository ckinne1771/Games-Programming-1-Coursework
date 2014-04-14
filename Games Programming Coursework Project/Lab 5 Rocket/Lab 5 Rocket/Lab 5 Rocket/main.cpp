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
#include "cEnemy.h"
#include "cXAudio.h"


using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();
	
float rot = 0.0f;

//The transforms and scales used for each sprite
D3DXVECTOR2 rocketTrans = D3DXVECTOR2(350,500);
D3DXVECTOR2 rocketScale = D3DXVECTOR2(0.5f,0.5f);
D3DXVECTOR2 enemyTrans1 = D3DXVECTOR2(350,0);
D3DXVECTOR2 enemyTrans2 = D3DXVECTOR2(350,100);
D3DXVECTOR2 enemyTrans3 = D3DXVECTOR2(350,200);
D3DXVECTOR2 enemyTrans4 = D3DXVECTOR2(350,300);
D3DXVECTOR2 enemyTrans5 = D3DXVECTOR2(350,400);
D3DXVECTOR2 enemyScale = D3DXVECTOR2(0.5f,0.5f);

//delta time
float dt;

//boolean values for movement
bool MoveLeft = false;
bool MoveRight = false;
bool MoveUp  = false;
bool MoveDown = false;
bool moveEnemyLeft1 =true;
bool moveEnemyLeft2 = false;
bool moveEnemyLeft3=true;
bool moveEnemyLeft4 =false;
bool moveEnemyLeft5 =true;
bool moveEnemyRight1 = false;
bool moveEnemyRight2 = true;
bool moveEnemyRight3 = false;
bool moveEnemyRight4 = true;
bool moveEnemyRight5 = false;
LPCSTR rocketTexture;

RECT clientBounds;
cXAudio BackgroundMusic;
cXAudio AlienSoundEffect;




	

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
				//The following code changes the boolean movement values for the player sprite from flase to true according to the key pressed.
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
				//The following code stops the player moving when they lift the appropriate key
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
	wcex.lpszClassName = "Dodge The Aliens"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,"plant.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("Dodge The Aliens",			// the window class to use
							 "Dodge The Aliens",			// the title bar text
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
	
	float enemyMovementValue = 100;
	SetRect(&clientBounds, 0, 0, 800, 600);
	//The variables declared here are all used to help calculate delta time
	float fpsRate = 1.0f/60.0f; //the frame rate
	float numFrames = 0.0f; 
	float timeElapsed = 0.0f;
	__int64 currentTime = 0;
	__int64 previousTime = 0;
	__int64 freq = 0;				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;
	GetClientRect(wndHandle,&clientBounds);
	float timer = timeElapsed;

	//cD3DXTexture rocketTexture(d3dMgr -> getTheD3DDevice(), "Images//rocketSprite.png");
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

	//intial starting positions for enemies
	D3DXVECTOR3 enemyPos1 = D3DXVECTOR3 (100,300,0);
	D3DXVECTOR3 enemyPos2 = D3DXVECTOR3 (250,300,0);
	D3DXVECTOR3 enemyPos3 = D3DXVECTOR3 (400,300,0);
	D3DXVECTOR3 enemyPos4 = D3DXVECTOR3 (500,300,0);
	D3DXVECTOR3 enemyPos5 = D3DXVECTOR3 (700,300,0);

	//Initial creation of the player sprite
	cSprite theRocket;//(rocketPos,d3dMgr->getTheD3DDevice(),"Images\\rocketSprite.png");
	theRocket.setSpritePos(rocketPos);
	theRocket.setTexture(d3dMgr->getTheD3DDevice(), "Images\\topdownfighter.png");
	theRocket.SetTranslation(D3DXVECTOR2(5.0f,0.0f));

	//
	cSprite theEnemy1;
	theEnemy1.setSpritePos(enemyPos1);
	theEnemy1.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Alien.png");
	theEnemy1.SetTranslation(D3DXVECTOR2(5.0f,0.0f));
	
	cSprite theEnemy2;
	theEnemy2.setSpritePos(enemyPos2);
	theEnemy2.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Alien.png");
	theEnemy2.SetTranslation(D3DXVECTOR2(5.0f,0.0f));
	
	cSprite theEnemy3;
	theEnemy3.setSpritePos(enemyPos3);
	theEnemy3.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Alien.png");
	theEnemy3.SetTranslation(D3DXVECTOR2(5.0f,0.0f));
	
	cSprite theEnemy4;
	theEnemy4.setSpritePos(enemyPos4);
	theEnemy4.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Alien.png");
	theEnemy4.SetTranslation(D3DXVECTOR2(5.0f,0.0f));

	cSprite theEnemy5;
	theEnemy5.setSpritePos(enemyPos5);
	theEnemy5.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Alien.png");
	theEnemy5.SetTranslation(D3DXVECTOR2(5.0f,0.0f));

				
	
	//theEnemy.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Alien.png");
	

	//The matrices declared here help with transform calculations
	D3DXMATRIX transformMatrix;
	D3DXMATRIX enemytransformMatrix1;
	D3DXMATRIX enemytransformMatrix2;
	D3DXMATRIX enemytransformMatrix3;
	D3DXMATRIX enemytransformMatrix4;
	D3DXMATRIX enemytransformMatrix5;


	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Create the background surface
	aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\gamebackground.png");

	//A failed attempt at collision detection between the aliens and the player.

	QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);

					if(theEnemy1.collidedWith (theEnemy1.getBoundingRect(), theRocket.getBoundingRect()))
				{
					OutputDebugString("Hit!\n");
					theRocket.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Explosion1.png");
					
				}
				if(theEnemy2.collidedWith(theEnemy2.getBoundingRect(), theRocket.getBoundingRect()))
				{
					OutputDebugString("Hit!\n");
					theRocket.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Explosion1.png");
				}
				if(theEnemy3.collidedWith(theEnemy3.getBoundingRect(), theRocket.getBoundingRect()))
				{
					OutputDebugString("Hit!\n");
					theRocket.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Explosion1.png");
				}
				if(theEnemy4.collidedWith(theEnemy4.getBoundingRect(), theRocket.getBoundingRect()))
				{
					OutputDebugString("Hit!\n");
					theRocket.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Explosion1.png");
				}
				if(theEnemy5.collidedWith(theEnemy5.getBoundingRect(), theRocket.getBoundingRect()))
				{
					OutputDebugString("Hit!\n");
					theRocket.setTexture(d3dMgr->getTheD3DDevice(), "Images\\Explosion1.png");
				}

				//the background music of the game

				BackgroundMusic.playSound(L"Sounds\\BackgroundMusic.wav", true);
				

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
			
			//Whenever a boolean movement value is true, the player sprite will move until he collides with certian boundaries in the world.
			if(MoveRight == true)
			{
				if((rocketTrans.x)>= 770)
				{
					rocketTrans.x+=0;
				}
				else
				{
				rocketTrans.x+=(150.0f*dt);
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
					rocketTrans.x-=(150.0f*dt);
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
					rocketTrans.y-=(150.0f*dt);
				}
			}
			if(MoveDown == true)
			{
				if(rocketTrans.y >=530)
				{
					rocketTrans.y+=0;
				}

				else
				{
				rocketTrans.y+=(150.0f*dt);
				}
			}

			//Whenever an movement boolean for the aliens is true, the aliens will move.
			if(moveEnemyLeft1==true)
				{
				enemyTrans1.x -=(enemyMovementValue*dt);
				}
				if(moveEnemyLeft2==true)
				{
				enemyTrans2.x -=(enemyMovementValue*dt);
				}
				if(moveEnemyLeft3==true)
				{
				enemyTrans3.x -=(enemyMovementValue*dt);
				}
				if(moveEnemyLeft4==true)
				{
				enemyTrans4.x -=(enemyMovementValue*dt);
				}
				if(moveEnemyLeft5==true)
				{
				enemyTrans5.x -=(enemyMovementValue*dt);
				}

				if(moveEnemyRight1==true)
				{
				enemyTrans1.x +=(enemyMovementValue*dt);
				}
				if(moveEnemyRight2==true)
				{
				enemyTrans2.x +=(enemyMovementValue*dt);
				}
				if(moveEnemyRight3==true)
				{
				enemyTrans3.x +=(enemyMovementValue*dt);
				}
				if(moveEnemyRight4==true)
				{
				enemyTrans4.x +=(enemyMovementValue*dt);
				}
				if(moveEnemyRight5==true)
				{
				enemyTrans5.x +=(enemyMovementValue*dt);
				}
			
				//collision detection with the aliens and the boundaries of the level
				if(enemyTrans1.x<(clientBounds.left))
				{
					enemyTrans1.y+=80;
					moveEnemyLeft1=false;
					moveEnemyRight1=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans2.x<(clientBounds.left))
				{
					enemyTrans2.y+=80;
					moveEnemyLeft2=false;
					moveEnemyRight2=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans3.x<(clientBounds.left))
				{
					enemyTrans3.y+=80;
					moveEnemyLeft3=false;
					moveEnemyRight3=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans4.x<(clientBounds.left))
				{
					enemyTrans4.y+=80;
					moveEnemyLeft4=false;
					moveEnemyRight4=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans5.x<(clientBounds.left))
				{
					enemyTrans5.y+=80;
					moveEnemyLeft5=false;
					moveEnemyRight5=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}

				if(enemyTrans1.x>(clientBounds.right -80))
				{
					enemyTrans1.y+=80;
					moveEnemyRight1=false;
					moveEnemyLeft1=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans2.x>(clientBounds.right -80))
				{
					enemyTrans2.y+=80;
					moveEnemyRight2=false;
					moveEnemyLeft2=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans3.x>(clientBounds.right -80))
				{
					enemyTrans3.y+=80;
					moveEnemyRight3=false;
					moveEnemyLeft3=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans4.x>(clientBounds.right -80))
				{
					enemyTrans4.y+=80;
					moveEnemyRight4=false;
					moveEnemyLeft4=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}
				if(enemyTrans5.x>(clientBounds.right -80))
				{
					enemyTrans5.y+=80;
					moveEnemyRight5=false;
					moveEnemyLeft5=true;
					AlienSoundEffect.playSound(L"Sounds\\Alien.wav", false);
				}

				if(enemyTrans1.y>(clientBounds.bottom - 80))
				{
					enemyTrans1.y=0;
				}
				if(enemyTrans2.y>(clientBounds.bottom - 80))
				{
					enemyTrans2.y=0;
				}
				if(enemyTrans3.y>(clientBounds.bottom - 80))
				{
					enemyTrans3.y=0;
				}
				if(enemyTrans4.y>(clientBounds.bottom - 80))
				{
					enemyTrans4.y=0;
				}
				if(enemyTrans5.y>(clientBounds.bottom - 80))
				{
					enemyTrans5.y=0;
					enemyMovementValue+=50;
				}


			


			if (timeElapsed > fpsRate)
			{
									

			//Here is where the sprites are rendered.	

			rocketPos = D3DXVECTOR3(rocketTrans.x,rocketTrans.y,0);
			theRocket.setSpritePos(rocketPos);
			
			theEnemy1.setSpritePos(enemyPos1);
			theEnemy2.setSpritePos(enemyPos2);
			theEnemy3.setSpritePos(enemyPos3);
			theEnemy4.setSpritePos(enemyPos4);
			theEnemy5.setSpritePos(enemyPos5);

			D3DXMatrixTransformation2D(&transformMatrix,NULL,0.0f,&rocketScale,&(theRocket.getSpriteCentre()),rot,&rocketTrans);
			D3DXMatrixTransformation2D(&enemytransformMatrix1,NULL,0.0f,&enemyScale,&(theEnemy1.getSpriteCentre()),rot,&enemyTrans1);
			D3DXMatrixTransformation2D(&enemytransformMatrix2,NULL,0.0f,&enemyScale,&(theEnemy2.getSpriteCentre()),rot,&enemyTrans2);
			D3DXMatrixTransformation2D(&enemytransformMatrix3,NULL,0.0f,&enemyScale,&(theEnemy3.getSpriteCentre()),rot,&enemyTrans3);
			D3DXMatrixTransformation2D(&enemytransformMatrix4,NULL,0.0f,&enemyScale,&(theEnemy4.getSpriteCentre()),rot,&enemyTrans4);
			D3DXMatrixTransformation2D(&enemytransformMatrix5,NULL,0.0f,&enemyScale,&(theEnemy5.getSpriteCentre()),rot,&enemyTrans5);

			d3dMgr->beginRender();
			theBackbuffer = d3dMgr->getTheBackBuffer();
			d3dMgr->updateTheSurface(aSurface, theBackbuffer);
			d3dMgr->releaseTheBackbuffer(theBackbuffer);
			
		

			d3dxSRMgr->beginDraw();
			
				
			d3dxSRMgr->setTheTransform(transformMatrix);
			d3dxSRMgr->drawSprite(theRocket.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			d3dxSRMgr->setTheTransform(enemytransformMatrix1);
			d3dxSRMgr->drawSprite(theEnemy1.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			d3dxSRMgr->setTheTransform(enemytransformMatrix2);
			d3dxSRMgr->drawSprite(theEnemy2.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			d3dxSRMgr->setTheTransform(enemytransformMatrix3);
			d3dxSRMgr->drawSprite(theEnemy3.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			d3dxSRMgr->setTheTransform(enemytransformMatrix4);
			d3dxSRMgr->drawSprite(theEnemy4.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			d3dxSRMgr->setTheTransform(enemytransformMatrix5);
			d3dxSRMgr->drawSprite(theEnemy5.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
			d3dxSRMgr->endDraw();
			d3dMgr->endRender();
			timeElapsed=0.0f;
			}
			previousTime = currentTime;
			}
		}
		
		
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;


	
}


