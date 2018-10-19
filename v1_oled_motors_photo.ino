#include "definitions.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {

  Serial.begin(9600);

  setupOled();
  setupButtons();
  setupIR();
  setupMotors();
  setupVoltmeter();
}

//System Global vars
uint8_t flywheelPower=127;  //max 255, min 0(off)
uint8_t pusherPower=127;
uint8_t firingMode=FIREMODE_NONE;
uint8_t Ammo=99;
uint8_t pendingShots=0;
unsigned long lastShotMillis = 0;
void loop(){
  loopButtons();
  loopIR();
  loopVoltmeter();

  //Swap between setup and firing modes
  if(GetButtonState(BTN_TAC)){
    //Go into configuration mode
    loopFireMode(false);
    loopConfig();
    ScreenLogicMotorPower();
  }
  else{
      if(GetButtonState(BTN_ROTARY_A)){
        confirmFiringState(FIREMODE_SINGLE);
      }
      else if (GetButtonState(BTN_ROTARY_B)){
        confirmFiringState(FIREMODE_FULL);
      }
      else if (GetButtonState(BTN_ROTARY_C)){
        confirmFiringState(FIREMODE_BURST);
      }
      loopFireMode(GetButtonState(BTN_MAIN_TRIG));
      ScreenLogicAmmoCountDown();
  }

  
}

void confirmFiringState(uint8_t mode){
  if(firingMode != mode){
    firingMode=mode;
    loopFireMode(false);
    ScreenRedraw();
  }
}



