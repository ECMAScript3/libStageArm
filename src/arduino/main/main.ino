#include "definitions.h"
#include "pinModes.h"
#include "movement.h"
#include "collision.h"
#include "calibrate.h"

void setup() {
  for(int i = 0; i < 3; i++){
    coord[i] = 0;
    calibrated[i] = false;
  }
    
  Serial.begin(9600);
  set_pins();
  vac_on = false;

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

//Set Period of loop
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


//Move head to coordinate position
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

