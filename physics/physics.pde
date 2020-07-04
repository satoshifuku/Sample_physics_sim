
PVector g;        //gravity
PVector velocity;
PVector location;
float e;

void setup() {
  size(2480,1440);
  
  location = new PVector(100,1000);
  velocity = new PVector(0.7*sqrt(2)*9.8, -0.7*sqrt(2)*9.8);
  g = new PVector(0,0.1);
  e = 0.8;
  background(25, 25, 25);
}

void draw() {
  // background(25, 25, 25);
  
  location.add(velocity);
  velocity.add(g);
  
  // Bounceing off
  if ((location.x > width) || (location.x < 0)) {
    velocity.x = -e * velocity.x;
  }
  if (location.y > height) {
    velocity.y = -e * velocity.y; 
    location.y = height;
  }

  draw_circle();
}

void draw_circle(){
  fill(50,255,50);
  ellipse(location.x,location.y,48,48);
}