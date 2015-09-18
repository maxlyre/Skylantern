
//----------------------------- Couleur de la lantern change
void colorChange(){
  rainbow();
     
     for(int i=0; i<NUMPIXELS;i++){
       pixels.setPixelColor(i,pixels.Color(cur_color.red,cur_color.green,cur_color.blue)); 
       pixels.setBrightness(30);
       pixels.show();
     }   
    
    cycle= true;
}


//----------------------------- couleur
void rainbow(){
  hue += 0.003;
  if ( hue >=1 ) hue = 0.01;
  sat = 1.0;
  val = 0.4;
  cur_color.convert_hcl_to_rgb(hue,sat,val);
 // delay(20);
}


//----------------------------- Envoi de la lantern
void Begin(){
  protect = true;
      
      for(int i=30; i<100;i++){
       pixels.setBrightness(i);
       pixels.show();
       delay(10);
     }
      
      
     //---------------- Lance Timer pour extinction
      timer_id1 = timer.setTimeout(51000, End); 
       
       cycle= false; 
}


//----------------------------- Baisse la luminosité
void End() {
   for(int i=100; i>30; i--){ 
     pixels.setBrightness(i);
     pixels.show();
     delay(10);
    
   }
     
   //---------------- Lance Timer qui desactive la protection
   timer_id1 = timer.setTimeout(6500, Protect); 
    
}
 
 
 void Protect(){
    protect=false;
 }
