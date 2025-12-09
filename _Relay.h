#ifndef _Relay_H    // Put these two lines at the top of your file.
#define _Relay_H    // (Use a suitable name, usually based on the file name.)

//---------------------------------------------Relay Communication
  void SetRelay(){
      //ground latchPin and hold low for as long as you are transmitting
      //Serial.println("SetRelay");
      //Serial.println(Data);
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, (Data >> 8));
      yield(); // Allow background tasks between shift operations
      shiftOut(dataPin, clockPin, MSBFIRST, Data);
      //return the latch pin high to signal chip that it
      //no longer needs to listen for information
      digitalWrite(latchPin, HIGH);
  }


void relaysOff() {
  if (relay_NC) { 
    Data = Data | R0G;
  } else {
    Data = Data & R0F;
  }
  //Serial.println("********RelayOff********");
  //Serial.println(Data,BIN);
  SetRelay();
}

  
#endif // _Relay_H    // Put this line at the end of your file.