

//menuLCD v2.2.1
//there are the main functions


//крутится в loop и принимает значение кнопки
void simpleMenu::control(uint8_t button) {

    //variable for correct work displayClean()
    uint8_t buttonIsPressed = button;

    _button = &button;

    //screen sleeps if menuSleep == 1
    simpleMenu::displaySleep();

    //screen sleep
    if (_menuSleep == 0) _LCD.backlight();
    else {
        _LCD.noBacklight();
        _mainDisplay = 1;
    }

    //if displays main screen and the button has been pressed and screen does not sleep
    if (_mainDisplay == 1 && button == B_ENTER && _menuSleep == 0) {
        _mainDisplay = 0;
        button = 0;
        _leafer = 1;

        #ifdef MENU_detachPoints
        _pointDetached = isPointDetached(&_leafer);
        #endif
        //_leafer = 1;
    }

    //_mainDisplay == 0 calls menu
    simpleMenu::menuDisplay();
    //_inPoint == 1 calls point
    simpleMenu::pointDisplay();

    //screen cleaner
    simpleMenu::displayClean(&buttonIsPressed);
    buttonIsPressed = 0;
}

void simpleMenu::menuDisplay() {
    if (_mainDisplay == 0) {

        char nameBuf1[LCD_cols];
        char nameBuf2[LCD_cols];

        strcpy_P(nameBuf1, _pCtrls[0].p_name);
        strcpy_P(nameBuf2, _pCtrls[_leafer].p_name);

        //to leaf the menu items
        if (_inPoint == 0) { //if the menu
          //leaf down
            if (*_button == B_DOWN && _leafer < MENU_points) {
                _leafer++;

                #ifdef MENU_detachPoints 
                _pointDetached = isPointDetached(&_leafer);
                #endif
            }

            //leaf up
            if (*_button == B_UP && _leafer > 1) {
                _leafer--;

                #ifdef MENU_detachPoints 
                _pointDetached = isPointDetached(&_leafer);
                #endif
            }
        }

        //if inPoint is 0, then displays the menu
        if (_inPoint == 0) {
            _LCD.setCursor(0, 0);
            _LCD.print(nameBuf1);
            _LCD.setCursor(0, 1);
            _LCD.print(nameBuf2);

            #ifdef MENU_detachPoints
            if (_pointDetached == 1) {
                _LCD.setCursor(15, 1);
                _LCD.print(MENU_bannedPoint);
            }
            #endif
        }

        //if displays the menu and the enter button has been pressed
        if (_inPoint == 0) {
            if (*_button == B_ENTER) {
                #ifdef MENU_detachPoints
                if (_pointDetached == 0)
                #endif
                    _inPoint = 1;
            }

            if (*_button == B_ESC) {
                _mainDisplay = 1;
            }
        }
    }
}

//отвечает за вывод пункта
void simpleMenu::pointDisplay() {
    if (_inPoint == 1 && _menuSleep == 0) {

        //at the entrance read from EEPROM and zeroing button value
        if (_firstEntry == 0) {

            _point_type = pgm_read_byte(&(_pCtrls[_leafer].configVal));
            _EE_addr = EEPROM.read(_leafer);

            //read point value
            EEPROM.get(_EE_addr, _pointVal);

            //read point name, min and max value from PROGMEM
            strcpy_P(_pointName, _pCtrls[_leafer].p_name);
            _minVal = pgm_read_byte(&(_pCtrls[_leafer].val1));
            _maxVal = pgm_read_byte(&(_pCtrls[_leafer].val2));

            _firstEntry = 1;
            *_button = 0;
        }

        //change the point type
        switch (_point_type) {

        #ifdef MENU_pointType_SETVAL
        case pTYPE_setVal:
            point_type1(_button);
            break;
        #endif // MENU_pointType_SETVAL

        #ifdef MENU_pointType_SELECT
        case pTYPE_select:
            point_type2(_button);
            break;
        #endif // MENU_pointType_SELECT
        }

        //exit from point
        if (*_button == B_ESC) 
                EEPROM.put(_EE_addr, _pointVal);

        if (*_button == B_ESC || _menuSleep == 1) {
            _pointVal = 0;
            _inPoint = 0;
            _firstEntry = 0;
            *_button = 0;
        }
    }
}



