#include "RFID.h"

#include <MFRC522.h>
#include <SPI.h>

#include <string>

#define SS_PIN 5
#define RST_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

void RFID::init() {
	Serial.println("Tap an RFID/NFC tag on the reader");
	SPI.begin();
	mfrc522.PCD_Init();
	resetKey();
}

String RFID::detect() {
	if (!mfrc522.PICC_IsNewCardPresent()) return "";
	if (!mfrc522.PICC_ReadCardSerial()) return "";
	MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
	// Serial.print("RFID/NFC Tag Type: ");
	// Serial.println(mfrc522.PICC_GetTypeName(piccType));

	String cardUid = "";

	for (int i = 0; i < mfrc522.uid.size; i++) {
		// Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
		// Serial.print(mfrc522.uid.uidByte[i], HEX);
		cardUid.concat(String(mfrc522.uid.uidByte[i], HEX));
		cardUid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
	}

	// Serial.println();

	mfrc522.PICC_HaltA();
	mfrc522.PCD_StopCrypto1();
	return cardUid;
}

void RFID::resetKey() {
	for (byte i = 0; i < 6; i++) {
		key.keyByte[i] = 0xFF;
	}
}

void RFID::read() {}

void RFID::write() {}