#define IR_LED_GND 2
#define PHOTO_READ A7
#define IR_THRESHOLD 600

void setupIR(){
  pinMode(IR_LED_GND, OUTPUT); 
  digitalWrite(IR_LED_GND,LOW);
  pinMode(PHOTO_READ, INPUT_PULLUP); 
}
uint8_t IR_Count=0;
uint8_t IR_last=0;

void loopIR(){
  uint8_t IR_reading = (analogRead(PHOTO_READ) < IR_THRESHOLD);
  if( IR_last && ! IR_reading){
    IR_Count++;
    pendingShots=max(0,pendingShots-1);
    lastShotMillis=millis();
  }
  IR_last=IR_reading;
  
}
uint8_t IR_Pop(){
  uint8_t temp = IR_Count;
  IR_Count=0;
  return temp;
}
unsigned long TimeSinceLastShot(){
  if(lastShotMillis==0){
    lastShotMillis=millis();
  }
  return (millis()-lastShotMillis);
}
