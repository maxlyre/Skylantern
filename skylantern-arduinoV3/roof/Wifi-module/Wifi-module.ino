#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//Name variable
int nomMotor = 0;
boolean nameSetup = false;
char motorState[20]; //Nom du channel du moteur
char lanternState[20]; //Nom du channel de la lantern

// Update these with values suitable for your network.
const char* ssid = "SkylanternBox"; //Nom du reseau
const char* password = "Undefined"; // MDP du reseau
const char* mqtt_server = "192.168.1.8"; //Ip du server

WiFiClient espClient;
PubSubClient client(espClient);
boolean bConnected = false;

//Serial communication
String outputString = ""; 
String inputString ="";
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Serial.begin(9600);
  
  setup_wifi(); //Connecter l'arduino
  client.setServer(mqtt_server, 1883); // Setup du serveur
  client.setCallback(callback);

}

void loop() {
  //Indique au Trinket la connection au wifi
  wifiConnected();
  
  //si le client se deconnecte
  if (!client.connected() && nameSetup) {
    reconnect();
  }
  client.loop(); // Recupere les messages dans le channel


  serialEvent(); //call the function
  
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(outputString);
    
    //recupere le numero du groupe
    if(outputString.charAt(0) == 'n' && nameSetup == false){
       char bufN = outputString.charAt(1);
       nomMotor = bufN-'0';
       setup_name();
     }
    //Si nom setup, envoi les message du trinket au serveur
    else if(nameSetup){
      int str_len = outputString.length() + 1;
      char message_buf[str_len];
      outputString.toCharArray(message_buf,str_len);
      client.publish(motorState, message_buf); // Choix du channel qui envoi
     }
    // clear the string: 
    outputString = "";
    stringComplete = false;
  }

}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    
    // if the incoming character is a "," = set a flag
    if (inChar == '\n') { 
      stringComplete = true;
    }
    // add it to the inputString:
    else{
    outputString += inChar;
    }
  }
}
