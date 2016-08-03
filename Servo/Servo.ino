/* 
 Controlling a servo position using a potentiometer (variable resistor) 
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;
volatile int state = LOW;
long debouncing_time = 1000; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
int pin = 13;

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(pin, OUTPUT);
  attachInterrupt(0, debounceInterrupt, CHANGE);
}

void loop() 
{ 
//  myservo.write(180);                  // sets the servo position according to the scaled value 
//  digitalWrite(pin, HIGH);
//  delay(1000);                           // waits for the servo to get there 
//  myservo.write(10);
//  digitalWrite(pin, LOW);
//  delay(1000);  
} 

void switchServo()
{
  if ( digitalRead( 2 ) == HIGH ) {
     state = HIGH;
     digitalWrite(pin, state);
     myservo.write(180);
  }
  else {
     state = LOW;
     digitalWrite(pin, state);
     myservo.write(10);
  }
  
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    switchServo();
    last_micros = micros();
  }
}

