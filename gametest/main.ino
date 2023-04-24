#include <Adafruit_NeoPixel.h>
//GLOBALE VARIABLEN//

//HELLIGKEITS EINSTELLUNG GLOBAL//
int brght = 170;
//

//PIN-BELEGUNG SPIELER//
int player_one = 2;
int player_x_one = A3;
int player_y_one = A4;
int player_two = 3;
int player_x_two = A5;
int player_y_two = A6;
int player_three = 4;
int player_x_three = A7;
int player_y_three = A8;
int player_four = 5;
int player_x_four = A9;
int player_y_four = A10;
//PIN-BELEGUNG//
int LED_PIN = 6;
int PIN_AUDIO = 36;
//

//LAUFLICHT//
int n = 96;
//

//NUMMER DER LEDS UND TIMER FUNKTION FÜR STANDBY-MODUS//
int MAXLED = 2304;
int count = 0;
int long standby_Timer = 0;
int long st = 10000000000;  // gibt an wann der standby-Modus beginnt nicht zu groß machen!!
//

//VARIABLEN ZUR SPIEL AUSWAHL UND ZUM RESET//
int select = 1;
int select_input = 12;
int x_one;
int y_one;
int x_two;
int y_two;
int x_three;
int y_three;
int x_four;
int y_four;
//

//RACE GAME//
int TBEEP = 3;

int run = 0;

float speed1 = 0;
float speed2 = 0;
float speed3 = 0;
float speed4 = 0;
float dist1 = 0;
float dist2 = 0;
float dist3 = 0;
float dist4 = 0;

byte loop1 = 0;
byte loop2 = 0;
byte loop3 = 0;
byte loop4 = 0;

byte leader = 0;
byte loop_max = 5;  //Rundenanzahl

float ACEL = 100.0;
float kf = 0.3;

byte flag_sw1 = 0;
byte flag_sw2 = 0;
byte flag_sw3 = 0;
byte flag_sw4 = 0;
byte draworder = 0;

unsigned long timestamp = 0;
int tdelay = 5;
int race_win_delay = 1000;
//

//TIC TAC TOE//
int grid1 = 16;
int grid2 = 32;
int grid3 = 768;
int grid4 = 1536;

int select_beginner;
bool beginner;

int ttt_start = 0;

//PLAYER X //
bool a1_used1 = false;
bool a2_used1 = false;
bool a3_used1 = false;
bool b1_used1 = false;
bool b2_used1 = false;
bool b3_used1 = false;
bool c1_used1 = false;
bool c2_used1 = false;
bool c3_used1 = false;
//PLAYER O //
bool a1_used2 = false;
bool a2_used2 = false;
bool a3_used2 = false;
bool b1_used2 = false;
bool b2_used2 = false;
bool b3_used2 = false;
bool c1_used2 = false;
bool c2_used2 = false;
bool c3_used2 = false;

int ttt_x = A11;
int ttt_y = A12;

int status = 0;
int status_pressed = 1;

bool player_x_win = false;
bool player_o_win = false;
bool no_winner = false;
//

//COIN COLLECT//
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
float countcoin = 0;
int dotdelay = 10;
//



Adafruit_NeoPixel led(MAXLED, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  led.begin();
  for (int i = 0; i < MAXLED; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));
  }
  led.show();
  pinMode(player_one, INPUT_PULLUP);
  pinMode(player_x_one, INPUT_PULLUP);
  pinMode(player_y_one, INPUT_PULLUP);
  pinMode(player_two, INPUT_PULLUP);
  pinMode(player_x_two, INPUT_PULLUP);
  pinMode(player_y_two, INPUT_PULLUP);
  pinMode(player_three, INPUT_PULLUP);
  pinMode(player_x_three, INPUT_PULLUP);
  pinMode(player_y_three, INPUT_PULLUP);
  pinMode(player_four, INPUT_PULLUP);
  pinMode(player_x_four, INPUT_PULLUP);
  pinMode(player_y_four, INPUT_PULLUP);
  pinMode(select_input, INPUT_PULLUP);
  pinMode(ttt_x, INPUT_PULLUP);
  pinMode(ttt_y, INPUT_PULLUP);
  randomSeed(analogRead(0));
  led.setBrightness(brght);
}


//RUFT STANDBY BILDSCHIRM, SOWIE RESET UND DEN START BILDSCHIRM//
void start_program() {
  if (standby_Timer > st) {
    select = 0;
    runlight();
    reset();
  }
  if (select == 0 && standby_Timer < st) {
    start_screen();
    reset();
  }
}
//

//SPIELAUSWAHL UND ZURÜCK ZUM START BILDSCHIRM//
void reset() {
  int digital_input = digitalRead(select_input);
  if (digital_input == 0) {
    select = 0;
    standby_Timer = 0;
  }
  if (select == 0) {
    x_one = analogRead(player_x_one);
    y_one = analogRead(player_y_one);
    x_two = analogRead(player_x_two);
    y_two = analogRead(player_y_two);
    x_three = analogRead(player_x_three);
    y_three = analogRead(player_y_three);
    x_four = analogRead(player_x_four);
    y_four = analogRead(player_y_four);
    //RACE GAME//
    /* if (x_one < 150 || x_two < 150 || x_three < 150 || x_four < 150) {
      select = 1;
      standby_Timer = 0;
    }
    //TIC TAC TOE//
    if (x_one < 950 || x_two < 950 || x_three < 950 || x_four < 950) {
      select = 2;
      standby_Timer = 0;
    }
    //COIN COLLECT//
    if(y_one < 150 || y_two < 150 || y_three < 150 || y_four < 150){
      select = 3;
      standby_Timer = 0;
    }*/
  }
}
//

