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

    switchToMode(0);
}

void loop()
{
    captureKeypadEvents();
    captureTickEvent();
}

void switchToMode(int index)
{
    lcd.clear();
    modeIndex = index;
    switch (modeIndex)
    {
        case TIME_MODE:
            break;
        case TEMPERATURE_MODE:
            lcd.print("Temperature");
            break;
        case AC_MODE:
            lcd.print("Air Conditioning");
            lcd.setCursor(0, 1);
            lcd.print("Monitor       ON");
            break;
        case WIFI_MODE:
            lcd.print("WiFi");
            lcd.setCursor(0, 1);
            lcd.print("192.168.2.14");
            break;
        case ABOUT_MODE:
            lcd.print("Smart Homekit");
            lcd.setCursor(0, 1);
            lcd.print("Makers Bootcamp");
            break;
    }
    onTick();
}

void switchToLastMode()
{
    if (modeIndex == 0)
    {
        switchToMode(MODE_COUNT - 1);
    }
    else
    {
        switchToMode(modeIndex - 1);
    }
}

void switchToNextMode()
{
    if (modeIndex == MODE_COUNT - 1)
    {
        switchToMode(0);
    }
    else
    {
        switchToMode(modeIndex + 1);
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
    if (modeIndex == ABOUT_MODE) return;

    DateTime now = rtc.now();
    lcd.setCursor(0, 1);
    switch (modeIndex)
    {
        case TIME_MODE:
            lcd.setCursor(0, 0);
        	lcd.print(formatDate(now));
            lcd.setCursor(0, 1);
            lcd.print(formatTime(now));
            break;
        case TEMPERATURE_MODE:
            rtc.convertTemperature();
            lcd.print(rtc.getTemperature());
            break;
    }
}

void onLeftKeyDown()
{
    switchToLastMode();
}

void onRightKeyDown()
{
    switchToNextMode();
}

void onUpKeyDown()
{
    switchToLastMode();
}

void onDownKeyDown()
{
    switchToNextMode();
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
    result.concat(' ');
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
