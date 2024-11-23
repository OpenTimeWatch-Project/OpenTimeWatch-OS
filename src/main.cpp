/*
 *                                                      OpenTime Watch OS
 *                                                          V 0.1
 *  An open source OS for watches.
 * 
 *  created on 15 November 2024
 *  by Jaswanth Venkata Sai Chennu
 *  
 *  Release notes - 
 *  15 November 2024 - V 0.1 -
 *  Initial alpha release still in development and very basic in features.
 *  19 November 2024 - V 0.2 -
 *  Added more features, check README.md file for more information.
 *  23 November 2024 - V 0.2.1 -
 *  Made improvements in navigation of the OS and updated the README.md file to include a manual and changed the tone of the speaker.
 */

// include all the necessary libraries for the OS
#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Button2.h"
#include <SPI.h>
#include "driver/temp_sensor.h"
#include <DigitalRainAnimation.hpp>
// these files contain images dor background and the ui
#include "catalina.h"
#include"walk.h"
#include"fire.h"
#include"cloud.h"

// create an object for the lcd display
TFT_eSPI tft = TFT_eSPI();
DigitalRainAnimation<TFT_eSPI> matrix_effect = DigitalRainAnimation<TFT_eSPI>();
// define the pin definitions for the buttons
#define BUTTON1PIN 47
#define BUTTON2PIN 0

// create 2 objects for the buttons
Button2 button;
Button2 button2;

// a variable to store the battery charge voltage
float batteryVoltage;
// an array to hold the names of apps in the menu
String menuItems[] = {"Activity view", "Pong", "Peripherals", "Settings", "Hacker Mode"};
// x coordinate for menu items and cursor
int listItemX = 3;
// y coordinate for menu items and cursor
int listItemY = 2;
// a varible to check if any item in the menu is selected
int selected = 0;
// a variable to check which screen the user is looking at
int screenMode = 0;
// a variable to store the amount of items in the menu
int menuItemsNo = 4;
// just a fake ground
const int fakeGroundPin = 34;
// torch LED pin
const int ledPin = 33;
// speaker pin
const int speakerPin = 16;
// list of menu items for the peripheral menu
String peripheralItems[] = {"Torch - off", "Speaker - off", "Accelerometer", "Gyroscope", "CPU Temperature"};
// no of items in peripheral menu
int peripheralItemsNo = 4;
// state of the led's power
boolean ledState = 0;
// state of the speaker's power
boolean speakerState = 0;
// variable to hold the value of the cpu temperature
float cpuTemp = 0.00;
// list of menu items for the settings menu
String settingsItems[] = {"Sync Time", "Sync Weather", "About"};
// no of items in peripheral menu
int settingsItemsNo = 2;
//height and width of the screen
int16_t h = 128;
int16_t w = 128;
// height and width of the paddle
int16_t paddle_h = 30;
int16_t paddle_w = 4;
// x coordinates of right and left paddle
int16_t lpaddle_x = 0;
int16_t rpaddle_x = w - paddle_w;
// y coordinates of right and left paddle
int16_t lpaddle_y = 0;
int16_t rpaddle_y = h - paddle_h;
// paddle direction
int16_t lpaddle_d = 1;
int16_t rpaddle_d = -1;
// paddle trigger area
int16_t lpaddle_ball_t = w - w / 4;
int16_t rpaddle_ball_t = w / 4;
// p
int16_t target_y = 0;
// x and y coordinates for the ball
int16_t ball_x = 2;
int16_t ball_y = 2;
int16_t oldball_x = 2;
int16_t oldball_y = 2;
// ball x and y direction
int16_t ball_dx = 1;
int16_t ball_dy = 1;
// ball's dimensions
int16_t ball_w = 6;
int16_t ball_h = 6;
// variables for the middle dashed line
int16_t dashline_h = 4;
int16_t dashline_w = 2;
int16_t dashline_n = h / dashline_h;
int16_t dashline_x = w / 2 - 1;
int16_t dashline_y = dashline_h / 2;
// a variable to indicate if the game is currently being played or not
boolean gameMode = 0;
// a variable forr storing the temperature
float Temperature = 0.00;

// A handy function to clear the screen
void clearScreen() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
}

// a function which contains all of the ui for the homescreen
void homeScreen() {
  // show the background image
  tft.pushImage(0,0,135,135,catalina);
  // show the battery voltage
  tft.setTextColor(TFT_WHITE);
  tft.drawString(String(batteryVoltage), 20,0,2);
  // show the time
  tft.drawString("12:00 PM", 3, 100, 2);
}

