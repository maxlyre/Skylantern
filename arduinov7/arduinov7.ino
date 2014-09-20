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
    
     for(int i=0;i<20;i++){
     stepper0.run();
     stepper1.run();
     }
     
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


