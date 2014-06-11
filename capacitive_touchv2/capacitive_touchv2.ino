#include <SimpleTimer.h>
#include <Servo.h> 
#include <Adafruit_NeoPixel.h>
#include <color.h>




Servo myservo;

//Timer

SimpleTimer timer;
int timer_id1;
int timer_id2;
int timer_id3;

//Capacitive
int  i;
unsigned int x, y;
float accum, fout, fval= .07;    // these are variables for a simple low-pass (smoothing) filter - fval of 1 = no filter - .001 = max filter
int SwitchPin;
boolean touch = false;
boolean cycle = false;
boolean protect = false;



Color cur_color = Color(1,1,1);
float hue = 0;
float  sat = 0;
float val=0;

float sendcolor;
// Which pin on the FLORA is connected to the NeoPixel ring?
//#define PIN            3

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

//testRGB
const int greenLEDPin = 3;
const int redLEDPin = 6;
const int blueLEDPin = 5;

void setup() {
  Serial.begin(4800);
  int newval;

  pinMode(8, OUTPUT);     // output pin
  pinMode(9, INPUT);      // input pin
  pinMode(10, OUTPUT);    // guard pin
  digitalWrite(10, LOW);
  myservo.attach(10);
  myservo.write(90);

  /* pixels.begin(); // This initializes the NeoPixel library.
   for(i=0; i < 8; i++){
   
   pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose green
   pixels.setBrightness(10);
   pixels.show(); // Initialize all pixels to 'off'
   }
   */
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
   
   
}

void loop() {

  //Boucle capacitive
  y = 0;        // clear out variables
  x = 0;

  for (i=0; i < 4 ; i++ ){       // do it four times to build up an average - not really neccessary but takes out some jitter

      // LOW-to-HIGH transition
    // Same as line below -  shows programmer chops but doesn't really buy any more speed
    digitalWrite(8, HIGH);    


    // while the sense pin is not high
    while (digitalRead(9) != 1){     // same as above port manipulation above - only 20 times slower!                
      x++;
    }
    delay(1);

    //  HIGH-to-LOW transition
    // Same as line below - these shows programmer chops but doesn't really buy any more speed
    digitalWrite(8, LOW);              
    // while pin is not low  -- same as below only 20 times faster
    while(digitalRead(9) != 0 ) {     // same as above port manipulation - only 20 times slower!
      y++;  
    }

    delay(1);
  }

  fout =  (fval * (float)x) + ((1-fval) * accum);  // Easy smothing filter "fval" determines amount of new data in fout
  accum = fout; 


  // AU TOUCH 
  timer.run();
  
  if (fout > 40){ 
    touch = true;
  } else {
    touch = false;
  }
  
  if (touch == true && protect == false){ 

    /* for(i=10; i<255;i++){
     //pixels.setPixelColor(i,pixels.Color(150,150,150)); 
     pixels.setBrightness(i);
     pixels.show();
     delay(10);
     }*/


    rainbow();
    sendcolor=hue;
    cycle= true;
    //Serial.println("1");
  }
 // Serial.println(fout);
  if (cycle== true && touch == false) {
    Serial.println(sendcolor);
    Serial.println(""); // On saute une ligne afin d'avoir plus de clarté.
      Serial.write("AT");
      Serial.println(""); // On saute une ligne afin d'avoir plus de clarté.
      protect = true;
      myservo.write(0);
        timer_id1 = timer.setTimeout(1000, moteuroff1);
       cycle= false;
    }
}

