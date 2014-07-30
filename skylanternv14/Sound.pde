//------------------------------------ Music declaration
Minim minim;
AudioPlayer Pbase;
AudioPlayer Prouge;
AudioPlayer Pbleu;
AudioPlayer Pcyan;
AudioPlayer Pvert;
AudioPlayer Pjaune;
AudioPlayer Pviolet;
AudioPlayer Pmagenta;


//------------------------------------------------------------------- Musique Methods

void playMusique(int i) {
  println("Play Music Lantern " + i);

  if (lampColor[i]>0 && lampColor[i]< 25) {
    println("Lantern " + i + " is ROUGE ");
    
    Prouge.setGain(-80);
    Prouge.loop();

      Prouge.shiftGain(-80, 0, 1000); 

  }
  
  else if (lampColor[i]>25 && lampColor[i]< 90) {
    println("Lantern " + i + " is JAUNE ");
    Pjaune.setGain(-80);
    Pjaune.loop();

      Pjaune.shiftGain(-80, 0, 1000); 

  }
  
  else if (lampColor[i]>90 && lampColor[i]< 140) {
    println("Lantern " + i + " is VERT ");
    Pvert.setGain(-80);
    Pvert.loop();

      Pvert.shiftGain(-80, 0, 1000); 

  }
  
  else if (lampColor[i]>140 && lampColor[i]< 200) {
    println("Lantern " + i + " is CYAN");
    Pcyan.setGain(-80);
    Pcyan.loop();

      Pcyan.shiftGain(-80, 0, 1000); 
 
  }
  
  else if (lampColor[i]>200 && lampColor[i]< 250) {
    println("Lantern " + i + " is BLEU");
    Pbleu.setGain(-80);
    Pbleu.loop();

      Pbleu.shiftGain(-80, 0, 1000); 
 
  }
  
  else if (lampColor[i]>250 && lampColor[i]< 310) {    
    println("Lantern " + i + " is VIOLET");
    Pviolet.setGain(-80);
    Pviolet.loop();

      Pviolet.shiftGain(-80, 0, 1000); 
 
  }
  
  else if (lampColor[i]>310 && lampColor[i]< 360) {
    println("Lantern " + i + " is ROUGE 2");
    Prouge.setGain(-80);
    Prouge.loop();
    Prouge.shiftGain(-80, 0, 1000); 
  }
   else if (lampColor[i]>310 && lampColor[i]< 360) {
    println("Lantern " + i + " is MAGENTA");
    Pmagenta.setGain(-80);
    Pmagenta.loop();
    Pmagenta.shiftGain(-80, 0, 1000); 
  }

}

void stopZik(int i) {
  println("Stop Music Lantern " + i);

  if (lampColor[i]>0 && lampColor[i]< 25) {
    println("Lantern " + i + " stops ROUGE ");
    Prouge.shiftGain(0, -80, 1000);
  }
  
  else if (lampColor[i]>25 && lampColor[i]< 90) {
    println("Lantern " + i + " stops JAUNE ");
    Pjaune.shiftGain(0, -80, 1000); 

  }
  
  else if (lampColor[i]>90 && lampColor[i]< 140) {
    println("Lantern " + i + " stops VERT ");
    Pvert.shiftGain(0, -80, 1000); 

  }
  
  else if (lampColor[i]>140 && lampColor[i]< 200) {
    println("Lantern " + i + " stops CYAN");
    Pcyan.shiftGain(0, -80, 1000); 
 
  }
  
  else if (lampColor[i]>200 && lampColor[i]< 250) {
    println("Lantern " + i + " stops BLEU");
    Pbleu.shiftGain(0, -80, 1000); 
 
  }
  
  else if (lampColor[i]>250 && lampColor[i]< 310) {    
    println("Lantern " + i + " stops VIOLET");
    Pviolet.shiftGain(0, -80, 1000); 
 
  }
  
  else if (lampColor[i]>310 && lampColor[i]< 360) {
    println("Lantern " + i + " stops ROUGE 2");
    Prouge.shiftGain(0, -80, 1000); 
  }
  else if (lampColor[i]>310 && lampColor[i]< 360) {
    println("Lantern " + i + " stops MAGENTA");
    Pmagenta.shiftGain(0, -80, 1000); 
  }

}


void stopFullMusique() {
  println("STOP ALL ZIK & RESTART BASE !");
  float gainRouge = Prouge.getGain();
  float gainJaune = Pjaune.getGain();
  float gainVert = Pvert.getGain();
  float gainCyan = Pcyan.getGain();
  float gainBleu = Pbleu.getGain();
  float gainViolet = Pviolet.getGain();
  
  Prouge.shiftGain(gainRouge, -80, 1000);
  Pjaune.shiftGain(gainJaune, -80, 1000);
  Pvert.shiftGain(gainVert, -80, 1000);
  Pcyan.shiftGain(gainCyan, -80, 1000);
  Pbleu.shiftGain(gainBleu, -80, 1000);
  Pviolet.shiftGain(gainViolet, -80, 1000);

 
}


