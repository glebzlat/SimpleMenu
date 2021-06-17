//example of use the SimpleMenu v2.2 library 
//if you found a bug, please tell me: 
//https://github.com/edKotinsky

//before you start reading my comments: I call the menu item a point. Don't know, how correct is this.

//before include the library to code, you need to config it

#define MENU_points 6    //number of points
//#define MENU_sleepTime 10000
//#define MENU_cleanTime 1000

//attach point types
#define MENU_pointType_SETVAL 
#define MENU_pointType_SELECT
#define MENU_pointType_FUNCTIONCALLER
#define MENU_pointType_VIEWONLY
//if you do not attach the point type, you will not be able to use it

//and you need to include Wire and Liquid Crystal libraries
//I use the AlexGyver libraries because they are take up little memory
#include <microWire.h>
#include <microLiquidCrystal_I2C.h>

//also you need to include or write some code, 
//which process the buttons or the encoder
//for example I include my button library
#include "myButton.h"

//then you need to include SimpleMenu library
#include <SimpleMenu.h>

//button objects
myButton bt1(6);
myButton bt2(5);
myButton bt3(4);
myButton bt4(3);

//then you need to write this struct
//it contains these point configs:
//name, point type, min val, max val
const menuStruct PROGMEM points [MENU_structNum] = {
  {"MENU v 2.2", 0, 0, 0},            //0 <- zero element of array is not a point
  {"point1", pTYPE_setVal, 0, 10 },   //1
  {"point2", pTYPE_select, 0, 1},     //2
  {"point3", pTYPE_caller, 1, 2},     //3
  {"point4", pTYPE_view,   0, 0},     //4
  {"point5", pTYPE_view,   0, 0},     //5
  {"point6", pTYPE_view,   0, 0},     //6
};

//now, you need to create LCD object and menu object
//using internal SimpleMenu defines
LiquidCrystal_I2C LCD(0x27, LCD_cols, LCD_rows);
//and passing in menu oject points array and LCD object
simpleMenu menu(points, LCD);

//you can use your own functions like menu points
//note: you cant use any types besides void and you cant use functions
//with any passing parameters
void testFunc(){
  LCD.setCursor(0, 0);
  LCD.print("here is the");
  LCD.setCursor(0, 1);
  LCD.print("test function");
}

void setup() {
  LCD.init();
  LCD.backlight(); 
  pinMode(9, OUTPUT);
}

void loop() {
  //you need to create a button variable to pass it to control()
  uint8_t button = 0;
  if (bt4.isPressed())      button = 4; //esc
  else if (bt3.isPressed()) button = 3; //down
  else if (bt2.isPressed()) button = 2; //up
  else if (bt1.isPressed()) button = 1; //enter

  //this is a main function of menu
  //it should be in loop()
  menu.control(button);

  //you can set your own main display parameters
  menu.mainDisplay("SimpleMenu v 2.2", "\r",
                   "display", 1234);

  //in this way you can use your function
  //you need to point out point number and name of your function
  menu.functionToCall(3, testFunc);

  //in this way you can display your variables
  //like this
  menu.showValue(4, 3.14);
  //or like this
  menu.showValue(5, "abc");
  //or like this
  int32_t testValue = -123456;
  menu.showValue(6, testValue);

  //and you can get point values
  //on or off the pin
  digitalWrite(9, menu.getPointVal(3));
  //and you can to change the brigthness, for example
  analogWrite(10, map(menu.getPointVal(1), 0, 10, 0, 1023));
  //connect the LEDs and try it!

  //also you can detach any point - you will not to be able to enter in this point
  //menu.detachPoint(1);
  
  //or attach point - allow to enter
  //menu.attachPoint(2);
}

//that is all, excuse me for my english (because I am study), and have a good luck!
