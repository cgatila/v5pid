#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
distance leftSen = distance(PORT11);
distance rightSen = distance(PORT20);
motor leftMotor = motor(PORT1, ratio18_1, false);

motor rightMotor = motor(PORT10, ratio18_1, true);

bumper BumperC = bumper(Brain.ThreeWirePort.C);
#pragma endregion VEXcode Generated Robot Configuration

// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;
float error, derivative, power;
float integral = 0;
float maxIntegral = 0;

/*
void telemetry(){
      Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    Brain.Screen.print(power);
    Brain.Screen.newLine();
    // value 1
    Brain.Screen.print("proportional: ");
    Brain.Screen.print(error);
    Brain.Screen.newLine();
    // value 2
    Brain.Screen.print("integral: ");
    Brain.Screen.print(integral);
    Brain.Screen.newLine();
    // value 3
    Brain.Screen.print("derivative: ");
    Brain.Screen.print(derivative);
    Brain.Screen.newLine();
    Brain.Screen.print("maxIntegral:  ");
    Brain.Screen.print(maxIntegral);
    Brain.Screen.newLine();
}

*/
int main() {
  const float kP = 5.2; // Proportional gain - original is 5.2
  const float kI = 0.01; // Integral gain changed from .01 to .02
  const float kD = 0.5; // Derivative gain - 0.6 moves more violently with increased speed of 30
  float lastError = 0;

  int leftSensor, rightSensor;
  int startSpeed = 15; // intial speed was 15
  int divisor = 20;

  // Main control loop
  while (true) {
    
    leftSensor = leftSen.objectDistance(mm);
    rightSensor = rightSen.objectDistance(mm);

    error = rightSensor - leftSensor;

    integral += error;
    derivative = error - lastError;
    lastError = error;

    if(integral > maxIntegral){
      maxIntegral = integral;
    }

    power = (kP * error) + (kI * integral) + (kD * derivative);
    leftMotor.setVelocity(startSpeed + power/divisor, percent);
    rightMotor.setVelocity(startSpeed - power/divisor, percent);
    leftMotor.spin(forward);
    rightMotor.spin(forward);

   // telemetry();


    wait(0.1, seconds);

    if (BumperC.pressing()) {
      Brain.Screen.print("Button Pressed");
      leftMotor.stop();
      rightMotor.stop();
      wait(0.1, seconds);

      leftMotor.spinFor(forward, 650.0, degrees, false);
      rightMotor.spinFor(forward, -650.0, degrees);
/*
      leftSensor = leftSen.objectDistance(mm);
      rightSensor = rightSen.objectDistance(mm);
      
      error = rightSensor - leftSensor;
      
      integral += error;
      derivative = error - lastError;
      lastError = error;
      
      power = (kP * error) + (kI * integral) + (kD * derivative);
      leftMotor.setVelocity(startSpeed + power/divisor, percent);
      rightMotor.setVelocity(startSpeed - power/divisor, percent);
      leftMotor.spin(forward);
      rightMotor.spin(forward);

    }*/

    wait(0.02,seconds);
  }
}}

