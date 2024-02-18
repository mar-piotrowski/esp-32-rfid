#include "Button.h"

#include <Arduino.h>

Button::Button(byte pin) {
	this->pin = pin;
	this->prevState = LOW;
	this->currentState = LOW;
	this->lastClickTime = 0;
	this->clickDelay = 50;
	init();
}

int Button::readState() {
	int state = digitalRead(this->pin);
	if (state == this->prevState) {
		return this->currentState;
	}
	if (state == HIGH) {
		this->lastClickTime = millis();
	}
	if ((millis() - this->lastClickTime) >= this->clickDelay) {
		this->currentState = !this->currentState;
	}
	this->prevState = state;
	return this->currentState;
}

void Button::init() { pinMode(this->pin, INPUT); }