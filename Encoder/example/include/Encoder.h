#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

#define CONFIG_ENCODER_A_PIN 35
#define CONFIG_ENCODER_B_PIN 34

typedef enum
{
    Event_None,
    Event_UP,
    Event_DOWN
} Encoder_Event;

class ENCODER
{
    private:
        typedef void(*FuncCallback_t)(ENCODER* encoder, Encoder_Event event, uint16_t state);
        FuncCallback_t eventCallback;
        

    public:
        static Encoder_Event Event_status;
        uint16_t state = 0;
        uint16_t config_detent;
        bool ifDeattach = false;

        void Encoder_Init(uint16_t detent);
        void Encoder_Update();
        void EventAttach(FuncCallback_t function);
        // ENCODER(uint16_t detent);
    
};

#endif