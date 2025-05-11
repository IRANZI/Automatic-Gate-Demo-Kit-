#include <Servo.h>
const int redGround = 7;
const int blueGround = 8;
const int trigPin = 2;
const int echoPin = 3;
const int redLED = 4;
const int blueLED = 5;
const int servoPin = 6;
const int buzzer = 12;

Servo barrier;

long duration;
int distance;

void setup() {
  Serial.begin(9600); // <-- Must come first before any Serial print!

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redGround,OUTPUT);
  pinMode(blueGround,OUTPUT);


  barrier.attach(servoPin);
  barrier.write(0); // Start with barrier closed

// set the grounds to low
  digitalWrite(redGround, LOW);
  digitalWrite(blueGround, LOW);


  // Initial status (no object)


  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, LOW);
  digitalWrite(buzzer, LOW);

  Serial.println("System initialized. Red LED ON. Waiting for object...");
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration and calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= 15) {
    Serial.println("Object detected!");

    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);

    // Buzzer beeps
    for (int i = 0; i < 10; i++) {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
    }

    // Move barrier
    barrier.write(90);
    delay(5000);
    barrier.write(0);

    // Restore to idle state
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, LOW);

    Serial.println("Resetting to idle: Red ON, Blue OFF, Buzzer OFF");
  } else {
    // No object
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, LOW);
    digitalWrite(buzzer, LOW);
    barrier.write(0);

    Serial.println("No object - Red LED ON, Buzzer OFF");
  }

  delay(500);
}
