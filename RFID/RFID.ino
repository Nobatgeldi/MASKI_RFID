#include <SPI.h>
#include <MFRC522.h>
#include"RFID_Utilities.h"

#define RST_PIN    9   // 
#define SS_PIN    10    //

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
RFID_Utilities rc522Utilities;
MFRC522::MIFARE_Key keyA, keyB;

void setup() {
	Serial.begin(9600);   // Initialize serial communications with the PC
	while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	// Prepare the key (used both as key A and as key B)
	// using FFFFFFFFFFFFh which is the default at chip delivery from the factory
	for (byte i = 0; i < 6; i++) {
		keyA.keyByte[i] = 0xFF;
		keyB.keyByte[i] = 0xFF;
	}
	SPI.begin();      // Init SPI bus
	mfrc522.PCD_Init();   // Init MFRC522
	rc522Utilities.setMFRC(&mfrc522);
	rc522Utilities.showReaderDetails(); // Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("MASKI kart booooommmm!!!!!!!"));
}

void loop() 
{
	if (rc522Utilities.detectNewCard()) 
	{
		/*rc522Utilities.formatToNDEF(&rc522Utilities.NFCDefaultKeyB, &rc522Utilities.NFCDefaultKeyB);*/

		// sector 0 block 0
		byte dataBlock0[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
   
		// sector 0 block 1
		byte dataBlock1[] = { 0x00, 0x00, 0x00, 0x42, 0x53, 0x61, 0x00, 0x59, 0x13, 0x81, 0x00, 0x03, 0x00, 0x00, 0x96, 0x01 };
		
		// sector 0 block 2
		//					   00	 03	   93	 00    03	 00	   00	 03    00    14    00    F0    00    00    00    91
		byte dataBlock2[] = { 0x00, 0x09, 0x93, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x14, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x91 };
		
		/*//sector 1 block 4 
		byte dataBlock4[] = { 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0xFF, 0x1E, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00 };
		
		// sector 1 block 5 
		byte dataBlock5[] = { 0x00, 0x99, 0x00, 0x00, 0x99, 0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		
		// sector 1 block 6 
		byte dataBlock6[] = { 0x00, 0x0C, 0x01, 0x01, 0x00, 0x00, 0x0C, 0x01, 0x01, 0x00, 0x00, 0x0C, 0x01, 0x01, 0x00, 0xD9 };
		
		// sector 2 block 8
		//                    00    00    00    00    00    00    02    7D    09    17    08    0A    11    44    06    21 
		byte dataBlock8[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7D, 0x09, 0x17, 0x08, 0x0A, 0x11, 0x44, 0x06, 0x21 };
		// sector 2 block 9 
		//                    00    03    0A    03    13    00    03    0A    03    13    00    00    00    00    00    00
		byte dataBlock9[] = { 0x00, 0x03, 0x0A, 0x03, 0x13, 0x00, 0x03, 0x0A, 0x03, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		// sector 2 block 10
		//                    1D    15    1B    03    13    15    15    1B    03    13    00    00    00    00    00    32 
		byte dataBlock10[] = { 0x1D, 0x15, 0x1B, 0x03, 0x13, 0x15, 0x15, 0x1B, 0x03, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32 };
		// sector 3 block 12
		//                    00    00    00    00    00    00    00    00    00    00    00    1D    15    1B    03    13 
		byte dataBlock12[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x15, 0x1B, 0x03, 0x13 };
		// sector 3 block 13
		//                    EE    75    00    00    2E    B7    01    00    1A    09    00    00    00    00    00    00 
		byte dataBlock13[] = { 0xEE, 0x75, 0x00, 0x00, 0x2E, 0xB7, 0x01, 0x00, 0x1A, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		// sector 3 block 14
		//                    65    04    00    00    18    00    00    00    1A    00    00    00    00    00    00    6B 
		byte dataBlock14[] = { 0x65, 0x04, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6B };
		// sector 4 block 16
		//                    00    04    4D    00    04    3A    00    04    26    00    04    0E    00    03    F5    00 
		byte dataBlock16[] = { 0x00, 0x04, 0x4D, 0x00, 0x04, 0x3A, 0x00, 0x04, 0x26, 0x00, 0x04, 0x0E, 0x00, 0x03, 0xF5, 0x00 };
		// sector 4 block 17 
		//                    00    03    D4    00    03    B2    00    03    7B    00    03    53    00    03    2E    00
		byte dataBlock17[] = { 0x00, 0x03, 0xD4, 0x00, 0x03, 0xB2, 0x00, 0x03, 0x7B, 0x00, 0x03, 0x53, 0x00, 0x03, 0x2E, 0x00 };
		// sector 4 block 18 
		//                    00    02    F7    00    02    D9    27    00    27    00    00    00    03    00    59    D3
		byte dataBlock18[] = { 0x00, 0x02, 0xF7, 0x00, 0x02, 0xD9, 0x27, 0x00, 0x27, 0x00, 0x00, 0x00, 0x03, 0x00, 0x59, 0xD3 };
		// sector 5 block 20
		//00000000000000000000000000000001 
		byte dataBlock20[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };
		// sector 5 block 21
		//06000000000000000000000000000000 
		byte dataBlock21[] = { 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		// sector 5 block 22 
		//                    00    00    00    42    53    61    00    00    00    00    00    05    19    0A    00    26
		byte dataBlock22[] = { 0x00, 0x00, 0x00, 0x42, 0x53, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x19, 0x0A, 0x00, 0x26 };*/

		//rc522Utilities.writeBlock(0, 2, dataBlock2, &keyB);
		/*rc522Utilities.writeBlock(0, 2, dataBlock2, &keyB);
		rc522Utilities.writeBlock(1, 4, dataBlock4, &keyB);
		rc522Utilities.writeBlock(1, 5, dataBlock5, &keyB);
		rc522Utilities.writeBlock(1, 6, dataBlock6, &keyB);
		rc522Utilities.writeBlock(2, 8, dataBlock8, &keyB);
		rc522Utilities.writeBlock(2, 9, dataBlock9, &keyB);
		rc522Utilities.writeBlock(2, 10, dataBlock10, &keyB);
		rc522Utilities.writeBlock(3, 12, dataBlock12, &keyB);
		rc522Utilities.writeBlock(3, 13, dataBlock13, &keyB);
		rc522Utilities.writeBlock(3, 14, dataBlock14, &keyB);
		rc522Utilities.writeBlock(4, 16, dataBlock16, &keyB);
		rc522Utilities.writeBlock(4, 17, dataBlock17, &keyB);
		rc522Utilities.writeBlock(4, 18, dataBlock18, &keyB);
		rc522Utilities.writeBlock(5, 20, dataBlock20, &keyB);
		rc522Utilities.writeBlock(5, 21, dataBlock21, &keyB);
		rc522Utilities.writeBlock(5, 22, dataBlock22, &keyB);*/

		//rc522Utilities.printAllSectors(&rc522Utilities.MADKeyA, &rc522Utilities.NFCKeyA);
		
		for (size_t i = 0; i < 16; i++)
		{
			rc522Utilities.printSector(i, &keyA, &keyB);
			delay(100);
		}
		delay(10000);
	}
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
	for (byte i = 0; i < bufferSize; i++) {
		Serial.print(buffer[i] < 0x10 ? " 0" : " ");
		Serial.print(buffer[i], HEX);
	}
}
