#include "osVariables.h"

// a variable to store the battery charge voltage
float batteryVoltage;
// an array to hold the names of apps in Activitythe menu
String menuItems[] = {"Today view", "Pong", "Peripherals", "Settings", "Hacker Mode", "Back"};
// a varible to check if any item in the menu is selected
int selected = 0;
// a variable to check which screen the user is looking at
int screenMode = 0;
// a variable to store the amount of items in the menu
int menuItemsNo = 5;
// just a fake ground
const int fakeGroundPin = 34;
// torch LED pin
const int ledPin = 33;
// speaker pin
const int speakerPin = 16;
// list of menu items for the peripheral menu
String peripheralItems[] = {"Torch - off", "Speaker - off", "Accelerometer", "Gyroscope", "CPU Temperature", "Back"};
// no of items in peripheral menu
int peripheralItemsNo = 5;
// state of the led's power
boolean ledState = 0;
// state of the speaker's power
boolean speakerState = 0;
// variable to hold the value of the cpu temperature
float cpuTemp = 0.00;
// list of menu items for the settings menu
String settingsItems[] = {"Sync Time", "Sync Weather", "About", "Back"};
// no of items in peripheral menu
int settingsItemsNo = 3;
// a variable to indicate if the game is currently being played or not
boolean gameMode = 0;
// a variable to hold the state of the current watch face being displayed
int watchFaceMode = 1;
// No. of total watch faces
int maxWatchFaceNo = 2;
// WiFi network name
const char* ssid       = "SSID";
// WiFi network password
const char* password   = "Password";
// URL of the ntp server
const char* ntpServer = "asia.pool.ntp.org";
// GMT offset (in seconds)
const long  gmtOffset_sec = 19800;
// Day light offset (in seconds)
const int   daylightOffset_sec = 0;
// A variable to store the first 3 letters of the current weekday name
char dayName[4];
// A variable to store the first 3 letters of the current month name
char monthName[4];
// A variable to store the current month number
int monthNo = 1;
