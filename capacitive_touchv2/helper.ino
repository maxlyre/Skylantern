//---------------------------------------------couleur-----------------------------------
void rainbow(){
  hue += 0.06;
  if ( hue >=1 ) hue = 0;
  sat = 1.0;
  val = 0.4;
  delay(20);
}


//----------------------------------------------cycle-----------------------------------
void moteuroff1() {
  myservo.write(90);
  //Serial.print("2");
  timer_id2 = timer.setTimeout(1000, ledoffmoteuron); //-----------------------------------------------------------Durée session Changer le 1000 pour le temps.
}

void ledoffmoteuron() {


     myservo.write(180);
    
    timer_id3 = timer.setTimeout(1000, moteuroff2);

  //Serial.print("3");

}
void moteuroff2() {
   myservo.write(90);
  Serial.write("AO");
  Serial.println(""); // On saute une ligne afin d'avoir plus de clarté.
  protect= false;
}


