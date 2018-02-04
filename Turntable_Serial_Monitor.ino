////////////////////////////////////////////////////////////////////////////////
//
//   Turntable V1 20180204 MCR
//     based on the idea from Ray on rmweb.co.uk forum
//     http://www.rmweb.co.uk/community/index.php?/topic/78578-dcc-controlled-peco-turntable-project-using-a-arduino-uno/
//
//     The idea was having a sensor determine and calibrate de stepper motor on startup of the system.
//     From there all the positions are relative to position (0) the sensor.
//
//     Works fine but, for the moment, only interact with Arduino serial monitor commands
//     0 - Go to home position
//     1, 2, 3 & 4 - Go to position 1, 2, 3 & 4
//     9 - Calibrate the turntable again
//
//     This is a work in progress. The goal is to make a DDC Accessory Decoder
//
//     Works with the very cheap Stepper Motor DC 5V 28BYJ-48 + ULN2003 Stepper Motor Driver Module
//     The sensor is an Hall Effect Magnetic sensor, also very cheap
//
////////////////////////////////////////////////////////////////////////////////

#include <AccelStepper.h>

// Absolute positions. You need to find out the positions on your track.
// One full turn takes 4076 steps.
int position0 = 500;
int position1 = 1000;
int position2 = 1500;
int position3 = 1700;
int position4 = 2800;

int positionChoice;

#define HALFSTEP 8

// ligação de Pins do Motor
#define motorPin1  3     // IN1 on the Module ULN2003 - PIN 3 Arduino
#define motorPin2  4     // IN2 on the Module ULN2003 - PIN 4 Arduino
#define motorPin3  5     // IN3 on the Module ULN2003 - PIN 5 Arduino
#define motorPin4  6     // IN4 on the Module ULN2003 - PIN 6 Arduino

const int sensorPin = 8; // Hall sensor on Pin 8
const int ledPin = 13;   // Control led pin 13 on Arduino

int sensorStatus = 0;    // Sensor State
int initialStatus = 0;   // Initial State Variable on 0 starts de cxalibration process
int position0Status = 0; // Home Position Variable on 0 finds home

// Start Pin sequence pin's IN1-IN3-IN2-IN4 to work with Library AccelStepper on the 28BYJ-48 Stepper
AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {

  //Opens the seriial communication
  Serial.begin(9600);

  // Initialize pin state (Input or Output)
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  // Define de speed and acceleration on every move the stepper makes
  stepper.setMaxSpeed(200.0);
  stepper.setAcceleration(30.0);
  stepper.setSpeed(100);


}//--(END of setup )---

void loop() {

  if (initialStatus == 0) { //Starts by finding the sensor
    calibrate();

  }

  else if (position0Status == 0) { //After calibration sends the turntable to home position

    while (stepper.currentPosition () != position0) {
      stepper.moveTo(position0);
      stepper.run();
    }
    releaseCoil();
    position0Status = 1;
    Serial.print("Home Position on: ");
    Serial.println(position0Status);
  }
  else {


    Serial.println("Insert the desire position");
    while (Serial.available() == 0) { } // Wait for User to Input Data

    positionChoice = Serial.parseInt(); //Read the data the user has input

    switch (positionChoice) {
      case 0:
        Serial.println("You choose the Home position");
        while (stepper.currentPosition () != position0) {
          stepper.moveTo(position0);
          stepper.run();
        }
        break;
      case 1:
        Serial.println("Choose position 1");
        while (stepper.currentPosition () != position1) {
          stepper.moveTo(position1);
          stepper.run();
        }
        releaseCoil();
        break;
      case 2:
        Serial.println("Choose position 2");
        while (stepper.currentPosition () != position2) {
          stepper.moveTo(position2);
          stepper.run();
        }
        releaseCoil();
        break;
      case 3:
        Serial.println("Choose position 3");
        while (stepper.currentPosition () != position3) {
          stepper.moveTo(position3);
          stepper.run();
        }
        releaseCoil();
        break;
      case 4:
        Serial.println("Choose position 4");
        while (stepper.currentPosition () != position4) {
          stepper.moveTo(position4);
          stepper.run();
        }
        releaseCoil();
        break;
      case 9:
        Serial.println("Starting the Calibration process");
        initialStatus = 0;
        position0Status = 0;
        calibrate();

        break;
    }
  }
}



