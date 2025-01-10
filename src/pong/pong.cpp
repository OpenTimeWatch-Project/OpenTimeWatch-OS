#include "pong.h"

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
int16_t ball_x = 2;
int16_t ball_y = 2;

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