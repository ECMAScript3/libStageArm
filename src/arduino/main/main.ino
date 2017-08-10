#include "constants.h"
typedef bool spin_direction;
int delay_ms = 4000;
spin_direction xDir;
spin_direction yDir;
spin_direction zDir;

float coord[3];
bool calibrated[3];
bool vac_on;

bool isColliding(byte dir, byte axis){
  //variables:
  //dir -- either CLOCKWISE or COUNTERCLOCKWISE
  //axis -- X, Y, or Z
  
  //pretty bad code, improve if you want
  //basically, what this does is check to see if the 
  //sensor that's in the direction of motion
  //is detecting the presence of the platform.
  //if this function returns true, it means the
  //platform cannot move more or else it'll collide
  //with the boundaries.
  /*if(axis==X){
    if(dir==CLOCKWISE && digitalRead(X_RIGHT_SENSOR)==SENSOR_TRIPPED){
      return true;
    }
    if(dir==COUNTERCLOCKWISE && digitalRead(X_LEFT_SENSOR)==SENSOR_TRIPPED){
      coord[X] = 0;
      return true;
    }
  }else if(axis==Y){
    if(dir==CLOCKWISE && digitalRead(Y_BACK_SENSOR)==SENSOR_TRIPPED){
      return true;
    }
    if(dir==COUNTERCLOCKWISE && digitalRead(Y_FORWARD_SENSOR)==SENSOR_TRIPPED){
      coord[Y] = 0;
      return true;
    }
  }else if(axis==Z){
    if(dir==CLOCKWISE && digitalRead(Z_BOTTOM_SENSOR)==SENSOR_TRIPPED){
      coord[Z] = 0;
      return true;
    }
  }*/
  return false;
}

void setup() {
  for(int i = 0; i < 3; i++){
    coord[i] = 0;
    calibrated[i] = false;
  }
    
  Serial.begin(9600);
  pinMode(CP_Y_PIN, OUTPUT);
  pinMode(EN_Y_PIN, OUTPUT);
  pinMode(DIR_Y_PIN, OUTPUT);
  digitalWrite(CP_Y_PIN, LOW);
  digitalWrite(EN_Y_PIN, LOW);
  digitalWrite(DIR_Y_PIN, LOW);

  pinMode(CP_X_PIN, OUTPUT);
  pinMode(EN_X_PIN, OUTPUT);
  pinMode(DIR_X_PIN, OUTPUT);
  digitalWrite(CP_X_PIN, LOW);
  digitalWrite(EN_X_PIN, LOW);
  digitalWrite(DIR_X_PIN, LOW);

  pinMode(CP_Z_PIN, OUTPUT);
  pinMode(EN_Z_PIN, OUTPUT);
  pinMode(DIR_Z_PIN, OUTPUT);
  digitalWrite(CP_Z_PIN, LOW);
  digitalWrite(EN_Z_PIN, LOW);
  digitalWrite(DIR_Z_PIN, LOW);
  
  pinMode(VACUUM_PIN, OUTPUT);
  //high signal disables vacuum
  digitalWrite(VACUUM_PIN, VAC_OFF);
  vac_on = false;

  //pinMode(X_LEFT_SENSOR, INPUT);
  //pinMode(X_RIGHT_SENSOR, INPUT);
  //pinMode(Y_FORWARD_SENSOR, INPUT);
  //pinMode(Y_BACK_SENSOR, INPUT);
  //pinMode(Z_BOTTOM_SENSOR, INPUT);

  pinMode(DEBUG_LIGHT,OUTPUT);
}

void loop() {
  digitalWrite(DEBUG_LIGHT, digitalRead(A3));
  if(Serial.available()){
    delay(15); //wait for transmission to finish
    byte command = Serial.read();

    if(command == 'a'){
      digitalWrite(DEBUG_LIGHT, LOW);
    }

    switch(command){
     case CALIBRATE: 
       Serial.print(calibrate());
       break;
     case REL_MOV:
       Serial.print(relMov());
       break;
     case ABS_MOV:
       Serial.print(absMov());
       break;
     case SET_VAC:
       Serial.print(setVac());
       break;
     case TOG_VAC:
       Serial.print(togVac());
       break;
     case SET_DEL:
       Serial.print(setDel());
     default: 
       Serial.print(GENERIC_FAIL);
     }
  }
}

byte calibrate() {
  byte axis = Serial.read();
  byte dir;
  byte direction_pin;
  byte pulse_pin;

  switch(axis){
    case X:
      dir = xDir = COUNTERCLOCKWISE;
      direction_pin = DIR_X_PIN;
      digitalWrite(direction_pin, X_NEG);
      pulse_pin = CP_X_PIN;
      break;
    case Y:
      dir = yDir = COUNTERCLOCKWISE;
      direction_pin = DIR_Y_PIN;
      digitalWrite(direction_pin, Y_NEG);
      pulse_pin = CP_Y_PIN;
      break;
    case Z:
      dir = zDir = CLOCKWISE;
      direction_pin = DIR_Z_PIN;
      digitalWrite(direction_pin, Z_NEG);
      pulse_pin = CP_Z_PIN;
      break;
    default:
      return GENERIC_FAIL;
  }

  while(!isColliding(dir, axis)){
    digitalWrite(pulse_pin, HIGH);
    digitalWrite(pulse_pin, LOW);
    delayMicroseconds(delay_ms);
  }

  coord[axis] = 0;
  calibrated[axis] = true;
  return SUCCESS;
}

