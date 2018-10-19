#define VOLT_READ A0


#define THRESHOLD_FULL 94 //12.6v =max charge
#define THRESHOLD_MID    400   // 11.1v =nominal voltage, standard?
#define THRESHOLD_CUTOFF  200  //9.6v = all motors off
#define THRESHOLD_DANGER 100 //9.0v =DO NOT OPERATE!!!
void setupVoltmeter(){
  pinMode(VOLT_READ, INPUT_PULLUP);
}
void loopVoltmeter(){
  //Serial.println(analogRead(VOLT_READ));
}


