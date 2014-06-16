// particule background. Voir Nature of code pour la construction.

class Particule{
  float x;
  float y;
  float H = 0; //Couleur rouge
  float S = 80;  //Couleur vert
  float B = 80;  //Couleur bleu
  int CO = 125;  //couleur opacité
  float diameter = random(10,30);;
  PVector velocity;
  PVector acceleration;
  PVector location;
  boolean life=true;
  
  Particule(float hBackground){
    acceleration = new PVector(-0.02, -0.02);
     velocity = new PVector(random(-1, 1), random(0, -2));
     H = hBackground;
       if (H >360){
           H = H -360;
       }

    location = new PVector(random(width+500),random(height-100,height));
  }
  
  void display(){
    noStroke();
    fill(H ,S, B,CO);
    
    ellipse(location.x,location.y,diameter,diameter);
  }
  
  void move(){
    velocity.add(acceleration);
    location.add(velocity);
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
