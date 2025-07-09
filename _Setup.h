#ifndef _Setup_H    // Put these two lines at the top of your file.
#define _Setup_H    // (Use a suitable name, usually based on the file name.)

void handleNotFound()
{
    if (http_rest_server.method() == HTTP_OPTIONS)
    {
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*");
        http_rest_server.sendHeader("Access-Control-Max-Age", "10000");
        http_rest_server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
        http_rest_server.sendHeader("Access-Control-Allow-Headers", "*");
        http_rest_server.send(204);
    }
    else
    {
        http_rest_server.send(404, "text/plain", "");
    }
}

void config_rest_server_routing() {
  // Handler for CORS preflight requests (OPTIONS)

    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.sendHeader("Access-Control-Allow-Origin", "*", 1);
        http_rest_server.send(200, "text/html",
            "Welcome to the ESP8266 REST Web Server");
    });

    http_rest_server.on("/blks", HTTP_GET, get_blks);
    http_rest_server.on("/blks", HTTP_POST, post_put_blks);
    http_rest_server.onNotFound(handleNotFound);
    /*
    http_rest_server.on("/leds", HTTP_GET, get_leds);
    http_rest_server.on("/leds", HTTP_POST, post_put_leds);
    http_rest_server.on("/leds", HTTP_PUT, post_put_leds);
    */
}

int init_wifi() {
    int retries = 0;

    Serial.println("Connecting to WiFi AP..........");

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_passwd);
    // check the status of WiFi connection to be WL_CONNECTED
    while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY)) {
        retries++;
        delay(WIFI_RETRY_DELAY);
        Serial.print("#");
    }
    return WiFi.status(); // return the WiFi connection status
}

void setup(void) {
    Serial.begin(115200);
      delay(10);

    // Set all the pins of 74HC595 as OUTPUT
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT); 
    pinMode(clockPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    Data = R0F;
    //Serial.println("Data Initialized");
    //Serial.println(Data,BIN);
    relaysOff();

    if (init_wifi() == WL_CONNECTED) {
        Serial.print("Connetted to ");
        Serial.print(wifi_ssid);
        Serial.print("--- IP: ");
        Serial.println(WiFi.localIP());
    }
    else {
        Serial.print("Error connecting to: ");
        Serial.println(wifi_ssid);
    }

    config_rest_server_routing();

    //http_rest_server.enableCORS(true);
    http_rest_server.begin();
    
    Serial.println("HTTP REST Server Started");
}

#endif // _Setup_H    // Put this line at the end of your file.