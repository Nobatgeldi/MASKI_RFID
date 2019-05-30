/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9     // Configurable, see typical pin layout above
#define SS_PIN    10    // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
byte block0_buffer[] = { 0x1E, 0x23, 0x02, 0x7d, 0x42, 0x08, 0x04, 0x00, 0x01, 0x5A, 0x25, 0xCE, 0x3E, 0xF3, 0x25, 0x1D };

void setup() {
	Serial.begin(9600);  // Initialize serial communications with the PC
	while (!Serial);     // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();         // Init SPI bus
	mfrc522.PCD_Init();  // Init MFRC522 card
	Serial.println(F("Warning: this code change Tag Sector 0 Block 0, use with care!"));
}

void loop() 
{
	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
	if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
		delay(50);
		return;
	}
	// Dump UID
	Serial.print(F("Card UID:"));
	for (byte i = 0; i < mfrc522.uid.size; i++) {
		Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
		Serial.print(mfrc522.uid.uidByte[i], HEX);
	}
	Serial.println();

	if (MIFARE_UnbrickUidSector(true, block0_buffer)) 
	{
		Serial.println(F("Sector 0 Block 0 changed changed."));
	}

	delay(1000);
}

bool MIFARE_UnbrickUidSector(bool logErrors, byte block0_buffer[]) 
{
	mfrc522.MIFARE_OpenUidBackdoor(logErrors);

	// Write modified block 0 back to card
	MFRC522::StatusCode status = mfrc522.MIFARE_Write((byte)0, block0_buffer, (byte)16);
	if (status != mfrc522.STATUS_OK) {
		if (logErrors) {
			Serial.print(F("MIFARE_Write() failed: "));
			Serial.println(mfrc522.GetStatusCodeName(status));
		}
		return false;
	}
	return true;
}
