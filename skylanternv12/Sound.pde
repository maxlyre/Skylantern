//------------------------------------ Music declaration
Minim minim;
AudioPlayer Pbase;
AudioPlayer Prouge;
AudioPlayer Pbleu;
AudioPlayer Pcyan;
AudioPlayer Pvert;
AudioPlayer Pjaune;
AudioPlayer Pviolet;
boolean Mteinte = false;
boolean fade = false;
boolean isPlaying = false;

//------------------------------------------------------------------- Musique Methods

void playMusique(int i) {
  println("Play Music Lantern " + i + "\nFADE is " + fade);

  if (lampColor[i]>0 && lampColor[i]< 25) {
    println("Lantern " + i + " is ROUGE " + "Fade is " + fade);
    
    Prouge.setGain(-80);
    Prouge.loop();
    //if (!fade) {
      Prouge.shiftGain(-80, -10, 1000); 
    //  fade = true;
    //} 
  }
  
  else if (lampColor[i]>25 && lampColor[i]< 70) {
    println("Lantern " + i + " is JAUNE " + "Fade is " + fade);
    Pjaune.setGain(-80);
    Pjaune.loop();
    //if (!fade) {
      Pjaune.shiftGain(-80, -10, 1000); 
    //  fade = true;
    //} 
  }
  
  else if (lampColor[i]>70 && lampColor[i]< 140) {
    println("Lantern " + i + " is VERT " + "Fade is " + fade);
    Pvert.setGain(-80);
    Pvert.loop();
    //if (!fade) {
      Pvert.shiftGain(-80, -10, 1000); 
    //  fade = true;
    //} 
  }
  
  else if (lampColor[i]>140 && lampColor[i]< 200) {
    println("Lantern " + i + " is CYAN " + "Fade is " + fade);
    Pcyan.setGain(-80);
    Pcyan.loop();
    //if (!fade) {
      Pcyan.shiftGain(-80, -10, 1000); 
    //  fade = true;
    //} 
  }
  
  else if (lampColor[i]>200 && lampColor[i]< 250) {
    println("Lantern " + i + " is BLEU " + "Fade is " + fade);
    Pbleu.setGain(-80);
    Pbleu.loop();
    //if (!fade) {
      Pbleu.shiftGain(-80, -10, 1000); 
    //  fade = true;
    //}  
  }
  
  else if (lampColor[i]>250 && lampColor[i]< 310) {    
    println("Lantern " + i + " is VIOLET " + "Fade is " + fade);
    Pviolet.setGain(-80);
    Pviolet.loop();
    //if (!fade) {
      Pviolet.shiftGain(-80, -10, 1000); 
    //  fade = true;
    //}  
  }
  
  else if (lampColor[i]>310 && lampColor[i]< 360) {
    println("Lantern " + i + " is ROUGE 2 " + "Fade is " + fade);
    Prouge.setGain(-80);
    Prouge.loop();
    //if (!fade) {
      Prouge.shiftGain(-80, -10, 1000); 
    //  fade = true;
    //} 
  }

  Mteinte = true;
}

void stopMusique() {
  fade = false;
  Prouge.shiftGain(-10, -80, 1000);
  Pjaune.shiftGain(-10, -80, 1000);
  Pvert.shiftGain(-10, -80, 1000);
  Pcyan.shiftGain(-10, -80, 1000);
  Pbleu.shiftGain(-10, -80, 1000);
  //Pmagenta.shiftGain(-10, -80, 1000);
  Pviolet.shiftGain(-10, -80, 1000);


  Pbase.shiftGain(-80, -10, 1000);

  Mteinte = false;
}

