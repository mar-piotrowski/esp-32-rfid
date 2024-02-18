#include <WiFi.h>

#include <string>

#include "Arduino.h"

class CppQuery {
   public:
	CppQuery();
	int post(String url, String cardId);
};
