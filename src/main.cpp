/*
 *                                                      OpenTime Watch OS
 *                                                          V 0.3
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
// import the UI for watch
#include "otwUI/otwUI.h"
#include "pong/pong.h"
#include "settingsMenu/settingsMenu.h"
#include "osVariables/osVariables.h"
#include "peripheralMenu/peripheralMenu.h"
#include "watchFace/watchFace.h"
#include "todayViewApp/todayViewApp.h"
#include "timeSync/timeSync.h"

// create an object for the lcd display
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite timing = TFT_eSprite(&tft);
DigitalRainAnimation<TFT_eSPI> matrix_effect = DigitalRainAnimation<TFT_eSPI>();
// define the pin definitions for the buttons
#define BUTTON1PIN 47
#define BUTTON2PIN 0

// create 2 objects for the buttons
Button2 button;
Button2 button2;

// function for showing the menu screen when right button pressed once
void menuScreenOpen(Button2& btn) {
  menuScreen(menuItems, menuItemsNo);
  // set the screenMode variable to 1 to change the button behaviour
  screenMode = 1;
}
// function for scrolling through the menu
void scroll(Button2& btn) {
  cursorControll(menuItemsNo);
}

// function for doing nothing
void nothing(Button2& btn) {
  
}

// function for doing nothing
void changeWatchFace(Button2& btn) {
  homeScreen();
  watchFaceMode++;
  if(watchFaceMode > maxWatchFaceNo) {
    watchFaceMode = 1;
  }
}

// function for opening items in the menu
void openMenuItem(Button2& btn) {
  switch(selected + 1) {
    case 0:
      // Default
      break;
    case 1:
      //show the activity view 
      todayView();
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
    case 6:
      // initialize the text rain effect (Hacker mode)
      homeScreen();
      screenMode = 0;
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
  // assign the buttons action functions to the handler functions
  button.setPressedHandler(menuScreenOpen);
  button.setDoubleClickHandler(nothing);
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
  timing.createSprite(128, 128);
  clearScreen();
  // show the homescreen on startup
  homeScreen();
  
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
      button2.setPressedHandler(changeWatchFace);
      // when on home screen or any single page application allow the menu button to open the menu
      button.setPressedHandler(menuScreenOpen);
      button.setDoubleClickHandler(nothing);
      if(watchFaceMode == 2){
        homeScreen();
        timing.pushSprite(0,0);
      }
      break;
    case 1:
      // when on menu screen enable scroll
      button2.setPressedHandler(scroll);
      // when on menu screen allow the menu button to open the menu items
      button.setPressedHandler(openMenuItem);
      button.setDoubleClickHandler(nothing);
      break;
    case 2:
      // when on peripheral screen enable scroll
      button2.setPressedHandler(scroll);
      // when on peripheral screen allow the menu button to open the menu items
      button.setPressedHandler(peripheralMenu);
      button.setDoubleClickHandler(nothing);
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
      button.setDoubleClickHandler(nothing);
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
      button.setDoubleClickHandler(nothing);
      break;
    case 7:
      // when on settings menu item allow going to the main menu
      button2.setPressedHandler(menuScreenOpen);
      // when on settings menu item allow the menu button to open the peripheral screen
      button.setPressedHandler(openSettingsScreen);
      button.setDoubleClickHandler(nothing);
      break;
  }
}
