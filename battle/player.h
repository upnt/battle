#pragma once

#include <string>
#include "framework.h"

#ifdef UNICODE
using tstring = std::wstring;
#define to_tstring std::to_wstring
#else
using tstring = std::string;
#define to_tstring std::to_string
#endif

class player
{
private:
	RECT textBoxRec = {
		0,		// left
		200,	// top
		280,	// right
		280		// bottom
	};

	RECT textRec = {
		textBoxRec.left	  + 10,
		textBoxRec.top    + 10,
		textBoxRec.right  - 10,
		textBoxRec.bottom - 10
	};

	RECT myHpRec = {
		textBoxRec.left,
		textBoxRec.top  - 30,
		textBoxRec.left + 100,
		textBoxRec.top
	};
    
	RECT enemyHpRec = {
		textBoxRec.right - 100,
		0,
		textBoxRec.right,
		30
	};

	int hp;
	int maxHp;
	int atk;
	tstring texts[3];
	tstring name;

	void appendTexts(tstring text);
	tstring formatTexts();

public:
    player(tstring name, int maxHp, int atk);

	void attack(player& another);
	bool damage(int damage);
	bool isAlive();
	void draw(HDC& hdc, bool isEnemy);
	void drawHp(HDC& hdc, bool isMyHp);

};

