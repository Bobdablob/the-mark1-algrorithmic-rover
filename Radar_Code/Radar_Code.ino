// Includes the Servo library
#include <Servo.h>
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor

long previousSwing = 0;        // will store last time LED was updated
long previousUpdate = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long updateInterval = 30;           // interval at which to blink (milliseconds)
long swingInterval = 30;

int swingAngles[] = {15,30,45,60,75,90,105,120,135,150,165};
int angleArrayLength = sizeof(swingAngles) / sizeof(swingAngles[0]);
int distanceAngles[angleArrayLength];

int currentServo = 0;

int forwardsSwing = 1;

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD 0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
//Default pins:
#define DIRA 8 // Direction control for motor A
#define PWMA 9  // PWM control (speed) for motor A
#define DIRB 7 // Direction control for motor B
#define PWMB 10 // PWM control (speed) for motor B

////Alternate pins:
//#define DIRA 8 // Direction control for motor A
//#define PWMA 9 // PWM control (speed) for motor A
//#define DIRB 7 // Direction control for motor B
//#define PWMB 10 // PWM control (speed) for motor B

void setup() {
  setupArdumoto(); // Set all pins as outputs

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
}

void loop() {

  if(currentMillis - previousSwing > swingInterval) { // Check's if it's time to swing.
    previousSwing = currentMillis; // Sets NOW to the last time it was swung.

    if (currentServo >= angleArrayLength){ // Checks if we've reached the end of the angle array.
      forwardsSwing = 0; // Sets swing direction to backwards
    } else if (currentServo == 0) { // Checks if we've reached the beginning of the angle array.
      forwardsSwing = 1; // Sets swing direction to forwards
    } else {
      Serial.println("ERROR, angle array overrun.") // Error state
    }

    if (forwardsSwing == 1){
      currentServo = currentServo + 1;
    } else if (forwardsSwing == 0) {
      currentServo = currentServo - 1;
    } else {
      Serial.println("ERROR, forwards swing state not 0 or 1.") // Error state
    }

    myServo.write(swingAngles[currentServo]); // Assign the current angle to the servo.

  }
  
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd) {
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor) {
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto() {
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
