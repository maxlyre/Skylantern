#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

//Name variable
int nomMotor = 0;
boolean nameSetup = false;
char motorState[20];
char lanternState[20];

const char* ssid = "SkylanternBox"; //Nom du reseau
const char* password = ""; // MDP du reseau
const char* mqtt_server = "192.168.0.8"; //Ip du server

WiFiClient espClient;
PubSubClient client(espClient);

//I2C communication
#define I2C_ADDRESS_OTHER 0x2
#define I2C_ADDRESS_ME 0x1

String outputString = ""; 
String inputString ="";

void setup() {
  Serial.begin(115200);
  setup_wifi(); //Connecter l'arduino
  client.setServer(mqtt_server, 1883); // Setup du serveur
  client.setCallback(callback);

  Serial.begin(9600);
  Wire.begin(4, 5);
  Wire.begin(I2C_ADDRESS_ME);
  Wire.onReceive(receiveI2C);
}

void loop() {
  //si le client se deconnecte
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Recupere les messages dans le channel

}

void receiveI2C(int howMany) {
 outputString ="";
 while (Wire.available() > 0) {
  char inChar = (char)Serial.read();
  outputString += inChar;
 }
 Serial.println();
 
 if(outputString.charAt(0) == 'n' && nameSetup == false){
   char bufN = outputString.charAt(1);
   nomMotor = bufN - '0';
   setup_name();
 }
 else if(nameSetup){
  int str_len = outputString.length() + 1;
  char message_buf[str_len];
  outputString.toCharArray(message_buf,str_len);
  client.publish(motorState, message_buf); // Choix du channel qui envoi
 }
}