byte relMov() {
  byte input[12];

  for(int i = 0; i < 12; i++){
    input[i] = Serial.read();
  }

  float x_coord = *((float*)(input+0));
  float y_coord = *((float*)(input+4));
  float z_coord = *((float*)(input+8));

  return rawRelMov(x_coord, y_coord, z_coord);
}

byte rawRelMov(float x_coord, float y_coord, float z_coord) {
  bool xDir = (x_coord<0)?COUNTERCLOCKWISE:CLOCKWISE; //counterclockwise is left
  //negative is left
  bool yDir = (y_coord<0)?COUNTERCLOCKWISE:CLOCKWISE; //counterclockwise is backwards
  //negative is backwards
  bool zDir = (z_coord<0)?CLOCKWISE:COUNTERCLOCKWISE; //for some reason, the z-axis goes backwards; counterclockwise is up
  //negative is down

  int xTicks = abs(x_coord*PULSES_PER_CIRCLE/DISTANCE_PER_TURN);
  int yTicks = abs(y_coord*PULSES_PER_CIRCLE/DISTANCE_PER_TURN);
  int zTicks = abs(z_coord*PULSES_PER_CIRCLE/DISTANCE_PER_TURN);
  int maxTicks = max(xTicks, max(yTicks, zTicks));
  double current_delay = 5000;
  digitalWrite(DIR_X_PIN, (x_coord > 0? X_POS: X_NEG));
  digitalWrite(DIR_Y_PIN, (y_coord > 0? Y_POS: Y_NEG));
  digitalWrite(DIR_Z_PIN, (z_coord > 0? Z_POS: Z_NEG));

  for(int i = 0; i < maxTicks; i++){
    if(isColliding(zDir,Z) && zTicks!=0){
      zTicks = 0;
      int maxTicks = max(xTicks, max(yTicks, zTicks));
    }
    if(isColliding(yDir,Y) && yTicks!=0){
      yTicks = 0;
      int maxTicks = max(xTicks, max(yTicks, zTicks));
    }
    if(isColliding(xDir,X) && xTicks!=0){
      xTicks = 0;
      int maxTicks = max(xTicks, max(yTicks, zTicks));
    }

    if(i<xTicks){
      digitalWrite(CP_X_PIN, HIGH);
      digitalWrite(CP_X_PIN, LOW);
    }
    if(i<yTicks){
      digitalWrite(CP_Y_PIN, HIGH);
      digitalWrite(CP_Y_PIN, LOW);
    }
    if(i<zTicks){
      digitalWrite(CP_Z_PIN, HIGH);
      digitalWrite(CP_Z_PIN, LOW);
    }
    if (5000 > delay_ms) {
      if (i <= 1.5 * PULSES_PER_CIRCLE/DISTANCE_PER_TURN) {
        current_delay -= (5000 - delay_ms)/(1.5 * PULSES_PER_CIRCLE/DISTANCE_PER_TURN);
      }
      if (i > maxTicks - (1.5 * PULSES_PER_CIRCLE/DISTANCE_PER_TURN)) {
        current_delay += (5000 - delay_ms)/(1.5 * PULSES_PER_CIRCLE/DISTANCE_PER_TURN);
      }
    }
    delayMicroseconds(max(delay_ms, current_delay));
  }

  return SUCCESS;
}

byte setDel() {
  byte input[4];

  for(int i = 0; i < 4; i++){
    input[i] = Serial.read();
  }
  int _delay = *((int*)input);

  if (_delay >= 500) {
    delay_ms = _delay;
    return SUCCESS;
  } else {
    return VOOB;
  }
}

byte absMov(){
  byte input[12];

  for(int i = 0; i < 12; i++){
    input[i] = Serial.read();
  }

  float x_coord = *((float*)(input+0));
  float y_coord = *((float*)(input+4));
  float z_coord = *((float*)(input+8));

  if(x_coord != 0 && !calibrated[X]) return UNDEFINED_FAIL;
  if(y_coord != 0 && !calibrated[Y]) return UNDEFINED_FAIL;
  if(z_coord != 0 && !calibrated[Z]) return UNDEFINED_FAIL;

  return rawRelMov(x_coord - coord[X], y_coord - coord[Y], z_coord - coord[Z]);
}

byte setVac() {
  byte input = Serial.read();

  digitalWrite(VACUUM_PIN, input == 1? VAC_ON: VAC_OFF);

  vac_on = (input == 1);

  return SUCCESS;
}

byte togVac() {
  vac_on = !vac_on;

  digitalWrite(VACUUM_PIN, vac_on? VAC_ON: VAC_OFF);

  return SUCCESS;
}

