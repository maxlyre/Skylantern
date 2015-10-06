

void GoToStep1()
{
  Serial.println("\tStep 2 : Up");
        stepperUp();
        irsensor = true;
        
        Wire.beginTransmission(I2C_ADDRESS_OTHER);
        Wire.write("up");
        Wire.endTransmission();
}

void GoToStep2()
{
    irsensor=false;
    Serial.println("Step 3 : Waiting");
    stepperStop();
    timerStepper = timer.setTimeout(waitTime, GoToStep3);

    Wire.beginTransmission(I2C_ADDRESS_OTHER);
    Wire.write("fly");
    Wire.endTransmission();
}

void GoToStep3()
{
    Serial.println("Step 4 : stepper Down");
    stepperDown();
    downState = true;
    Wire.beginTransmission(I2C_ADDRESS_OTHER);
    Wire.write("down");
    Wire.endTransmission(); 
}

void GoToStep4()
{
   if(downState){
     if (stepper.distanceToGo() == 0){
      Wire.beginTransmission(I2C_ADDRESS_OTHER);
      Wire.write("stop");
      Wire.endTransmission(); 
     }
     downState=false;
   }
   Serial.println("Step 5 : Stop");
}
//--------------------------------------- Ordre Moteur
void stepperUp()
{
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(2500); 
  stepper.move(-900000000);
}

void stepperStop(){
  stepper.move(0); 
  stepper.setSpeed(0);
  stepper.runSpeed();
}

void stepperDown()
{
  stepper.setMaxSpeed(6000);
  stepper.setAcceleration(2500);
  stepper.move(stepsdescente);
}
//--------------------------------------- IrSensor
void irSensor(){
  
  if(irsensor){
    int distancelantern= analogRead(8);
    
    if(distancelantern>250){
      countpositif = countpositif+1;
    }else{
      countpositif=0;
    }
    
    if(countpositif == 5){
    Serial.println("Capteur On");
      GoToStep2();
    }
    
    
  }
  
}


