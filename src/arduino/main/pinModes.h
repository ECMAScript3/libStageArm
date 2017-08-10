void set_pins() {
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
  //pinMode(X_LEFT_SENSOR, INPUT);
  //pinMode(X_RIGHT_SENSOR, INPUT);
  //pinMode(Y_FORWARD_SENSOR, INPUT);
  //pinMode(Y_BACK_SENSOR, INPUT);
  //pinMode(Z_BOTTOM_SENSOR, INPUT);

  pinMode(DEBUG_LIGHT,OUTPUT);
}