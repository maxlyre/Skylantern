

void Up()
{
  Serial.println("\tStep 2 : Up");
        stepperUp();
        irsensor = true;
        mySerial.println("up");
       /* Wire.beginTransmission(I2C_ADDRESS_OTHER);
        Wire.write("up");
        Wire.endTransmission();*/
}

void Wait()
{
    irsensor=false;
    Serial.println("Step 3 : Waiting");
    stepperStop();
    timerStepper = timer.setTimeout(waitTime, Down);
    mySerial.println("wait");
    /*Wire.beginTransmission(I2C_ADDRESS_OTHER);
    Wire.write("fly");
    Wire.endTransmission();*/
}

void Down()
{
    Serial.println("Step 4 : stepper Down");
    stepperDown();
    downState = true;
   /* Wire.beginTransmission(I2C_ADDRESS_OTHER);
    Wire.write("down");
    Wire.endTransmission(); */
    mySerial.println("down");
}

void Stop()
{ 
  
    if(downState){
       if (stepper.distanceToGo() == 0){
        /*Wire.beginTransmission(I2C_ADDRESS_OTHER);
        Wire.write("stop");
        Wire.endTransmission(); */
    
        downState=false;
        Serial.println("Step 5 : Stop");
        mySerial.println("stop");
       }
    }
}
//--------------------------------------- Ordre Moteur
void stepperUp()
{
  stepper.setMaxSpeed(8000);
  stepper.setAcceleration(2500); 
  stepper.move(-900000000);
}

void stepperStop(){
  stepper.move(0); 
  stepper.setSpeed(0);
  stepper.runSpeed();
  stepper.setCurrentPosition(0);
}

void stepperDown()
{
  stepper.setMaxSpeed(8000);
  stepper.setAcceleration(2500);
  stepper.move(stepsdescente);
}

//--------------------------------------- IrSensor
void irSensor(){
  
  if(irsensor){
    int distancelantern= analogRead(1);
    
    if(distancelantern>300){
      countpositif = countpositif+1;
    }else{
      countpositif=0;
    }
    
    if(countpositif == 5 ){ //&& motorReady
    Serial.println("Capteur On");
      Wait();
    }else if (countpositif == 5 && motorReady == false){
      stepperDown();
      
    }
    
    
  }
  
}

void Setupbegin(){
    stepperUp();
    irsensor = true;

}

