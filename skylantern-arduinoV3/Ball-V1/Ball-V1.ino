#include <SimpleTimer.h>
#include <Adafruit_NeoPixel.h>
#include <color.h>

//Nom Lantern
char nomLantern = 'A';

//Timer
SimpleTimer timer;
int timer_id1;

//Capacitive 
int capacitivePin = 16;
int capacitiveState = 0;

//Compteur de Touch
int touchcount=0;
int nottouchcount=0;

//Bolean Cycle
boolean touch = false;
boolean cycle = false;
boolean protect = false;
boolean time=false;

//Conversion Couleur
Color cur_color = Color(1,1,1);
float hue = 0;
float  sat = 0;
float val=0;

// Which pin on the FLORA is connected to the NeoPixel ring?
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      32
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  //Setup Radio
  Serial.begin(115200);
   
  pinMode(capacitivePin, INPUT);
  pinMode(5,OUTPUT);
  digitalWrite(5, HIGH);
  //Setup Led
   pixels.begin(); // This initializes the NeoPixel library.
   for(int i=0; i < NUMPIXELS; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,0)); // we choose green
     pixels.setBrightness(10);
     pixels.show(); // Initialize all pixels to 'off'
   }
   
}

void loop() {
  timer.run();
  
  //Serial.println(total1);  
  
    //----------------------------- DEBUG
   /*char chartotall[sizeof(total1)];
      dtostrf(total1, sizeof(total1),0,chartotall);     
        vw_send((uint8_t *)chartotall,sizeof(chartotall));
       vw_wait_tx();                                          // On attend que le message complet soit envoyé.
       delay(200);  */
       
   capacitiveState = digitalRead(capacitivePin);
       
  //----------------------------- Incremente touch
  if (capacitiveState == 1 ){ 
    nottouchcount = 0;
    touchcount=touchcount+1;
    //touch = true;
  } else {
    nottouchcount = nottouchcount+1;
    touchcount = 0;
    //touch = false;
  }
  
  //----------------------------- Touch, Si 3 loop true : touch = true
  if(touchcount == 5){
    touch = true;
    touchcount=0;
  }else if(nottouchcount == 20){
    touch = false;
    nottouchcount=0;
  }
       
 //------------------------------------------------------------------------------------ Debut du cycle
  
  //----------------------------- Change de couleurs 
  if (touch == true && protect == false){ 
    Serial.println("Couleur cbange");  
    colorChange(); 
    
  }
  
  //----------------------------- S'envole 
 if (cycle== true && touch == false) {
   Serial.println("Send");   
    Begin();
      
 }
}

