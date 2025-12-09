#ifndef _BitOps_H    // Put these two lines at the top of your file.
#define _BitOps_H    // (Use a suitable name, usually based on the file name.)

// Turn off the Block A
void ControlAOff() {
          Serial.printf("A-0");
          Serial.println("  ");
          if (relay_NC) {
            Data = Data | RG1;
          } else {
            Data = Data & ~R00;
            Data = Data & ~R01;
            Data = Data & ~R02;
            Data = Data & ~R03;
            Data = Data & ~R04;
            Data = Data & ~R05;
            Data = Data & ~R06;
            Data = Data & ~R07;
          }
}
// Set the Block to ppk 1
void ControlA1() {
          Serial.printf("A-1");
          Serial.println("  "); 
          if (relay_NC) { 
            Data = Data & ~R00;
            Data = Data & ~R01;
          } else {
            Data = Data | R00;
            Data = Data | R01;
            Data = Data & ~R02;
            Data = Data & ~R03;
            Data = Data & ~R04;
            Data = Data & ~R05;
          }
}
// Set the Block to ppk 2
void ControlA2() {
          Serial.printf("A-2");
          Serial.println("  ");
          if (relay_NC) { 
            Data = Data & ~R02;
            Data = Data & ~R03; 
          } else {
            Data = Data & ~R00;
            Data = Data & ~R01;
            Data = Data | R02;
            Data = Data | R03;
            Data = Data & ~R04;
            Data = Data & ~R05;
          }
}
// Set the Block to ppk 3
void ControlA3() {
          Serial.printf("A-3");
          Serial.println("  ");
          if (relay_NC) { 
            Data = Data & ~R04;
            Data = Data & ~R05;  
          } else {
            Data = Data & ~R00;
            Data = Data & ~R01;
            Data = Data & ~R02;
            Data = Data & ~R03;
            Data = Data | R04;
            Data = Data | R05;
          }
}
// Turn off the Block B
void ControlBOff() {
          Serial.printf("B-0");
          Serial.println("  ");
          if (relay_NC) { 
            Data = Data | RG2;
          } else {
            Data = Data & ~R15;
            Data = Data & ~R14;
            Data = Data & ~R13;
            Data = Data & ~R12;
            Data = Data & ~R11;
            Data = Data & ~R10;
            Data = Data & ~R09;
            Data = Data & ~R08;
          }
}
// Set the Block to ppk 1
void ControlB1() {
          Serial.printf("B-1");
          Serial.println("  ");
          if (relay_NC) { 
            Data = Data & ~R15;
            Data = Data & ~R14; 
          } else {
            Data = Data | R15;
            Data = Data | R14;
            Data = Data & ~R13;
            Data = Data & ~R12;
            Data = Data & ~R11;
            Data = Data & ~R10;            
          }
}
// Set the Block to ppk 2
void ControlB2() {
          Serial.printf("B-2");
          Serial.println("  ");
          if (relay_NC) { 
            Data = Data & ~R13;
            Data = Data & ~R12;   
          } else {
            Data = Data & ~R15;
            Data = Data & ~R14;
            Data = Data | R13;
            Data = Data | R12;
            Data = Data & ~R11;
            Data = Data & ~R10;           
          }
}
// Set the Block to ppk 3
void ControlB3() {
          Serial.printf("B-3");
          Serial.println("  ");
          if (relay_NC) { 
            Data = Data & ~R11;
            Data = Data & ~R10;
          } else {
            Data = Data & ~R15;
            Data = Data & ~R14;
            Data = Data & ~R13;
            Data = Data & ~R12;
            Data = Data | R11;
            Data = Data | R10;
          }
}




#endif // _BitOps_H    // Put this line at the end of your file.