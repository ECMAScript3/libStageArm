#pragma once
#define DIR_X_PIN 2 //red
#define CP_X_PIN 3 //orange
#define EN_X_PIN 4 //eliminated

#define DIR_Y_PIN 5 //yellow
#define CP_Y_PIN 6 //green
#define EN_Y_PIN 7 //eliminated

#define DIR_Z_PIN 8 //blue
#define CP_Z_PIN 9 //purple
#define EN_Z_PIN 10 //eliminated

#define DEBUG_LIGHT 13

//below are the metal sensors that are plugged into the analog ports
#define X_LEFT_SENSOR A2
#define X_RIGHT_SENSOR A4
#define Y_POS_SENSOR A3
#define Y_NEG_SENSOR A0
#define Z_BOTTOM_SENSOR A1

#define SENSOR_TRIPPED LOW

#define VACUUM_PIN 11  //LOW signal maps to vacuum on

#define STOP_PIN 12    //LOW signal input means stopped, this is because the internal pullup resistor inverts the signal

#define X 0
#define Y 1
#define Z 2

#define COUNTERCLOCKWISE 0
#define CLOCKWISE 1

#define PULSES_PER_CIRCLE 1600
//7.22 cm per turn at 19V DC
#define DISTANCE_PER_TURN 7.22
//Delay is in microseconds

//Serial commands
#define CALIBRATE_ALL 0x00
#define CALIBRATE 0x01
#define REL_MOV 0x02
#define ABS_MOV 0x03
#define SET_VAC 0x04
#define TOG_VAC 0x05
#define SET_DEL 0x06

#define VAC_ON LOW
#define VAC_OFF HIGH

//Directions
#define X_NEG LOW
#define X_POS HIGH
#define Y_NEG LOW
#define Y_POS HIGH
#define Z_NEG HIGH
#define Z_POS LOW

//Error codes
#define SUCCESS 0x00
#define GENERIC_FAIL 0x01
#define UNDEFINED_FAIL 0x0A;
#define VOOB 0x0B;

//typedefs
typedef bool spin_direction;
typedef struct {
  spin_direction xDir;
  spin_direction yDir;
  spin_direction zDir;
  int delay_ms;
  float coord[3];
  bool calibrated[3];
  bool vac_on;
} stageArm;