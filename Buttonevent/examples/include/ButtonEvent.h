#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H

#include "Arduino.h"
#define CONFIG_BUTTON_KEY_PIN 22

#define LOW_VOLTAGE  0X0
#define hIGH_VOLTAGE  0X1

typedef enum
{
    Event_NONE,
    Event_PRESS,
    Event_LONG_PRESS,
    Event_RELEASE
} Event_t;

typedef enum
{
    STATE_NO_PRESS,
    STATE_PRESSING,
    STATE_LONG_PRESSING
} State_t;

class BUTTONEVENT
{
    private:
        typedef void(*FuncCallback_t)(BUTTONEVENT* btn, int event);
        uint16_t config_longPressTime;
        uint32_t lastPressTime;
        FuncCallback_t eventCallback;
 
        uint32_t GetTickElaps(uint32_t prevTick);
        void EventMonitor(bool isPress);

    public:
        Event_t Event_status;
        State_t State_status;

        BUTTONEVENT(uint16_t longPressTime = 2000);
        void EventAttach(FuncCallback_t function);
        void Button_Update();

};


#endif