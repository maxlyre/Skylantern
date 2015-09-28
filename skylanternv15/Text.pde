// affichage du texte quand en attente

class Text{
  PFont font;
  int opacity = 0;
  Text(){
   font = loadFont("Museo-300-48.vlw");
  }
  
  void display(int textcount){
    if(textcount == 1){
       opacity = 0;
     }
   
    if (opacity < 255) {
       opacity ++;}

    fill(0,0,255,opacity);
       textFont(font, 40);
       textAlign(CENTER);
      text(" Put your hands on the marks\n And hold the lantern,\n Select your color inside the lantern\n And release it \n ------\n Mettere le mani sui marchi  \n E tenere la lanterna \n Scegliere il colore dei vuoi desideri interno della lanterna \n E fatelo salire", width/2, height/2-170);
     
      }
    
  
  
  
  void move(){
  
  }
  
  void disparu(){
  }
}