// a screen which shows number of steps walked, burned calories and weather
void activityView() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.pushImage(5, 7, 30, 30, walk);
  tft.drawString("6900", 54, 8, 4);
  tft.fillRect(0, 42, 128, 3, TFT_DARKGREY);
  tft.pushImage(5, 51, 30, 30, fire);
  tft.drawString("300", 54, 59, 4);
  tft.fillRect(0, 85, 128, 3, TFT_DARKGREY);
  tft.pushImage(5, 94, 30, 30, cloud);
  tft.drawString(String(Temperature), 54, 102, 4);
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

void peripheralScreen() {
  // show the peripheral screen
  menuScreen(peripheralItems, peripheralItemsNo);
  screenMode = 2;
}

void settingsScreen() {
  // show the settings screen
  menuScreen(settingsItems, settingsItemsNo);
  screenMode = 4;
}

void openPeripheralScreen(Button2& btn) {
  peripheralScreen();
}

void openSettingsScreen(Button2& btn) {
  settingsScreen();
}

// a game over screen for the pong game
void gameOver() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("GAME OVER", 0, 0, 2);
}

// a function to draw the dashed line for the pong game
void midline() {
  // If the ball is not on the line then don't redraw the line
  if ((ball_x<dashline_x-ball_w) && (ball_x > dashline_x+dashline_w)) return;
  // start drawing the line
  tft.startWrite();
  // Quick way to draw a dashed line
  tft.setAddrWindow(dashline_x, 0, dashline_w, h);
  for(int16_t i = 0; i < dashline_n; i+=2) {
    tft.pushColor(TFT_WHITE, dashline_w*dashline_h); // push dash pixels
    tft.pushColor(TFT_BLACK, dashline_w*dashline_h); // push gap pixels
  }
  // stop drawing the line
  tft.endWrite();
}


// a function to calculate the y target
void calc_target_y() {
  int16_t target_x;
  int16_t reflections;
  int16_t y;
  if (ball_dx == 1) {
    target_x = w - ball_w;
  } 
  else {
    target_x = -1 * (w - ball_w);
  }
  y = abs(target_x * (ball_dy / ball_dx) + ball_y);

  reflections = floor(y / h);

  if (reflections % 2 == 0) {
    target_y = y % h;
  } 
  else {
    target_y = h - (y % h);
  }
}

void initgame() {
  // calculate the y coordinate of both of the paddles
  lpaddle_y = random(0, h - paddle_h);
  rpaddle_y = random(0, h - paddle_h);
  // calculate the balls y coordinate
  ball_y = lpaddle_y + (paddle_h / 2);
  // calculate the y target
  calc_target_y();
  // draw the midline
  midline();
  // draw the paddle for the player
  tft.fillRect(rpaddle_x, rpaddle_y, paddle_w, paddle_h, TFT_WHITE);
}

void lpaddle() {
  // check the paddle's direction and hide it
  if (lpaddle_d == 1) {
    tft.fillRect(lpaddle_x, lpaddle_y, paddle_w, 1, TFT_BLACK);
  } 
  else if (lpaddle_d == -1) {
    tft.fillRect(lpaddle_x, lpaddle_y + paddle_h - 1, paddle_w, 1, TFT_BLACK);
  }
  // update the paddle's y coordinate
  lpaddle_y = lpaddle_y + lpaddle_d;
  // check if the balls's x axis direction is 1
  if(ball_dx == 1){
    // reset the paddles direction
    lpaddle_d = 0;
  } 
  // else change the paddles direction or reset it
  else {
    if(lpaddle_y + paddle_h / 2 == target_y) {
      lpaddle_d = 0;
    }
    else if(lpaddle_y + paddle_h / 2 > target_y) {
      lpaddle_d = -1;
    }
    else{
      lpaddle_d = 1;
    }
  }

  if (lpaddle_y + paddle_h >= h && lpaddle_d == 1) lpaddle_d = 0;
  else if (lpaddle_y <= 0 && lpaddle_d == -1) lpaddle_d = 0;

  tft.fillRect(lpaddle_x, lpaddle_y, paddle_w, paddle_h, TFT_WHITE);
}
// function to controll the ball
void ball() {
  ball_x = ball_x + ball_dx;
  ball_y = ball_y + ball_dy;

  if (ball_dx == -1 && ball_x == paddle_w && ball_y + ball_h >= lpaddle_y && ball_y <= lpaddle_y + paddle_h) {
    ball_dx = ball_dx * -1;
    calc_target_y(); 
  } else if (ball_dx == 1 && ball_x + ball_w == w - paddle_w && ball_y + ball_h >= rpaddle_y && ball_y <= rpaddle_y + paddle_h) {
    ball_dx = ball_dx * -1;
    calc_target_y();
  } else if ((ball_dx == 1 && ball_x >= w) || (ball_dx == -1 && ball_x + ball_w < 0)) {
  }

  if (ball_y > h - ball_w || ball_y < 0) {
    ball_dy = ball_dy * -1;
    ball_y += ball_dy; // Keep in bounds
  }

  tft.drawRect(oldball_x, oldball_y, ball_w, ball_h, TFT_BLACK); // Less TFT refresh aliasing than line above for large balls
  tft.fillRect(   ball_x,    ball_y, ball_w, ball_h, TFT_WHITE);
  oldball_x = ball_x;
  oldball_y = ball_y;
}

