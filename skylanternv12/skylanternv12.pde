import processing.serial.*;
import ddf.minim.*;

boolean touch = false;
float[] lampColor = new float [2];
int caseColor;
int nbLantern = 0;
ArrayList<Particule> particules;


//------------------------------------Music declaration
Minim minim;
AudioPlayer Pbase;
AudioPlayer Prouge;
AudioPlayer Pbleu;
AudioPlayer Pcyan;
AudioPlayer Pvert;
AudioPlayer Pjaune;
AudioPlayer Pviolet;
boolean Mteinte = false;

//----------------------Texte
Text text;
int textcount = 0;

Serial myPort;

    

void setup() {
  size(1024 , 768, P2D);
  colorMode(HSB, 360, 100, 100);

  //---------------------------------------------------------Serial Setup---------------------------------------------
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[5], 4800);
  println("\tmyPort is : " + myPort);
  text = new Text();
  
  //--------------------------------------------Particule setup
  particules = new ArrayList<Particule>();

  //---------------------------------------------------------Musique Setup---------------------------------------------
  minim = new Minim(this);


  Pbase = minim.loadFile("base.mp3");
  Prouge = minim.loadFile("rouge.mp3");
  Pviolet = minim.loadFile("violet.mp3");
  Pbleu = minim.loadFile("bleu.mp3");
  Pcyan = minim.loadFile("cyan.mp3");
  Pvert = minim.loadFile("vert.mp3");
  Pjaune = minim.loadFile("jaune.mp3");
  Pbase.loop();
}

//-------------------Draw
void draw() {
  background(360, 100, 0);

  //--------------------------------------------------------Recuperation donnée flora----------------------------------------------------
  while (myPort.available () > 0) {
    
    String inByte = myPort.readStringUntil('\n'); //lecture sur le port
    if (inByte != null) { //regarde si donnée

      String data = trim(inByte.replace("\n", ""));  
        println(data);
        
        //regarde quel lantern
      if (data.equals( "AT")) { 
         caseColor = 0;
         println("Selected Lantern is A\n");
      }
      else if (data.equals( "BT")){
          caseColor = 1;
      }
      
      //récupération de la teinte et assignation dans la case adéquate du tableau
      else {
        float teintecal = float(data); //cast les valeurs de data (en string) en float
        teintecal = map(teintecal, 0, 1, 0, 360);
        int couleur = int(teintecal);
        if (couleur == 0) {} // ne fait rien si la valeur de teinte est nulle 
        else {
          lampColor[caseColor] = couleur;
          println("La Lanterne " + caseColor + " a pris la teinte " + couleur);
        }
      }
      
      //compte le nombre de lanternes activées - ne reçoit que A et B pour l'instant
      if (data.equals( "AT")) {
        nbLantern ++;
      }
      else if (data.equals("BT")){
        nbLantern ++;
      }
     
     //supprime les lanternes au timeout
      if (data.equals("AO") && nbLantern > 0) {
        nbLantern --;
        lampColor[0] = 0;
      }
      else if (data.equals("BO") && nbLantern > 0){
        nbLantern --;
        lampColor[1]=0; //met la couleur à zéro -> stop la génération de particules ?
      }
      println("Nombre de lanternes = " + nbLantern);
      // lancement de l'animation
      if(nbLantern > 0){
        touch = true;
      }
      else {
        touch = false;
      }
    }
  }


  //------------------------------------------------Touch-----------------------------------  

  if (touch) {
   
    if (Mteinte == false) { 
      for(int i=0; i<2;i++){
       if(lampColor[i] != 0){
        playMusique();
       }
      } 
    }
         
    // Particule --------------------------------------------------------------------------------
    // add particule
    for(int i = 0; i < 2; i++){
       if(lampColor[i] != 0){
          particules.add(new Particule(lampColor[i]));
       }
    }
    
    textcount = 1;
  } 
  else {
    //Texte et musique stop
    text.display(textcount);
    textcount = 0;
    //particules.clear();
    //particules.clear();
    if (Mteinte == true) {                       
      stopMusique();
    }
  }
  //----------------Mise à jours particule Particule
  for (int i = 0; i < particules.size(); i ++) {
    particules.get(i).move();
    particules.get(i).display();
    particules.get(i).disparu();
    if (particules.get(i).disparu() == false) {
      particules.remove(i);
    }
  }
  
  frame.setTitle("fps"+round(frameRate));
  
}

//-------------------------------------------------------------------Musique
void playMusique() {
  println("GoTrue");
  for(int i=0; i<2;i++){
    
  
  Pbase.pause();

  if (lampColor[i]>0 && lampColor[i]< 25) {
    Prouge.loop();
  }
  else if (lampColor[i]>25 && lampColor[i]< 70) {
    Pjaune.loop();
  }
  else if (lampColor[i]>70 && lampColor[i]< 140) {
    Pvert.loop();
  }
  else if (lampColor[i]>140 && lampColor[i]< 200) {
    Pcyan.loop();
  }
  else if (lampColor[i]>200 && lampColor[i]< 250) {
    Pbleu.loop();
  }
  else if (lampColor[i]>250 && lampColor[i]< 310) {
    Pviolet.loop();
  }
  else if (lampColor[i]>310 && lampColor[i]< 360) {
    Prouge.loop();
  }
  }
  Mteinte = true;
}

void stopMusique() {

  Prouge.pause();
  Pjaune.pause();
  Pvert.pause();
  Pcyan.pause();
  Pbleu.pause();
  //Pmagenta.pause();
  Pviolet.pause();


  Pbase.loop();

  Mteinte = false;
}

