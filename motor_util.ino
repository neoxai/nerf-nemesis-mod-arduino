#define MOSFET_FLYWHEEL 5
#define MOSFET_PUSHER 6

void setupMotors(){
  analogWrite(MOSFET_FLYWHEEL, 0);
  pinMode(MOSFET_FLYWHEEL, OUTPUT);
  analogWrite(MOSFET_PUSHER,0);
  pinMode(MOSFET_PUSHER, OUTPUT);
}


unsigned long flywheelOnMillis = 0;
unsigned long pusherOnMillis = 0;
void setFlywheel(bool enable){
  if(enable){
    analogWrite(MOSFET_FLYWHEEL,flywheelPower);
    if(flywheelOnMillis==0){
      flywheelOnMillis=millis();
    }
  }
  else{
    analogWrite(MOSFET_FLYWHEEL,0);
    flywheelOnMillis=0;
  }
}
void setPusher(bool enable){
  if(enable){
    analogWrite(MOSFET_PUSHER,pusherPower);
    if(pusherOnMillis==0){
      pusherOnMillis=millis();
    }
  }
  else{
    analogWrite(MOSFET_PUSHER,0);
    pusherOnMillis=0;
  }
}

unsigned long PusherOnTime(){
  if(pusherOnMillis==0){return 0;}
  return millis()-pusherOnMillis;
}
unsigned long FlywheelOnTime(){
  if(flywheelOnMillis==0){return 0;}
  return (millis()-flywheelOnMillis);
}
void motorPower(uint8_t flywheel,uint8_t pusher){
  flywheelPower=min(flywheel,255);
  pusherPower=min(pusher,255);
}

