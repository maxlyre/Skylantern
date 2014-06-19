// particule background. Voir Nature of code pour la construction.

class Particule{
  float       x;
  float       y;
  float       H = 0; //Couleur rouge
  float       S = 80;  //Couleur vert
  float       B = 80;  //Couleur bleu
  int         CO = 125;  //couleur opacité
  float       diameter_x = random(10,30);
  float       diameter_y = diameter_x + random(-5,5);
  PVector     velocity;
  PVector     acceleration;
  PVector     location;
  float       lifespan;
  boolean     life = true;
  
  Particule(float hBackground){
     acceleration = new PVector(-0.02, -0.02);
     velocity = new PVector(random(-1, 1), random(0, -2));
     H = hBackground;
       if (H >360){
           H = H -360;
       }
    lifespan = random(125, 200);
    location = new PVector(random(width+500),random(height-100,height));
  }
  
  void display(){
    noStroke();
    //println(lifespan);
    fill(H ,S, B, lifespan);
    ellipse(location.x,location.y,diameter_x, diameter_y);
  }
  
  void move(){
    velocity.add(acceleration);
    location.add(velocity);
    lifespan -= random(0.4, 0.6);
  }
  
  boolean disparu(){
    if(location.y < -100 || lifespan <= 0){
      life = false;
    } 
    else{
      life = true;
    }
    return life;
  }
}