// controll the upward direction of the paddle
void rpaddleUpControll(Button2& btn) {
  tft.fillRect(rpaddle_x, rpaddle_y, paddle_w, paddle_h, TFT_BLACK);
  rpaddle_y-=10;
  rpaddle_d = -1;
  tft.fillRect(rpaddle_x, rpaddle_y, paddle_w, paddle_h, TFT_WHITE);
}
// controll the upward direction of the paddle
void rpaddleDownControll(Button2& btn) {
  tft.fillRect(rpaddle_x, rpaddle_y, paddle_w, paddle_h, TFT_BLACK);
  rpaddle_y+=10;
  rpaddle_d = 1;
  tft.fillRect(rpaddle_x, rpaddle_y, paddle_w, paddle_h, TFT_WHITE);
}
// function for opening items in the settings menu
void settingsMenu(Button2& btn) {
  switch (selected + 1) {
    case 1:
      // Option for synchronising time with wifi(not implemented yet)
      clearScreen();
      tft.drawString("WiFi not connected", 0, 0, 2);
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
  }
}
// function for opening items in the text rain mode
void peripheralMenu(Button2& btn) {
  switch (selected + 1) {
    case 1:
      // toggle the led on / off, when the user interacts with the menu item
      // change the ledState variable's state
      ledState = !ledState;
      // turn on the led if the user turned it on
      if(ledState == 1){
        digitalWrite(ledPin, ledState);
        peripheralItems[0] = "Torch - on";
        menuScreen(peripheralItems, peripheralItemsNo);
      }
      // turn it off
      else{
        digitalWrite(ledPin, ledState);
        peripheralItems[0] = "Torch - off"; 
        menuScreen(peripheralItems, peripheralItemsNo);
        ledState = 0;
      } 
      break;

    case 2: 
      // toggle the speaker on / off, when the user interacts with the menu item
      // change the speakerState variable's state
      speakerState = !speakerState;
      // turn on the speaker if the user turned it on
      if(speakerState == 1){
        peripheralItems[1] = "Speaker - on";
        menuScreen(peripheralItems, peripheralItemsNo); 
        for(int i = 0; i < 100; i++){
          digitalWrite(speakerPin, HIGH);
          delay(2);
          digitalWrite(speakerPin, LOW);
          delay(2);
        }
        peripheralItems[1] = "Speaker - off"; 
        menuScreen(peripheralItems, peripheralItemsNo);
        speakerState = 0;
      }
      // turn it off
      else{
        digitalWrite(speakerPin, LOW);
        peripheralItems[1] = "Speaker - off"; 
        menuScreen(peripheralItems, peripheralItemsNo);
        speakerState = 0;
      }
      break;
    case 3:
      // currently the accelerometer is not connected, expected to be updated in version V0.3
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE);
      tft.drawString("Accelerometer not",0,0,2);
      tft.drawString("connected",0,20,2);
      screenMode = 6;
      break;
    case 4:
      // currently the gyroscope is not connected, expected to be updated in version V0.3
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE);
      tft.drawString("Gyroscope not",0,0,2);
      tft.drawString("connected",0,20,2);
      screenMode = 6;
      break;
    case 5:
      // show the internal cpu temperature
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_WHITE);
      tft.drawString("CPU Temperature",0,0,2);
      tft.drawString(String(cpuTemp),0,20,2);
      screenMode = 6;
      break;
  }
}

// function for showing the menu screen when right button pressed once
void menuScreenOpen(Button2& btn) {
  menuScreen(menuItems, menuItemsNo);
  // set the screenMode variable to 1 to change the button behaviour
  screenMode = 1;
}
// function for showing the home screen when left button pressed twice
void homeScreenOpen(Button2& btn) {
  homeScreen();
  screenMode = 0;
}
// function for scrolling through the menu
void scroll(Button2& btn) {
  cursorControll(menuItemsNo);
}
// scroll function for the settings menu
void scrollSettings(Button2& btn) {
  cursorControll(settingsItemsNo);
}
// function for doing nothing
void nothing(Button2& btn) {
  
}
// function for opening items in the menu
void openMenuItem(Button2& btn) {
  switch(selected + 1) {
    case 0:
      // Default
      break;
    case 1:
      //show the activity view 
      activityView();
      screenMode = 0;
      break;
    case 2:
      // open the game
      clearScreen();
      initgame();
      gameMode = 1;
      screenMode = 3;
      break;
    case 3:
      // show the peripherals menu
      peripheralScreen();
      break;
    case 4:
      // show the settings menu
      settingsScreen();
      break;
    case 5:
      // initialize the text rain effect (Hacker mode)
      matrix_effect.init(&tft);
      screenMode = 5;
      break;
  }
}


