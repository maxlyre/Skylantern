#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <Color.h>

//LeaveMe

//--------------------------------------------------Configuration

//Nom Lantern
int nomLantern = 1;

//Light variable
int minPulse =20; //Brightness Min du Pulse
int maxPulse = 60; // Brightness Max du Pulse
int flyLight = 120; // Brightness en vole

//Configuration reseau
const char* ssid = "SkylanternBox"; //Nom du reseau
const char* password = "Undefined"; // MDP du reseau
const char* mqtt_server = "192.168.1.8"; //Ip du server

//--------------------------------------------------

//Setup Wifi et client
WiFiClient espClient;
PubSubClient client(espClient);
String inputString ="";

//Nom Channel
char lanternState[20];
char lanternColor[20];
char motorState[20];

//Bolean Cycle
boolean motorReady = true;
boolean cycle = false;
boolean fly = false;
boolean touch = false;
boolean warning = false;
boolean warningstate = false;
int compteurTouch =0;

//Pulse Variable
int compteurPulse = minPulse;
boolean sidePulse = true;
    
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
int capacitiveResetcount = 0;

// Which pin on the FLORA is connected to the NeoPixel ring?
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      32

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  
  //Setup connection
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
   
   //Led rouge en attedant l'initialisation des moteurs
   for(int i=0; i < NUMPIXELS; i++){   
     pixels.setPixelColor(i,pixels.Color(0,255,0)); // we choose green
     pixels.setBrightness(minPulse);
     pixels.show();
   }
}

void loop() {
  //si le client se deconnecte
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Recupere les messages dans le channel
  
  if(motorReady){
    stateManage();
  }
  
}
