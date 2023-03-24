#include <Encoder.h>
Encoder_Event ENCODER::Event_status = Event_None;

static void Encoder_EventHandler()
{
    // static variable initialize as 0
    static volatile uint8_t a0, b0;
    static volatile uint8_t ab0;
    uint8_t a = digitalRead(CONFIG_ENCODER_A_PIN);
    uint8_t b = digitalRead(CONFIG_ENCODER_B_PIN);
    uint8_t ab = (a == b);

    // falling edge of pin A
    if (a == 0x0)
    {
        a0 = a;
        b0 = b;
        ab0 = ab;
    }

    // rising edge of pin A
    if (a == 0x1)
    {
        if (a != a0 & b != b0 & ab == ab0)
        {
            ENCODER::Event_status = ab == 0x0 ? Event_UP : Event_DOWN;
        }
    }
}

// ENCODER::ENCODER(uint16_t detent)
// {   
//     config_detent = detent;
//     pinMode(CONFIG_ENCODER_A_PIN,INPUT_PULLUP);
//     pinMode(CONFIG_ENCODER_B_PIN,INPUT_PULLUP);
//     attachInterrupt(CONFIG_ENCODER_A_PIN,&Encoder_EventHandler,CHANGE);
// }

void ENCODER::Encoder_Init(uint16_t detent)
{   
    config_detent = detent;
    pinMode(CONFIG_ENCODER_A_PIN,INPUT_PULLUP);
    pinMode(CONFIG_ENCODER_B_PIN,INPUT_PULLUP);
    attachInterrupt(CONFIG_ENCODER_A_PIN,&Encoder_EventHandler,CHANGE);
}

void ENCODER::EventAttach(FuncCallback_t function)
{
    eventCallback = function;
}

void ENCODER::Encoder_Update()
{
    if (Event_status == Event_None)
    {
        return;
    }
    if (Event_status == Event_UP)
    {
        state = state == config_detent ? 0 : state+1;
    }
    if (Event_status == Event_DOWN)
    {
        state = state == 0 ? config_detent : state-1;
    }

    if (!ifDeattach)
    {
        (*eventCallback)(this,Event_status,state);
    }
    Event_status = Event_None;
    return;
}





