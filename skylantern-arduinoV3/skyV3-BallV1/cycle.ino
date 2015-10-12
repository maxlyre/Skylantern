void stateManage(){
  
  //Reception du touch (1 ou 0)
  capacitiveState = digitalRead(capacitivePin);
  if (capacitiveState == 0){ 
    touch = true;
  } else { 
    touch = false;
  }

  //Compte le temps toucher et change couleurs
  if(touch && fly == false){
    colorChange();
    
    compteurTouch ++;
    if(compteurTouch == 50){
      client.publish(lanternState, "touch");
      Serial.println("compteurOK");
      cycle = true;
    } else if(compteurTouch > 1000){
      capacitiveReset();
      cycle = false;
      touch = false;
      Serial.println("Debloque touch");
    }
  }

  //Action
  if (touch == false && cycle == true && fly == false) {//----- S'envole 
    capacitiveResetcount = 0;
    flyState();    
  } 
  else if (touch == false && cycle == false && fly == false){ //----- Reste au sol 
    compteurTouch = 0; //Remet a 0 le touch si trop court
    Appel(); //Animation Pulse

    //Reset le capacitive toute les 
    capacitiveResetcount ++;
    if (capacitiveResetcount == 1500) {
        capacitiveReset();
        capacitiveResetcount = 0;
    }
  } 
}

//----------------------------- Couleur de la lantern change
void colorChange(){
  rainbow();
     
     for(int i=0; i<NUMPIXELS;i++){
       pixels.setPixelColor(i,pixels.Color(cur_color.red,cur_color.green,cur_color.blue)); 
       pixels.setBrightness(60);
       pixels.show();
     }   
}

//----------------------------- couleur
void rainbow(){
  hue += 0.003
  if ( hue >=1 ) hue = 0.01;
  sat = 1.0;
  val = 0.4;
  cur_color.convert_hcl_to_rgb(hue,sat,val);
}


//----------------------------- Envoi de la lantern
void flyState(){  
     fly = true;
     cycle= false;

     //Send message
      client.publish(lanternState, "fly");
      
      dtostrf(hue, 4,2,hueMsg);
      Serial.print("Envoi :"); Serial.println(hueMsg);
      client.publish(lanternColor, hueMsg); //Envoi le statut de base
      Serial.println("Fly");
     
     //Allume lantern
      for(int i=compteurPulse; i<flyLight;i++){
       pixels.setBrightness(i);
       pixels.show();
       delay(10);
     }
     
}


//----------------------------- Baisse la luminosité
void downState() {
   for(int i=flyLight; i>compteurPulse; i--){ 
     pixels.setBrightness(i);
     pixels.show();
     delay(20);
   }
   Serial.println("light low");

   capacitiveReset();
}
//----------------------------- Remet au blanc
void endState(){
   for(int i=0; i < NUMPIXELS; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose white
     pixels.show(); // Initialize all pixels to 'off'
     delay(40);
   }
    client.publish(lanternState, "wait");
    client.publish(lanternColor, "0");
    fly=false;
    Serial.println("fly off");
}

 void Appel(){
  for(int i=0; i < NUMPIXELS; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose white
     pixels.show(); // Initialize all pixels to 'off'
   }

    if(compteurPulse >= maxPulse){
      sidePulse = false;
      Serial.print("wave");
    }else if(compteurPulse <= minPulse){
      sidePulse = true;
    }
    
    if(sidePulse){
      compteurPulse++;
    }else{
      compteurPulse--;
    }
    pixels.setBrightness(compteurPulse);
    pixels.show();
 }

 void capacitiveReset(){
  digitalWrite(capacitiveOn,LOW);
  delay(20);
  digitalWrite(capacitiveOn,HIGH);
  Serial.println("Reset");
 }

