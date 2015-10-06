void setup_name(){
  snprintf (motorState, 20, "Sky/%ld/motor", nomMotor); //Channel statut lantern
  Serial.print("Channel motor statut : ");
  Serial.println(motorState);

  snprintf (lanternState, 20, "Sky/%ld/lantern", nomMotor); //Channel statut lantern
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
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
  if(nameSetup){
    Wire.beginTransmission(I2C_ADDRESS_OTHER);
    Wire.write(payload,length);
    Serial.print("Transfer vers trinket");
    //Serial.println((char)payload);
    Wire.endTransmission();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
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
