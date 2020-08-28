#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#define HTTP_REST_PORT 80
#define WIFI_RETRY_DELAY 500
#define MAX_WIFI_INIT_RETRY 50

#define FAN_SPEED_1 5
#define FAN_SPEED_2 4
#define FAN_SPEED_3 0
#define OSCILLATION 2

const char* wifi_ssid = "reaktor23";
const char* wifi_passwd = "highsecuritypassword";

ESP8266WebServer http_rest_server(HTTP_REST_PORT);

int speed = 0;
bool oscillation = false;

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

void send_state() {
    StaticJsonDocument<200> doc;
    char JSONmessageBuffer[200];
    doc["speed"] = speed;
    doc["oscillation"] = oscillation;
    serializeJsonPretty(doc, JSONmessageBuffer);
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}


void init_relays() {
    pinMode(FAN_SPEED_1, OUTPUT);
    pinMode(FAN_SPEED_2, OUTPUT);
    pinMode(FAN_SPEED_3, OUTPUT);
    pinMode(OSCILLATION, OUTPUT);
    digitalWrite(FAN_SPEED_1, LOW);
    digitalWrite(FAN_SPEED_2, LOW);
    digitalWrite(FAN_SPEED_3, LOW);
    digitalWrite(OSCILLATION, LOW);
}

void off() {
    digitalWrite(FAN_SPEED_1, LOW);
    digitalWrite(FAN_SPEED_2, LOW);
    digitalWrite(FAN_SPEED_3, LOW);
    digitalWrite(OSCILLATION, LOW);
    speed = 0;
    oscillation = false;
    send_state();
}

void speed_1() {
    digitalWrite(FAN_SPEED_2, LOW);
    digitalWrite(FAN_SPEED_3, LOW);
    digitalWrite(FAN_SPEED_1, HIGH);
    speed = 1;
    send_state();
}

void speed_2() {
    digitalWrite(FAN_SPEED_1, LOW);
    digitalWrite(FAN_SPEED_3, LOW);
    digitalWrite(FAN_SPEED_2, HIGH);
    speed = 2;
    send_state();
}

void speed_3() {
    digitalWrite(FAN_SPEED_1, LOW);
    digitalWrite(FAN_SPEED_2, LOW);
    digitalWrite(FAN_SPEED_3, HIGH);
    speed = 3;
    send_state();
}

void oscillation_on() {
    digitalWrite(OSCILLATION, HIGH);
    oscillation = true;
    send_state();
}

void oscillation_off() {
    digitalWrite(OSCILLATION, LOW);
    oscillation = false;
    send_state();
}

void config_rest_server_routing() {
    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.send(200, "text/html",
            "Welcome to RESTfan");
    });
    http_rest_server.on("/state", HTTP_GET, send_state);
    http_rest_server.on("/off", HTTP_GET, off);
    http_rest_server.on("/speed/1", HTTP_GET, speed_1);
    http_rest_server.on("/speed/2", HTTP_GET, speed_2);
    http_rest_server.on("/speed/3", HTTP_GET, speed_3);
    http_rest_server.on("/oscillation/on", HTTP_GET, oscillation_on);
    http_rest_server.on("/oscillation/off", HTTP_GET, oscillation_off);
}

void setup(void) {
    init_relays();

    Serial.begin(115200);

    if (init_wifi() == WL_CONNECTED) {
        Serial.print("Connected to ");
        Serial.print(wifi_ssid);
        Serial.print("--- IP: ");
        Serial.println(WiFi.localIP());
    }
    else {
        Serial.print("Error connecting to: ");
        Serial.println(wifi_ssid);
    }

    config_rest_server_routing();

    http_rest_server.begin();
    Serial.println("HTTP REST Server Started");
}

void loop(void) {
    http_rest_server.handleClient();
}
