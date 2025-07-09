#ifndef _RouteFunctions_H    // Put these two lines at the top of your file.
#define _RouteFunctions_H    // (Use a suitable name, usually based on the file name.)

void get_blks() {
    JsonDocument jsonObj;
    String output;
    copyArray(BLK_Status, jsonObj);
    serializeJsonPretty(jsonObj, Serial);
    serializeJson(jsonObj, output);
    if (false)
        http_rest_server.send(204);
    else {
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*", 1);
        http_rest_server.send(200, "application/json", output);
    }
}

void setppk (String BLK, int ppk) {
  String response;
  response = "";
  if (BLK == "A")  {
    BLK_Status[0][2] = ppk; // BLK A PPK
    response = ControlAOff(); // First turn everything off then turn on
    SetRelay();
    switch (ppk) {
        case 0:
          response = ControlAOff();
          break;
        case 1:
            response = ControlA1();
          break;
        case 2:
            response = ControlA2();
          break;
        case 3:
            response = ControlA3();
          break;          
        default:
            response = ControlAOff();
          break;
      }
    SetRelay();
  }
  else {
    BLK_Status[1][2] = ppk; // BLK B PPK
    response = ControlBOff(); // First turn everything off then turn on
    SetRelay();
    switch (ppk) {
        case 0:
            response = ControlBOff();
          break;
        case 1:
            response = ControlB1();
          break;
        case 2:
            response = ControlB2();
          break;
        case 3:
            response = ControlB3();
          break;          
        default:
            response = ControlAOff();
          break;
      }
      SetRelay();
  }

}

void post_put_blks() {
    String body = http_rest_server.arg("plain"); // Access POST request body
  
    JsonDocument jsonObj;
    deserializeJson(jsonObj, body);
    const char* sboard = jsonObj["CNTRL"];
    const int blk = jsonObj["BLK"];
    const int ppk = jsonObj["PPK"];
    String board = String(sboard);

    if (board == ControlBoard) {
      switch (blk) {
        case 1:
          setppk ("A",ppk);
          break;
        case 2:
          setppk ("B",ppk);
          break;
        case 3:
          setppk ("A",ppk);
          break;
        case 4:
          setppk ("B",ppk);
          break;
        case 5:
          setppk ("A",ppk);
          break;
        case 6:
          setppk ("B",ppk);
          break;
        case 7:
          setppk ("A",ppk);
          break;
        case 8:
          setppk ("B",ppk);
          break;
      }
    }

    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*",1);
    if (false)
        http_rest_server.send(204);
    else {
        http_rest_server.send(200);
    }
}



#endif // _RouteFunctions_H    // Put this line at the end of your file.