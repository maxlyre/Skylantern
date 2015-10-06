void receiveI2C(int howMany) {
  inputString ="";
 while (Wire.available() > 0) {
  char inChar = (char)Serial.read();
  inputString += inChar;
 }
 Serial.println();
 
 if(inputString.charAt(0) == 'f'){
   GoToStep1();
 }
}

void setupName(){
        Wire.beginTransmission(I2C_ADDRESS_OTHER);
        Wire.write("n");
        Wire.write(nomMotor);
        Wire.endTransmission();
}

