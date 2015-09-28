import processing.serial.*;
import ddf.minim.*;
import processing.mqtt.*;

MQTTClient client;

int nbLantern = 2;

float temp = random(1)*768;
boolean touch = false;
float[] lampColor = new float [nbLantern];
int caseColor;
int nbFly = 0;
ArrayList<Particule> particules;
int hue = 180;
float visible = 125;
boolean restart = false;
boolean isBase = true;

int WIDTH = 1920;
int HEIGHT = 1080;

//----------------------Texte
Text text;
int textcount = 0;

Serial myPort;



void setup() {
  noCursor();
  size( WIDTH, HEIGHT, P2D);
  colorMode(HSB, 360, 100, 100);
  
  text = new Text();
  
  //MQTT
  client = new MQTTClient(this);
  client.connect("mqtt://try:try@192.168.1.8", "processing");
  client.subscribe("Sky/0/color");
  client.subscribe("Sky/1/color");
  //--------------------------------------------------------- Musique Setup ---------------------------------------------
  minim = new Minim(this);


  Pbase = minim.loadFile("base.mp3");
  Prouge = minim.loadFile("rouge.mp3");
  Pviolet = minim.loadFile("violet.mp3");
  Pbleu = minim.loadFile("bleu.mp3");
  Pcyan = minim.loadFile("cyan.mp3");
  Pvert = minim.loadFile("vert.mp3");
  Pjaune = minim.loadFile("jaune.mp3");
  Pmagenta = minim.loadFile("magenta.mp3");
  
  Pbase.loop();
  Pbase.setGain(-10);
  float Gain_base = Pbase.getGain();
  println(Gain_base);
  

  
  //--------------------------------------------Particule setup
  particules = new ArrayList<Particule>();
}

//-------------------Draw
void draw() {
  background(360, 0, 0);

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
    
    float randomBase = random(1,6);
    //println(randomBase);
    if(int(randomBase) == 1){
      //println("in");
          particules.add(new Particule(200));
       }
    
    if (nbLantern == 0 && !isBase) {
      stopFullMusique();
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

void messageReceived(String topic, byte[] payload) {
  println("new message: " + topic + " - " + new String(payload)); //Descriptif du message
  
  //Numéro de la lantern
  String nlantern = trim(topic.replace("Sky/",""));
         nlantern = trim(nlantern.replace("/color",""));       
  caseColor = (int(nlantern));
  println("Select lantern is : " + caseColor);
  
  //Acquisition de la couleur
  if(new String(payload).equals("0")){
    //nbFly--;
    stopZik(caseColor);
    lampColor[caseColor] = 0;
    println("Lantern " + caseColor + " Stop");
  }
  else{
    float teintecal = float(new String(payload));
    teintecal = map(teintecal, 0, 1, 0, 360);
    int couleur = int(teintecal);
    println("couleur de la lantern " + caseColor + " : " + couleur);
    
    lampColor[caseColor] = couleur;
    stopZik(caseColor); //Stop musique avant la prochaine
    playMusique(caseColor); //Lance musique
    //nbFly++;
    println("Lantern " + caseColor + " start");
  }
   
   //Compte le nombre de couleur active
  nbFly = 0;
  for(int i=0; i<nbLantern; i++){
      if(lampColor[i] != 0){
        nbFly++;
      }
  }
  println("Nombre de lantern active : " + nbFly);
  //Activation de la projection
  if(nbFly > 0){
        touch = true;
        println("touch");
   }
   else {
        touch = false;
        println("dont touch");
   }
   
}
