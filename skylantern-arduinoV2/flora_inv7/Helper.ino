//----------------------------- Couleur de la lantern change
void colorChange(){
  rainbow();
     
     for(int i=0; i<16;i++){
       pixels.setPixelColor(i,pixels.Color(cur_color.red,cur_color.green,cur_color.blue)); 
       pixels.setBrightness(60);
       pixels.show();
     }   
    
    //cycle= true;
}

//----------------------------- couleur
void rainbow(){
  hue += 0.0008;
  if ( hue >=1 ) hue = 0.01;
  sat = 1.0;
  val = 0.4;
  cur_color.convert_hcl_to_rgb(hue,sat,val);
  //delay(10);
}


//----------------------------- Envoi de la lantern
void Begin(){
  protect = true;
     fly = true;
      for(int i=60; i<200;i++){
       pixels.setBrightness(i);
       pixels.show();
       delay(10);
     }
       
    //---------------- Envoi Lettre
        //vw_send((uint8_t *)"A", 1); //<----------------------------------------------------------------------!Nom Lantern
        //vw_wait_tx();                                          
        //delay(200);
     
     //---------------- Envoi teinte
     char charteinte[sizeof(hue)];
      dtostrf(hue, sizeof(hue),2,charteinte);
      char sendMessage[sizeof(charteinte)+1];
      sendMessage[0]=nomLantern;
      for(int i=0; i< sizeof(charteinte); i++){
        sendMessage[i+1] = charteinte[i];
      }
      vw_send((uint8_t *)sendMessage,sizeof(sendMessage));
      vw_wait_tx();                                          
      delay(200); 
      
      
     //---------------- Lance Timer pour extinction
      timer_id1 = timer.setTimeout(23500, End); 
       
       protectwaiting = false;
       cycle= false;
}


//----------------------------- Baisse la luminosité
void End() {
   for(int i=200; i>60; i--){ 
     pixels.setBrightness(i);
     pixels.show();
     delay(10);
    
   }
   for(int i=0; i < 16; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose green
     pixels.show(); // Initialize all pixels to 'off'
   }
   //---------------- Envoi l'ordre d'arrêt
  // vw_send((uint8_t *)"AO", 2);
    // vw_wait_tx();      // On attend que le message complet soit envoyé.
     //delay(200);
     
   //---------------- Lance Timer qui desactive la protection
   timer_id1 = timer.setTimeout(1500, Protect); 
    fly=false;
}
 
 
 void Protect(){
    protect=false;
 }
 void Appel(){
   for(int i=0; i < 16; i++){   
     pixels.setPixelColor(i,pixels.Color(255,255,255)); // we choose green
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
