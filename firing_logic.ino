uint8_t lastTrigger=false;
void loopFireMode(bool trigger){
  
  
  switch (firingMode){
      case FIREMODE_NONE:
        //display.println("---SAFE---");
        break;
      case FIREMODE_SINGLE:
         logicCountshots(trigger,1);
         break;
      case FIREMODE_BURST:
        logicCountshots(trigger,3);
        break;
      case FIREMODE_FULL:
        if (!trigger){resetFullAuto();}
        else{logicFullAuto();}
        break;
  }
  lastTrigger=trigger;



  
}

void logicCountshots(uint8_t trigger,uint8_t shots){
  if(!lastTrigger && trigger){
    Serial.println("New triggerpress");
    pendingShots=shots;
    lastShotMillis=millis();//to calibrate timeout starting at trigger press, renewed by IR sensor
  }
  
  //if we consumed all the pendingshots, turn off everything
  if(pendingShots==0){
    Serial.println("no pending shots");
    setFlywheel(false);
    setPusher(false);
    return;
  }
  
  if(TimeSinceLastShot() > COUNTSHOT_TIMEOUT){
    Serial.println("Too long with no shots, set pending to zero");
    pendingShots=0;
    setFlywheel(false);
    setPusher(false);
    return;
  }
  
  //no matter what, startup the flywheels otherwise
  setFlywheel(true);

  //if the flywheels have been going for at least WARMUP time, then run the pusher:
  
  if(FlywheelOnTime() > FULLAUTO_WARMUP_TIME){
    setPusher(true);
  }
  
}
void resetFullAuto(){
  //if trigger releases stop everthing
    setFlywheel(false);
    setPusher(false);
}


void logicFullAuto(){
  
  //no matter what, startup the flywheels otherwise
  setFlywheel(true);

  //if the flywheels have been going for at least WARMUP time, then run the pusher:
  
  if(FlywheelOnTime() > FULLAUTO_WARMUP_TIME){
    setPusher(true);
  }
}

