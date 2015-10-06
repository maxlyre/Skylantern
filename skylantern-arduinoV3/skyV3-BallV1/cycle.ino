void stateManage(){
  
  //Reception du touch (1 ou 0)
  capacitiveState = digitalRead(capacitivePin);
  if (capacitiveState == 0){ 
    touch = true;
  } else { 
    touch = false;
  }
  
  if(touch && fly == false){//----- Quand toucher
    colorChange();
    compteur ++;

    //Serial.println(compteur);
    if(compteur == 60){
      client.publish(lanternState, "touch");
      Serial.println("compteurOK");
      cycle = true;
    }
  }
  
  if (touch == false && cycle == true && fly == false) {//----- S'envole 
    flyState();     
  } 
  else if (touch == false && cycle == false && fly == false){ //----- Reste au sol 
    compteur = 0;
    Appel();
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
  hue += 0.0008;
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
      for(int i=60; i<200;i++){
       pixels.setBrightness(i);
       pixels.show();
       delay(10);
     }
     
}


//----------------------------- Baisse la luminosité
void downState() {
   for(int i=200; i>60; i--){ 
     pixels.setBrightness(i);
     pixels.show();
     delay(10);
   }
   Serial.println("light low");

   capacitiveReset();
}
//----------------------------- Remet au blanc
void endState(){
   for(int i=0; i < NUMPIXELS; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose green
     pixels.show(); // Initialize all pixels to 'off'
   }
    client.publish(lanternState, "wait");
    client.publish(lanternColor, "0");
    fly=false;
    Serial.println("fly off");
}

 void Appel(){ //Change pulse, voir bookmark A VOIR
   for(int i=0; i < NUMPIXELS; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose white
     pixels.show(); // Initialize all pixels to 'off'
     delay(30);
   }
    Serial.print("wave");
     for(int i=40; i<130; i++){ 
       pixels.setBrightness(i);
       pixels.show();
       delay(7);
       }
       for(int i=130; i>40; i--){ 
       pixels.setBrightness(i);
       pixels.show();
       delay(7);
       }
 }

 void capacitiveReset(){
  digitalWrite(capacitiveOn,LOW);
  delay(20);
  digitalWrite(capacitiveOn,HIGH);
 
 }// Add timer pour le capacitive

