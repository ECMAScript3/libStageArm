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
#define X_LEFT_SENSOR A3
#define X_RIGHT_SENSOR A2
#define Y_FRONT_SENSOR A1
#define Y_BACK_SENSOR A4
#define Z_BOTTOM_SENSOR A0

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
    if(dir==COUNTERCLOCKWISE && digitalRead(Y_FRONT_SENSOR)==SENSOR_TRIPPED){
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

  pinMode(X_LEFT_SENSOR, INPUT);
  pinMode(X_RIGHT_SENSOR, INPUT);
  pinMode(Y_FRONT_SENSOR, INPUT);
  pinMode(Y_BACK_SENSOR, INPUT);
  pinMode(Z_BOTTOM_SENSOR, INPUT);

  pinMode(DEBUG_LIGHT,OUTPUT);
}

void loop() {
  if(Serial.available()){
    digitalWrite(DEBUG_LIGHT, HIGH);
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

    delayMicroseconds(delay_ms);
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

