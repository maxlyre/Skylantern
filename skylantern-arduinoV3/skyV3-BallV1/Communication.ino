void setup_name(){
  snprintf (lanternState, 20, "Sky/%ld/lantern", nomLantern); //Channel statut lantern
  Serial.print("Channel Lantern statut : ");
  Serial.println(lanternState);
  
  snprintf (lanternColor, 20, "Sky/%ld/color", nomLantern); //Channel couleurs
  Serial.print("Channel Lantern color : ");
  Serial.println(lanternColor);
  
  snprintf (motorState, 20, "Sky/%ld/motor", nomLantern); //Channel statut moteur
  Serial.print("Channel Motor statut : ");
  Serial.println(motorState);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  inputString="";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    inputString += (char)payload[i];
  }
  Serial.println();
  
  // Filtre suivant message
  if (inputString == "ready") {
    motorReady = true; //Active la lampe + Mpteur ready
  } else if (inputString == "down" && fly){
    downState(); //Descente des lampe
  }else if (inputString == "stop" && fly){
    endState(); //Arret des moteurs en position basse
  }

}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

     // Create random name client
    char nameClient[20];
    snprintf (nameClient, 20, "LanternClient%d", nomLantern);
        
    // Attempt to connect
    if (client.connect(nameClient)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(lanternState, "ready"); //Envoi le statut de base
      // ... and resubscribe
      client.subscribe(motorState); //S'inscrit au channel statut du moteurs
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
