#include <SimpleTimer.h>
#include <Adafruit_NeoPixel.h>
#include <Color.h>
#include <CapacitiveSensor.h>
#include <VirtualWire.h>

//Nom Lantern
char nomLantern = 'A';

//Timer
SimpleTimer timer;
int timer_id1;
int timer_id2;
//Capacitive 
CapacitiveSensor   cs_12_6 = CapacitiveSensor(12,6);

//Bolean Cycle
boolean touch = false;
boolean cycle = false;Hel
boolean protect = false;
boolean time=false;
boolean protectwaiting=false;
boolean fly = false;
int compteur =0;
//Conversion Couleur
Color cur_color = Color(1,1,1);
float hue = 0;
float  sat = 0;
float val=0;

// Which pin on the FLORA is connected to the NeoPixel ring?
#define PIN            10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  //Setup Radio
   vw_setup(2000);                // Bits par seconde (vous pouvez le modifier mais cela modifiera la portée). Voir la documentation de la librairie VirtualWire.
   vw_set_tx_pin(9);             // La broche 9 sera utilisée pour transmettre la DATA, vous pouvez changez de broche si vous le désirez.
  Serial.begin(4800);
  
   cs_12_6.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   
  pinMode(12, OUTPUT);     // output pin capacitive
  pinMode(6, INPUT);      // input pin capacitive
  pinMode(9, OUTPUT);     // flora> arduino
  
  //Setup Led
   pixels.begin(); // This initializes the NeoPixel library.
   for(int i=0; i < 16; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose green
     pixels.setBrightness(60);
     pixels.show(); // Initialize all pixels to 'off'
   }
   
}

void loop() {

  
  long start = millis();
  long total1 =  cs_12_6.capacitiveSensor(30);
  timer.run();
  
  //Serial.println(total1);  
  
    //----------------------------- DEBUG
   /*char chartotall[sizeof(total1)];
      dtostrf(total1, sizeof(total1),0,chartotall);     
        vw_send((uint8_t *)chartotall,sizeof(chartotall));
       vw_wait_tx();                                          // On attend que le message complet soit envoyé.
       delay(200);  */
       
       
  //----------------------------- TOuch or not
  if (total1 ==0 ){ 
   touch= true;
  } else {
    
    touch = false;
  }
  
 //------------------------------------------------------------------------------------ Debut du cycle
  
  //----------------------------- Change de couleurs 
  if (touch == true && protect == false){ 
   // Serial.println("Couleur cbange");  
    colorChange();
    compteur ++;
    
    protectwaiting = true;
    Serial.println(compteur);
    if(compteur==60){
      Serial.println("compteurOK");
      cycle=true;
    }
    
  }
  
  
  
  //----------------------------- S'envole 
 if (cycle== true && touch == false) {
   Serial.println("Send");   
    Begin();     
 } 
 else if ( touch ==false && cycle == false && protectwaiting == false && fly == false){
   //Serial.println("compteur 0");
   compteur = 0;
   Appel();
 }
 
 if(touch== false){
    protectwaiting = false;
  }
}


