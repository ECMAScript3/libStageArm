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