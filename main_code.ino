//Code for arduino
#include <Servo.h>

Servo servo;

#define trigPin 10
#define echoPin 11

int pos = 0;
long duration;
int distance;
bool targetDetected = false;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Forward sweep
  for (pos = 0; pos <= 180; pos += 4) {
    if (!targetDetected) {
      servo.write(pos);
      distance = getDistance();
      Serial.print(pos);
      Serial.print(",");
      Serial.println(distance);
      checkTarget(distance);
      delay(15);
    } else {
      stopUntilClear();
    }
  }

  // Backward sweep
  for (pos = 180; pos >= 0; pos -= 4) {
    if (!targetDetected) {
      servo.write(pos);
      distance = getDistance();
      Serial.print(pos);
      Serial.print(",");
      Serial.println(distance);
      checkTarget(distance);
      delay(15);
    } else {
      stopUntilClear();
    }
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // timeout after 20ms
  int dist = duration * 0.034 / 2;
  return dist;
}

void checkTarget(int dist) {
  if (dist > 0 && dist < 40) {  // Adjust detection distance here
    targetDetected = true;
  }
}

void stopUntilClear() {
  // Keep reading distance until target disappears
  distance = getDistance();
  Serial.print(pos);
  Serial.print(",");
  Serial.println(distance);

  if (distance >= 40 || distance == 0) {  // Object gone
    targetDetected = false;
  }
  delay(100); // Check 10 times per second while stopped
}