#include "Arduino.h"

#include "keypad.h"

int pressingKey = NO_KEY_PRESSED;
int pressingKeyReleased = true;

int readKeyCode()
{
    int keyValue = analogRead(0);
    int keyCode = 0;
    if (keyValue < 50)
    {
        keyCode = RIGHT_KEY;
    }
    else if (keyValue < 195)
    {
        keyCode = UP_KEY;
    }
    else if (keyValue < 380)
    {
        keyCode = DOWN_KEY;
    }
    else if (keyValue < 555)
    {
        keyCode = LEFT_KEY;
    }
    else if (keyValue < 790)
    {
        keyCode = SELECT_KEY;
    }
    else
    {
        if (pressingKey)
        {
            pressingKey = NO_KEY_PRESSED;
            pressingKeyReleased = true;
        }
        return NO_KEY_PRESSED;
    }

    if (!pressingKey && pressingKeyReleased)
    {
        pressingKey = keyCode;
        pressingKeyReleased = false;
        return keyCode;
    }
    else
    {
        return NO_KEY_PRESSED;
    }
}

void captureKeypadEvents()
{
    int keyCode = 0;
    if ((keyCode = readKeyCode()))
    {
        switch (keyCode)
        {
            case LEFT_KEY:
                onLeftKeyDown();
                break;
            case RIGHT_KEY:
                onRightKeyDown();
                break;
            case UP_KEY:
                onUpKeyDown();
                break;
            case DOWN_KEY:
                onDownKeyDown();
                break;
            case SELECT_KEY:
                Serial.println("SELECT KEY");
                break;
        }
    }
}
