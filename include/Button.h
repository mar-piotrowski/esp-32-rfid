#include <Arduino.h>

class Button {
   private:
	byte pin;
	int currentState;
	int prevState;
	unsigned long lastClickTime;
	unsigned long clickDelay;
	void init();

   public:
	Button(byte pin);
	int readState();
};