//ANIMATION START BILDSCHIRM//
void start_screen() {
  for (int i = 0; i < MAXLED; i++) {  //Home Rot
    if (i == 265 || i == 1338 || i == 1337 || i == 1336 || i == 1290 || i == 1289 || i == 1288 || i == 1242 || i == 1241 || i == 1240 || i == 1194 || i == 1193 || i == 1192 || i == 1287 || i == 1239 || i == 1238 || i == 1291 || i == 1243 || i == 1244 || i == 1892 || i == 1939 || i == 1941 || i == 1988 || i == 1033 || i == 1032 || i == 1031 || i == 985 || i == 984 || i == 983 || i == 937 || i == 936 || i == 935 || i == 889 || i == 888 || i == 887 || i == 841 || i == 840 || i == 839 || i == 793 || i == 792 || i == 791 || i == 744 || i == 696 || i == 648 || i == 1178 || i == 1177 || i == 1176 || i == 1175 || i == 1174 || i == 1130 || i == 1129 || i == 1128 || i == 1127 || i == 1126 || i == 1082 || i == 1081 || i == 1080 || i == 1079 || i == 1078 || i == 1271 || i == 1270 || i == 1223 || i == 1222 || i == 1274 || i == 1273 || i == 1226 || i == 1225 || i == 1323 || i == 1322 || i == 1318 || i == 1317 || i == 1269 || i == 1268 || i == 1267 || i == 1277 || i == 1276 || i == 1275 || i == 1233 || i == 1232 || i == 1231 || i == 1230 || i == 1229 || i == 1219 || i == 1218 || i == 1217 || i == 1216 || i == 1215 || i == 1184 || i == 1183 || i == 1135 || i == 1169 || i == 1168 || i == 1121 || i == 1329 || i == 1328 || i == 1376 || i == 1375 || i == 1374 || i == 1422 || i == 1421 || i == 1420 || i == 1419 || i == 1418 || i == 1417 || i == 1416 || i == 1415 || i == 1414 || i == 1413 || i == 1412 || i == 1411 || i == 1410 || i == 1362 || i == 1361 || i == 1360 || i == 1312 || i == 1311 || i == 1467 || i == 1466 || i == 1465 || i == 1464 || i == 1463 || i == 1462 || i == 1461) {
      led.setPixelColor(i - 1, led.Color(255, 0, 0));
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //Home Weiß
    if (i == 2134 || i == 2086 || i == 2138 || i == 2090 || i == 2044 || i == 2043 || i == 1852 || i == 1851 || i == 1798 || i == 1750 || i == 1802 || i == 1754 || i == 2042 || i == 1994 || i == 1946 || i == 1898 || i == 1850 || i == 1849 || i == 1848 || i == 1847 || i == 1846 || i == 2041 || i == 2040 || i == 2039 || i == 2038 || i == 1990 || i == 1942 || i == 1894 || i == 1147 || i == 1146 || i == 1145 || i == 1144 || i == 1143 || i == 1099 || i == 1098 || i == 1097 || i == 1096 || i == 1095 || i == 1051 || i == 1050 || i == 1049 || i == 1048 || i == 1047 || i == 1003 || i == 1002 || i == 1001 || i == 1000 || i == 999 || i == 955 || i == 954 || i == 953 || i == 952 || i == 951 || i == 1266 || i == 1265 || i == 1264 || i == 1263 || i == 1316 || i == 1315 || i == 1314 || i == 1313 || i == 1373 || i == 1372 || i == 1371 || i == 1370 || i == 1369 || i == 1368 || i == 1367 || i == 1366 || i == 1365 || i == 1364 || i == 1363 || i == 1321 || i == 1320 || i == 1319 || i == 1272 || i == 1224 || i == 1327 || i == 1326 || i == 1325 || i == 1324 || i == 1281 || i == 1280 || i == 1279 || i == 1278 || i == 2037 || i == 2036 || i == 1845 || i == 1844) {
      led.setPixelColor(i - 1, led.Color(brght * 0.5, brght * 0.5, brght * 0.5));
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //Home Blau
    if (i == 1993 || i == 1991 || i == 1944 || i == 1897 || i == 1895 || i == 354 || i == 306 || i == 1161 || i == 1160 || i == 1159 || i == 1158 || i == 1157 || i == 1156 || i == 1155 || i == 1208 || i == 1207 || i == 1206 || i == 1205 || i == 1204 || i == 1255 || i == 1254 || i == 1253 || i == 1302) {
      led.setPixelColor(i - 1, led.Color(0, 0, 255));
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //Home räder auto
    if (i == 163 || i == 162 || i == 115 || i == 114 || i == 167 || i == 119 || i == 166 || i == 118) {
      led.setPixelColor(i - 1, led.Color(brght, brght, brght));
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //Home Gelb
    if (i == 257 || i == 1109 || i == 1108 || i == 1061 || i == 1060 || i == 1013 || i == 1012 || i == 965 || i == 964 || i == 917 || i == 916 || i == 1112 || i == 1111 || i == 1064 || i == 1063 || i == 1016 || i == 1015 || i == 968 || i == 967 || i == 920 || i == 919 || i == 1110 || i == 918) {
      led.setPixelColor(i - 1, led.Color(255, 255, 0));
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //Home Grün
    if (i == 359 || i == 358 || i == 357 || i == 356 || i == 355 || i == 311 || i == 310 || i == 309 || i == 308 || i == 307 || i == 263 || i == 262 || i == 261 || i == 260 || i == 259 || i == 215 || i == 214 || i == 213 || i == 212 || i == 211 || i == 312 || i == 264 || i == 216 || i == 217 || i == 258 || i == 210 || i == 209) {
      led.setPixelColor(i - 1, led.Color(0, 255, 0));
    }
  }
  for (int i = 0; i < MAXLED; i++) {  //Home strasse weiß
    if (i == 79 || i == 78 || i == 77 || i == 76 || i == 75 || i == 74 || i == 73 || i == 72 || i == 71 || i == 70 || i == 69 || i == 68 || i == 67 || i == 66 || i == 65 || i == 64 || i == 63 || i == 62 || i == 61) {
      led.setPixelColor(i - 1, led.Color(255, 255, 255));
    }
  }
  while (count < 1) {
    for (int i = 62; i <= 79; i++) {  //Home strasse Schwarz
      if (i == 79 || i == 78 || i == 77 || i == 76 || i == 75 || i == 74 || i == 73 || i == 72 || i == 71 || i == 70 || i == 69 || i == 68 || i == 67 || i == 66 || i == 65 || i == 64 || i == 63 || i == 62 || i == 61) {
        led.setPixelColor(i - 1, led.Color(0, 0, 0));
        led.setPixelColor(i - 3, led.Color(0, 0, 0));
        led.setPixelColor(i - 5, led.Color(0, 0, 0));
        led.setPixelColor(i - 7, led.Color(0, 0, 0));
        led.setPixelColor(i - 9, led.Color(0, 0, 0));
        led.setPixelColor(i - 11, led.Color(0, 0, 0));
        led.show();
        led.setPixelColor(i - 1, led.Color(255, 255, 255));
        led.setPixelColor(i - 3, led.Color(255, 255, 255));
        led.setPixelColor(i - 5, led.Color(255, 255, 255));
        led.setPixelColor(i - 7, led.Color(255, 255, 255));
        led.setPixelColor(i - 9, led.Color(255, 255, 255));
        led.setPixelColor(i - 11, led.Color(255, 255, 255));
        led.fill(led.Color(0, 0, 0), 48, 12);
        led.show();
      }
    }
    count++;
  }
}
//

//STANDBY-MODUS LAUFLICHT//
void runlight() {
  for (int i = 0; i < MAXLED; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));
  }
  for (int i = 0; i < MAXLED; i++) {
    led.setPixelColor(i, led.Color(brght * 0.2, brght * 0.2, brght * 0.2));
  }
  for (int i = 0; i < MAXLED; i++) {
    if (i == 1773 || i == 1772 || i == 1771 || i == 1770 || i == 1769 || i == 1768 || i == 1767 || i == 1766 || i == 1725 || i == 1724 || i == 1723 || i == 1722 || i == 1721 || i == 1720 || i == 1719 || i == 1718 || i == 1674 || i == 1673 || i == 1626 || i == 1625 || i == 1578 || i == 1577 || i == 1530 || i == 1529 || i == 1482 || i == 1481 || i == 1434 || i == 1433 || i == 1386 || i == 1385 || i == 1338 || i == 1337 || i == 1290 || i == 1289 || i == 1242 || i == 1241 || i == 1194 || i == 1193 || i == 1146 || i == 1145 || i == 1098 || i == 1097 || i == 1050 || i == 1049 || i == 1002 || i == 1001 || i == 954 || i == 953 || i == 1763 || i == 1762 || i == 1715 || i == 1714 || i == 1667 || i == 1666 || i == 1619 || i == 1618 || i == 1571 || i == 1570 || i == 1523 || i == 1522 || i == 1475 || i == 1474 || i == 1427 || i == 1426 || i == 1379 || i == 1378 || i == 1331 || i == 1330 || i == 1283 || i == 1282 || i == 1235 || i == 1234 || i == 1187 || i == 1186 || i == 1139 || i == 1138 || i == 1091 || i == 1090 || i == 1043 || i == 1042 || i == 995 || i == 994 || i == 947 || i == 946 || i == 1761 || i == 1760 || i == 1759 || i == 1713 || i == 1712 || i == 1711 || i == 1377 || i == 1376 || i == 1375 || i == 1329 || i == 1328 || i == 1327 || i == 993 || i == 992 || i == 991 || i == 945 || i == 944 || i == 943 || i == 1660 || i == 1659 || i == 1612 || i == 1611 || i == 1564 || i == 1563 || i == 1516 || i == 1515 || i == 1468 || i == 1467 || i == 1420 || i == 1419 || i == 1273 || i == 1272 || i == 1225 || i == 1224 || i == 1177 || i == 1176 || i == 1129 || i == 1128 || i == 1081 || i == 1080 || i == 1033 || i == 1032 || i == 988 || i == 987 || i == 986 || i == 985 || i == 984 || i == 940 || i == 939 || i == 938 || i == 937 || i == 936 || i == 1372 || i == 1371 || i == 1370 || i == 1369 || i == 1368 || i == 1324 || i == 1323 || i == 1322 || i == 1321 || i == 1320 || i == 1756 || i == 1755 || i == 1754 || i == 1753 || i == 1752 || i == 1708 || i == 1707 || i == 1706 || i == 1705 || i == 1704 || i == 1749 || i == 1748 || i == 1701 || i == 1700 || i == 1653 || i == 1652 || i == 1605 || i == 1604 || i == 1557 || i == 1556 || i == 1509 || i == 1508 || i == 1461 || i == 1460 || i == 1413 || i == 1412 || i == 1365 || i == 1364 || i == 1317 || i == 1316 || i == 1269 || i == 1268 || i == 1221 || i == 1220 || i == 1173 || i == 1172 || i == 1125 || i == 1124 || i == 1077 || i == 1076 || i == 1029 || i == 1028 || i == 981 || i == 980 || i == 933 || i == 932 || i == 979 || i == 978 || i == 977 || i == 931 || i == 930 || i == 929 || i == 1742 || i == 1741 || i == 1694 || i == 1693 || i == 1646 || i == 1645 || i == 1598 || i == 1597 || i == 1550 || i == 1549 || i == 1502 || i == 1501 || i == 1454 || i == 1453 || i == 1406 || i == 1405 || i == 1358 || i == 1357 || i == 1310 || i == 1309 || i == 1262 || i == 1261 || i == 1214 || i == 1213 || i == 1166 || i == 1165 || i == 1118 || i == 1117 || i == 1070 || i == 1069 || i == 1022 || i == 1021 || i == 974 || i == 973 || i == 926 || i == 925 || i == 1736 || i == 1735 || i == 1688 || i == 1687 || i == 1640 || i == 1639 || i == 1592 || i == 1591 || i == 1544 || i == 1543 || i == 1496 || i == 1495 || i == 1448 || i == 1447 || i == 1400 || i == 1399 || i == 1352 || i == 1351 || i == 1304 || i == 1303 || i == 1256 || i == 1255 || i == 1208 || i == 1207 || i == 1160 || i == 1159 || i == 1112 || i == 1111 || i == 1064 || i == 1063 || i == 1016 || i == 1015 || i == 968 || i == 967 || i == 920 || i == 919 || i == 1740 || i == 1739 || i == 1738 || i == 1737 || i == 1692 || i == 1691 || i == 1690 || i == 1689 || i == 1356 || i == 1355 || i == 1354 || i == 1353 || i == 1308 || i == 1307 || i == 1306 || i == 1305) {
      led.setPixelColor(i - n, led.Color(255, 0, 0));
    }
  }
  n--;
  led.show();
  if (n <= 0) {
    n = 96;
  }
}
//


//RACE GAME FUNKTIONEN//
void draw_car1(void) {
  for (int i = 0; i <= loop1; i++) {
    led.setPixelColor(((word)dist1 % MAXLED) + i, led.Color(255 - i * 20, 0, 0));
  }
}
void draw_car2(void) {
  for (int i = 0; i <= loop2; i++) {
    led.setPixelColor(((word)dist2 % MAXLED) + i, led.Color(0, 255 - i * 20, 0));
  }
}
void draw_car3(void) {
  for (int i = 0; i <= loop1; i++) {
    led.setPixelColor(((word)dist3 % MAXLED) + i, led.Color(0, 0, 255 - i * 20));
  }
}
void draw_car4(void) {
  for (int i = 0; i <= loop2; i++) {
    led.setPixelColor(((word)dist4 % MAXLED) + i, led.Color(255 - i * 20, 255, 255));
  }
}
//

//TIC TAC TOE FUNKTIONEN
void check_win() {
  //PLAYER X
  if (a1_used1 && a2_used1 && a3_used1) {
    player_x_win = true;
  }
  if (b1_used1 && b2_used1 && b3_used1) {
    player_x_win = true;
  }
  if (c1_used1 && c2_used1 && c3_used1) {
    player_x_win = true;
  }
  if (a1_used1 && b1_used1 && c1_used1) {
    player_x_win = true;
  }
  if (a2_used1 && b2_used1 && c2_used1) {
    player_x_win = true;
  }
  if (a3_used1 && b3_used1 && c3_used1) {
    player_x_win = true;
  }
  if (a1_used1 && b2_used1 && c3_used1) {
    player_x_win = true;
  }
  if (a3_used1 && b2_used1 && c1_used1) {
    player_x_win = true;
  }
  //PLAYER O
  if (a1_used2 && a2_used2 && a3_used2) {
    player_o_win = true;
  }
  if (b1_used2 && b2_used2 && b3_used2) {
    player_o_win = true;
  }
  if (c1_used2 && c2_used2 && c3_used2) {
    player_o_win = true;
  }
  if (a1_used2 && b1_used2 && c1_used2) {
    player_o_win = true;
  }
  if (a2_used2 && b2_used2 && c2_used2) {
    player_o_win = true;
  }
  if (a3_used2 && b3_used2 && c3_used2) {
    player_o_win = true;
  }
  if (a1_used2 && b2_used2 && c3_used2) {
    player_o_win = true;
  }
  if (a3_used2 && b2_used2 && c1_used2) {
    player_o_win = true;
  }
}
void select_field() {
  int x_achse = analogRead(ttt_x);
  int y_achse = analogRead(ttt_y);
  if (x_achse <= 540 && x_achse >= 520 && y_achse <= 550 && y_achse >= 525) {
    status = 1;
  } else if (x_achse > 540 && x_achse <= 800 || x_achse < 520 && x_achse >= 300 || y_achse > 550 && y_achse <= 800 || y_achse < 525 && y_achse >= 300) {
    status = 0;
  } else if (x_achse >= 950 && y_achse >= 525 && y_achse <= 550) {
    status = 2;
  } else if (x_achse < 950 && x_achse > 540 && (y_achse < 950 && y_achse > 550 || y_achse < 520 && y_achse >= 300)) {
    status = 0;
  } else if (x_achse >= 950 && y_achse <= 100) {
    status = 3;
  } else if (x_achse < 950 && x_achse > 540 && y_achse > 100 && y_achse < 525) {
    status = 0;
  } else if (x_achse >= 950 && y_achse >= 950) {
    status = 4;
  } else if (x_achse < 950 && x_achse > 540 && y_achse < 950 && y_achse > 550) {
    status = 0;
  } else if (x_achse >= 520 && x_achse <= 540 && y_achse <= 100) {
    status = 5;
  } else if ((x_achse > 540 && x_achse <= 800 || x_achse < 520 && x_achse >= 300) && y_achse > 100 && y_achse < 525) {
    status = 0;
  } else if (x_achse >= 520 && x_achse <= 540 && y_achse >= 950) {
    status = 6;
  } else if ((x_achse > 540 && x_achse <= 800 || x_achse < 520 && x_achse >= 300) && y_achse < 950 && y_achse > 550) {
    status = 0;
  } else if (x_achse <= 100 && y_achse <= 550 && y_achse >= 525) {
    status = 7;
  } else if (x_achse > 100 && x_achse < 520 && (y_achse > 550 && y_achse <= 800 || y_achse < 525 && y_achse >= 300)) {
    status = 0;
  } else if (x_achse <= 100 && y_achse <= 100) {
    status = 8;
  } else if (x_achse > 100 && x_achse < 520 && y_achse > 100 && y_achse < 525) {
    status = 0;
  } else if (x_achse <= 100 && y_achse >= 950) {
    status = 9;
  } else if (x_achse > 100 && x_achse < 520 && y_achse < 950 && y_achse > 550) {
    status = 0;
  }
}
void draw_grid() {
  if (status == 0) {
    for (int i = 0; i < MAXLED; i++) {
      led.setPixelColor(i, led.Color(0, 0, 0));
    }
  }
  for (int i = 16; i < MAXLED; i += 48) {
    led.setPixelColor(i, led.Color(255, 255, 255));
  }
  for (int i = 32; i < MAXLED; i += 48) {
    led.setPixelColor(i, led.Color(255, 255, 255));
  }
  for (int i = 768; i < 815; i++) {
    led.setPixelColor(i, led.Color(255, 255, 255));
  }
  for (int i = 1536; i < 1583; i++) {
    led.setPixelColor(i, led.Color(255, 255, 255));
  }

  if (a1_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 2303 || i == 2254 || i == 2205 || i == 2156 || i == 2107 || i == 2058 || i == 2009 || i == 1960 || i == 1911 || i == 1862 || i == 1813 || i == 1764 || i == 1715 || i == 1666 || i == 1617 || i == 2007 || i == 2054 || i == 2101 || i == 2148 || i == 2195 || i == 2242 || i == 2289 || i == 1913 || i == 1866 || i == 1819 || i == 1772 || i == 1725 || i == 1678 || i == 1631) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (a2_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 1535 || i == 1486 || i == 1437 || i == 1388 || i == 1339 || i == 1290 || i == 1241 || i == 1192 || i == 1143 || i == 1094 || i == 1045 || i == 996 || i == 947 || i == 898 || i == 849 || i == 1239 || i == 1286 || i == 1333 || i == 1380 || i == 1427 || i == 1474 || i == 1521 || i == 1145 || i == 1098 || i == 1051 || i == 1004 || i == 957 || i == 910 || i == 863) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (a3_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 767 || i == 718 || i == 669 || i == 620 || i == 571 || i == 522 || i == 473 || i == 424 || i == 375 || i == 326 || i == 277 || i == 228 || i == 179 || i == 130 || i == 81 || i == 471 || i == 518 || i == 565 || i == 612 || i == 659 || i == 706 || i == 753 || i == 377 || i == 330 || i == 283 || i == 236 || i == 189 || i == 142 || i == 95) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (b1_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 2287 || i == 2238 || i == 2189 || i == 2140 || i == 2091 || i == 2042 || i == 1993 || i == 1944 | i == 1895 || i == 1846 || i == 1797 || i == 1748 || i == 1699 || i == 1650 || i == 1991 || i == 2038 || i == 2085 || i == 2132 || i == 2179 || i == 2226 || i == 2273 || i == 1897 || i == 1850 || i == 1803 || i == 1756 || i == 1709 || i == 1662 || i == 1615) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (b2_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 1519 || i == 1470 || i == 1421 || i == 1372 || i == 1323 || i == 1274 || i == 1225 || i == 1176 || i == 1127 || i == 1078 || i == 1029 || i == 980 || i == 931 || i == 882 || i == 833 || i == 1223 || i == 1270 || i == 1317 || i == 1364 || i == 1411 || i == 1458 || i == 1505 || i == 1129 || i == 1082 || i == 1035 || i == 988 || i == 941 || i == 894 || i == 847) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (b3_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 751 || i == 702 || i == 653 || i == 604 || i == 555 || i == 506 || i == 457 || i == 408 || i == 359 || i == 310 || i == 261 || i == 212 || i == 163 || i == 114 || i == 65 || i == 455 || i == 502 || i == 549 || i == 596 || i == 643 || i == 690 || i == 737 || i == 361 || i == 314 || i == 267 || i == 220 || i == 173 || i == 126 || i == 79) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (c1_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 2271 || i == 2222 || i == 2173 || i == 2124 || i == 2075 || i == 2026 || i == 1977 || i == 1928 || i == 1879 || i == 1830 || i == 1781 || i == 1732 || i == 1683 || i == 1634 || i == 1975 || i == 2022 || i == 2069 || i == 2116 || i == 2163 || i == 2210 || i == 2257 || i == 1881 || i == 1834 || i == 1787 || i == 1740 || i == 1693 || i == 1646 || i == 1599) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (c2_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 1503 || i == 1454 || i == 1405 || i == 1356 || i == 1307 || i == 1258 || i == 1209 || i == 1160 || i == 1111 || i == 1062 || i == 1013 || i == 964 || i == 915 || i == 866 || i == 817 || i == 1207 || i == 1254 || i == 1301 || i == 1348 || i == 1395 || i == 1442 || i == 1489 || i == 1113 || i == 1066 || i == 1019 || i == 972 || i == 925 || i == 878 || i == 831) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (c3_used1) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 735 || i == 686 || i == 637 || i == 588 || i == 539 || i == 490 || i == 441 || i == 392 || i == 343 || i == 294 || i == 245 || i == 196 || i == 147 || i == 98 || i == 49 || i == 439 || i == 486 || i == 533 || i == 580 || i == 627 || i == 674 || i == 721 || i == 345 || i == 298 || i == 251 || i == 204 || i == 157 || i == 110 || i == 63) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (a1_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 2194 ||i == 2146 ||i == 2098 ||i == 2050 ||i == 2002 ||i == 1954 ||i == 1906 ||i == 1858 ||i == 1810 ||i == 1762 ||i == 1714 ||i == 2253 || i == 2252 || i == 2251 || i == 2250 || i == 2249 || i == 2248 || i == 2247 || i == 2246 || i == 2245 || i == 2244 || i == 2243 ||i == 2206 ||i == 2158 ||i == 2110 ||i == 2062 ||i == 2014 ||i == 1966 ||i == 1918 ||i == 1870 ||i == 1822 ||i == 1774 ||i == 1726 ||i == 1677 || i == 1676 || i == 1675 || i == 1674 || i == 1673 || i == 1672 || i == 1671 || i == 1670 || i == 1669 || i == 1668 || i == 1667) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (a2_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 1426 ||i == 1378 ||i == 1330 ||i == 1282 ||i == 1234 ||i == 1186 ||i == 1138 ||i == 1090 ||i == 1042 ||i == 994 ||i == 946 ||i == 898 ||i == 1485 || i == 1484 || i == 1483 || i == 1482 || i == 1481 || i == 1480 || i == 1479 || i == 1478 || i == 1477 || i == 1476 || i == 1475 ||i == 1438 ||i == 1390 ||i == 1342 ||i == 1294 ||i == 1246 ||i == 1198 ||i == 1150 ||i == 1102 ||i == 1054 ||i == 1006 ||i == 958 ||i == 909 || i == 908 || i == 907 || i == 906 || i == 905 || i == 904 || i == 903 || i == 902 || i == 901 || i == 900 || i == 899) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (a3_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 658 ||i == 610 ||i == 562 ||i == 514 ||i == 466 ||i == 418 ||i == 370 ||i == 322 ||i == 274 ||i == 226 ||i == 178 ||i == 717 || i == 716 || i == 715 || i == 714 || i == 713 || i == 712 || i == 711 || i == 710 || i == 709 || i == 708 || i == 707 ||i == 670 ||i == 622 ||i == 574 ||i == 526 ||i == 478 ||i == 430 ||i == 382 ||i == 334 ||i == 286 ||i == 238 ||i == 190 ||i == 141 || i == 140 || i == 139 || i == 138 || i == 137 || i == 136 || i == 135 || i == 134 || i == 133 || i == 132 || i == 131) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (b1_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 2178 ||i == 2130 ||i == 2082 ||i == 2034 ||i == 1986 ||i == 1938 ||i == 1890 ||i == 1842 ||i == 1794 ||i == 1746 ||i == 1698 ||i == 2237 || i == 2236 || i == 2235 || i == 2234 || i == 2233 || i == 2232 || i == 2231 || i == 2230 || i == 2229 || i == 2228 || i == 2227 ||i == 2190 ||i == 2142 ||i == 2094 ||i == 2046 ||i == 1998 ||i == 1950 ||i == 1902 ||i == 1854 ||i == 1806 ||i == 1758 ||i == 1710 ||i == 1661 || i == 1660 || i == 1659 || i == 1658 || i == 1657 || i == 1656 || i == 1655 || i == 1654 || i == 1653 || i == 1652 || i == 1651) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (b2_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 1410 ||i == 1362 ||i == 1314 ||i == 1266 ||i == 1218 ||i == 1170 ||i == 1122 ||i == 1074 ||i == 1026 ||i == 978 ||i == 930 ||i == 882 ||i == 1469 || i == 1468 || i == 1467 || i == 1466 || i == 1465 || i == 1464 || i == 1463 || i == 1462 || i == 1461 || i == 1460 || i == 1459 ||i == 1422 ||i == 1374 ||i == 1326 ||i == 1278 ||i == 1230 ||i == 1182 ||i == 1134 ||i == 1086 ||i == 1038 ||i == 990 ||i == 942 ||i == 893 || i == 892 || i == 891 || i == 890 || i == 889 || i == 888 || i == 887 || i == 886 || i == 885 || i == 884 || i == 883) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (b3_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 642 ||i == 594 ||i == 546 ||i == 498 ||i == 450 ||i == 402 ||i == 354 ||i == 306 ||i == 258 ||i == 210 ||i == 162 ||i == 701 || i == 700 || i == 699 || i == 698 || i == 697 || i == 696 || i == 695 || i == 694 || i == 693 || i == 692 || i == 691 ||i == 654 ||i == 606 ||i == 558 ||i == 510 ||i == 462 ||i == 414 ||i == 366 ||i == 318 ||i == 270 ||i == 222 ||i == 174 ||i == 125 || i == 124 || i == 123 || i == 122 || i == 121 || i == 120 || i == 119 || i == 118 || i == 117 || i == 116 || i == 115) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (c1_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 2162 ||i == 2114 ||i == 2066 ||i == 2018 ||i == 1970 ||i == 1922 ||i == 1874 ||i == 1826 ||i == 1778 ||i == 1730 ||i == 2219 || i == 2218 || i == 2217 || i == 2216 || i == 2215 || i == 2214 || i == 2213 || i == 2212 || i == 2211 || i == 2210 || i == 2209 ||i == 2174 ||i == 2126 ||i == 2078 ||i == 2030 ||i == 1982 ||i == 1934 ||i == 1886 ||i == 1838 ||i == 1790 ||i == 1742 ||i == 1694 ||i == 1645 || i == 1644 || i == 1643 || i == 1642 || i == 1641 || i == 1640 || i == 1639 || i == 1638 || i == 1637 || i == 1636 || i == 1635) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (c2_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 1394 ||i == 1346 ||i == 1298 ||i == 1250 ||i == 1202 ||i == 1154 ||i == 1106 ||i == 1058 ||i == 1010 ||i == 962 ||i == 914 ||i == 866 ||i == 1453 || i == 1452 || i == 1451 || i == 1450 || i == 1449 || i == 1448 || i == 1447 || i == 1446 || i == 1445 || i == 1444 || i == 1443 ||i == 1406 ||i == 1358 ||i == 1310 ||i == 1262 ||i == 1214 ||i == 1166 ||i == 1118 ||i == 1070 ||i == 1022 ||i == 974 ||i == 926 ||i == 877 || i == 876 || i == 875 || i == 874 || i == 873 || i == 872 || i == 871 || i == 870 || i == 869 || i == 868 || i == 867) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  if (c3_used2) {
    for (int i = 0; i < MAXLED; i++) {
      if (i == 626 ||i == 578 ||i == 530 ||i == 482 ||i == 434 ||i == 386 ||i == 338 ||i == 290 ||i == 242 ||i == 194 ||i == 146 ||i == 685 || i == 684 || i == 683 || i == 682 || i == 681 || i == 680 || i == 679 || i == 678 || i == 677 || i == 676 || i == 675 ||i == 638 ||i == 590 ||i == 542 ||i == 494 ||i == 446 ||i == 398 ||i == 350 ||i == 302 ||i == 254 ||i == 206 ||i == 158 ||i == 109 || i == 108 || i == 107 || i == 106 || i == 105 || i == 104 || i == 103 || i == 102 || i == 101 || i == 100 || i == 99) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
    }
  }
  led.show();
}

//
void game_ONE_LED_RACE() {
  if (select == 1) {
    if (digitalRead(12) == 0) {
      select == 4;
    }
    if (run == 0) {
      for (int i = 0; i < MAXLED; i++) {
        led.setPixelColor(i, led.Color(0, 0, 0));
      }
      led.show();
      delay(2000);
      for (int i = 0; i < MAXLED; i++) {
        led.setPixelColor(i, led.Color(255, 0, 0));
      }
      led.show();
      tone(PIN_AUDIO, 400);
      delay(2000);
      noTone(PIN_AUDIO);
      for (int i = 0; i < MAXLED; i++) {
        led.setPixelColor(i, led.Color(255, 255, 0));
      }
      led.show();
      tone(PIN_AUDIO, 600);
      delay(2000);
      noTone(PIN_AUDIO);
      for (int i = 0; i < MAXLED; i++) {
        led.setPixelColor(i, led.Color(0, 255, 0));
      }
      led.show();
      tone(PIN_AUDIO, 1200);
      delay(2000);
      noTone(PIN_AUDIO);
      timestamp = 0;

      run = 1;
    }
    if (run == 1) {
      for (int i = 0; i < MAXLED; i++) {
        led.setPixelColor(i, led.Color(0, 0, 0));
      }
      if ((flag_sw1 == 1) && (digitalRead(player_one) == 1)) {
        standby_Timer = 0;
        flag_sw1 = 0;
        speed1 += ACEL;
      }
      if ((flag_sw1 == 0) && (digitalRead(player_one) == 0)) {
        flag_sw1 = 1;
      }
      speed1 -= speed1 * kf;

      if ((flag_sw2 == 1) && (digitalRead(player_two) == 1)) {
        standby_Timer = 0;
        flag_sw2 = 0;
        speed2 += ACEL;
      }
      if ((flag_sw2 == 0) && (digitalRead(player_two) == 0)) {
        flag_sw2 = 1;
      }
      speed2 -= speed2 * kf;

      if ((flag_sw3 == 1) && (digitalRead(player_three) == 1)) {
        standby_Timer = 0;
        flag_sw3 = 0;
        speed3 += ACEL;
      }
      if ((flag_sw3 == 0) && (digitalRead(player_three) == 0)) {
        flag_sw3 = 1;
      }
      speed3 -= speed3 * kf;

      if ((flag_sw4 == 1) && (digitalRead(player_four) == 1)) {
        standby_Timer = 0;
        flag_sw4 = 0;
        speed4 += ACEL;
      }
      if ((flag_sw4 == 0) && (digitalRead(player_four) == 0)) {
        flag_sw4 = 1;
      }
      speed4 -= speed4 * kf;

      dist1 += speed1;
      dist2 += speed2;
      dist3 += speed3;
      dist4 += speed4;

      if (dist1 > dist2 && dist1 > dist3 && dist1 > dist4) {
        leader = 1;
      }
      if (dist2 > dist1 && dist2 > dist3 && dist2 > dist4) {
        leader = 2;
      }
      if (dist3 > dist1 && dist3 > dist2 && dist3 > dist4) {
        leader = 3;
      }
      if (dist4 > dist1 && dist4 > dist2 && dist4 > dist3) {
        leader = 4;
      }

      if (dist1 > MAXLED * loop1) {
        loop1++;
        tone(PIN_AUDIO, 600);
        TBEEP = 2;
      }
      if (dist2 > MAXLED * loop2) {
        loop2++;
        tone(PIN_AUDIO, 700);
        TBEEP = 2;
      }
      if (dist3 > MAXLED * loop3) {
        loop3++;
        tone(PIN_AUDIO, 800);
        TBEEP = 2;
      }
      if (dist4 > MAXLED * loop4) {
        loop4++;
        tone(PIN_AUDIO, 900);
        TBEEP = 2;
      }

      if (loop1 > loop_max) {
        for (int i = 0; i < MAXLED; i++) {
          led.setPixelColor(i, led.Color(255, 0, 0));
        }
        led.show();
        loop1 = 0;
        loop2 = 0;
        loop3 = 0;
        loop4 = 0;
        dist1 = 0;
        dist2 = 0;
        dist3 = 0;
        dist4 = 0;
        speed1 = 0;
        speed2 = 0;
        speed3 = 0;
        speed4 = 0;
        run = 0;
        timestamp = 0;
        delay(race_win_delay);
      }

      if (loop2 > loop_max) {
        for (int i = 0; i < MAXLED; i++) {
          led.setPixelColor(i, led.Color(0, 255, 0));
        }
        led.show();
        loop1 = 0;
        loop2 = 0;
        loop3 = 0;
        loop4 = 0;
        dist1 = 0;
        dist2 = 0;
        dist3 = 0;
        dist4 = 0;
        speed1 = 0;
        speed2 = 0;
        speed3 = 0;
        speed4 = 0;
        run = 0;
        timestamp = 0;
        delay(race_win_delay);
      }

      if (loop3 > loop_max) {
        for (int i = 0; i < MAXLED; i++) {
          led.setPixelColor(i, led.Color(0, 0, 255));
        }
        led.show();
        loop1 = 0;
        loop2 = 0;
        loop3 = 0;
        loop4 = 0;
        dist1 = 0;
        dist2 = 0;
        dist3 = 0;
        dist4 = 0;
        speed1 = 0;
        speed2 = 0;
        speed3 = 0;
        speed4 = 0;
        run = 0;
        timestamp = 0;
        delay(race_win_delay);
      }

      if (loop4 > loop_max) {
        for (int i = 0; i < MAXLED; i++) {
          led.setPixelColor(i, led.Color(255, 255, 255));
        }
        led.show();
        loop1 = 0;
        loop2 = 0;
        loop3 = 0;
        loop4 = 0;
        dist1 = 0;
        dist2 = 0;
        dist3 = 0;
        dist4 = 0;
        speed1 = 0;
        speed2 = 0;
        speed3 = 0;
        speed4 = 0;
        run = 0;
        timestamp = 0;
        delay(race_win_delay);
      }

      if ((millis() & 512) == (512 * draworder)) {
        if (draworder == 0) {
          draworder = 1;
        } else {
          draworder = 0;
        }
      }

      if (draworder == 0) {
        draw_car1();
        draw_car2();
        draw_car3();
        draw_car4();
      } else {
        draw_car4();
        draw_car3();
        draw_car2();
        draw_car1();
      }
      led.show();
      delay(tdelay);

      if (TBEEP > 0) {
        TBEEP -= 1;
        if (TBEEP == 0) {
          noTone(PIN_AUDIO);
        }
      }
    }
  }
}
//
void game_TWO_TIC_TAC_TOE() {
  if (select == 2) {
    if (ttt_start == 0) {
      draw_grid();
      select_beginner = random(10);
      if (select_beginner <= 5) {
        beginner = false;
      }
      if (select_beginner >= 6) {
        beginner = true;
      }
      ttt_start = 1;
      beginner = false;
    }
    if (ttt_start == 1) {
      draw_grid();
      select_field();
      Serial.println(c3_used1);
      if (!beginner) {
        status_pressed = digitalRead(player_one);
        check_win();
        if (status == 1) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 1519 || i == 1470 || i == 1421 || i == 1372 || i == 1323 || i == 1274 || i == 1225 || i == 1176 || i == 1127 || i == 1078 || i == 1029 || i == 980 || i == 931 || i == 882 || i == 833 || i == 1223 || i == 1270 || i == 1317 || i == 1364 || i == 1411 || i == 1458 || i == 1505 || i == 1129 || i == 1082 || i == 1035 || i == 988 || i == 941 || i == 894 || i == 847) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !b2_used1 && !b2_used2) {
            b2_used1 = true;
            beginner = true;
          }
        }
        if (status == 2) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 1535 || i == 1486 || i == 1437 || i == 1388 || i == 1339 || i == 1290 || i == 1241 || i == 1192 || i == 1143 || i == 1094 || i == 1045 || i == 996 || i == 947 || i == 898 || i == 849 || i == 1239 || i == 1286 || i == 1333 || i == 1380 || i == 1427 || i == 1474 || i == 1521 || i == 1145 || i == 1098 || i == 1051 || i == 1004 || i == 957 || i == 910 || i == 863) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !a2_used1 && !a2_used2) {
            a2_used1 = true;
            beginner = true;
          }
        }
        if (status == 3) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 767 || i == 718 || i == 669 || i == 620 || i == 571 || i == 522 || i == 473 || i == 424 || i == 375 || i == 326 || i == 277 || i == 228 || i == 179 || i == 130 || i == 81 || i == 471 || i == 518 || i == 565 || i == 612 || i == 659 || i == 706 || i == 753 || i == 377 || i == 330 || i == 283 || i == 236 || i == 189 || i == 142 || i == 95) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !a3_used1 && !a3_used2) {
            a3_used1 = true;
            beginner = true;
          }
        }
        if (status == 4) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 2303 || i == 2254 || i == 2205 || i == 2156 || i == 2107 || i == 2058 || i == 2009 || i == 1960 || i == 1911 || i == 1862 || i == 1813 || i == 1764 || i == 1715 || i == 1666 || i == 1617 || i == 2007 || i == 2054 || i == 2101 || i == 2148 || i == 2195 || i == 2242 || i == 2289 || i == 1913 || i == 1866 || i == 1819 || i == 1772 || i == 1725 || i == 1678 || i == 1631) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !a1_used1 && !a1_used2) {
            a1_used1 = true;
            beginner = true;
          }
        }
        if (status == 5) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 751 || i == 702 || i == 653 || i == 604 || i == 555 || i == 506 || i == 457 || i == 408 || i == 359 || i == 310 || i == 261 || i == 212 || i == 163 || i == 114 || i == 65 || i == 455 || i == 502 || i == 549 || i == 596 || i == 643 || i == 690 || i == 737 || i == 361 || i == 314 || i == 267 || i == 220 || i == 173 || i == 126 || i == 79) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !b3_used1 && !b3_used2) {
            b3_used1 = true;
            beginner = true;
          }
        }
        if (status == 6) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 2287 || i == 2238 || i == 2189 || i == 2140 || i == 2091 || i == 2042 || i == 1993 || i == 1944 | i == 1895 || i == 1846 || i == 1797 || i == 1748 || i == 1699 || i == 1650 || i == 1991 || i == 2038 || i == 2085 || i == 2132 || i == 2179 || i == 2226 || i == 2273 || i == 1897 || i == 1850 || i == 1803 || i == 1756 || i == 1709 || i == 1662 || i == 1615) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !b1_used1 && !b1_used2) {
            b1_used1 = true;
            beginner = true;
          }
        }
        if (status == 7) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 1503 || i == 1454 || i == 1405 || i == 1356 || i == 1307 || i == 1258 || i == 1209 || i == 1160 || i == 1111 || i == 1062 || i == 1013 || i == 964 || i == 915 || i == 866 || i == 817 || i == 1207 || i == 1254 || i == 1301 || i == 1348 || i == 1395 || i == 1442 || i == 1489 || i == 1113 || i == 1066 || i == 1019 || i == 972 || i == 925 || i == 878 || i == 831) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !c2_used1 && !c2_used2) {
            c2_used1 = true;
            beginner = true;
          }
        }
        if (status == 8) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 735 || i == 686 || i == 637 || i == 588 || i == 539 || i == 490 || i == 441 || i == 392 || i == 343 || i == 294 || i == 245 || i == 196 || i == 147 || i == 98 || i == 49 || i == 439 || i == 486 || i == 533 || i == 580 || i == 627 || i == 674 || i == 721 || i == 345 || i == 298 || i == 251 || i == 204 || i == 157 || i == 110 || i == 63) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !c3_used1 && !c3_used2) {
            c3_used1 = true;
            beginner = true;
          }
        }
        if (status == 9) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 2271 || i == 2222 || i == 2173 || i == 2124 || i == 2075 || i == 2026 || i == 1977 || i == 1928 || i == 1879 || i == 1830 || i == 1781 || i == 1732 || i == 1683 || i == 1634 || i == 1975 || i == 2022 || i == 2069 || i == 2116 || i == 2163 || i == 2210 || i == 2257 || i == 1881 || i == 1834 || i == 1787 || i == 1740 || i == 1693 || i == 1646 || i == 1599) {
              led.setPixelColor(i, led.Color(255, 0, 0));
            }
          }
          led.show();
          if (status_pressed == 0 && !c1_used1 && !c1_used2) {
            c1_used1 = true;
            beginner = true;
          }
        }
      }
      if (beginner) {
        status_pressed = digitalRead(player_two);
        check_win();
        if (status == 0) {
        }
        if (status == 1) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 1410 ||i == 1362 ||i == 1314 ||i == 1266 ||i == 1218 ||i == 1170 ||i == 1122 ||i == 1074 ||i == 1026 ||i == 978 ||i == 930 ||i == 882 ||i == 1469 || i == 1468 || i == 1467 || i == 1466 || i == 1465 || i == 1464 || i == 1463 || i == 1462 || i == 1461 || i == 1460 || i == 1459 ||i == 1422 ||i == 1374 ||i == 1326 ||i == 1278 ||i == 1230 ||i == 1182 ||i == 1134 ||i == 1086 ||i == 1038 ||i == 990 ||i == 942 ||i == 893 || i == 892 || i == 891 || i == 890 || i == 889 || i == 888 || i == 887 || i == 886 || i == 885 || i == 884 || i == 883) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !b2_used1 && !b2_used2) {
            b2_used2 = true;
            beginner = false;
          }
        }
        if (status == 2) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 1426 ||i == 1378 ||i == 1330 ||i == 1282 ||i == 1234 ||i == 1186 ||i == 1138 ||i == 1090 ||i == 1042 ||i == 994 ||i == 946 ||i == 898 ||i == 1485 || i == 1484 || i == 1483 || i == 1482 || i == 1481 || i == 1480 || i == 1479 || i == 1478 || i == 1477 || i == 1476 || i == 1475 ||i == 1438 ||i == 1390 ||i == 1342 ||i == 1294 ||i == 1246 ||i == 1198 ||i == 1150 ||i == 1102 ||i == 1054 ||i == 1006 ||i == 958 ||i == 909 || i == 908 || i == 907 || i == 906 || i == 905 || i == 904 || i == 903 || i == 902 || i == 901 || i == 900 || i == 899) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !a2_used1 && !a2_used2) {
            a2_used2 = true;
            beginner = false;
          }
        }
        if (status == 3) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 658 ||i == 610 ||i == 562 ||i == 514 ||i == 466 ||i == 418 ||i == 370 ||i == 322 ||i == 274 ||i == 226 ||i == 178 ||i == 717 || i == 716 || i == 715 || i == 714 || i == 713 || i == 712 || i == 711 || i == 710 || i == 709 || i == 708 || i == 707 ||i == 670 ||i == 622 ||i == 574 ||i == 526 ||i == 478 ||i == 430 ||i == 382 ||i == 334 ||i == 286 ||i == 238 ||i == 190 ||i == 141 || i == 140 || i == 139 || i == 138 || i == 137 || i == 136 || i == 135 || i == 134 || i == 133 || i == 132 || i == 131) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !a3_used1 && !a3_used2) {
            a3_used2 = true;
            beginner = false;
          }
        }
        if (status == 4) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 2194 ||i == 2146 ||i == 2098 ||i == 2050 ||i == 2002 ||i == 1954 ||i == 1906 ||i == 1858 ||i == 1810 ||i == 1762 ||i == 1714 ||i == 2253 || i == 2252 || i == 2251 || i == 2250 || i == 2249 || i == 2248 || i == 2247 || i == 2246 || i == 2245 || i == 2244 || i == 2243 ||i == 2206 ||i == 2158 ||i == 2110 ||i == 2062 ||i == 2014 ||i == 1966 ||i == 1918 ||i == 1870 ||i == 1822 ||i == 1774 ||i == 1726 ||i == 1677 || i == 1676 || i == 1675 || i == 1674 || i == 1673 || i == 1672 || i == 1671 || i == 1670 || i == 1669 || i == 1668 || i == 1667) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !a1_used1 && !a1_used2) {
            a1_used2 = true;
            beginner = false;
          }
        }
        if (status == 5) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 642 ||i == 594 ||i == 546 ||i == 498 ||i == 450 ||i == 402 ||i == 354 ||i == 306 ||i == 258 ||i == 210 ||i == 162 ||i == 701 || i == 700 || i == 699 || i == 698 || i == 697 || i == 696 || i == 695 || i == 694 || i == 693 || i == 692 || i == 691 ||i == 654 ||i == 606 ||i == 558 ||i == 510 ||i == 462 ||i == 414 ||i == 366 ||i == 318 ||i == 270 ||i == 222 ||i == 174 ||i == 125 || i == 124 || i == 123 || i == 122 || i == 121 || i == 120 || i == 119 || i == 118 || i == 117 || i == 116 || i == 115) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !b3_used1 && !b3_used2) {
            b3_used2 = true;
            beginner = false;
          }
        }
        if (status == 6) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 2178 ||i == 2130 ||i == 2082 ||i == 2034 ||i == 1986 ||i == 1938 ||i == 1890 ||i == 1842 ||i == 1794 ||i == 1746 ||i == 1698 ||i == 2237 || i == 2236 || i == 2235 || i == 2234 || i == 2233 || i == 2232 || i == 2231 || i == 2230 || i == 2229 || i == 2228 || i == 2227 ||i == 2190 ||i == 2142 ||i == 2094 ||i == 2046 ||i == 1998 ||i == 1950 ||i == 1902 ||i == 1854 ||i == 1806 ||i == 1758 ||i == 1710 ||i == 1661 || i == 1660 || i == 1659 || i == 1658 || i == 1657 || i == 1656 || i == 1655 || i == 1654 || i == 1653 || i == 1652 || i == 1651) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !b1_used1 && !b1_used2) {
            b1_used2 = true;
            beginner = false;
          }
        }
        if (status == 7) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 1394 ||i == 1346 ||i == 1298 ||i == 1250 ||i == 1202 ||i == 1154 ||i == 1106 ||i == 1058 ||i == 1010 ||i == 962 ||i == 914 ||i == 866 ||i == 1453 || i == 1452 || i == 1451 || i == 1450 || i == 1449 || i == 1448 || i == 1447 || i == 1446 || i == 1445 || i == 1444 || i == 1443 ||i == 1406 ||i == 1358 ||i == 1310 ||i == 1262 ||i == 1214 ||i == 1166 ||i == 1118 ||i == 1070 ||i == 1022 ||i == 974 ||i == 926 ||i == 877 || i == 876 || i == 875 || i == 874 || i == 873 || i == 872 || i == 871 || i == 870 || i == 869 || i == 868 || i == 867) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !c2_used1 && !c2_used2) {
            c2_used2 = true;
            beginner = false;
          }
        }
        if (status == 8) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 626 ||i == 578 ||i == 530 ||i == 482 ||i == 434 ||i == 386 ||i == 338 ||i == 290 ||i == 242 ||i == 194 ||i == 146 ||i == 685 || i == 684 || i == 683 || i == 682 || i == 681 || i == 680 || i == 679 || i == 678 || i == 677 || i == 676 || i == 675 ||i == 638 ||i == 590 ||i == 542 ||i == 494 ||i == 446 ||i == 398 ||i == 350 ||i == 302 ||i == 254 ||i == 206 ||i == 158 ||i == 109 || i == 108 || i == 107 || i == 106 || i == 105 || i == 104 || i == 103 || i == 102 || i == 101 || i == 100 || i == 99) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !c3_used1 && !c3_used2) {
            c3_used2 = true;
            beginner = false;
          }
        }
        if (status == 9) {
          for (int i = 0; i < MAXLED; i++) {
            if (i == 2162 ||i == 2114 ||i == 2066 ||i == 2018 ||i == 1970 ||i == 1922 ||i == 1874 ||i == 1826 ||i == 1778 ||i == 1730 ||i == 2219 || i == 2218 || i == 2217 || i == 2216 || i == 2215 || i == 2214 || i == 2213 || i == 2212 || i == 2211 || i == 2210 || i == 2209 ||i == 2174 ||i == 2126 ||i == 2078 ||i == 2030 ||i == 1982 ||i == 1934 ||i == 1886 ||i == 1838 ||i == 1790 ||i == 1742 ||i == 1694 ||i == 1645 || i == 1644 || i == 1643 || i == 1642 || i == 1641 || i == 1640 || i == 1639 || i == 1638 || i == 1637 || i == 1636 || i == 1635) {
              led.setPixelColor(i, led.Color(0, 0, 255));
            }
          }
          led.show();
          if (status_pressed == 0 && !c1_used1 && !c1_used2) {
            c1_used2 = true;
            beginner = false;
          }
        }
      }
    }
  }
}
//
void game_COIN_COLLECT(){
  if(select == 3){

  }
}
//

void loop() {
  start_program();
  reset();
  game_ONE_LED_RACE();
  game_TWO_TIC_TAC_TOE();
  game_COIN_COLLECT();
  standby_Timer++;
}
