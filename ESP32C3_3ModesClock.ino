



#include <WiFi.h>
const char * ssid = "SSID";
const char * wifipw = "PASSWORD";

#include "time.h"
int DFheures, DFminutes, DFjour, DFdate, DFmois;
#define timeGet 1
float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;
float sdeg = 0, mdeg = 0, hdeg = 0;
uint16_t osx = 120, osy = 120, omx = 120, omy = 120, ohx = 120, ohy = 120;
uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;
int hh, mm;
String mmTxt, hhTxt;
bool firstTimeCall = true;
int timeCall = (55) * 1000; // pour 55 secondes en microsecondes
unsigned long lastTimeCall;

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#define TFT_CS_ST7735   10
#define TFT_RST_ST7735   9
#define TFT_DC           8
#define TFT_GREY    0xBDF7
#define TFT_GREEN   0x07E0
#define TFT_BLUE    0x001F
#define TFT_BLACK   0x0000
#define TFT_CYAN    0x07FF
#define TFT_RED     0xF800
#define TFT_WHITE   0xFFFF
Adafruit_ST7735 tft_ST7735 = Adafruit_ST7735(TFT_CS_ST7735, TFT_DC, TFT_RST_ST7735);

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

#define   FPSerial Serial1
DFRobotDFPlayerMini myDFPlayer;

#define timeGet 1

void printDetail(uint8_t type, int value);


void setTimezone(String timezone) {

  setenv("TZ", timezone.c_str(), 1); //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
  tzset();

}


void initTime(String timezone) {

  struct tm timeinfo;
  configTime(0, 0, "pool.ntp.org");    // First connect to NTP server, with 0 TZ offset
  if (!getLocalTime(&timeinfo)) {
    return;
  }
  setTimezone(timezone);

}


void printLocalTime() {

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return;
  }

  char timeHour[3];
  strftime(timeHour, 3, "%H", &timeinfo);
  String heures = timeHour;
  DFheures = heures.toInt();
  int dizHeure = heures.substring(0, 1).toInt();
  int uniHeure = heures.substring(1, 2).toInt();

  char timeMinute[3];
  strftime(timeMinute, 3, "%M", &timeinfo);
  String minutes = timeMinute;
  DFminutes = minutes.toInt();
  int dizMinute = minutes.substring(0, 1).toInt();
  int uniMinute = minutes.substring(1, 2).toInt();

  char timeInfoDay[2];
  strftime(timeInfoDay, 2, "%u", &timeinfo);
  int timeDay = String(timeInfoDay).toInt();
  DFjour = timeDay;
  char timeInfoJour[3];
  strftime(timeInfoJour, 3, "%e", &timeinfo);
  int timeJour = String(timeInfoJour).toInt();
  DFdate = timeJour;
  char timeInfoMois[3];
  strftime(timeInfoMois, 3, "%m", &timeinfo);
  int timeMois = String(timeInfoMois).toInt();
  DFmois = timeMois;

}


void startWifi() {

  WiFi.begin(ssid, wifipw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

}
//
//


void setTime(int yr, int month, int mday, int hr, int minute, int sec, int isDst) {

  struct tm tm;
  tm.tm_year = yr - 1900;   // Set date
  tm.tm_mon = month - 1;
  tm.tm_mday = mday;
  tm.tm_hour = hr;      // Set time
  tm.tm_min = minute;
  tm.tm_sec = sec;
  tm.tm_isdst = isDst;  // 1 or 0
  time_t t = mktime(&tm);

  struct timeval now = { .tv_sec = t };
  settimeofday(&now, NULL);

}



void setup() {

     pinMode(timeGet, INPUT);

     tft_ST7735.initR(INITR_BLACKTAB); //  ou GREENTAB
     tft_ST7735.setRotation(0);
     tft_ST7735.fillScreen(TFT_BLACK);
     tft_ST7735.setTextColor(TFT_WHITE, TFT_BLACK);
     tft_ST7735.setCursor(23, 135);
     tft_ST7735.setTextSize (2);
     tft_ST7735.print("DF init");

     FPSerial.begin(9600, SERIAL_8N1, /*rx =*/3, /*tx =*/2); //  ESP32C3 Super mini

     if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {
         while (true) {
                delay(0); //  pour compatibilite ESP8266
               }
        }
      myDFPlayer.volume(10);
      myDFPlayer.playFolder(06, 001); //  initialisation time txt
      delay(1500);

      startWifi();
      initTime("CET-1CEST,M3.5.0,M10.5.0/3"); //  Time Zone pour Berlin
      WiFi.disconnect();

      horlogeCadran();
      localTime();
      myDFPlayer.playFolder(03, DFjour);
      delay(1600);
      myDFPlayer.playFolder(04, DFdate);
      delay(900);
      myDFPlayer.playFolder(05, DFmois);
      delay(1600);
      myDFPlayer.playFolder(01, DFheures);
      delay(1600);
      myDFPlayer.playFolder(02, DFminutes + 25);

}


void loop() {

     if (((millis() - lastTimeCall) > timeCall) || (firstTimeCall == true)) {
         lastTimeCall = millis();
         firstTimeCall = false;

         localTime();
         horlogeAfficheTemps();
        }

      if (digitalRead(timeGet) == HIGH) {
          myDFPlayer.playFolder(03, DFjour);
          delay(1600);
          myDFPlayer.playFolder(04, DFdate);
          delay(900);
          myDFPlayer.playFolder(05, DFmois);
          delay(1600);
          myDFPlayer.playFolder(01, DFheures);
          delay(1600);
          myDFPlayer.playFolder(02, DFminutes + 25);
         }

}


//
