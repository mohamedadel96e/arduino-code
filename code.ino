#include <SoftwareSerial.h>
#define hallSensorPin 3
int off = 1;
SoftwareSerial Bluetooth(10,11);
int pwm;
#define motor 5
volatile int rpmCount = 0; 
unsigned long previousMillis = 0; 




void setup() {
  Bluetooth.begin(38400);
  pinMode(motor,OUTPUT);
  
  digitalWrite(motor, 0);

  Serial.begin(38400);
  pinMode(hallSensorPin, INPUT); 
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), rpmCounter, RISING);
    
}

void loop() {

  unsigned long currentMillis = millis();




        if(Bluetooth.available()) {
         pwm=Bluetooth.read();
          // LED 1 on
          if (pwm == (1) ) {
              analogWrite(motor,1);
              off = 1;
          }
          // LED 1 off
         else  if (pwm == (0)) {
              digitalWrite(motor,0);
              off = 0;
          }

          else if(pwm>0&&pwm<=250 && off != 0) {                          
          analogWrite(motor, pwm);                
          }

      }
      
  if (currentMillis - previousMillis >= 1000) {
    
    float rpm = (rpmCount * 60.0);  
    
    
    Bluetooth.print(rpm);

    
    rpmCount = 0;

    
    previousMillis = currentMillis;
  } 



}


void rpmCounter() {
  rpmCount++;
}
