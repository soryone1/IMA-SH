 /*
  * Volcano Project 2021
  * 
  * Tools: 12v LED Bulb (E27), Wood body, Attiny 13， FQP30N06L MOSFET，LM7805
  * 
 */

#define lightPin 0                        // Connect to MOSFET Gate
#define sensorPin 4                       // Read the touch sense value

bool sensorValue;
int state = 0;                             // define the 3 different brightness
int buttonState = LOW; 
int lastButtonState = LOW;
int lastPressedTime = 0;
const int debounceDelay = 100;                   // how fast you want the press could be

void setup() {
  pinMode(lightPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {

  sensorValue = digitalRead(sensorPin);    // get the result of the input: 0/1

  if (sensorValue != lastButtonState) {
    lastPressedTime = millis();
  }

  if (millis() - lastPressedTime > debounceDelay ) {
    if (sensorValue != buttonState) {
      buttonState = sensorValue;
      if (buttonState == HIGH) {           //touched!
        if (state < 4 ) {
          state++;
        } 

        if(state == 4){
          state = 0;
        }

      }
    }
  }

  lastButtonState = sensorValue;

  switch (state) {
    case 0:
      analogWrite(lightPin, 0);
      break;
    case 1:
      analogWrite(lightPin, 20);
      break;
    case 2:
      analogWrite(lightPin, 80);
      break;
    case 3:
      analogWrite(lightPin, 255);
      break;
  }

}
