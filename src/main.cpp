#include "Arduino.h"
#include <LiquidCrystal.h>
#include <Sodaq_DS3231.h>
#include <Wire.h>

#include "main.h"
#include "keypad.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void adjustTime()
{
    //year, month, date, hour, min, sec and week-day(starts from 0 and goes to 6)
    //writing any non-existent time-data may interfere with normal operation of the RTC.
    //Take care of week-day also.
    DateTime dt(2016, 8, 28, 11, 6, 0, 0);
    rtc.setDateTime(dt);
}

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    rtc.begin();
    lcd.begin(16, 2);

    //adjustTime();

    switchToScene(0);
}

void loop()
{
    captureKeypadEvents();
    captureTickEvent();
}

void switchToScene(int index)
{
    lcd.clear();
    sceneIndex = index;
    switch (sceneIndex)
    {
        case TIME_SCENE:
            break;
        case TEMPERATURE_SCENE:
            lcd.print("Temperature");
            break;
        case ABOUT_SCENE:
            lcd.print("Smart Homekit");
            lcd.setCursor(0, 1);
            lcd.print("Makers Bootcamp");
            break;
    }
    onTick();
}

void switchToLastScene()
{
    if (sceneIndex == 0)
    {
        switchToScene(SCENE_COUNT - 1);
    }
    else
    {
        switchToScene(sceneIndex - 1);
    }
}

void switchToNextScene()
{
    if (sceneIndex == SCENE_COUNT - 1)
    {
        switchToScene(0);
    }
    else
    {
        switchToScene(sceneIndex + 1);
    }
}





void captureTickEvent()
{
    if (lastTick == 0 || millis() - lastTick > 1000)
    {
        lastTick = millis();
        onTick();
    }
}

void onTick()
{
    if (sceneIndex == ABOUT_SCENE) return;

    DateTime now = rtc.now();
    lcd.setCursor(0, 1);
    switch (sceneIndex)
    {
        case TIME_SCENE:
            lcd.setCursor(0, 0);
        	lcd.print(formatDate(now));
            lcd.setCursor(0, 1);
            lcd.print(formatTime(now));
            lcd.print("   ");
            rtc.convertTemperature();
            lcd.print(rtc.getTemperature());
            break;
        case TEMPERATURE_SCENE:
            rtc.convertTemperature();
            lcd.print(rtc.getTemperature());
            break;
    }
}

void onLeftKeyDown()
{
    switchToLastScene();
}

void onRightKeyDown()
{
    switchToNextScene();
}

void onUpKeyDown()
{
    switchToLastScene();
}

void onDownKeyDown()
{
    switchToNextScene();
}


String digit2(int num)
{
    String result = "";
    if (num < 10)
    {
        result.concat("0");
    }
    result.concat(num);
    return result;
}


String WEEK_DAY[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
String formatDate(DateTime now)
{
    String result = "";
    result.concat(now.year());
    result.concat('-');
    result.concat(digit2(now.month()));
    result.concat('-');
    result.concat(digit2(now.date()));
    result.concat("   ");
    result.concat(WEEK_DAY[now.dayOfWeek()]);
    return result;
}

String formatTime(DateTime now)
{
    String result = "";
    result.concat(digit2(now.hour()));
    result.concat(':');
    result.concat(digit2(now.minute()));
    result.concat(':');
    result.concat(digit2(now.second()));
    return result;
}
