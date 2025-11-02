//

import processing.serial.*;

Serial myPort;
String data = "";
float angle = 0;
float distance = 0;

void setup() {
  size(800, 600);
  println(Serial.list());
  myPort = new Serial(this, "COM3", 9600);  
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  stroke(0, 255, 0);
  noFill();

  // Draw radar arc
  arc(width/2, height, 800, 800, PI, TWO_PI);

  // Draw sweep line
  float x = width/2 + 400 * cos(radians(angle));
  float y = height - 400 * sin(radians(angle));
  stroke(0, 255, 0);
  line(width/2, height, x, y);

  // If something is detected close (e.g., under 40 cm)
  if (distance > 0 && distance < 40) {
    float dx = width/2 + distance * 4 * cos(radians(angle));
    float dy = height - distance * 4 * sin(radians(angle));
    fill(255, 0, 0);   // red dot for object
    noStroke();
    ellipse(dx, dy, 12, 12);

    // Optional: show “target detected” text
    fill(255, 0, 0);
