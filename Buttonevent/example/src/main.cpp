#include <Arduino.h>
#include <ButtonEvent.h>
 
BUTTONEVENT button(3000);

//callback function initialize
//three state: PRESS,LONG_PRESS,RELEASE
void Button_PushHandler(BUTTONEVENT* btn, int event)
{
  switch (event){
    case Event_PRESS:
      Serial.println("pressed!");
    break;
    case Event_LONG_PRESS:
      Serial.println("long pressed!");
    break;
    case Event_RELEASE:
      Serial.println("released!");
    break;
  }
}

void setup() {
  Serial.begin(115200);
  // attach your own callback function
  button.EventAttach(&Button_PushHandler);
  // button.ifDeattach = true;
}

void loop() 
{
  button.Button_Update();
  //detect the change of button evey 100ms
  delay(50);
}