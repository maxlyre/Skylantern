void setup_name(){
  snprintf (motorState, 20, "Sky/%d/motor", nomMotor); //Channel statut lantern
  Serial.print("Channel motor statut : ");
  Serial.println(motorState);

  snprintf (lanternState, 20, "Sky/%d/lantern", nomMotor); //Channel statut lantern
  Serial.print("Channel Lantern statut : ");
  Serial.println(lanternState);
  
  nameSetup = true;
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
  
  bConnected =true;
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create random name client
    char nameClient[20];
    snprintf (nameClient, 20, "MotorClient%d", nomMotor); 
    
    //connection
    if (client.connect(nameClient)) {
      Serial.print("MQTT connected with Client :");
      Serial.println(nameClient);
      
      // ... and resubscribe
      client.subscribe(lanternState); //Choix du chanel de recuperation
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void wifiConnected(){
  if(bConnected && nameSetup == false){
    Serial.println("wificonnected");
    delay(100);
  }
}

