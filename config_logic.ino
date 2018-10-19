uint8_t prevConfig=0;
uint8_t configReady=0;
void loopConfig(){
  configReady=0;
  if(GetButtonState(BTN_MAIN_TRIG)){configReady+=1;}
  if(GetButtonState(BTN_REV_TRIG) ){configReady+=2;}

  if(prevConfig==0){
    if(configReady==1){
      increaseROF();
    }
    if(configReady==2){
      increaseVelocity();
    }
  }
  prevConfig=configReady;
}
void increaseROF(){
  if(pusherPower >=255){
    pusherPower =15;
  }
  else{
    pusherPower +=16;
  }
  ScreenRedraw();
}
void increaseVelocity(){
  if(flywheelPower >=255){
    flywheelPower =15;
  }
  else{
    flywheelPower +=16;
  }
  ScreenRedraw();
}

