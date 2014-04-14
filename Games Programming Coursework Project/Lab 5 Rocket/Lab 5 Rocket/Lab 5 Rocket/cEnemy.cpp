/*
=================
cEnemy.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cEnemy.h"
/*
=================
- Data constructor initializes the cEnemy to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cEnemy::cEnemy(): cSprite() 			// Default constructor
{
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	/* generate secret number: */
	mScore = (rand() % 10 + 1)*10;
	mDirection = static_cast<eDirection>(rand() % 2);
}
cEnemy::cEnemy(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename): cSprite(sPosition,pd3dDevice,theFilename)  // Constructor
{
	/* initialize random seed: */
	srand ( (unsigned int)time(NULL) );
	/* generate secret number: */
	mScore = (rand() % 10 + 1)*10;
	mDirection = static_cast<eDirection>(rand() % 2);
}
/*
=================
- update the position etc of the sprite.
=================
*/
void cEnemy::update(float deltaTime) 					// update the Enemys position based on the translation
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	tempV2 = cEnemy::getSpritePos2D() + (cEnemy::GetTranslation())*deltaTime;
	tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cEnemy::setSpritePos(tempV3);
	cSprite::Update();
}
/*
=================
- Returns the current direction of the sprite.
=================
*/
eDirection cEnemy::getDirection()       // Rturns the current direction of the sprite
{
	return cEnemy::mDirection;
}
/*
=================
- Sets the current direction for the sprite.
=================
*/
void cEnemy::setDirection(eDirection theDirection)  // Sets the current direction for the sprite.
{
	cEnemy::mDirection = theDirection;
}
