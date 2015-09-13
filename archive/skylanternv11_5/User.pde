// Class user. En retirant la kinect deviant inutile.

class User {
  

  PVector com2d;
  int userList;
  Boolean hover;
  ArrayList<PVector> userMapPos;
  ArrayList<Particule> particules;

  float hueUser;
  float hue;

  User(int userId_) {
    com2d= new PVector();
    userMapPos =new ArrayList<PVector>();
    particules = new ArrayList<Particule>();
    userList = userId_;
    hover = false;


  }

  void run() {
    println("nombre : "+ userMapPos.size());
    

    fill(0, 0, 100);
    //ellipse(com2d.x, com2d.y, 20,20);
   // println("userMapPos.size() : "+userMapPos.size()+" particules.size() : "+particules.size());


    for (int i = 0; i <particules.size(); i ++) {
      particules.get(i).move();
      particules.get(i).display();
      if (particules.get(i).disparu() == false) {
        particules.remove(i);
      }
    }
    for (int i = 0; i <background1.size(); i ++) {
      background1.get(i).move();
      background1.get(i).display();
      background1.get(i).disparu();
    }

    //removeUserMapElement();
  }

  void removeUserMapElement()
  {
    if (userMapPos.size() > 1000)
    {
      
        userMapPos.clear();
      
    }
  }


  void addPVectorToArray()
  {
    //println("\t nous devons rajouter une PVector");
    //PVector temp = new PVector();
    //com2d.add(temp);
  }


  

  //------------------------------------condition utilisateurs dans la zone
  void over()
  {
    boolean _over= false;

    if (com2d.x>zAx && com2d.x<zAx+zAw || com2d.x>zBx && com2d.x<zBx+zBw) {
      if (com2d.x>zAx && com2d.x<zAx+zAw) {
        hue=lampColor[0];
      }
      if (com2d.x> zBx&& com2d.x<zBx+zBw) {
        hue = lampColor[1];
      }
      _over = true;
    }
    else {

      _over=false;
    }
    hover= _over;
  }



  int numeroPixel(PImage img)
  {
    float x = map(com2d.x, 0, width, 0, 640);
    float y = map(com2d.y, 0, height, 0, 480);
    int numeroDuPixel = int(y*640+x);
    numeroDuPixel = constrain(numeroDuPixel, 0, 640*480);
    return numeroDuPixel;
  }

  void setUserColorMap(float hue_)
  {
    hueUser = hue_;
  }
  void addParticle()
  {
    if (userMapPos.size()>0 && hover== true)
    {
      for(int i=0; i<5; i++){
      int randomIndex=int(random(userMapPos.size()-1));
      PVector loc = userMapPos.get(randomIndex);
      particules.add(new Particule(hue, loc.x, loc.y));
      }
    }
  }
}

