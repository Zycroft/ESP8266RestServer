#ifndef _Declarations_H    // Put these two lines at the top of your file.
#define _Declarations_H    // (Use a suitable name, usually based on the file name.)

#define HTTP_REST_PORT 80
#define WIFI_RETRY_DELAY 500
#define MAX_WIFI_INIT_RETRY 500

//Declarations for Control Boards
// Block control A   Board 1 BLKA=01 Board 2 BLKA=03 Board 3 BLKA=05 Board 4 BLKA=07 
// Block control B   Board 1 BLKB=02 Board 2 BLKB=04 Board 3 BLKB=06 Board 4 BLKB=08


String ControlBoard = "1"; // 
String BLKA = "01";   // Block control A   Board 1 BLKA=01 
String BLKB = "02";   // Block control B   Board 1 BLKB=02
int BLK_Status[2][3] = { {1,1,0}, {1,2,0} };
/*
BLK_Status[0][0] = 1; // Control Board
BLK_Status[0][1] = 1; // Block
BLK_Status[0][2] = 0; // PPK
BLK_Status[1][0] = 1; // Control Board
BLK_Status[1][1] = 2; // Block
BLK_Status[1][2] = 0; // PPK
*/

//String ControlBoard = "2"; // Com 6 = 1  ###  Com 5 =2
//String BLKA = "03";   // Block control A   Board 2 BLKA=03
//String BLKB = "04";   // Block control B   Board 2 BLKB=04
//int BLK_Status[2][3] = { {2,3,0}, {2,4,0} };

//String ControlBoard = "3"; // Com 6 = 1  ###  Com 5 =2
//String BLKA = "05";   // Board 3 BLKA=05
//String BLKB = "06";   // Board 3 BLKB=06
//int BLK_Status[2][3] = { {3,5,0}, {3,6,0} };

//String ControlBoard = "4"; // Com 6 = 1  ###  Com 5 =2
//String BLKA = "07";   // Board 4 BLKA=07 
//String BLKB = "08";   // Board 4 BLKB=08
//int BLK_Status[2][3] = { {4,7,0}, {4,8,0} };

const char* wifi_ssid = "Williams24G";
const char* wifi_passwd = "zoey1120";

ESP8266WebServer http_rest_server(HTTP_REST_PORT);

//Declarations for Relay
int latchPin = 12;  // Latch pin of 74HC595 (12) is connected to Digital pin 5 Storage register
int clockPin = 13; // Clock pin of 74HC595 (11) is connected to Digital pin 6
int dataPin = 14;  // Data pin of 74HC595 (14) is connected to Digital pin 4
int oePin = 5;    // oePin - not using this
uint16_t Data; 
const uint16_t R0F = 0b0000000000000000;
const uint16_t R0G = 0b1111111111111111;
const uint16_t RG1 = 0b0000000000111111;
const uint16_t RG2 = 0b1111110000000000;
const uint16_t R00 = 0b0000000000000001;// BLK1A
const uint16_t R01 = 0b0000000000000010;// BLK1A
const uint16_t R02 = 0b0000000000000100;// BLK1B
const uint16_t R03 = 0b0000000000001000;// BLK1B
const uint16_t R04 = 0b0000000000010000;// BLK1C
const uint16_t R05 = 0b0000000000100000;// BLK1C
const uint16_t R06 = 0b0000000001000000;// BLK2A
const uint16_t R07 = 0b0000000010000000;// BLK2A
const uint16_t R08 = 0b0000000100000000;// BLK2B
const uint16_t R09 = 0b0000001000000000;// BLK2B
const uint16_t R10 = 0b0000010000000000;// BLK2C
const uint16_t R11 = 0b0000100000000000;// BLK2C
const uint16_t R12 = 0b0001000000000000;// BLK3A
const uint16_t R13 = 0b0010000000000000;// BLK3A
const uint16_t R14 = 0b0100000000000000;// BLK3B
const uint16_t R15 = 0b1000000000000000;// BLK3B

#endif // _Declarations_H    // Put this line at the end of your file.