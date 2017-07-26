#define CP_X_PIN 2 //red
#define DIR_X_PIN 3 //yellow
#define EN_X_PIN 4 //green

#define CP_Y_PIN 5
#define DIR_Y_PIN 6
#define EN_Y_PIN 7

//pins out of order because of soldering mistake the pins are intentionally switched around
#define CP_Z_PIN 8
#define DIR_Z_PIN 10
#define EN_Z_PIN 9

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
#define DELAY 1000

//Serial commands
#define CALIBRATE_ALL 0x00
#define CALIBRATE 0x01
#define REL_MOV 0x02
#define ABS_MOV 0x03
#define SET_VAC 0x04
#define TOG_VAC 0x05

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

typedef char byte;
typedef bool spin_direction;

spin_direction xDir;
spin_direction yDir;
spin_direction zDir;

float coord[3];
bool calibrated[3];

for(int i = 0; i < 3; i++){
  coord[i] = 0;
  calibrated[i] = false;
}

void setup() {
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

  pinMode(X_LEFT_SENSOR, INPUT);
  pinMode(X_RIGHT_SENSOR, INPUT);
  pinMode(Y_FRONT_SENSOR, INPUT);
  pinMode(Y_BACK_SENSOR, INPUT);
  pinMode(Z_BOTTOM_SENSOR, INPUT);

  pinMode(DEBUG_LIGHT,OUTPUT);
}

void loop() {
  if(Serial.available()){
   byte command = Serial.read();

   switch(command){
    case CALIBRATE: 
      Serial.print(calibrate());
      break;
    case REL_MOV:
      Serial.print(relMov());
      break;
    //uncomment the following as you write functions
    /*case ABS_MOV:
      Serial.print(absMov());
      break;
    case SET_VAC:
      Serial.print(setVac());
      break;
    case TOG_VAC:
      Serial.print(togVac());
      break;*/ 
    default: 
      Serial.print(GENERAL_FAIL);
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
    delayMicroseconds(DELAY);
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

  //do_stuff

  return SUCCESS;
}

