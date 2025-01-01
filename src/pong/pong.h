#ifndef PONG_H
   #define PONG_H
   #include <Arduino.h>
   #include <TFT_eSPI.h>
   #include <Button2.h>
   extern TFT_eSPI tft;
   extern int16_t ball_x;
   extern int16_t ball_y;
   void gameOver();
   void midline();
   void calc_target_y();
   void initgame();
   void lpaddle();
   void ball();
   void rpaddleUpControll(Button2& btn);
   void rpaddleDownControll(Button2& btn);

#endif