#pragma once

enum EN_DIRECTION
{
	DRT_LEFT = 211,
	DRT_UP,
	DRT_RIGHT,
	DRT_DOWN
};

enum EN_SHAPE
{
	SHAPE_BEGIN = -1,
	SHAPE_I,//I
	SHAPE_L,	//L
	SHAPE_O,	//��
	SHAPE_K,	//|-

	SHAPE_Z,	//  |_
				//    |
	SHAPE_END
};

enum DIAMOND_COLOR{DIAMOND_COLOR_RED, DIAMOND_COLOR_GREE, DIAMOND_COLOR_BLUE, DIAMOND_COLOR_BLACK, DIAMOND_COLOR_YELLOW};

extern COLORREF g_aDiamondColor[7];

//enum MAIN_SIZE{ MAIN_WIDTH = 600, MAIN_HEIGHT = 600 };
enum MAIN_SIZE{ MAIN_WIDTH = 260, MAIN_HEIGHT = 400 };

enum GAME_ZONE{ GAME_ZONE_LEFT = 60, GAME_ZONE_TOP = 100, GAME_ZONE_RIGHT = MAIN_WIDTH - 60, GAME_ZONE_BOTTM = MAIN_HEIGHT - 100 ,
				GAME_ZONE_WIDTH = GAME_ZONE_RIGHT - GAME_ZONE_LEFT, GAME_ZONE_HEIGHT = GAME_ZONE_BOTTM - GAME_ZONE_TOP};


enum MENU_ID{ MENU_START = 1001, MENU_PAUSE, MENU_EXIT, MENU_LEVEL1, MENU_LEVEL2, MENU_LEVEL3, MENU_SPEED };


const int PER_DIAMOND_LENTH = 10;

enum DIAMOND_ID{DIAMOND_ID_1 = 5000,DIAMOND_ID_2, DIAMOND_ID_3, DIAMOND_ID_4, DIAMOND_ID_A, DIAMOND_ID_B, DIAMOND_ID_C,
				DIAMOND_ID_D};

const int TIMER_ID = 2000;

enum TURN_DIRECTION{TURN_DIRECTION_RIGHT = 1, TURN_DIRECTION_LEFT = -1};

class Define
{
public:
	Define(void);
	~Define(void);

};
