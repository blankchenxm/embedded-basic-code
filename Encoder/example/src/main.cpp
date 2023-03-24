#include <Arduino.h>
#include <Encoder.h>

//WHY CAN'T INITIALIZE WITH ENCODER::ENCODER(15)
ENCODER encoder;

void Encoder_PushHandler(ENCODER* enc, Encoder_Event event, uint16_t state)
{
  switch (event){
    case Event_UP:
      Serial.print("UP DIAL THE DETENT！ ");
      Serial.print("current state is:");
      Serial.println(state);
    break;
    case Event_DOWN:
      Serial.print("DOWN DIAL THE DETENT！ ");
      Serial.print("current state is:");
      Serial.println(state);
    break;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  encoder.Encoder_Init(15);
  encoder.EventAttach(&Encoder_PushHandler);
  //maximum detent
  //it ranges from 0~detent
}

void loop() {
  // put your main code here, to run repeatedly:
    encoder.Encoder_Update();
    delay(50);
}

