#include "timeSync.h"

void getTime() {
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  tft.drawString("Time synchronised!", 2, 2, 2);
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void showTime(int timeX, int timeY, int dateX, int dateY, int dayX, int dayY) {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;TFT_eSprite timing = TFT_eSprite(&tft);
  }
  timing.setFreeFont(&FreeMonoBold12pt7b);
  timing.setCursor(26,35);
  timing.println(&timeinfo, "%H:%M");
  strftime(dayName,4, "%A", &timeinfo);
  timing.setFreeFont(&FreeMonoBold9pt7b);

  timing.setCursor(14,53);
  timing.println(&timeinfo, "%d/01 ");
  timing.setCursor(74,53);
  timing.println(dayName);
}