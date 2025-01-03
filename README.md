# OpenTimeWatch-OS
An open source watch OS for ESP32 based development boards and watches which integrates flexibility of users customizing their watches and developers making their own apps, watch faces, widgets,etc. This OS currently supported by LILYGO TQT Pro based on ESP32-S3, we will add support for more microcontrollers and development boards in the future.

# Update
Due to some issues in the prototype the development of the project has been halted for some time, for more information click [here](https://github.com/OpenTimeWatch-Project/OpenTimeWatch-OS/issues/8).

# Why need another OS for watches?
When we look at the current smart watches (especially the cheap ones) the are pretty bad, specifically the software (and also the hardware) as it is very limited in features, lack of flexibility, comes with preloaded watch faces which we cannot remove, most of the time there are no games :( ,etc. We wanted to bring a change as these cheap smartwatches are being bought by millions around the world where many consumers are dissappointed by the lack features and the microcontrollers getting cheaper day-by-day, it was our chance to make a revolution! To be honest I just wanted to make a watch with games so I won't get bored during the annual day dance practice.

# Requirements
1. LILYGO TQT Pro
2. USB-C cable
3. LED (White colour)
4. small speaker
5. A computer with platformio or arduino ide installed

# Hardware setup
1. Solder a white coloured LED to IO33 and 34 with the ground pin being on IO34
2. Solder a speaker to ground and IO16
3. Solder a JST connector (included in the TQT Pro's box) to the battery charge pads

# Installation (for platformio users)
Create a new project and paste all of the files in your project's directory and upload the code (Note:- You may need to change the build flags in ```platformio.ini``` if using an 8MB version of TQT Pro)

# Installation (for arduino users)
All of the required code is in the ```src``` directory, just rename the file ```main.cpp``` to ```main.ino``` and install ```Button2``` and ```TFT_eSPI``` (according to LILYGO TFT_eSPI version 2.0.14 or lower is recommended) in the ide and upload the code 

# Features
1. Home screen with custom background
2. Activity view shows steps walked, calories burned and weather (It is just a dummy and not functionally implemented yet)
3. Pong game
4. A torch
5. Speaker
6. Shows CPU temperature
7. Hacker Mode (ITS JUST A MATRIX EFFECT AND NOT ANYTHING RELATED TO HACKING AND DON'T GET MAD AT ME)
8. Battery voltage

# How to use?
1. If on the home screen press the menu (right) button to access the menu
2. If on the menu use the scroll (left) button to scroll down, the menu button to select an item and double press the menu button to access the home screen 
3. If on any single page application press the menu button to go back to the previous menu, press the scroll button to go to the main menu and double press the menu button to access the home screen
4. While playing pong scroll button moves the paddle up and the menu button moves the paddle down

# Release Notes
1. **V0.2.1** - Added refinements to the OS navigation, added a manual in the ```README.md``` and changed the tone of the speaker.
2. **V0.2** - A significant update compared to V0.1, as it introduced menus, pong, interaction with peripherals (torch and speaker), OS being open sourced, matrix effect, settings menu. 
3. **V0.1** - The initial release it just had a home screen and an about screen.

# When could you expect SDKs for apps, custom home screens and widgets
By V0.7 or V0.8 we could start making SDKs for developers to make apps and games, we will also extend support for other microcontrollers and screen resolutions as the OS currently runs at 128 * 128 px.

# Can I contribute ?
Yes, you can contribute to the project by the following ways :
1. Help us add features to the project by making a PR.
2. Help us test and find bugs.
3. Give feature suggestions by making an issue.
4. Help us test or review PRs.
5. Leave a star ✨ if you like the project.
6. PS : If you have a better logo for the project please let us know by opening a new issue (don't worry we will credit you)

# Images
![Alt text](images/IMG_20241119_201516.jpg)
![Alt text](images/IMG_20241119_201547.jpg)
![Alt text](images/IMG_20241119_201559.jpg)
![Alt text](images/IMG_20241119_201614.jpg)
![Alt text](images/IMG_20241119_201707.jpg)
![Alt text](images/IMG_20241119_201715.jpg)
![Alt text](images/IMG_20241119_201733.jpg)
![Alt text](images/IMG_20241119_201758.jpg)
![Alt text](images/IMG_20241119_202308.jpg)
