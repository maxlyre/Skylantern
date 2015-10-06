#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <Color.h>
#include <SimpleTimer.h>
//Add timer reset library

// Update these with values suitable for your network.

const char* ssid = "SkylanternBox"; //Nom du reseau
const char* password = ""; // MDP du reseau
const char* mqtt_server = "192.168.1.8"; //Ip du server

//Setup Wifi et client
WiFiClient espClient;
PubSubClient client(espClient);

//Nom Lantern
int nomLantern = 0;

//Nom Channel
char lanternState[20];
char lanternColor[20];
char motorState[20];

//Bolean Cycle
boolean cycle = false;
boolean fly = false;
boolean touch = false;
int compteur =0;

//Conversion Couleur
Color cur_color = Color(1,1,1);
float hue = 0;
float  sat = 0;
float val=0;
char hueMsg[4];

//Capacitive variable
int capacitivePin = 16; //Numero de la pin
int capacitiveState = 0; //Etat du touch
int capacitiveOn = 5;

// Which pin on the FLORA is connected to the NeoPixel ring?
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      32

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(115200);
  
  //Setup connection
  delay(50);
  setup_name(); // Setup nom lantern
  setup_wifi(); //Connecter l'arduino
  client.setServer(mqtt_server, 1883); // Setup du serveur
  client.setCallback(callback); // Setup Callback

  //Pin du capacitive
  pinMode(capacitivePin, INPUT);

  //Active le capacitive
  pinMode(capacitiveOn, OUTPUT);
  digitalWrite(capacitiveOn,HIGH);

  //Setup Led
   pixels.begin(); // This initializes the NeoPixel library.
   for(int i=0; i < NUMPIXELS; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose green
     pixels.setBrightness(60);
     pixels.show();
   }
}

void loop() {
  //si le client se deconnecte
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Recupere les messages dans le channel

  stateManage();
  
}