void setup() {
  // initialize the serial console for debugging purposes
  Serial.begin(115200);
  // initialize the screen and set the correct screen rotation
  tft.init();
  tft.setRotation(4);
  // allow images to be displayed
  tft.setSwapBytes(true);
  // initialize the 2 buttons
  button.begin(BUTTON1PIN);
  button2.begin(BUTTON2PIN);
  // show the homescreen on startup
  homeScreen();
  // assign the buttons action functions to the handler functions
  button.setPressedHandler(menuScreenOpen);
  button.setDoubleClickHandler(homeScreenOpen);
  button2.setPressedHandler(nothing);
  // set the fake ground as output
  pinMode(fakeGroundPin, OUTPUT);
  // set the torch LED as output
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  // initialize the temperature sensor
  temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
  temp_sensor.dac_offset = TSENS_DAC_L2;  
  temp_sensor_set_config(temp_sensor);
  temp_sensor_start();
  
}

void loop() {
  // read and calculate the battery voltage
  batteryVoltage = ((float)analogRead(4) / 4095.0) * 2.0 * 3.3 * (1100 / 1000.0);
  // update the buttons state
  button.loop();
  button2.loop();
  temp_sensor_read_celsius(&cpuTemp);
  // switch case statement for preventing cursor scrolling effect on the home screen
  switch(screenMode) {
    case 0:
      // when on home screen or any single page application disable scroll
      button2.setPressedHandler(nothing);
      // when on home screen or any single page application allow the menu button to open the menu
      button.setPressedHandler(menuScreenOpen);
      button.setDoubleClickHandler(nothing);
      break;
    case 1:
      // when on menu screen enable scroll
      button2.setPressedHandler(scroll);
      // when on menu screen allow the menu button to open the menu items
      button.setPressedHandler(openMenuItem);
      button.setDoubleClickHandler(homeScreenOpen);
      break;
    case 2:
      // when on peripheral screen enable scroll
      button2.setPressedHandler(scroll);
      // when on peripheral screen allow the menu button to open the menu items
      button.setPressedHandler(peripheralMenu);
      button.setDoubleClickHandler(homeScreenOpen);
      break;
    case 3:
      // when on playing the game, make the left button controll the paddle's upward movement
      button2.setPressedHandler(rpaddleUpControll);
      // when on playing the game, make the right button controll the paddle's downward movement
      button.setPressedHandler(rpaddleDownControll);
      // disable home screen
      button.setDoubleClickHandler(nothing);
      // while the player is playing the game
      while (gameMode == 1) {
        // update the buttons state
        button.loop();
        button2.loop();
        // draw the left paddle
        lpaddle();
        // draw the midline
        midline();
        // controll the ball
        ball();
        // if the player missed the ball
        if (ball_x >= 128) {
          // set the gameMode to 0
          gameMode = 0;
        }
        // add delay for the player's sanity
        delay(10);
      }
      // show the game over screen if the player missed the ball
      if(gameMode == 0) {
        gameOver();
        // set the screenMode to 0 to escape from the game
        screenMode = 0;
      }
      // reset the x and y coordinates of the ball
      ball_x = 2;
      ball_y = 2;
      break;
    case 4:
      // when on settings screen enable scroll
      button2.setPressedHandler(scrollSettings);
      // when on settings screen allow the menu button to open the settings menu items
      button.setPressedHandler(settingsMenu);
      button.setDoubleClickHandler(homeScreenOpen);
      break;
    case 5:
      // when on hacker mode disable scroll
      button2.setPressedHandler(nothing);
      // when on hacker mode the menu button to go back to the menu
      button.setPressedHandler(menuScreenOpen);
      button.setDoubleClickHandler(nothing);
      // show the text rain effect
      matrix_effect.loop();
      break;
    case 6:
      // when on perpheral menu application allow going to the main menu
      button2.setPressedHandler(menuScreenOpen);
      // when on peripheral menu application allow the menu button to open the peripheral screen
      button.setPressedHandler(openPeripheralScreen);
      button.setDoubleClickHandler(homeScreenOpen);
      break;
    case 7:
      // when on settings menu item allow going to the main menu
      button2.setPressedHandler(menuScreenOpen);
      // when on settings menu item allow the menu button to open the peripheral screen
      button.setPressedHandler(openSettingsScreen);
      button.setDoubleClickHandler(homeScreenOpen);
      break;
  }
}
