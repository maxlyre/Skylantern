void ManageMessage(){
  if (stringComplete) {
    
    inputString.trim();
    Serial.println(inputString);
    
    if(inputString.equals("wificonnected")){
      Serial.println("envoi nom");
      setupName();
    }
    if(inputString == "fly"){
      Up();
      delay(200);
      Serial.write("answer,");
     }
     
    // clear the string: 
    inputString = "";
    stringComplete = false;
  }
}
void serialEvent() {
  while (mySerial.available()) {
    // get the new byte:
    char inChar = (char)mySerial.read();
    
    // if the incoming character is a "," = set a flag
    if (inChar == '\n') { 
      stringComplete = true;
    }
    // add it to the inputString:
    else{
    inputString += inChar;
    }
  }
}

void setupName(){
  char nameSend[3];
  snprintf (nameSend, 3, "n%d", nomMotor);
  mySerial.println(nameSend);
}

