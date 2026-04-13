#ifndef BUTTONS_H
#define BUTTONS_H

typedef enum {
    BUTTON_NONE = 0,
    BUTTON_RED,
    BUTTON_GREEN,
    BUTTON_BLUE,
    BUTTON_YELLOW,
    BUTTON_START
} button_t;

void initButtons(void);
button_t ButtonsPressed(void);

#endif