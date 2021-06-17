

//menuLCD v2.2
//there are the point types functions


#ifdef MENU_pointType_SETVAL
void simpleMenu::point_type1(uint8_t* button) {

     if (*button == B_DOWN)
         _pointVal--;

     if (*button == B_UP)
         _pointVal++;

    _LCD.setCursor(0, 0);
    _LCD.print(_pointName);

    _LCD.setCursor(0, 1);
    _LCD.print(_pointVal);

    _pointVal = constrain(_pointVal, _minVal, _maxVal);
}
#endif // MENU_pointType_SETVAL

#ifdef MENU_pointType_SELECT
void simpleMenu::point_type2(uint8_t* button) {

    if (_pointVal == 0) {
        _LCD.setCursor(3, 1);
        _LCD.print(MENU_cursor);

        if (*button == B_ENTER || *button == B_DOWN || *button == B_UP)
            _pointVal = 1;
    }
    else {
        _LCD.setCursor(8, 1);
        _LCD.print(MENU_cursor);

        if (*button == B_ENTER || *button == B_DOWN || *button == B_UP)
            _pointVal = 0;
    }

    _LCD.setCursor(0, 0);
    _LCD.print(_pointName);

    _LCD.setCursor(0, 1);
    _LCD.print(_minVal);

    _LCD.setCursor(5, 1);
    _LCD.print(_maxVal);
}
#endif // MENU_pointType_SELECT
