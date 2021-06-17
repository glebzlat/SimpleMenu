

//the SimpleMenu v 2.2.2 library
//is a simple menu on LCD
//by _edKotinsky

//based 
//  https://github.com/PaulStoffregen/EEPROM


//I recommend to use these libraries, cos they are takes up a really little memory
//  https://github.com/GyverLibs/microWire
//  https://github.com/AlexGyver/GyverLibs

//many thanks for this guy
//  https://alexgyver.ru

//feedback
//  https://github.com/edKotinsky
//  mrkotofey@inbox.ru
//  https://vk.com/dudewhodied

#pragma once

#include <Arduino.h>
#include <EEPROM.h>
//#include <microWire.h>
//#include <microLiquidCrystal_I2C.h>
#include "src/config.h"


//in this struct there are the point parameters 
    struct menuStruct {
        const char p_name[LCD_cols];
        const uint8_t configVal;
        const int8_t val1;
        const int8_t val2;
    };


class simpleMenu {
public:

    simpleMenu
    (const menuStruct* const pointCtrls, LiquidCrystal_I2C& objectLCD) :
    _pCtrls(pointCtrls), _LCD(objectLCD) 
    {
        firstLaunch();
    }

public:                     //public functions

    void control(uint8_t button);
    int8_t getPointVal(uint8_t point); 
    
    void warningAttach(int8_t warningCode);
    void warningDetach();

    #ifdef MENU_detachPoints
    void attachPoint(uint8_t pointNum);
    void detachPoint(uint8_t pointNum);
    #endif

    #ifdef MENU_pointType_VIEWONLY
    template <typename T>
    void showValue(uint8_t pointNum, T sVal);
    #endif // MENU_pointType_VIEWONLY

    #ifdef MENU_pointType_FUNCTIONCALLER
    void functionToCall(uint8_t pointNum, void (*funcPtr)());
    #endif // MENU_pointType_FUNCTIONCALLER


public:                     //main display

        //нешаблонная перегрузка
    void mainDisplay();

        //шаблонная функция
    template <typename T, typename... Types>
    void mainDisplay(T firstArg, Types... args);

private:                    //private functions

    void firstLaunch();
    void displaySleep();
    void menuDisplay();
    void pointDisplay();
    void displayClean(uint8_t *button);

    #ifdef MENU_detachPoints
    boolean isPointDetached(uint8_t *curPointNum);
    #endif

    #ifdef MENU_pointType_SETVAL    
    void point_type1(uint8_t* button);
    #endif // MENU_pointType_SETVAL

    #ifdef MENU_pointType_SELECT
    void point_type2(uint8_t* button);
    #endif

private:                    //references

    const menuStruct* const _pCtrls;
    LiquidCrystal_I2C& _LCD;

private:

    uint8_t* _button;

    uint8_t _leafer;
    uint8_t _row;
    int8_t _attention;
    boolean _inPoint;
    boolean _mainDisplay;
    boolean _menuSleep;
    uint8_t _endBytes;

private:                    //variables for menuDisplay function

    #ifdef MENU_detachPoints
    boolean _pointDetached;
    #endif

private:                    //variables for pointDisplay function

    int8_t _pointVal;
    int8_t _minVal, _maxVal;
    boolean _firstEntry;
    uint8_t _point_type;
    uint8_t _EE_addr;
    char _pointName[LCD_cols];
};

    //main func
#include "src/mainFunc.h"

    //point types realisation
#include "src/func.h"

    //interface func
#include "src/interfaceFunc.h"

    //internal func
#include "src/internalFunc.h"