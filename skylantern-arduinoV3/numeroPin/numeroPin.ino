#include <Adafruit_NeoPixel.h>

//Capacitive variable
int capacitivePin = 16; //Numero de la pin
int capacitiveState = 0; //Etat du touch

//Pin de led
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      32

//Initialisation Neopixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1; // delay for half a second

void setup() {
  //Pin du capacitive
  pinMode(capacitivePin, INPUT);

  //Active le capacitive (Numero Pin 5)
  pinMode(5, OUTPUT);
  digitalWrite(5,HIGH);
  
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  //Reception du touch (1 ou 0)
  capacitiveState = digitalRead(capacitivePin);

 // Si sa touch
  if(capacitiveState){
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,255,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  }
  else{
     for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  }
}
