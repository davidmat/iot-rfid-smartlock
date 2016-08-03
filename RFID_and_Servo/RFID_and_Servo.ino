#define rxPin 4
#define txPin 5


// link between the computer and the SoftSerial Shield
//at 9600 bps 8-N-1
//Computer is connected to Hardware UART
//SoftSerial Shield is connected to the Software UART:D2&D3 
 
#include <SoftwareSerial.h>
#include <Servo.h>

// Serial
SoftwareSerial SoftSerial(rxPin, txPin);
int  val = 0; 
char code[10]; 
int bytesread = 0;

// Servo
Servo myservo;
volatile int state = LOW;
long debouncing_time = 1000; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
int pin = 13;

void setup()
{
  SoftSerial.begin(9600);               // the SoftSerial baud rate   
  Serial.begin(9600);             // the Serial port of Arduino baud rate.
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(pin, OUTPUT);
  attachInterrupt(0, debounceInterrupt, CHANGE);
}
 
void loop()
{
  if(SoftSerial.available() > 0) {          // if data available from reader 
    if((val = SoftSerial.read()) == 2) {   // check for header 
      bytesread = 0; 
      while(bytesread<10) {              // read 10 digit code 
        if( SoftSerial.available() > 0) { 
          val = SoftSerial.read(); 
          if((val == 10)||(val == 13)) { // if header or stop bytes before the 10 digit reading 
            break;                       // stop reading 
          } 
          code[bytesread] = val;         // add the digit           
          bytesread++;                   // ready to read next digit  
        } 
      } 
      if(bytesread == 10) {              // if 10 digit read is complete 
        Serial.print("RFID");   // possibly a good TAG 
        Serial.println(code);            // print the TAG code 
      } 
      bytesread = 0; 
    } 
  } 
}

void switchServo()
{
  if ( digitalRead( 2 ) == HIGH ) {
     state = HIGH;
     digitalWrite(pin, state);
     myservo.write(0);
     Serial.println("DOOROPEN");
  }
  else {
     state = LOW;
     digitalWrite(pin, state);
     myservo.write(90);
     Serial.println("DOORCLOSE");
  }
  
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    switchServo();
    last_micros = micros();
  }
}

