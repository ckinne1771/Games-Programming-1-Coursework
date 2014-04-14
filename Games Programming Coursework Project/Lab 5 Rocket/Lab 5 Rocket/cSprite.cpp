/*
=================
cSprite.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cSprite.h"
/*
=================
- Data constructor initializes the cSprite to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cSprite::cSprite() 			// Default constructor
{

	cSprite::spritePos.x = 0.0f;
	cSprite::spritePos.y = 0.0f;
	cSprite::spritePos.z = 0.0f;
	//cSprite::setTexture(new cD3DXTexture());
}
cSprite::cSprite(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename) // Constructor
{
	D3DXVECTOR2 translation = D3DXVECTOR2(0,0);
	cSprite::setSpritePos(sPosition);
	cSprite::setSpritePos2D(sPosition);
	cSprite::setTexture(pd3dDevice, theFilename);
	cSprite::spriteTexture.setTextureInfo(theFilename);
	cSprite::SetTranslation(translation);
	cSprite::setSpriteCentre();
}
/*
=================
- Destructor 
=================
*/
cSprite::~cSprite()			// Destructor
{
}
/*
=================
- Return the sprites current position.
=================
*/

D3DXVECTOR3 cSprite::getSpritePos()  // Return the sprites current position
{
	return cSprite::spritePos;
}
/*
=================
- set the position of the sprite.
=================
*/

void cSprite::setSpritePos(D3DXVECTOR3 sPosition)  // set the position of the sprite
{
	cSprite::spritePos = sPosition;
}
/*
=================
- Return the sprites current 2D position.
=================
*/
D3DXVECTOR2 cSprite::getSpritePos2D()   // Return the sprites current 2D position
{
	return cSprite::spritePos2D;
}

/*
=================
- set the 2D position of the sprite.
=================
*/
void cSprite::setSpritePos2D(D3DXVECTOR3 sPosition)  // set the 2D position of the sprite
{
	cSprite::spritePos2D.x = sPosition.x;
	cSprite::spritePos2D.y = sPosition.y;
}

/*
=================
- Return the sprites translation.
=================
*/

D3DXVECTOR2 cSprite::GetTranslation() 		// Return the sprites translation
{
	return cSprite::spriteTranslation;
}

/*
=================
- set the position of the sprite.
=================
*/
void cSprite::SetTranslation (D3DXVECTOR2 Translation) 		// set the translation for the sprite
{
	cSprite::spriteTranslation = Translation;
}

/*
=================
- Return the sprites current image.
=================
*/

LPDIRECT3DTEXTURE9 cSprite::getTexture()  // Return the sprites current image
{
	return cSprite::spriteTexture.getTexture();
}
/*
=================
- set the image of the sprite.
=================
*/

void cSprite::setTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename)  // set the image of the sprite
{
	cSprite::spriteTexture.createTexture(pd3dDevice, theFilename);
}
/*
=================
- set the image of the sprite.
=================
*/

void cSprite::setSpriteCentre()      // set the centre of the sprite for rotation
{
	D3DXIMAGE_INFO aTextureInfo;
	aTextureInfo = cSprite::spriteTexture.getTextureInfo();
	cSprite::spriteCentre.x = (float)aTextureInfo.Height/2;
	cSprite::spriteCentre.y = (float)aTextureInfo.Width/2;
}
/*
=================
- set the image of the sprite.
=================
*/
D3DXVECTOR2 cSprite::getSpriteCentre()      // return the centre of the sprite for rotation
{
	return cSprite::spriteCentre;
}
