#pragma once

#include <arduino.h>

//версия 1 из коробки

class myButton {
public:
	myButton(uint8_t pin) {
		pinMode(pin, INPUT_PULLUP);			
		_pin = pin;
	}

	void setDebounce(uint16_t value);
	boolean isPressed();
private:
	uint32_t _debounceValue;
	uint8_t _pin;

	boolean button_flag;
	boolean button_pressed;
	boolean one_return;
	uint32_t last_press;
};

boolean myButton::isPressed() {							//функция обработчик нажатия на кнопку	

	boolean button = !digitalRead(_pin);				//ну-ка, что там у нас с кнопкой?

	if (button && !button_flag							//кажется, ее нажали
		&& millis() - last_press > _debounceValue) {	//а ты на время смотрел?
		button_flag = 1;								//ну вот все по учебнику:
		one_return = 1;									//поднимаем флаг, опускаем флаг...
	}
	if (!button && button_flag) {						//о, что тут у нас, кажется, кнопка БЫЛА нажата, но уже нет
		button_flag = 0;								//значит опускаем флаг, фигли
		last_press = millis();							//и запоминаем новое значение millis()
		one_return = 0;									//во славу антидребезга
	}

	if (one_return) {									//а потом проверяем, было ли нажатие, которое надо вернуть
		one_return = 0;									//если было, то не было. Возвращаем один раз - и баста
		return 1;										//до следующего нажатия
	}
	else return 0;										//ничего у нас здесь с тобой не было.
}

void myButton::setDebounce(uint16_t value) {			//задание значения антидребезга
	_debounceValue = value;								//вот даже названия функций у Гайвера сплагиатил
}														//айяя, как не стыдно
