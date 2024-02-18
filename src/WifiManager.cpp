#include "WifiManager.h"

#include <WiFi.h>

#include <string>

WifiManager::WifiManager() { Serial.println("Initialize Wifi Manager"); }

void WifiManager::init() {
	Serial.println("Connecting to the WIFI");
	WiFi.mode(WIFI_STA);
	WiFi.begin("PeepoG", "A42NbbP522");
	if (WiFi.waitForConnectResult() != WL_CONNECTED)
		Serial.printf("Connection Failed\n");
	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());
}

WifiManager::~WifiManager() { Serial.println("Clean Wifi Manager"); }