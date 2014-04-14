/*
=================
cSprite.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CSPRITE_H
#define _CSPRITE_H
#include "cD3DXTexture.h"

class cSprite
{
private:
	D3DXVECTOR3 spritePos;
	D3DXVECTOR2 spritePos2D;
	D3DXVECTOR2 spriteTranslation;
	cD3DXTexture spriteTexture;
	D3DXVECTOR2 spriteCentre;
public:
	cSprite();			// Default constructor
	cSprite(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	~cSprite();			// Destructor
	D3DXVECTOR3 getSpritePos();  // Return the sprites current position
	void setSpritePos(D3DXVECTOR3 sPosition); // set the position of the sprite
	D3DXVECTOR2 getSpritePos2D();  // Return the sprites current 2D position
	void setSpritePos2D(D3DXVECTOR3 sPosition); // set the 2D position of the sprite
	D3DXVECTOR2 GetTranslation();		// Return the sprites translation
	void SetTranslation (D3DXVECTOR2 Translation);		// set the translation for the sprite
	LPDIRECT3DTEXTURE9 getTexture();  // Return the sprites current image
	void setTexture(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename);  // set the image of the sprite
	void setSpriteCentre();      // set the centre of the sprite for rotation
	D3DXVECTOR2 getSpriteCentre();      // return the centre of the sprite for rotation
};
#endif