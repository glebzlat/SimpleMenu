

//menuLCD v2.2.1
//these functions are user interface


//takes data for main display
void simpleMenu::mainDisplay() {
    _row = 0;
    _LCD.setCursor(0, 0);
}

//takes data for main display
template <typename T, typename... Types>
void simpleMenu::mainDisplay(T firstArg, Types... args) {
    if (_mainDisplay == 1) {

        //note: this function cant get dotted values 
        int8_t strCompare = strcmp((const char*)firstArg, "\r");

        if (strCompare != 0)
            _LCD.print(firstArg);

        if (strCompare == 0) {
            _row++;
            _LCD.setCursor(0, _row);
        }
    }

    simpleMenu::mainDisplay(args...);
}

//returns values
int8_t simpleMenu::getPointVal(uint8_t point) {
    uint8_t addr = EEPROM.read(point);
    return EEPROM.read(addr);
}

void simpleMenu::warningAttach(int8_t warningCode) {
    _attention = warningCode;
}

void simpleMenu::warningDetach() {
    _attention = 0;
}

#ifdef MENU_detachPoints
void simpleMenu::attachPoint(uint8_t pointNum) {
    if (pointNum <= MENU_points && pointNum != 0) {
        pointNum = pointNum - 1;
        uint8_t _bitsInByte = 8;
        uint8_t _prevByte = 8;
        uint8_t _writeByte = EEPROM.read(MENU_points) + 1;
        uint8_t _Byte = 0;

        while (pointNum >= _bitsInByte) {
            _bitsInByte += 8;
            if (_bitsInByte % 16 != 0) {
                _prevByte += 8;
            }
            _writeByte++;
        }

        _Byte = EEPROM.read(_writeByte);

        if (pointNum >= _prevByte && pointNum < _bitsInByte)     
            bitSet(_Byte, pointNum - _prevByte);
        else    
            bitSet(_Byte, pointNum);

        EEPROM.update(_writeByte, _Byte);
    }
}

void simpleMenu::detachPoint(uint8_t pointNum) {
    if (pointNum <= MENU_points && pointNum != 0) {
        pointNum = pointNum - 1;
        uint8_t _bitsInByte = 8;
        uint8_t _prevByte = 8;
        uint8_t _writeByte = EEPROM.read(MENU_points) + 1;
        uint8_t _Byte = 0;

        while (pointNum >= _bitsInByte) {
            _bitsInByte += 8;
            if (_bitsInByte % 16 != 0) {
                _prevByte += 8;
            }
            _writeByte++;
        }

        _Byte = EEPROM.read(_writeByte);

        if (pointNum >= _prevByte && pointNum < _bitsInByte)
            bitClear(_Byte, pointNum - _prevByte);
        else                                    
            bitClear(_Byte, pointNum);

        EEPROM.update(_writeByte, _Byte);
    }
}
#endif

#ifdef MENU_pointType_VIEWONLY
template <typename T>
void simpleMenu::showValue(uint8_t pointNum, T sVal) {

    if (_inPoint == true && _leafer == pointNum && _point_type == pTYPE_view) {
        strcpy_P(_pointName, _pCtrls[_leafer].p_name);

        _LCD.setCursor(0, 0);
        _LCD.print(_pointName);
        
        _LCD.setCursor(0, 1);
        _LCD.print(sVal);
    }
}
#endif // MENU_pointType_VIEWONLY

#ifdef MENU_pointType_FUNCTIONCALLER
//takes function for call
void simpleMenu::functionToCall(uint8_t pointNum, void (*handler)()) {
    uint8_t _point_type = pgm_read_byte (&(_pCtrls[pointNum].configVal));

    if (_inPoint == true && _leafer == pointNum && _point_type == pTYPE_caller) 
        handler();
}
#endif // MENU_pointType_FUNCTIONCALLER
