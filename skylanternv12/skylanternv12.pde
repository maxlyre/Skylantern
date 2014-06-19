import processing.serial.*;
import ddf.minim.*;

float temp = random(1)*768;
boolean touch = false;
float[] lampColor = new float [2];
int caseColor;
int nbLantern = 0;
ArrayList<Particule> particules;
int hue = 180;
float visible = 125;
boolean restart = false;
boolean isBase = true;



//----------------------Texte
Text text;
int textcount = 0;

Serial myPort;



void setup() {
  size( 1024, 768, P2D);
  colorMode(HSB, 360, 100, 100);
  //---------------------------------------------------------Serial Setup---------------------------------------------
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 4800);
  println("\tmyPort is : " + myPort);
  text = new Text();
  
  //--------------------------------------------------------- Musique Setup ---------------------------------------------
  minim = new Minim(this);


  Pbase = minim.loadFile("base.mp3");
  Prouge = minim.loadFile("rouge.mp3");
  Pviolet = minim.loadFile("violet.mp3");
  Pbleu = minim.loadFile("bleu.mp3");
  Pcyan = minim.loadFile("cyan.mp3");
  Pvert = minim.loadFile("vert.mp3");
  Pjaune = minim.loadFile("jaune.mp3");
  
  Pbase.loop();
  float Gain_base = Pbase.getGain();
  println(Gain_base);
  

  
  //--------------------------------------------Particule setup
  particules = new ArrayList<Particule>();
}

//-------------------Draw
void draw() {
  background(360, 0, 0);
// moving background lines
/*      for(int x = 0; x < 1024; x++) {
            if (hue != lampColor[0] && visible > 20.1 && restart == false) {
              visible -= 0.001;
            }
            else if (restart == true && visible < 100) {
              visible += 0.001;
            }
            if (visible < 20.1 && lampColor[0] > 0.1) {
              restart = true;
              hue = int(lampColor[0]);
            }
            if (visible >= 100.0)
              restart = false;
          //  if (lampColor[0] > 0) {
          //    hue = int(lampColor[0]);
          //  }
            stroke(hue + 30, 80, 50, (visible-30));
            line(x,0,x,random(1)*768);

            stroke(hue, 80, 50, visible);
            line(x,768,x,random(1)*800);
 
            stroke(222, 22, 16, 100);
            line(x,768,x,random(1)*random(1)*random(1)*768);
      }
  */    

  //--------------------------------------------------------Recuperation donnée flora----------------------------------------------------
  while (myPort.available () > 0) {
    
    String inByte = myPort.readStringUntil('\n'); //lecture sur le port
    if (inByte != null) { //regarde si donnée

      String data = trim(inByte.replace("\n", ""));  
        println(data);
        
        //regarde quelle lanterne
      if (data.equals("A")) {
        println("Selected Lantern is A\n");
        caseColor = 0;
         
      }
      else if (data.equals("B")){
        println("Selected Lantern is B\n");
        caseColor = 1;
      }
      
      //récupération de la teinte et assignation dans la case adéquate du tableau
      else {
        float teintecal = float(data); //cast les valeurs de data (en string) en float
        teintecal = map(teintecal, 0, 1, 0, 360);
        int couleur = int(teintecal);
        if (couleur == 0) {} // ne fait rien si la valeur de teinte est nulle 
        else {
          println("La Lanterne " + caseColor + " a pris la teinte " + couleur);
          lampColor[caseColor] = couleur;
          if (nbLantern > 0 && isBase == true) {
            Pbase.shiftGain(0.0, -80.0, 1000);
            isBase = false;
          }
          playMusique(caseColor);
        }
      }

      //compte le nombre de lanternes activées - ne reçoit que A et B pour l'instant
      if (data.equals( "A")) {
        nbLantern++;
      }
      else if (data.equals("B")){
        nbLantern++;
      }
     
     //supprime les lanternes au timeout
      if (data.equals("AO") && nbLantern > 0) {
        nbLantern--;
        lampColor[0] = 0;
      }
      else if (data.equals("BO") && nbLantern > 0){
        nbLantern--;
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

    if (nbLantern == 0 && !isBase) {
      println("TEST stop musique");
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
  
  frame.setTitle("fps "+round(frameRate));
}


