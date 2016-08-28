#ifndef main
#define main

#include <Sodaq_DS3231.h>

#define TIME_MODE 0
#define TEMPERATURE_MODE 1
#define AC_MODE 2
#define WIFI_MODE 3
#define ABOUT_MODE 4
#define MODE_COUNT 5
// 0 - Date
// 1 - Time
// 2 - Temperature
// 3 - About
int modeIndex = 0;
void switchToMode(int index);
void switchToLastMode();
void switchNextLastMode();

unsigned long lastTick = 0;
void captureTickEvent();
void onTick();

String formatTime(DateTime);
String formatDate(DateTime);

#endif
