#include <AccelStepper.h>
#include <SimpleTimer.h>
#include <SoftwareSerial.h>

//Créer function timer (si la boule ne monte pas après X seconde).

//--------------------------------------------------Configuration
char nomMotor = 0; //numero du groupe; 
long stepsdescente = -45000; //distance vers le bas
int waitTime = 20000; //Temps en haut

//--------------------------------------------------Configuration

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

int warningcount = 0;
int warningSetup = 0;
boolean warning = false;

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

  //Setup Stepper
  pinMode(stepperEnable, OUTPUT);
  digitalWrite(stepperEnable, LOW);
  stepper.setMaxSpeed(9000);
  stepper.setAcceleration(4000);
}

void loop() {
    timer.run();
    
     for(int i=0;i<30;i++){
     stepper.run();
       if(motorReady==false && irSensor && warning){
          warningSetup++;
       }
     }
      
    //Activateur
    irSensor();
    Stop();
    Warning();

    //Gestion message
   serialEvent(); //call the function
   ManageMessage(); //Trie new message
}
