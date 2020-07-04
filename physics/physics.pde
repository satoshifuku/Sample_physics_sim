
PVector g;        //gravity
PVector velocity;
PVector location;
PVector init_location;
float e;
int radius;

void setup() {
  size(2480,1440);
  init_location = new PVector(100,1000);
  location = new PVector(init_location.x,init_location.y);

  velocity = new PVector(2*sqrt(2)*9.8, -2*sqrt(2)*9.8);
  g = new PVector(0,0.98);
  e = 0.9;
  radius = 20;

  background(25, 25, 25);

  stroke(200);
  strokeWeight(6);

  line(0, init_location.y, displayWidth, init_location.y);

  line(init_location.x, 0, init_location.x, displayHeight);
}

void draw() {
  // background(25, 25, 25);
  
  location.add(velocity);
  velocity.add(g);
  
  // Bounceing off
  // if ((location.x > width) || (location.x < init_location.x + radius)) {
  //   velocity.x = -e * velocity.x;
  // }

  // if (location.y > init_location.y - radius) {
  //   velocity.y = -e * velocity.y; 
  //   location.y = init_location.y - radius;
  // }

  draw_circle();
}

void draw_circle(){
  noStroke();
  fill(50, 255, 50);
  ellipse(location.x, location.y, radius, radius);
}