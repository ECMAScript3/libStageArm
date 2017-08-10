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