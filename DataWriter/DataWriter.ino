/*
 * This program is modeified from an example provided by the RC522 library:
 * https://github.com/miguelbalboa/rfid
 * 
 * Author: BoolLi
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
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
#include <RC522_RFID_Utilities.h>

#define RST_PIN    9   // 
#define SS_PIN    10    //

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
RC522_RFID_Utilities rc522Utilities;

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  rc522Utilities.setMFRC(&mfrc522);
  rc522Utilities.showReaderDetails(); // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));
}

void loop() {
  if (rc522Utilities.detectNewCard()) {
    rc522Utilities.formatToNDEF(&rc522Utilities.NFCDefaultKeyB, &rc522Utilities.NFCDefaultKeyB);
    // sector 0 block 0
    byte dataBlock0[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    
    // sector 0 block 1
    byte dataBlock1[] = {0x00, 0x00, 0x00, 0x42, 0x53, 0x61, 0x00, 0x59, 0x13, 0x81, 0x00, 0x03, 0x00, 0x00, 0x96, 0x01};
    // sector 0 block 2 
    byte dataBlock2[] = {0x00, 0x02, 0x42, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x14, 0x00, 0xF0, 0x00, 0x00, 0x00, 0xCC};
    //sector 1 block 4 
    byte dataBlock4[] = {0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0xFF, 0x1E, 0x99, 0x99, 0x90, 0x00, 0x00, 0x00}; 
    // sector 1 block 5 
    byte dataBlock5[] = {0x00, 0x99, 0x00, 0x00, 0x99, 0x00, 0x00, 0x99, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
    // sector 1 block 6 
    byte dataBlock6[] = {0x00, 0x0C, 0x01, 0x01, 0x00, 0x00, 0x0C, 0x01, 0x01, 0x00, 0x00, 0x0C, 0x01, 0x01, 0x00, 0xD9};
    // sector 2 block 8
    //                    00    00    00    00    00    00    02    7D    09    17    08    0A    11    44    06    21 
    byte dataBlock8[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x7D, 0x09, 0x17, 0x08, 0x0A, 0x11, 0x44, 0x06, 0x21};
    // sector 2 block 9 
    //                    00    03    0A    03    13    00    03    0A    03    13    00    00    00    00    00    00
    byte dataBlock9[] = {0x00, 0x03, 0x0A, 0x03, 0x13, 0x00, 0x03, 0x0A, 0x03, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    // sector 2 block 10
    //                    1D    15    1B    03    13    15    15    1B    03    13    00    00    00    00    00    32 
    byte dataBlock10[] = {0x1D, 0x15, 0x1B, 0x03, 0x13, 0x15, 0x15, 0x1B, 0x03, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32};
    // sector 3 block 12
    //                    00    00    00    00    00    00    00    00    00    00    00    1D    15    1B    03    13 
    byte dataBlock12[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x15, 0x1B, 0x03, 0x13};
    // sector 3 block 13
    //                    EE    75    00    00    2E    B7    01    00    1A    09    00    00    00    00    00    00 
    byte dataBlock13[] = {0xEE, 0x75, 0x00, 0x00, 0x2E, 0xB7, 0x01, 0x00, 0x1A, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    // sector 3 block 14
    //                    65    04    00    00    18    00    00    00    1A    00    00    00    00    00    00    6B 
    byte dataBlock14[] = {0x65, 0x04, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6B};
    // sector 4 block 16
    //                    00    04    4D    00    04    3A    00    04    26    00    04    0E    00    03    F5    00 
    byte dataBlock16[] = {0x00, 0x04, 0x4D, 0x00, 0x04, 0x3A, 0x00, 0x04, 0x26, 0x00, 0x04, 0x0E, 0x00, 0x03, 0xF5, 0x00};
    // sector 4 block 17 
    //                    00    03    D4    00    03    B2    00    03    7B    00    03    53    00    03    2E    00
    byte dataBlock17[] = {0x00, 0x03, 0xD4, 0x00, 0x03, 0xB2, 0x00, 0x03, 0x7B, 0x00, 0x03, 0x53, 0x00, 0x03, 0x2E, 0x00};
    // sector 4 block 18 
    //                    00    02    F7    00    02    D9    27    00    27    00    00    00    03    00    59    D3
    byte dataBlock18[] = {0x00, 0x02, 0xF7, 0x00, 0x02, 0xD9, 0x27, 0x00, 0x27, 0x00, 0x00, 0x00, 0x03, 0x00, 0x59, 0xD3};
    // sector 5 block 20
    //00000000000000000000000000000001 
    byte dataBlock20[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    // sector 5 block 21
    //06000000000000000000000000000000 
    byte dataBlock21[] = {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    // sector 5 block 22 
    //                    00    00    00    42    53    61    00    00    00    00    00    05    19    0A    00    26
    byte dataBlock22[] = {0x00, 0x00, 0x00, 0x42, 0x53, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x19, 0x0A, 0x00, 0x26};

    rc522Utilities.writeBlock(0, 1, dataBlock1, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(0, 2, dataBlock2, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(1, 4, dataBlock4, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(1, 5, dataBlock5, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(1, 6, dataBlock6, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(2, 8, dataBlock8, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(2, 9, dataBlock9, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(2, 10, dataBlock10, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(3, 12, dataBlock12, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(3, 13, dataBlock13, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(3, 14, dataBlock14, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(4, 16, dataBlock16, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(4, 17, dataBlock17, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(4, 18, dataBlock18, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(5, 20, dataBlock20, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(5, 21, dataBlock21, &rc522Utilities.NFCKeyB);
    rc522Utilities.writeBlock(5, 22, dataBlock22, &rc522Utilities.NFCKeyB);
    //rc522Utilities.printAllSectors(&rc522Utilities.MADKeyA, &rc522Utilities.NFCKeyA);
  }
}
