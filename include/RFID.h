#include <Arduino.h>

#include <string>

class RFID {
   private:
	void resetKey();

   public:
	void init();
	String detect();
	void read();
	void write();
};