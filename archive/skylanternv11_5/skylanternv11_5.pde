import processing.serial.*;
import SimpleOpenNI.*;
import ddf.minim.*;
SimpleOpenNI kinect; // Kinect

boolean tracking = false; // kinect
boolean touch = false;
ArrayList<User> users; // Nombre d'utilisateurs, a retirer comme avec la kinect
int userID;  // same
float[] lampColor = new float [2];
int caseColor;
int nbLantern;
ArrayList<Background> background1;
ArrayList<PVector> userMaptab; //User avec la kinect


//PImage userMap;---------------------------------------------! Kinect
int[] userMap;
PImage userColor;

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

float zAx;
  float zAw;

  int zBx;
  int zBw;
  
    

void setup() {
  size(1024 , 768, P2D);
  colorMode(HSB, 360, 100, 100);

  //---------------------------------------------------------Serial Setup---------------------------------------------
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 4800);
  text = new Text();
  users= new ArrayList<User>();
  
  zAx=200;
    zAw=400; 

    zBx=800;
    zBw=400;
  //---------------------------------------------------------Kinect Setup---------------------------------------------
  kinect = new SimpleOpenNI(this);
  if (kinect.isInit() == false)
  {
    println("Can't init SimpleOpenNI, maybe the camera is not connected!"); 
    exit();
    return;
  }

  // enable depthMap generation 
  kinect.enableDepth();

  // enable skeleton generation for all joints
  kinect.enableUser();

  // enable color image from the Kinect
  kinect.enableRGB();
  //enable the finding of users but dont' worry about skeletons

  // turn on depth/color alignment

  kinect.alternativeViewPointDepthToImage();
  userMaptab = new ArrayList<PVector>();
  
  //--------------------------------------------Background setup
  background1 = new ArrayList<Background>();

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

//------------------------------------Kinect
  kinect.update();
  for (int i=0; i<users.size(); i++) {
    users.get(i).run();
  }
  //--------------------------------------------------------Recuperation donnée flora----------------------------------------------------

  while (myPort.available () > 0) {
    String inByte = myPort.readStringUntil('\n');
    if (inByte!= null) { //regarde si donnée

      String data = trim(inByte.replace("\n", ""));  
        println(data);
        
        //regarde quel lantern
      if (data.equals( "A")) { 
         caseColor =0;
      }else if (data.equals( "B")){
          caseColor = 1;
      }
      //prend la teinte
      float teintecal= float(data);
      teintecal= map(teintecal, 0, 1, 0, 360);
      int couleur= int(teintecal);
      if (couleur == 0) {
      }
      else {
        lampColor[caseColor]=couleur;
      }
        //compte les lantern
      if (data.equals( "AT")) {
        nbLantern ++;
        
      }else if (data.equals("BT")){
        nbLantern ++;
      }
     
      if (data.equals("AO")) {
        nbLantern --;
        lampColor[0] = 0;
      }else if (data.equals("BO")){
        nbLantern --;
        lampColor[1]=0;
      }
      
      if(nbLantern > 0){
        touch= true;
        //kinect (tableau users).
        for (int i = 0; i < users.size(); i++) {
          users.get(i).over();
      }
      
      }
      else{
        touch = false;
      }
    }
  }
  //lampColor = 15;

  addUserList(); // Kinect

  //------------------------------------------------Touch-----------------------------------  

  if (touch) {
    if (Mteinte == false) { 
      playMusique();
    }
    
        //Kinect------------------------------------------------------------------------
    if (tracking) { //Kinect
      addUserList();
      userImage();
      findColorUser();
      colorAnalysis();
      //add particule

      for (int i=0; i<users.size(); i= i+20) {
       users.get(i).addParticle();
       }
    }
      // Background --------------------------------------------------------------------------------
    //add particule
      // background1.add(new Background(45));
     // if(nbLantern == 1){        
          for(int i= 0; i<2;i++){
             if(lampColor[i] != 0){
                background1.add(new Background(lampColor[i]));
                
             }
          }
          println(background1.size());
      /* }else if(nbLantern == 2){
         int randomIndex = round(random(0, 1));
         background1.add(new Background(lampColor[randomIndex]));
       }*/
       
    textcount =1;
  } 
  else {
    //Texte et musique stop
    text.display(textcount);
    textcount = 0;
    //particules.clear();
    //background1.clear();
    if (Mteinte==true) {                       
      stopMusique();
    }
  }
  //----------------Mise à jours particule Background
  for (int i = 0; i <background1.size(); i ++) {
    background1.get(i).move();
    background1.get(i).display();
    background1.get(i).disparu();
    if(background1.get(i).disparu() == false){
      background1.remove(i);
    }
  }
  //println("\t\t nb particles : "+particules.size());
  
  frame.setTitle("fps"+round(frameRate));
  
 // displayPVector();
}

