#include <Arduino.h>
#include <ButtonEvent.h>

BUTTONEVENT button(3000);

void Button_PushHandler(BUTTONEVENT* btn, int event)
{
  switch (event){
    case Event_PRESS:Serial.println("pressed!");break;
    case Event_LONG_PRESS:Serial.println("long pressed!");break;
    case Event_RELEASE:Serial.println("released!");break;
  }
}

void setup() {
  Serial.begin(115200);
  button.EventAttach(Button_PushHandler);
}

void loop() 
{
  button.Button_Update();
  delay(100);
}