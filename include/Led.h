#include <Arduino.h>

class Led {
   private:
	byte pin;
	void init();

   public:
	Led(byte pin);
	void on();
	void off();
	void blink(int delayValue);
};