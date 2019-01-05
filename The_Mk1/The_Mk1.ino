#include <SimpleDHT.h>
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
const int pinDHT11 = 6;
SimpleDHT11 dht11;

//MOTOR SETUP(BEGIN)
// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD 0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
//Default pins:
#define DIRA 2 // Direction control for motor A
#define PWMA 3  // PWM control (speed) for motor A
#define DIRB 4 // Direction control for motor B
#define PWMB 11 // PWM control (speed) for motor B

////Alternate pins:
//#define DIRA 8 // Direction control for motor A
//#define PWMA 9 // PWM control (speed) for motor A
//#define DIRB 7 // Direction control for motor B
//#define PWMB 10 // PWM control (speed) for motor B

//MOTOR SETUP(END)

void setup() {
   Serial.begin(115200);
}

void loop() {

  // MOISTURE DEVICE(START)

  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  // read without samples.
  int temperature2 = readDHTTemperature();
  int humidity2 = readDHTHumidity();

  Serial.print("Sample OK: ");
  Serial.print((int)temperature2); Serial.print(" *C, ");
  Serial.print((int)humidity2); Serial.println(" %");

  //MOISTURE DEVICE(END)

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

int readDHTTemperature(){
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
  }
  return temperature;
}

int readDHTHumidity(){
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
  }
  return humidity;
}
