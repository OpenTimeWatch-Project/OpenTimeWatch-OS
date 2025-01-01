#include "peripheralMenu.h"

void peripheralScreen() {
  // show the peripheral screen
  menuScreen(peripheralItems, peripheralItemsNo);
  screenMode = 2;
}

void openPeripheralScreen(Button2& btn) {
  peripheralScreen();
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
      clearScreen();
      tft.drawString("Accelerometer not",0,0,2);
      tft.drawString("connected",0,20,2);
      screenMode = 6;
      break;
    case 4:
      // currently the gyroscope is not connected, expected to be updated in version V0.3
      clearScreen();
      tft.drawString("Gyroscope not",0,0,2);
      tft.drawString("connected",0,20,2);
      screenMode = 6;
      break;
    case 5:
      // show the internal cpu temperature
      clearScreen();
      tft.drawString("CPU Temperature",0,0,2);
      tft.drawString(String(cpuTemp),0,20,2);
      screenMode = 6;
      break;
    case 6:
      menuScreen(menuItems, menuItemsNo);
      // set the screenMode variable to 1 to change the button behaviour
      screenMode = 1;
      break;
  }
}