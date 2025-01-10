#include "timeSync.h"

// function to synchronise time
void getTime() {
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  tft.drawString("Time synchronised!", 2, 2, 2);
  //initialize and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

// display the date and time
void showTime(int timeX, int timeY, int dateX, int dateY, int dayX, int dayY) {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  // display time
  screenSprite.setFreeFont(&FreeMonoBold12pt7b);
  screenSprite.setCursor(26,35);
  screenSprite.println(&timeinfo, "%H:%M");
  // store the first three letters of the current week day name 
  strftime(dayName,4, "%A", &timeinfo);
  // store the first three letters of the current month name 
  strftime(monthName,4, "%A", &timeinfo);
  // change the month number depending upon the current month
  if (strcmp(monthName, "Feb") == 0) {
    monthNo = 2;
  }
  else if (strcmp(monthName, "Mar") == 0) {
    monthNo = 3;
  }
  else if (strcmp(monthName, "Apr") == 0) {
    monthNo = 4;
  }
  else if (strcmp(monthName, "May") == 0) {
    monthNo = 5;
  }
  else if (strcmp(monthName, "Jun") == 0) {
    monthNo = 6;
  }
  else if (strcmp(monthName, "Jul") == 0) {
    monthNo = 7;
  }
  else if (strcmp(monthName, "Aug") == 0) {
    monthNo = 8;
  }
  else if (strcmp(monthName, "Sep") == 0) {
    monthNo = 9;
  }
  else if (strcmp(monthName, "Oct") == 0) {
    monthNo = 10;
  }
  else if (strcmp(monthName, "Nov") == 0) {
    monthNo = 11;
  }
  else if (strcmp(monthName, "Dec") == 0) {
    monthNo = 12;
  }
  else {
    monthNo = 1;
  }
  screenSprite.setFreeFont(&FreeMonoBold9pt7b);
  // show date
  screenSprite.setCursor(14,53);
  screenSprite.println(&timeinfo, "%d/" + monthNo);
  screenSprite.setCursor(77,53);
  // show week day
  screenSprite.println(dayName);
}
