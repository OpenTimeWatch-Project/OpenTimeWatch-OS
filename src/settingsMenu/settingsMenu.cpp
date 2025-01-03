#include "settingsMenu.h"

void settingsScreen() {
  // show the settings screen
  menuScreen(settingsItems, settingsItemsNo);
  screenMode = 4;
}

void openSettingsScreen(Button2& btn) {
  settingsScreen();
}

// function for opening items in the settings menu
void settingsMenu(Button2& btn) {
  switch (selected + 1) {
    case 1:
      // Option for synchronising time using ntp
      clearScreen();
      getTime();
      screenMode = 7;
      break;
    case 2:
      // Option for synchronising weather with wifi(not implemented yet)
      clearScreen();
      tft.drawString("WiFi not connected", 0, 0, 2);
      screenMode = 7;
      break;
    case 3:
      // show the about screen
      infoScreen();
      screenMode = 7;
      break;
    case 4:
      menuScreen(menuItems, menuItemsNo);
      // set the screenMode variable to 1 to change the button behaviour
      screenMode = 1;
      break;
  }
}

// scroll function for the settings menu
void scrollSettings(Button2& btn) {
  cursorControll(settingsItemsNo);
}

void infoScreen(){
  // show all of the required information
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("OpenTime Watch OS",0,0,2);
  tft.drawString("Version : V 0.2.1",0,20,2);
  tft.drawString("CPU : ESP32-S3",0,40,2);
  tft.drawString("PSRAM : 2MB",0,60,2);
  tft.drawString("Flash : 4MB",0,80,2);
}
