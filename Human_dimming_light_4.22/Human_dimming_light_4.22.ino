
/*
   Wendy Ju Said in her book - Design for implicit interactions:
 
   "The smart switch that dims the lights slowly rather than turning them out all
   at once is like the doorman that opens the door a little rather than flinging
   it open at every prospective passerby."
   
   使用MOSFET,将3v信号变换成5v:无人走动时，传感器输出0v，对应的MOSFET的Drain（2号）输出5v；
   当有人经过时，传感器输出5v，对应的MOSFET的Drain（2号）输出0v.

   灯光亮度与时间：
   亮度范围：255 - 0
   时间范围：0 - 15s

*/

#define ledPin 4                 // a led indicate is human is detected or not
#define sensorPin 3              // comes out from MOSFET's Drain
#define lightPin 0               // pwm value to the light bulb

bool sensorValue;                // value from MOSFET: 1/0
int brightness = 255;            // light bulb brightness
int dimAmount = 1.5;             // for each time, how much light dims
unsigned long preTime = 0;
const int gapTime = 50;          // how many millis light dims certen amount

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(lightPin, OUTPUT);
}

void loop() {
  sensorValue = digitalRead(sensorPin);

  if (sensorValue == LOW) {               // led indicate human detected
    digitalWrite(ledPin, HIGH);
    analogWrite(lightPin, 255);
    brightness = 255;
  } else {
    digitalWrite(ledPin, LOW);
    dim();
  }
}

void dim() {

  if (brightness > 0) {
    analogWrite(lightPin, brightness);
  } else {
    analogWrite(lightPin, 0);
  }

  if (millis() - preTime > gapTime) {

    brightness = brightness - dimAmount;
    preTime = millis();
  }
}