//-------------------------------------------------------------------- Kinect
void onNewUser(SimpleOpenNI curContext, int userId)
{
  userID = userId;

  users.add(new User(userId));
  users.get(userId-1).addPVectorToArray();
}

void onLostUser(SimpleOpenNI curContext, int userId)
{
  tracking = false;
  println("onLostUser - userId: " + userId);
  users.remove(userId-1);
  //users.removePVector(userId-1);
}

void onVisibleUser(SimpleOpenNI curContext, int userId)
{
  tracking = true;
  //println("onVisibleUser - userId: " + userId);
}

//-------------------------------------------------------------------Musique
void playMusique() {

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

//----------------------------------------------------------------------------------------------Kinect fonction
void userImage()
{
  userColor = kinect.userImage().get();
  userMap = kinect.userMap();
  userColor.loadPixels();
}


void findColorUser()
{
  for (int i=0; i<users.size(); i++)
  {
    User user = users.get(i);
    color colorPixel = userColor.pixels[user.numeroPixel(userColor)]; 
    //println(userColor.width, user.numeroPixel(userColor));//, user.numeroPixel(userColor));
    user.setUserColorMap(hue(colorPixel));
  }
}

void colorAnalysis()
{

  float resX = 40;
  float resY = 40;

  /* for (int i =0; i < userMap.length; i+=userMap.length/10)
   {
   println(userMap[i]);
   }*/
   
  for (int k=0; k<users.size(); k++) {
    users.get(k).userMapPos.clear(); 
  }
  
  for (int i =0; i < userMap.length; i+=10) {
    // if the pixel is part of the user
    // if (userMap[i] >1) {
    // println("\tOn a des users");
    float x = (i%userColor.width)+1;
    float y = int(i/userColor.width);

    color colorPixel = userColor.pixels[i];

    float hue = hue(colorPixel);
    float sat = saturation(colorPixel);

    // println("\t\thue : "+hue+" sat : "+sat);

    for (int j=0; j<users.size(); j++)
    {
      User user = users.get(j);

      if (sat > 0 && hue == user.hueUser)
      {
        // println("\t\t\tON AJOUTE DES VECTEURSSSSSS");
        x = map(x, 0, 640, 0, width);
        y = map(y, 0, 480, 0, height);
        user.userMapPos.add(new PVector(x, y));
      }
    }
    //}
  }
  
  
}

void addUserList() {
  //---------------------------------créer une liste d'utilisateurs avec leur position.
  if (users !=null)
  {
    for (int i=0;i<users.size();i++)
    {   
      PVector com = new PVector();
      if (kinect.getCoM(users.get(i).userList, com))
      {
        kinect.convertRealWorldToProjective(com, users.get(i).com2d);
        PVector temp = users.get(i).com2d;
        users.get(i).com2d.x = map(temp.x, 0, 640, 0, width);
        users.get(i).com2d.y = map(temp.y, 0, 640, 0, width);
        // over(temp, i);
      }
    }
  }
}

//---------------------------------numero et pointer utilisateurs. DEBUG
  void displayPVector()
  {
    fill(25,100,100);
    stroke(25,100,100);

    rect(zAx, 0, zAw, height);
    rect(zBx, 0, zBw, height);
    
    /*
    for (int i=0; i<com2d.size(); i++)
     {
     PVector temp = com2d.get(i);
     stroke(0, 255, 100);
     fill(0, 255, 100);
     beginShape(LINES);
     vertex(temp.x, temp.y - 10);
     vertex(temp.x, temp.y + 10);
     
     vertex(temp.x - 10, temp.y);
     vertex(temp.x + 10, temp.y);
     endShape();
     
     fill(0, 255, 100);
     text(i, temp.x+10, temp.y);
     }
     rectMode(CORNER);*/
  }

