

//there are configurations for SimpleMenu v2.2.2 in this file 
//тут лежат настройки меню


	//user settings

#ifndef MENU_points
#define MENU_points 1
#endif // !MENU_points

#ifndef MENU_sleepTime
#define MENU_sleepTime 20000
#endif // !LCD_sleepTime

#ifndef MENU_cleanTime
#define MENU_cleanTime 1000
#endif // !MENU_cleanTime

//#define MENU_pointType_SETVAL
//#define MENU_pointType_SELECT
//#define MENU_pointType_VIEWONLY
//#define MENU_pointType_FUNCTIONCALLER
#define MENU_detachPoints

	//macros
#define EEMENU_nextFree EEPROM.read(MENU_points) + ceil(MENU_points / 8) + 1

	//internal settings

#define LCD_cols 16
#define LCD_rows 2
	
#define MENU_structNum MENU_points + 1

#define pTYPE_setVal 1
#define pTYPE_select 11
#define pTYPE_view 0
#define pTYPE_caller 10 

#define B_ENTER 1
#define B_UP    2
#define B_DOWN  3
#define B_ESC   4

#define MENU_cursor "<"
#define MENU_bannedPoint "\xFF"
#define FIRSTLAUNCHKEY 15