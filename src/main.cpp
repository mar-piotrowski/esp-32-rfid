#include <Arduino.h>

#include "Button.h"
#include "CppQuery.h"
#include "Led.h"
#include "RFID.h"
#include "WifiManager.h"

#define SUCCESS_LED_PIN 13
#define REJECT_LED_PIN 12
#define START_JOB_LED_PIN 26
#define END_JOB_LED_PIN 27

#define BUTTON_PIN 25

String url = "http://192.168.1.105:5189/integra/working-times/users";

WifiManager *manager;
RFID *rfid;
CppQuery *cppQuery;

Led successLed(SUCCESS_LED_PIN);
Led rejectLed(REJECT_LED_PIN);
Led startJobLed(START_JOB_LED_PIN);
Led endJobLed(END_JOB_LED_PIN);

Button buttonChangeRequest(BUTTON_PIN);

void setup() {
	Serial.begin(115200);
	manager = new WifiManager();
	manager->init();
	rfid = new RFID();
	rfid->init();
	cppQuery = new CppQuery();
}

void activeSendTypeLed(int buttonState) {
	if (buttonState == LOW) {
		Serial.println("End work request");
		endJobLed.off();
		startJobLed.on();
	} else {
		Serial.println("Start work request");
		startJobLed.off();
		endJobLed.on();
	}
}

void activeSendStatusLed(int responseCode) {
	if (responseCode == 200) {
		successLed.blink(500);
		return;
	}
	rejectLed.blink(500);
}

void sendRequest(int requestType, String cardId) {
	String fullUrl = url;
	if (requestType == 1) {
		fullUrl += "/start-work";
	}
	if (requestType == 0) {
		fullUrl += "/end-work";
	}
	Serial.print("Send to url: ");
	Serial.println(fullUrl);
	int responseCode = cppQuery->post(fullUrl, cardId);
	activeSendStatusLed(responseCode);
}

void loop() {
	int buttonState = buttonChangeRequest.readState();
	activeSendTypeLed(buttonState);
	String cardId = rfid->detect();
	if (cardId != "") {
		Serial.println sendRequest(buttonState, cardId);
		return;
	}
	delay(100);
}
