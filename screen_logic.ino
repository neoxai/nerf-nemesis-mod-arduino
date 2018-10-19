uint8_t lastScreen=0;
void ScreenRedraw(){
  lastScreen=0;
}
void ScreenLogicAmmoCountDown(){
  uint8_t temp=IR_Pop();
  if(temp > 0){
    Serial.println("POP");
    Ammo-=temp;
    drawInt(Ammo);
  }
  if(lastScreen !=1){
    drawAmmo(Ammo);
    drawFireMode();
    lastScreen=1;
  }
  
}
void ScreenLogicMotorPower(){
  if(lastScreen !=2){
    drawConfig(flywheelPower,pusherPower);
    lastScreen=2;
  }
  
}
