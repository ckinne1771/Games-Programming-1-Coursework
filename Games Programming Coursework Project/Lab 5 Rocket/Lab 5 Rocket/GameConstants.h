#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

// Include the Windows header file that’s needed for all Windows applications
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// This header file contains all the constants & enumarated types for the game
enum eSuit {CLUBS,DIAMONDS,HEARTS,SPADES};
enum eType {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum eDirection {UP, DOWN, LEFT, RIGHT};
const std::string strType[14] = {"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
const std::string strSuit[4] = {"C","D","H","S"};

struct CARD{
	eSuit cSuit;       // Suit card belongs to.
	eType cType;       // Type of card e.g. face card.
	short cValue;      // Numeric value of the playing card
	bool cIsFaceUp;
	std::string cFilename;
};
#endif