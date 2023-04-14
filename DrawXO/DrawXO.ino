#include <Adafruit_NeoPixel.h>
int MAXLEDS = 2051;
int LED_PIN = 6;
int num = 0;
Adafruit_NeoPixel led(MAXLEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
int XOB[] = {1375, 1327, 1279, 1231, 1183, 1135, 1087, 1039, 991, 943, 895, 847, 799, 1410, 1411, 1412, 1413, 1414, 1415, 1416, 1417, 1418, 1419, 1420, 1421, 1422, 1361, 1313, 1265, 1217, 1169, 1121, 1073, 1025, 977, 929, 881, 833, 785, 738, 739, 740, 741, 742, 743, 744, 745, 746, 747, 748, 749, 750};
int XOR[]= {1362, 1315, 1268, 1221, 1174, 1127, 1080, 1033, 986, 939, 892, 845, 798, 1129, 1178, 1227, 1276, 1325, 1374, 1031, 982, 933, 884, 835, 789};
void setup() {
led.begin();
led.show();
led.setBrightness(255);
}

void loop() {
drawxr();
num = 0;
drawob();
}
void drawob() {
  led.begin();
  for (int i = 0; i < sizeof(XOB) / sizeof(XOB[0]); i++) {
    num = XOB[i] - 1;
    led.setPixelColor(num, led.Color(0, 0, 255));
  }
  led.show();
}
void drawxr() {
  led.begin();
  for (int i = 0; i < sizeof(XOR) / sizeof(XOR[0]); i++) {
    num = XOR[i] - 1;
    led.setPixelColor(num, led.Color(255, 0, 0));
  }
  led.show();
}

