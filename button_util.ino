

uint8_t BUTTONCOUNT =6;

uint8_t btnPins[]={3,4,9,10,7,8};
uint8_t btnMasks[]={1,2,4,8,16,32};
uint8_t buttonState =0;
uint8_t lastButtonState =0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 0;

void setupButtons(){

  for (uint8_t i=0; i < BUTTONCOUNT; i++){
    pinMode(btnPins[i], INPUT_PULLUP);
  }
}
int GetButtonState(uint8_t button){
  return !(buttonState & btnMasks[button]);
}
int debugButtons(){
  Serial.println(buttonState);
  Serial.print("A:" + GetButtonState(BTN_ROTARY_A));
  Serial.print("B:" + GetButtonState(BTN_ROTARY_B));
  Serial.print("C:" + GetButtonState(BTN_ROTARY_C));
  Serial.print("D:" + GetButtonState(BTN_TAC));
  Serial.println();
}
void loopButtons(){
  //debugButtons();
  uint8_t reading=0;
  for(uint8_t i=0;i<BUTTONCOUNT;i++){
    if( digitalRead(btnPins[i])){
      reading = reading | btnMasks[i];
    }
  }
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
    }
  }
  lastButtonState = reading;
}

