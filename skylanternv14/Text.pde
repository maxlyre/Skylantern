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
   
    if (opacity < 100) {
       opacity ++;}

    fill(0,0,100,opacity);
       textFont(font, 32);
       textAlign(CENTER);
      text(" Mettez vos mains sur les marques\n maintenez la lanterne,\n choisissez la couleur de vos vœux\n et laissez-la s'envoler", width/2, height/2);
     
      }
    
  
  
  
  void move(){
  
  }
  
  void disparu(){
  }
}
