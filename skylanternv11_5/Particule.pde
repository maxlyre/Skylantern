class Particule{

  float x;
  float y;
  float H; //Couleur rouge
  int CO = 125;  //couleur opacité
  float diameter = random(10,30);;
  PVector velocity;
  PVector acceleration;
  PVector location;
  int count = 0;
  boolean life;
  User nUser;
  
  Particule(float hparticule, float x_, float y_){
    life = true;
    acceleration = new PVector(-0.05, -0.1);
     velocity = new PVector(random(-1, 1), random(0, -2));
    
    
    location = new PVector(x_,y_); //créer un PVector avec les coordonées
    
    //couleur particule
    H= hparticule;
   // println("x: " + x + "y: " +y + " n : "+ n);
   
  }
  
  void display(){
     if(velocity.y < -5 && location.y < height/2+200){      
      count = count+1;
     
      if( count < 50){
        H = H+1;
         if (H >360){
           H = H -360;
           }
    //  println(H);
      }
    }
    fill(H,80,80,CO);
    noStroke();
    ellipse(location.x,location.y,diameter,diameter);
  }
  
  void move(){
    velocity.add(acceleration);
    location.add(velocity);
   // println(velocity);
   
  }
  
  boolean disparu(){
    if( location.y < -100){
       life = false;
    } else{
      life = true;
    }
    return life;
  }
}
