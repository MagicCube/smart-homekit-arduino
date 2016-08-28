#ifndef KEYPAD
#define  KEYPAD

#define NO_KEY_PRESSED 0
#define LEFT_KEY 1
#define RIGHT_KEY 2
#define UP_KEY 3
#define DOWN_KEY 4
#define SELECT_KEY 10

void captureKeypadEvents();
int readKeyCode();

void onLeftKeyDown();
void onRightKeyDown();
void onUpKeyDown();
void onDownKeyDown();

#endif
