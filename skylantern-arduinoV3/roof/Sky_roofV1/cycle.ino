
//--------------------------------------- Etape
void Up()
{
  Serial.println("\tStep 2 : Up");
        stepperUp();
        irsensor = true;
        mySerial.println("up");
}

void Wait()
{
    irsensor=false;
    Serial.println("Step 3 : Waiting");
    stepperStop();
    timerStepper = timer.setTimeout(waitTime, Down);
    mySerial.println("wait");
}

void Down()
{
    Serial.println("Step 4 : stepper Down");
    stepperDown();
    downState = true;
    mySerial.println("down");
}

void Stop()
{ 
  
    if(downState && stepper.distanceToGo() == 0){
        if(motorReady == false){
            SetupMotor(3);
        }
        else if(warning==true){
            Up();
            mySerial.println("warningStop");
        }
        else{
          Serial.println("Step 5 : Stop");
          mySerial.println("stop");
        } 
        downState=false;
    }
    
}
//--------------------------------------- Ordre Moteur
void stepperUp()
{
  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(2500); 
  stepper.move(900000000);
}

void stepperStop(){
  stepper.move(0); 
  stepper.setSpeed(0);
  stepper.runSpeed();
  stepper.setCurrentPosition(0);
}

void stepperDown()
{
  stepper.setMaxSpeed(10000);
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
    
    if(countpositif == 5 && motorReady){
    Serial.println("Capteur On");
      Wait();
      warningcount=0;
    }else if (countpositif == 5 && motorReady == false){
      SetupMotor(2);
    }
       
  } 
  
}

//--------------------------------------- Setup du plafond
void SetupMotor(int gotoStep){
    switch (gotoStep) {
    case 1:
      Serial.println("Setup step 1");
      mySerial.println("Setup step 1");
      stepperUp();
      irsensor = true;
      break;
    case 2:
      Serial.println("Setup step 2");
      mySerial.println("Setup step 2");
      stepperStop();
      stepperDown();
      irsensor = false;
      downState = true;
      break;
    case 3:
      Serial.println("ready");
      mySerial.println("ready");
      motorReady = true;
      warningSetup = warningSetup + 5000;
      break; 
  }
}

void Warning(){

      if(motorReady && irsensor){
          warningcount = warningcount + 30;

          if(warningcount > warningSetup){
              Serial.println("Warning");
              mySerial.println("warningON");
              stepperStop();
            
              stepper.setMaxSpeed(10000);
              stepper.setAcceleration(2500);
              //stepper.move(2000);
              stepper.runToNewPosition(2000);
              
              Serial.println("Warning Stop");
              mySerial.println("warningOFF");
              Up();
              /*downState = true;
              warning = true;
              irsensor = false;
              warningcount=0;*/
          }
          
      }
}

