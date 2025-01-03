#include "todayViewApp.h"
// all image assets
static const unsigned char PROGMEM batteryCharging[] = {0x00,0x02,0x00,0x0f,0xe4,0xfe,0x10,0x0c,0x01,0x10,0x08,0x01,0x70,0x18,
0x01,0x80,0x30,0x01,0x80,0x3f,0x81,0x80,0x7f,0x01,0x80,0x03,0x01,0x80,0x06,0x01,0x70,0x04,0x01,0x10,0x0c,0x01,0x10,0x08,0x01,
0x0f,0xd3,0xfe,0x00,0x10,0x00
};
static const unsigned char PROGMEM notificationRecieved[] = {0x00,0x00,0x00,0x7f,0xff,0x00,0xc0,0x01,0x80,0xc0,0x01,0x80,0xa0,
0x02,0x80,0x90,0x04,0x80,0x88,0x08,0x80,0x84,0x10,0x80,0x82,0x20,0x80,0x85,0xd0,0x80,0x88,0x08,0x80,0x90,0x04,0x80,0xa0,0x02,
0x80,0xc0,0x01,0x80,0x7f,0xff,0x00,0x00,0x00,0x00
};
static const unsigned char PROGMEM bluetoothOn[] = {0x01,0x00,0x02,0x80,0x02,0x40,0x22,0x20,0x12,0x20,0x0a,0x40,0x06,0x80,0x03,
0x00,0x06,0x80,0x0a,0x40,0x12,0x20,0x22,0x20,0x02,0x40,0x02,0x80,0x01,0x00,0x00,0x00
};
static const unsigned char PROGMEM wifiConnected[] = {0x01,0xf0,0x00,0x07,0xfc,0x00,0x1e,0x0f,0x00,0x39,0xf3,0x80,0x77,0xfd,0xc0,
0xef,0x1e,0xe0,0x5c,0xe7,0x40,0x3b,0xfb,0x80,0x17,0x1d,0x00,0x0e,0xee,0x00,0x05,0xf4,0x00,0x03,0xb8,0x00,0x01,0x50,0x00,0x00,0xe0,
0x00,0x00,0x40,0x00,0x00,0x00,0x00
};
static const unsigned char PROGMEM stepsWalked[] = {0x10,0x38,0x38,0x10,0x6c,0xfe,0xee,0xfe,0xee,0xfe,0x7c,0x6c,0x6c,0x28,0x28,
0x6c
};
static const unsigned char PROGMEM weatherIcon[] = {0x1c,0x00,0x22,0x02,0x2b,0x05,0x2a,0x02,0x2b,0x38,0x2a,0x60,0x2b,0x40,0x2a,
0x40,0x2a,0x60,0x49,0x38,0x9c,0x80,0xae,0x80,0xbe,0x80,0x9c,0x80,0x41,0x00,0x3e,0x00
};
static const unsigned short flame[256] PROGMEM={
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0010 (16) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0020 (32) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0030 (48) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0040 (64) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0050 (80) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,   // 0x0060 (96) pixels
0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,   // 0x0070 (112) pixels
0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,   // 0x0080 (128) pixels
0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,   // 0x0090 (144) pixels
0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,   // 0x00A0 (160) pixels
0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,   // 0x00B0 (176) pixels
0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,   // 0x00C0 (192) pixels
0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,   // 0x00D0 (208) pixels
0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000,   // 0x00E0 (224) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x00F0 (240) pixels
0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,   // 0x0100 (256) pixels
};


// a screen which shows number of steps walked, burned calories and weather
void todayView() {
  clearScreen();
  tft.pushImage(5, 75, 16, 16, flame);
  tft.drawBitmap(5, 24, stepsWalked, 7, 16, 0xFFFF);
  tft.drawRoundRect(0, 22, 128, 45, 3, 0x9CD2);
  tft.setTextSize(1);
  tft.setFreeFont(&FreeMonoBold9pt7b);
  tft.drawString("10000", 69, 26);
  tft.drawLine(31, 43, 123, 43, 0x52AA);
  tft.drawString("7.28 KM", 45, 48);
  tft.drawString("300 cal", 46, 76);
  tft.drawRoundRect(0, 70, 128, 26, 3, 0x9CD2);
  tft.drawString("35*C", 78, 105);
  tft.drawRoundRect(0, 99, 128, 26, 3, 0x9CD2);
  tft.drawBitmap(4, 104, weatherIcon, 16, 16, 0xFFFF);
  tft.setFreeFont();
  tft.drawString("Today View", 4, 3);
  tft.drawString("12:00 PM", 77, 3);
  tft.drawRoundRect(0, 0, 128, 13, 3, 0xFB60);
}