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
  switch (axis) {
    case X:
      if (dir == CLOCKWISE) {
        if(digitalRead(X_RIGHT_SENSOR)==SENSOR_TRIPPED){
          return true;
        }
      } else {
        if(digitalRead(X_LEFT_SENSOR)==SENSOR_TRIPPED){
          coord[X] = 0;
          return true;
        }
      }
    break;
    case Y:
      if(dir==CLOCKWISE && digitalRead(Y_BACK_SENSOR)==SENSOR_TRIPPED){
        return true;
      }
      if(dir==COUNTERCLOCKWISE && digitalRead(Y_FORWARD_SENSOR)==SENSOR_TRIPPED){
        coord[Y] = 0;
        return true;
      }
    break;
    case Z:
      if(dir==CLOCKWISE && digitalRead(Z_BOTTOM_SENSOR)==SENSOR_TRIPPED){
        coord[Z] = 0;
        return true;
      }
    break;
  }
  return false;
}