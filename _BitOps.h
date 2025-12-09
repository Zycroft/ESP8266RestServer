#ifndef _BitOps_H    // Put these two lines at the top of your file.
#define _BitOps_H    // (Use a suitable name, usually based on the file name.)

// Turn off the Block A
String ControlAOff() {
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

          return "OK";
}
// Set the Block to ppk 1
String ControlA1() {
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
                   


          return "OK";
}
// Set the Block to ppk 2
String ControlA2() {
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
         

          return "OK";
}
// Set the Block to ppk 3
String ControlA3() {
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
         

          return "OK";
}
// Turn off the Block B
String ControlBOff() {
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
          return "OK";
}
// Set the Block to ppk 1
String ControlB1() {
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
          return "OK";
}
// Set the Block to ppk 2
String ControlB2() {
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
          return "OK";
}
// Set the Block to ppk 3
String ControlB3() {
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


          return "OK";
}




#endif // _BitOps_H    // Put this line at the end of your file.