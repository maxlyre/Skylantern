#include <VirtualWire.h>
#include <AccelStepper.h>
#include <SimpleTimer.h>
SimpleTimer timer;

AccelStepper stepper0(1, 3, 2);
AccelStepper stepper1(1, 7, 6);

int stepsmonte = 50000;
int stepsdescente = 5000;

int stepLight0 = 2;
int timerStepper0;

int stepLight1 = 2;
int timerStepper1;

boolean irsensor0 = false;
int distancelantern0=0;
boolean irsensor1 = false;
int distancelantern1=0;

void setup() {
  Serial.begin(4800);
  
  vw_setup(2000);                 // Bits par seconde (vous pouvez le modifier mais cela modifiera la portée). Voir la documentation de la librairie VirtualWire.
  vw_set_rx_pin(11);             // C'est sur cette broche que l'on reliera les broches DATA du récepteur, vous pouvez changez de broche si vous le désirez.
  vw_rx_start();                    // On démarre le récepteur.

  stepper0.setMaxSpeed(6000);
    stepper0.setAcceleration(4000);
  stepper1.setMaxSpeed(6000);
    stepper1.setAcceleration(4000);
    
}

void loop() {
    timer.run();
    /* int distancelantern1= analogRead(8);
     Serial.println(distancelantern1);
      if(distancelantern1>600){
      Serial.println("Test");
    }*/
     
     for(int i=0;i<20;i++){
     stepper0.run();
     stepper1.run();
     }
     
     /*int distancelantern0= analogRead(8);
     Serial.println(distancelantern0);*/
    irSensor();
  
    
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;


  if (vw_get_message(buf, &buflen)) // On test afin de savoir si un message est reçu.
  {
    int i;
    // Un message est reçu.
   
    for (i = 0; i < buflen; i++)
    {
         
       Serial.write(buf[i]);  // On affiche le message lettre par lettre. Par exemple buf[4] sera égale à la 5ème lettre du mot envoyé (Snootlab donc "t") car on compte le zéro ici.
       if(buf[i] == buf[0]){   
       Serial.println("");
       }else{}
   }
    Serial.println(""); // On saute une ligne afin d'avoir plus de clarté.
  }

  /* if (Serial.available()){
   recievedChar = Serial.read();
   Serial.print(recievedChar);
   }*/
  if( buf[0] == 'A'){
        buf[0] = 'Z';
        stepper0GoToStep1();
}
  else if( buf[0] == 'B'){
        buf[0] = 'Z';
        stepper1GoToStep1();
    
}
}




void stepper0GoToStep1()
{
  Serial.println("\tStep 2 : servo Up");
        stepper0Up();
        irsensor0 = true;
}

void stepper0GoToStep2()
{
  stepper0Stop();
  
  Serial.println("Step 2 : Stop");
}

void stepper0GoToStep3()
{
  irsensor0=false;
   Serial.println("Step 3 : Waiting");
    stepper0Stop();
    timerStepper0 = timer.setTimeout(15000, stepper0GoToStep4);
}

void stepper0GoToStep4()
{
   Serial.println("Step 4 : stepper Down");
    stepper0Down();
    Serial.println("AO");
}
//------------------------------------------------------------------------- Ordre Moteur
void stepper0Up()
{
  stepper0.setMaxSpeed(6000);
  stepper0.setAcceleration(4000); 
  stepper0.move(-900000000);
}

void stepper0Stop(){
  stepper0.move(0); 
  stepper0.setSpeed(0);
  stepper0.runSpeed();
  //stepper0.stop();
}

void stepper0Down()
{
  stepper0.setMaxSpeed(6000);
  stepper0.setAcceleration(4000);
  stepper0.move(13000);
  Serial.println("Step 5 : Stop");
}

//-------------------------------------------------------------------------------------------Stepper 2
void stepper1GoToStep1()
{
  Serial.println("\tStep 2B : servo Up");
        stepper1Up();
        irsensor1 = true;
}
void stepper1GoToStep2()
{
  stepper1Stop();
  
  Serial.println("Step 2B : Stop");
}

void stepper1GoToStep3()
{
  irsensor1=false;
   Serial.println("Step 3B : Waiting");
    stepper1Stop();
    timerStepper1 = timer.setTimeout(15000, stepper1GoToStep4);
}

void stepper1GoToStep4()
{
   Serial.println("Step 4B : stepper Down");
    stepper1Down();
    Serial.println("BO");
}
//------------------------------------------------------------------------- Ordre Moteur
void stepper1Up()
{
     stepper1.setMaxSpeed(6000);
  stepper1.setAcceleration(4000); 
  stepper1.move(-900000000);
}

void stepper1Stop(){
    stepper1.move(0); 
  stepper1.setSpeed(0);
  stepper1.runSpeed();
  //stepper0.stop();
}

void stepper1Down()
{
   stepper1.setMaxSpeed(6000);
  stepper1.setAcceleration(4000);
  stepper1.move(13000);
   Serial.println("Step 5B : Stop");
}

void irSensor(){
  
  if(irsensor0){
    int distancelantern0= analogRead(8);
    if(distancelantern0>200){
      Serial.println("Capteur On");
     stepper0GoToStep3();
    }
  }
  
  if(irsensor1){
    int distancelantern1= analogRead(9);
    if(distancelantern1>200){
      Serial.println("CapteurB On");
      stepper1GoToStep3();
    }
  }
  
}

