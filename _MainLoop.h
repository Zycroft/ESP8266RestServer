#ifndef _MainLoop_H    // Put these two lines at the top of your file.
#define _MainLoop_H    // (Use a suitable name, usually based on the file name.)

void loop(void) {
    // Feed the watchdog to prevent resets
    ESP.wdtFeed();
    
    // WiFi reconnection check - more frequent
    static unsigned long lastWiFiCheck = 0;
    static int wifiReconnectAttempts = 0;
    if (millis() - lastWiFiCheck > 5000) { // Check every 5 seconds (was 30)
        if (WiFi.status() != WL_CONNECTED) {
            wifiReconnectAttempts++;
            Serial.print("WiFi lost! Attempt #");
            Serial.print(wifiReconnectAttempts);
            Serial.println(" reconnecting...");
            
            if (wifiReconnectAttempts > 3) {
                // After 3 failed attempts, do a full reset
                Serial.println("Full WiFi reset...");
                WiFi.disconnect();
                delay(100);
                WiFi.mode(WIFI_STA);
                WiFi.setSleepMode(WIFI_NONE_SLEEP);
                WiFi.begin(wifi_ssid, wifi_passwd);
                wifiReconnectAttempts = 0;
            } else {
                // Try simple reconnect first
                WiFi.reconnect();
            }
        } else {
            // Connected - reset attempt counter
            if (wifiReconnectAttempts > 0) {
                Serial.println("WiFi reconnected successfully!");
                wifiReconnectAttempts = 0;
            }
        }
        lastWiFiCheck = millis();
    }
    
    // Memory monitoring (remove after debugging)
    static unsigned long lastHeapCheck = 0;
    if (millis() - lastHeapCheck > 10000) { // Every 10 seconds
        Serial.print("Free Heap: ");
        Serial.println(ESP.getFreeHeap());
        
        // Check for critically low memory
        if (ESP.getFreeHeap() < 8000) {
            Serial.println("WARNING: Low memory detected!");
        }
        lastHeapCheck = millis();
    }
    
    // Check for stuck relay flag periodically
    static unsigned long lastRelayCheck = 0;
    if (millis() - lastRelayCheck > 10000) { // Every 10 seconds
        if (relayBusy && (millis() - relayBusyTimestamp > RELAY_TIMEOUT)) {
            Serial.println("LOOP: Relay stuck detected, forcing unlock");
            relayBusy = false;
        }
        
        // Check for stuck handler
        if (handlerInProgress && (millis() - lastHandlerStart > 10000)) {
            Serial.println("LOOP: Handler stuck detected, forcing reset");
            handlerInProgress = false;
            relayBusy = false; // Also release relay if stuck
        }
        
        lastRelayCheck = millis();
    }
    
    // Periodic forced cleanup every 5 minutes
    static unsigned long lastForceCleanup = 0;
    if (millis() - lastForceCleanup > 300000) { // 5 minutes
        Serial.println("Periodic forced cleanup");
        WiFi.forceSleepWake(); // Wake WiFi to clear any stuck states
        delay(1);
        lastForceCleanup = millis();
    }
    
    http_rest_server.handleClient();
    ESP.wdtFeed(); // Feed watchdog again after handling client
    yield(); // CRITICAL: Give ESP8266 time for background tasks
    delay(1); // Small delay helps stability
}

#endif // _MainLoop_H    // Put this line at the end of your file.