

void stepper0GoToStep1()
{
  Serial.println("\tStep 2 : servo Up");
        stepper0Up();
        irsensor0 = true;
}

void stepper0GoToStep2()
{
  stepper0Stop();
  
  Serial.println("Step 2 : Stop");
}

void stepper0GoToStep3()
{
  irsensor0=false;
   Serial.println("Step 3 : Waiting");
    stepper0Stop();
    timerStepper0 = timer.setTimeout(25000, stepper0GoToStep4);
}

void stepper0GoToStep4()
{
   Serial.println("Step 4 : stepper Down");
    stepper0Down();
    Serial.println("AO");
}
//------------------------------------------------------------------------- Ordre Moteur
void stepper0Up()
{
  stepper0.setMaxSpeed(6000);
  stepper0.setAcceleration(2500); 
  stepper0.move(-900000000);
}

void stepper0Stop(){
  stepper0.move(0); 
  stepper0.setSpeed(0);
  stepper0.runSpeed();
  //stepper0.stop();
}

void stepper0Down()
{
  stepper0.setMaxSpeed(6000);
  stepper0.setAcceleration(2500);
  stepper0.move(7500);
  Serial.println("Step 5 : Stop");
}

//-------------------------------------------------------------------------------------------Stepper 2
void stepper1GoToStep1()
{
  Serial.println("\tStep 2B : servo Up");
        stepper1Up();
        irsensor1 = true;
}
void stepper1GoToStep2()
{
  stepper1Stop();
  
  Serial.println("Step 2B : Stop");
}

void stepper1GoToStep3()
{
  irsensor1=false;
   Serial.println("Step 3B : Waiting");
    stepper1Stop();
    timerStepper1 = timer.setTimeout(25000, stepper1GoToStep4);
}

void stepper1GoToStep4()
{
   Serial.println("Step 4B : stepper Down");
    stepper1Down();
    Serial.println("BO");
}
//------------------------------------------------------------------------- Ordre Moteur
void stepper1Up()
{
     stepper1.setMaxSpeed(6000);
  stepper1.setAcceleration(2500); 
  stepper1.move(-900000000);
}

void stepper1Stop(){
    stepper1.move(0); 
  stepper1.setSpeed(0);
  stepper1.runSpeed();
  //stepper0.stop();
}

void stepper1Down()
{
   stepper1.setMaxSpeed(6000);
  stepper1.setAcceleration(2500);
  stepper1.move(8000);
   Serial.println("Step 5B : Stop");
}

void irSensor(){
  
  if(irsensor0){
    int distancelantern0= analogRead(8);
    
    if(distancelantern0>250){
      countpositif0 = countpositif0+1;
    }else{
      countpositif0=0;
    }
    
    if(countpositif0 == 5){
    Serial.println("CapteurA On");
      stepper0GoToStep3();
    }
    
    
  }
  
  if(irsensor1){
    int distancelantern1= analogRead(9);
    if(distancelantern1>250){
      countpositif1 = countpositif1+1;
    }else{
      countpositif1=0;
    }
    
    if(countpositif1 == 5){
    Serial.println("CapteurB On");
      stepper1GoToStep3();
    }
  }
  
}


