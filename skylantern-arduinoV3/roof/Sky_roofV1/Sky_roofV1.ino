#include <Wire.h>
#include <AccelStepper.h>
#include <SimpleTimer.h>

byte nomMotor = 0; //numero du groupe; 
int stepsdescente = 5000; //distance vers le bas
int waitTime = 25000;

//Config Timer
SimpleTimer timer;

//Config Stepper
AccelStepper stepper(1, 3, 2);

//Config I2C
#define I2C_ADDRESS_OTHER 0x1
#define I2C_ADDRESS_ME 0x2
String inputString ="";


int timerStepper;

boolean downState = false;
boolean irsensor = false;
int distancelantern=0;
int countpositif =0;

void setup() {
  Serial.begin(9600);
  delay(5000);
  setupName();
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(4000);
  Wire.begin(I2C_ADDRESS_ME);
  Wire.onReceive(receiveI2C);
}

void loop() {
    timer.run();
    
     for(int i=0;i<20;i++){
     stepper.run();
     }
     
    irSensor();
    
    GoToStep4();
  
}
