#ifndef main
#define main

#include <Sodaq_DS3231.h>

#define TIME_SCENE 0
#define TEMPERATURE_SCENE 1
#define ABOUT_SCENE 2
#define SCENE_COUNT 3
// 0 - Date
// 1 - Time
// 2 - Temperature
// 3 - About
int sceneIndex = 0;
void switchToScene(int index);
void switchToLastScene();
void switchNextLastScene();

unsigned long lastTick = 0;
void captureTickEvent();
void onTick();

String formatTime(DateTime);
String formatDate(DateTime);

#endif
