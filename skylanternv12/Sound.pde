//------------------------------------ Music declaration
Minim minim;
AudioPlayer Pbase;
AudioPlayer Prouge;
AudioPlayer Pbleu;
AudioPlayer Pcyan;
AudioPlayer Pvert;
AudioPlayer Pjaune;
AudioPlayer Pviolet;


//------------------------------------------------------------------- Musique Methods

void playMusique(int i) {
  println("Play Music Lantern " + i);

  if (lampColor[i]>0 && lampColor[i]< 25) {
    println("Lantern " + i + " is ROUGE ");
    
    Prouge.setGain(-80);
    Prouge.loop();

      Prouge.shiftGain(-80, -10, 1000); 

  }
  
  else if (lampColor[i]>25 && lampColor[i]< 70) {
    println("Lantern " + i + " is JAUNE ");
    Pjaune.setGain(-80);
    Pjaune.loop();

      Pjaune.shiftGain(-80, -10, 1000); 

  }
  
  else if (lampColor[i]>70 && lampColor[i]< 140) {
    println("Lantern " + i + " is VERT ");
    Pvert.setGain(-80);
    Pvert.loop();

      Pvert.shiftGain(-80, -10, 1000); 

  }
  
  else if (lampColor[i]>140 && lampColor[i]< 200) {
    println("Lantern " + i + " is CYAN");
    Pcyan.setGain(-80);
    Pcyan.loop();

      Pcyan.shiftGain(-80, -10, 1000); 
 
  }
  
  else if (lampColor[i]>200 && lampColor[i]< 250) {
    println("Lantern " + i + " is BLEU");
    Pbleu.setGain(-80);
    Pbleu.loop();

      Pbleu.shiftGain(-80, -10, 1000); 
 
  }
  
  else if (lampColor[i]>250 && lampColor[i]< 310) {    
    println("Lantern " + i + " is VIOLET");
    Pviolet.setGain(-80);
    Pviolet.loop();

      Pviolet.shiftGain(-80, -10, 1000); 
 
  }
  
  else if (lampColor[i]>310 && lampColor[i]< 360) {
    println("Lantern " + i + " is ROUGE 2");
    Prouge.setGain(-80);
    Prouge.loop();
    Prouge.shiftGain(-80, -10, 1000); 
  }

}

void stopMusique() {
  println("STOP ZIK");
  Prouge.shiftGain(-10, -80, 1000);
  Pjaune.shiftGain(-10, -80, 1000);
  Pvert.shiftGain(-10, -80, 1000);
  Pcyan.shiftGain(-10, -80, 1000);
  Pbleu.shiftGain(-10, -80, 1000);
  Pviolet.shiftGain(-10, -80, 1000);

  Pbase.shiftGain(-80, -10, 1000);
  isBase = true;
}

