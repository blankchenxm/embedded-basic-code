#include "ButtonEvent.h"

#define GET_TICK() millis()

#ifndef UINT32_MAX
#  define UINT32_MAX  4294967295u
#endif

void BUTTONEVENT::EventMonitor(bool isPress)
{
    if(!isPress && State_status == STATE_NO_PRESS)
    {
        return;
    }
    
    if(isPress && State_status == STATE_NO_PRESS)
    {
        Event_status = Event_PRESS;
        State_status = STATE_PRESSING;
        if(!ifDeattach)  
            {(*eventCallback)(this,Event_PRESS);}
        lastPressTime = GET_TICK();
        return;
    }

    if(!isPress && State_status == STATE_PRESSING)
    {
        Event_status = Event_RELEASE;
        State_status = STATE_NO_PRESS;
        if(!ifDeattach) 
            {eventCallback(this,Event_RELEASE);}
        return;
    }

    if (isPress && GetTickElaps(lastPressTime) >= config_longPressTime && State_status == STATE_PRESSING)
    {        
        Event_status = Event_LONG_PRESS;
        State_status = STATE_LONG_PRESSING;
        if(!ifDeattach) 
            {(*eventCallback)(this,Event_LONG_PRESS);}
        lastPressTime = 0;
        return;
    }

    if(isPress && State_status == STATE_LONG_PRESSING)
    {
        return;
    }

    if(!isPress && State_status == STATE_LONG_PRESSING)
    {
        Event_status = Event_RELEASE;
        State_status = STATE_NO_PRESS;
        if(!ifDeattach) 
            {(*eventCallback)(this,Event_RELEASE);}
        return;
    }


}

uint32_t BUTTONEVENT::GetTickElaps(uint32_t prevTick)
{
    uint32_t actTime = GET_TICK();
    uint32_t gap;

    if(actTime >= prevTick)
    {
        gap = actTime - prevTick;
    }

    else

    {
        gap = UINT32_MAX - prevTick + 1;
        gap += actTime;
    }
    return gap;
}

void BUTTONEVENT::EventAttach(FuncCallback_t function)
{
    eventCallback = function;
}


//long press time initialzie
BUTTONEVENT::BUTTONEVENT(uint16_t longPressTime)
{
    config_longPressTime = longPressTime;
    pinMode(CONFIG_BUTTON_KEY_PIN,INPUT_PULLUP);
    Event_status = Event_NONE;
    State_status = STATE_NO_PRESS;
    
}

//pull up resistor connencted, thus detect low voltage
void BUTTONEVENT::Button_Update()
{
    EventMonitor(digitalRead(CONFIG_BUTTON_KEY_PIN) == LOW_VOLTAGE);
}