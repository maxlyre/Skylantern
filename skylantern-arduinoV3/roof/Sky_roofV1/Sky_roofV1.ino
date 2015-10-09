#include <AccelStepper.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>


// Créer function routine (send ready when finish)
//Créer function timer (si la boule ne monte pas après X seconde).
//Huzzah : change client

char nomMotor = 0; //numero du groupe; 
long stepsdescente = 10000; //distance vers le bas
int waitTime = 2000; //Temps en haut

//Config Timer
SimpleTimer timer;

//Config Stepper
AccelStepper stepper(1, 6, 5);
#define stepperEnable 8

//Config I2C
String inputString ="";
boolean stringComplete = false;  // whether the string is complete
SoftwareSerial mySerial(9, 10);//RX, TX

//Setup Timer
int timerStepper;

//Boolean activation
boolean downState = false; //Active le calcul de distance
boolean irsensor = false; //Active l'IR sensor
boolean motorReady = false; //Active la lantern après mise en place

//Ir sensor 
int distancelantern=0; //Distance de l'IR sensor
int countpositif =0; //Compteur confirmation IR

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  
  //Setupbegin();

  pinMode(stepperEnable, OUTPUT);
  digitalWrite(stepperEnable, LOW);
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(4000);
}

void loop() {
    timer.run();
    
     for(int i=0;i<30;i++){
     stepper.run();
     }
     
    irSensor();
    
    Stop();

   serialEvent(); //call the function
   ManageMessage(); //Trie new message
}
