class Text{
  PFont font;
  int opacity = 0;
  Text(){
   font = loadFont("HighTideSans-48.vlw");
  }
  
  void display(int textcount){
    if(textcount==1){
       opacity = 0;
     }
   
   opacity ++;
    fill(0,0,100,opacity);
       textFont(font, 32);
       textAlign(CENTER);
      text("Touchez la lanterne \n et choisissez la couleur de vos vœux", width/2, height/2);
     
      }
    
  
  
  
  void move(){
  
  }
  
  void disparu(){
  }
}
