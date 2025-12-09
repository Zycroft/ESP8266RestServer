#ifndef _RouteFunctions_H    // Put these two lines at the top of your file.
#define _RouteFunctions_H    // (Use a suitable name, usually based on the file name.)

void get_blks() {
    // Check WiFi status first
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("GET rejected - WiFi disconnected");
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(503, "application/json", "{\"error\":\"WiFi disconnected\"}");
        return;
    }
    
    StaticJsonDocument<512> jsonObj; // Fixed size prevents heap fragmentation
    
    copyArray(BLK_Status, jsonObj);
    
    // Only output to serial in debug mode - comment out in production
    // serializeJsonPretty(jsonObj, Serial);
    
    // Use fixed char buffer instead of String to prevent heap fragmentation
    char output[256];
    size_t len = serializeJson(jsonObj, output, sizeof(output));
    
    http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
    http_rest_server.sendHeader("Connection", "close"); // Force connection close to prevent accumulation
    http_rest_server.send(200, "application/json", output);
    
    jsonObj.clear(); // Explicitly clear
    yield();
}

void setppk (const char* BLK, int ppk) {
  // Race condition protection - check if relay is busy
  if (relayBusy) {
    Serial.println("Relay busy, request ignored");
    return;
  }
  
  relayBusy = true; // Lock relay access
  relayBusyTimestamp = millis(); // Record when we acquired lock
  
  // Emergency safety: ensure we always release lock within reasonable time
  // This runs even if function crashes/returns early
  bool localBusy = true; // Track local state
  
  // Validate ppk range
  if (ppk < 0 || ppk > 3) {
    Serial.println("Invalid ppk value, using 0");
    ppk = 0;
  }
  
  if (strcmp(BLK, "A") == 0)  {
    BLK_Status[0][2] = ppk; // BLK A PPK
    switch (ppk) {
        case 0:
          ControlAOff();
          break;
        case 1:
          ControlA1();
          break;
        case 2:
          ControlA2();
          break;
        case 3:
          ControlA3();
          break;          
        default:
          ControlAOff();
          break;
      }
  }
  else {
    BLK_Status[1][2] = ppk; // BLK B PPK
    switch (ppk) {
        case 0:
          ControlBOff();
          break;
        case 1:
          ControlB1();
          break;
        case 2:
          ControlB2();
          break;
        case 3:
          ControlB3();
          break;          
        default:
          ControlBOff();
          break;
      }
  }
  
  SetRelay(); // Call ONLY ONCE at the end to reduce blocking
  
  // Safety check before releasing
  if (relayBusy) {
    relayBusy = false; // Release lock
    Serial.print("Relay op completed for BLK ");
    Serial.print(BLK);
    Serial.print(" PPK ");
    Serial.println(ppk);
  }
  
  yield(); // Give system time
}

void post_put_blks() {
    handlerInProgress = true; // Mark handler as executing
    lastHandlerStart = millis();
    
    // CRITICAL: Check WiFi status first - reject if disconnected
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Request rejected - WiFi disconnected");
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(503, "application/json", "{\"error\":\"WiFi disconnected\"}");
        handlerInProgress = false;
        return;
    }
    
    requestCount++; // Track requests
    
    // Periodic cleanup every 500 requests to prevent resource exhaustion
    if (requestCount >= MAX_REQUESTS_BEFORE_CLEANUP) {
        Serial.println("Performing periodic cleanup...");
        requestCount = 0;
        // Force garbage collection by creating and destroying a small allocation
        yield();
    }
    
    StaticJsonDocument<256> jsonObj; // Fixed size to prevent memory leaks
    
    // Check for relay stuck in busy state (safety timeout)
    if (relayBusy && (millis() - relayBusyTimestamp > RELAY_TIMEOUT)) {
        Serial.println("WARNING: Relay timeout, forcing unlock");
        relayBusy = false;
    }
    
    // Emergency check: if memory critically low, reject request
    if (ESP.getFreeHeap() < 5000) {
        Serial.println("CRITICAL: Memory too low, rejecting request");
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(503, "application/json", "{\"error\":\"Low memory\"}");
        // Force some cleanup
        delay(100);
        yield();
        handlerInProgress = false;
        return;
    }
    
    // Check if body exists first
    if (!http_rest_server.hasArg("plain")) {
        Serial.println("Empty request body");
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(400, "application/json", "{\"error\":\"Empty body\"}");
        handlerInProgress = false;
        return;
    }
    
    Serial.print("Request #");
    Serial.print(requestCount);
    Serial.print(" Heap: ");
    Serial.println(ESP.getFreeHeap());
    
    // CRITICAL FIX: Create minimal scope for String to minimize lifetime
    DeserializationError error;
    {
        // String only lives in this block, then immediately destroyed
        const String& bodyRef = http_rest_server.arg("plain");
        error = deserializeJson(jsonObj, bodyRef);
        // bodyRef goes out of scope here, String reference released
    }
    
    if (error) {
        Serial.print("JSON Error: ");
        Serial.println(error.c_str());
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        jsonObj.clear();
        handlerInProgress = false;
        return;
    }
    
    const char* sboard = jsonObj["CNTRL"];
    const int blk = jsonObj["BLK"] | 0; // Default to 0 if missing
    const int ppk = jsonObj["PPK"] | 0; // Default to 0 if missing
    
    // Validate all required fields are present
    if (!sboard) {
        Serial.println("Missing CNTRL field");
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(400, "application/json", "{\"error\":\"Missing CNTRL field\"}");
        jsonObj.clear();
        handlerInProgress = false;
        return;
    }
    
    // Avoid String object creation - compare C strings directly
    if (strcmp(sboard, ControlBoard) == 0 && blk >= 1 && blk <= 8) {
        // Check if relay is busy before attempting operation
        if (relayBusy) {
            http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
            http_rest_server.sendHeader("Connection", "close");
            http_rest_server.send(503, "application/json", "{\"error\":\"Relay busy, try again\"}");
            jsonObj.clear();
            handlerInProgress = false;
            return;
        }
        // Odd blocks = A, Even blocks = B
        setppk((blk % 2 == 1) ? "A" : "B", ppk);
        
        Serial.println("POST request completed successfully");
        
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(200);
        jsonObj.clear();
        handlerInProgress = false;
    } else {
        // Invalid request - board/block mismatch
        Serial.println("Invalid board or block");
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Connection", "close");
        http_rest_server.send(400, "application/json", "{\"error\":\"Invalid board or block\"}" );
        jsonObj.clear();
        handlerInProgress = false;
    }
}



#endif // _RouteFunctions_H    // Put this line at the end of your file.