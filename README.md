![PROJECT_PHOTO](https://github.com/edKotinsky/SimpleMenu/blob/master/proj_img.png)
#���� �� LCD �������
* [��������](#chapter-0)
* [����������](#chapter-1)
* [��� �� ������ ������](#chapter-2)
* [FAQ](#chapter-3)

<a id="chapter-0"></a>

Ru / Eng  will be soon

## ��������
���������� �������� � ��������� � ������� �� ������������� ������ ���� SimpleMenu v 2.2
C������ ������������ ���������� [������ ������](https://alexgyver.ru/microlibs/), � ���� ���� ��� ������ ����� 15% ��� � 7% ���.

���������� ���� �������: ������� ����� -- ���� -- �����. �������, ��� ����������� �����������, �� � ����� ������� ���������� ������� ��������? � ����������� �������� ����� ����������.

���� ����������� ���������� �� 1 �� 4: ENTER, UP, DOWN � ESC, ��� ����� ���� ������ ��� �������. 

� ���� ����������� ������ ���� �������, ������� ����� �������� ��� ��������� ��� ����������: 

1. ����� ���� ��������� �������� **pTYPE_changeVal**. � ���� ������ �������� ����������������/���������������� �� 1 ��� ������� �� UP � DOWN ��������������.
2. ����� ���� ����� �������� **pTYPE_selVal**, � ��� �������� �������� ������� ����� ����� ������������������ ����������
3. ����� ���� ����� ������� **pTYPE_fuctionCall** ��������� ������������ ���������� ���� �������
4. ����� ���� ������������ �������� **pTYPE_viewOnly** - � ��� �������� ������ ������, ����� ������ �������������

���������� ����� ������� ��� ���������� ��������, ��� ��� ������ ������������ ����� ������ � ��� ��� ���������� �� ����� �������� ������ �� �������.

����� ������������ ��� ���������� ���������� �������� ������ � �������� ����.

<a id="chapter-1"></a>
## ����������
**���������� �������� EEPROM** � �������� �����. ���� ����� ������������ EEPROM, ��������� EEMENU_nextFree, ������� ������ ����� ���������� ���������� ����� ����� ����. 

	//������ ������� �������� �������:
	//���, ��� ������, ���, ���� ��������
	const menuStruct PROGMEM points [MENU_structNum] = {
		{"MENU v 2.2", 0, 0, 0},            //0			 ������� ������� ������� �� �����
		{"point1", pTYPE_setVal, 0, 10 },   //1			 ��������� ������� ���������� � 1
		{"point2", pTYPE_select, 0, 1},     //2
		{"point3", pTYPE_caller, 1, 2},     //3
		{"point4", pTYPE_view,   0, 0},     //4
		{"point5", pTYPE_view,   0, 0},     //5
		{"point6", pTYPE_view,   0, 0},     //6
	};

	//�������� ������� ���� � ������������� ��� �������� ������� � �������� LCD ������
	simpleMenu menu(points, LCD_object);

	//������� ������� ����, ������ ��������� � loop � ��������� �������� ������
	menu.control(button_value);

	//�� ������ ������ ���� �������� ��� ������ �� ������� �����
	menu.mainDisplay("SimpleMenu v 2.2", "\r",
					 "display ", 1234);

	//��� �� ������ ������������ ���� �������
	menu.functionToCall(point_number, yourFunction);

	//�������� ��� ������������ � ������ pTYPE_viewOnly
	menu.showValue(point_number, 3.14);
	menu.showValue(point_number, "abc");
	menu.showValue(point_number, -123456);

	//��� �������� �������� ���������� ������
	menu.getPointVal(point_number)
	//�����: �������� ���������� ������ ������ ���� pTYPE_changeVal � pTYPE_selVal

	//��� ����� ��������� ����� - � ���� ������ ����� �����, � �������� �������� ������ �������� ������
	menu.detachPoint(point_number);

	//��� ����� �������� ����������� �����
	menu.attachPoint(point_number);

## ���������
���������� ���� ������������ �����������, ���������� ����� ������������ ����������. 
���������� Wire � LiquidCrystal ����� ���� ���������� �� ����������� SimpleMenu
	
	#define MENU_points 6					//���������� ������� (��������� ������� ���������� � 1)
	#define MENU_sleepTime 10000			//������� ������� ����� �����, ������ ��� �����
	#define MENU_cleanTime 1000				//������ ������� �������

	//����������� ����� �������, ���� �� ����������� - ���� ��� ������ ������������ ����� ������
	#define MENU_pointType_SETVAL			//��������� ��������
	#define MENU_pointType_SELECT			//�����
	#define MENU_pointType_FUNCTIONCALLER	//����� �������
	#define MENU_pointType_VIEWONLY			//������������

	//����� Wire � LiquidCrystal
	#include <Wire.h>
	#include <LiquidCrystal_I2C.h>

	//� � ����� ����
	#include <SimpleMenu.h>

## ����������

**���� ����� ����:**
������� �� ����� ������ ������� ��� �� ���, ��������� ������� �����.

**� ������� ������:**
������� �� ENTER ���������� ����� ����.

**� ������ ����:**
������ ��������� �������� UP � DOWN,
����� ESC,
���� � �����, ���� ����� ����� ENTER,
�������� �������� ��������������� ������� ��������� ������  , � ��� ����� ������.

**� ������:**
����� ESC, ��������� ������� �� ���� ������:

����� ���� setVal:
��������� �������� �������������� �������� UP � DOWN.

����� ���� selectVal:
������������ ���������� �������� �������� � �������������� �������� �� ����� ������ ����� ESC.

� ������ ���� viewOnly
�������� ������ ������.

����� ���� functionCaller
����� ESC, ��������� ������������ ���������������� ��������.

<a id="chapter-2"></a>
## ��� �� ������ ������
���� ����� ���, �������� ����� ��� ���� mrkotofey@inbox.ru

<a id="chapter-2"></a>
## FAQ
��� ������������� ���������� � �������� � �������: https://support.arduino.cc/hc/en-us