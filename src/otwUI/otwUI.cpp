#include "otwUI.h"

// x coordinate for menu items and cursor
int listItemX = 3;
// y coordinate for menu items and cursor
int listItemY = 2;

// A handy function to clear the screen
void clearScreen() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
}

void clearScreenSprite() {
  timing.fillScreen(TFT_BLACK);
  timing.setTextColor(TFT_WHITE);
}

// a function to move the cursor
void cursorControll(int menuItemNoHolder) {
  // this function has one parameter which holds the number of items in the menu
  // hide the cursor
  tft.drawRoundRect(listItemX - 3, listItemY - 1 + (20 * selected), 127, 18, 4, TFT_BLACK);
  // increament the selected variable
  selected+=1;
  // if the cursor position is greater than the amount of items in the menu then reset the cursor position
  if(selected > menuItemNoHolder){
    selected = 0;
  }
  // show the cursor
  tft.drawRoundRect(listItemX - 3, listItemY - 1 + (20 * selected), 127, 18, 4, TFT_DARKGREEN);
}

// a function to store the ui of the menu
void menuScreen(String menuItemHolder[], int menuItemNoHolder) {
  // this function has two parameters, the first is to store the required items in that menu
  // and the second to hold the number of items in the menu
  // set the background and text colour
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  // display the menu items
  for(int iterate = 0; iterate < (menuItemNoHolder + 1); iterate++) {
    tft.drawString(menuItemHolder[iterate], listItemX, listItemY, 2);
    listItemY+=20;
  }
  // reset the y coordinate of the menu items and the cursor
  listItemY = 2;
  // show the cursor
  tft.drawRoundRect(listItemX - 3, listItemY - 1 + (20 * selected), 127, 18, 4, TFT_DARKGREEN);
}