#include <Adafruit_NeoPixel.h>
#define PIN 6
#define MAXLED 2304
Adafruit_NeoPixel led(MAXLED, PIN, NEO_GRB + NEO_KHZ800);
int p1x = A0;
int p1y = A1;
int p2x = A2;
int p2y = A3;
int p3x = A4;
int p3y = A5;
int p4x = A6;
int p4y = A7;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int ran = 0;
int game = 1;
int score1 = 0;
int score2 = 0;
int score3 = 0;
int score4 = 0;
int select = 3;
float countcoin = 0;
int dotdelay = 10;
void setup() {
  Serial.begin(9600);
  led.begin();
}

void loop() {
  game4();
}

void game4() {
  if (select == 3) {
    if (game == 1) {
      ledupdate();
      checkpos();
      checkwin();
    };
  }
}
void ledupdate() {
  for (int i = 0; i < MAXLED; i++) {
    if (i != ran) {
      led.setPixelColor(i, led.Color(0, 0, 0));
    }
  }
  ledupdatep1();
  ledupdatep2();
  ledupdatep3();
  ledupdatep4();
  coin();
  led.show();
}
void ledupdatep1() {
  for (int i = 100; i < 149; i++) {  //draw player 1

    if (i == 100 || i == 101||i==149||i==148) {
      led.setPixelColor(i + n1, led.Color(255, 0, 0));
    }
  }
}
void ledupdatep2() {
  for (int i = 100; i < 149; i++) {  //draw player 2

    if (i == 100 || i == 101||i==149||i==148) {
      led.setPixelColor(i + n2, led.Color(0, 255, 0));
    }
  }
}
void ledupdatep3() {
  for (int i = 100; i < 149; i++) {  //draw player 3

    if (i == 100 || i == 101||i==149||i==148) {
      led.setPixelColor(i + n3, led.Color(0, 0, 255));
    }
  }
}
void ledupdatep4() {
  for (int i = 100; i < 149; i++) {  //draw player 4

    if (i == 100 || i == 101||i==149||i==148) {
      led.setPixelColor(i + n4, led.Color(255, 255, 255));
    }
  }
}
void checkpos() {
  //PLAYER 1 Position
  if (analogRead(p1x) > 950)  //player 1 up
  {
    n1 = n1 + 48;
  }
  if (analogRead(p1x) < 300)  //player 1 down
  {
    n1 = n1 - 48;
  }
  if (analogRead(p1y) > 950)  //player 1 right
  {
    n1 = n1 - 1;
  }
  if (analogRead(p1y) < 300)  //player 1 left
  {
    n1 = n1 + 1;
  }

  //PLAYER 2 Position
  if (analogRead(p2x) > 950)  //player 2 up
  {
    n2 = n2 + 48;
  }
  if (analogRead(p2x) < 300)  //player 2 down
  {
    n2 = n2 - 48;
  }
  if (analogRead(p2y) > 950)  //player 2 right
  {
    n2 = n2 - 1;
  }
  if (analogRead(p2y) < 300)  //player 2 left
  {
    n2 = n2 + 1;
  }

  //PLAYER 3 Position
  if (analogRead(p3x) > 950)  //player 3 up
  {
    n3 = n3 + 48;
  }
  if (analogRead(p3x) < 300)  //player 3 down
  {
    n3 = n3 - 48;
  }
  if (analogRead(p3y) > 950)  //player 3 right
  {
    n3 = n3 - 1;
  }
  if (analogRead(p3y) < 300)  //player 3 left
  {
    n3 = n3 + 1;
  }

  //PLAYER 4 Position
  if (analogRead(p4x) > 950)  //player 4 up
  {
    n4 = n4 + 48;
  }
  if (analogRead(p4x) < 300)  //player 4 down
  {
    n4 = n4 - 48;
  }
  if (analogRead(p4y) > 950)  //player 4 right
  {
    n4 = n4 - 1;
  }
  if (analogRead(p4y) < 300)  //player 4 left
  {
    n4 = n4 + 1;
  }
}
void coin() {
  countcoin += 0.1;
  if (countcoin >= dotdelay) {  //add coin
    ran = (1+ rand()%2304);
    led.setPixelColor(ran, led.Color(255, 255, 0));
    countcoin = 0;
  }

 //player 1 check coin
    if (101 + n1 == ran || 100 + n1 == ran||149 + n1 == ran || 148 + n1 == ran) {
      score1++;
      Serial.println(score1);
      countcoin = dotdelay;
    }
  for (int i = 0; i < MAXLED; i++) {  //player 2 check coin
    if (101 + n2 == ran || 100 + n2 == ran||149 + n1 == ran || 148 + n1 == ran) {
      score2++;
      Serial.println(score2);
      countcoin = dotdelay;
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //player 3 check coin
    if (101 + n3 == ran || 100 + n3 == ran||149 + n1 == ran || 148 + n1 == ran) {
      score3++;
            Serial.println(score3);
      countcoin = dotdelay;
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //player 4 check coin
    if (101 + n4 == ran || 100 + n4 == ran||149 + n1 == ran || 148 + n1 == ran) {
      score4++;
            Serial.println(score4);
      countcoin = dotdelay;
    }
  }
}

void checkwin() {
  if (score1 >= 5) {  //player1 win screen
    for (int i = 0; i < MAXLED; i++) {
      led.setPixelColor(i, led.Color(255, 0, 0));
    }
    led.show();
    n1 = 0;
    n2 = 0;
    n3 = 0;
    n4 = 0;
    score1 = 0;
    delay(1000);
  }
  if (score2 >= 5) {  //player2 win screen
    for (int i = 0; i < MAXLED; i++) {
      led.setPixelColor(i, led.Color(0, 255, 0));
    }
    led.show();
    n1 = 0;
    n2 = 0;
    n3 = 0;
    n4 = 0;
    score1 = 0;
    delay(1000);
  }
  if (score3 >= 5) {  //player3 win screen
    for (int i = 0; i < MAXLED; i++) {
      led.setPixelColor(i, led.Color(0, 0, 255));
    }
    led.show();
    n1 = 0;
    n2 = 0;
    n3 = 0;
    n4 = 0;
    score1 = 0;
    delay(1000);
  }
  if (score4 >= 5) {  //player4 win screen
    for (int i = 0; i < MAXLED; i++) {
      led.setPixelColor(i, led.Color(255, 255, 255));
    }
    led.show();
     n1 = 0;
    n2 = 0;
    n3 = 0;
    n4 = 0;
    score1 = 0;
    delay(1000);
  }
}
