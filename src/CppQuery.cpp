#include "CppQuery.h"

#include <HTTPClient.h>
#include <WiFi.h>

#include <string>

CppQuery::CppQuery() {}

int CppQuery::post(String url, String cardId) {
	HTTPClient httpClient;
	httpClient.begin(url);
	httpClient.addHeader("Content-Type", "application/json");
	String payload = "{\"cardNumber\": \" " + cardId + " \"}";
	int responseCode = httpClient.POST(payload);
	Serial.print("Response code: ");
	Serial.println(responseCode);
	return responseCode;
};