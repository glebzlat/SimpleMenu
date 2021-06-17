

//menuLCD v2.2.1
//there are the internal functions


void simpleMenu::firstLaunch() {
    _mainDisplay = 1;

    uint8_t typeRead = 0;
    uint8_t pointCounter = MENU_points;
    uint8_t configByteCounter = 1;
    uint8_t bitsInByte = 8;
    _endBytes = 1;

    //read the key
    char readKey = EEPROM.read(0);

    //create the variable adresses and write them in the EEPROM
    for (uint8_t i = 1; i < MENU_structNum; i++) {
        typeRead = pgm_read_byte(&(_pCtrls[i].configVal));

        if (typeRead == pTYPE_caller)
            typeRead = 0;

        if (typeRead == pTYPE_select)
            typeRead = 1;
        
        pointCounter += typeRead;
        EEPROM.write(i, pointCounter);
    }

    //if read key is not matches
    if (readKey != FIRSTLAUNCHKEY) {
        //write EEPROM to defolt
        for (uint8_t i = MENU_structNum; i < pointCounter; i++) {
            EEPROM.write(i, 0);
        }

        //and write the key
        EEPROM.write(0, FIRSTLAUNCHKEY);
    }

    //set the attach point bytes in defolt value
    while (MENU_points > bitsInByte) {
        bitsInByte += 8;
        configByteCounter++;
        _endBytes++;
    }

    for (uint8_t i = pointCounter + 1; i < pointCounter + configByteCounter + 1; i++) {
        EEPROM.update(i, 255);
    }
}

#ifdef MENU_detachPoints
boolean simpleMenu::isPointDetached(uint8_t *curPointNum) {
    uint8_t _bitsInByte = 8;
    uint8_t _readByte = EEPROM.read(MENU_points) + 1;
    uint8_t byteCountPoint = *curPointNum - 1;
    uint8_t _prevByte = 8;

    while (byteCountPoint >= _bitsInByte) {
        _bitsInByte += 8;
        if (_bitsInByte % 16 != 0) {
            _prevByte += 8;
        }
        _readByte++;
    }

    uint8_t _Byte = EEPROM.read(_readByte);

    if (byteCountPoint >= _prevByte && byteCountPoint < _bitsInByte)    return bit_is_clear(_Byte, byteCountPoint - _prevByte);
    else    return bit_is_clear(_Byte, byteCountPoint);
}
#endif // #define MENU_detachPoints

void simpleMenu::displaySleep() {

    static uint32_t sleepTimer;

    if (*_button != 0)
        sleepTimer = millis();

    //if the button has been pressed
    //first value is going to zero
    if (*_button != 0 && _menuSleep == 1) {
        *_button = 0;
        _menuSleep = 0;
        _inPoint = 0;
        //_mainDisplay = 1;
    }

    //if the time has come
    //and if there is no attention
    if (_menuSleep == 0 && millis() - sleepTimer >= MENU_sleepTime && _attention == 0)
        _menuSleep = 1;
}

void simpleMenu::displayClean(uint8_t* buttonVal) {
    //cleans display, if the button has been pressed or if the MENU_cleanTime has come
    static uint32_t prev;

    if (*buttonVal != 0) {
        _LCD.clear();
        prev = millis();
    }

    if (millis() - prev > MENU_cleanTime) {
        _LCD.clear();
        prev = millis();
    }
}