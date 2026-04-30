#include <Arduino.h>
#include <WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include "credentials.h"

// --- Stepper motor control setup ---
const int pin1 = D0, pin2 = D1, pin3 = D2, pin4 = D3;
const long doorSteps = 90000; // Range of Motion
int minDelayTime = 2000;
int maxDelayTime = 4000;   
int delayTime = 2000;   // Torque vs speed
int currentStep = 0, motorDirection = 0, directionChange = 0;
long stepsRemaining = 0, loopCount = 0, stepsDone = 0;
unsigned long lastStepTime = 0;

//Half-step sequence for 28BYJ-48
const int steps[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}};

//Move stepper motor one step
void runMotor() {
    if (stepsRemaining <= 0) return;

    //Switch Direction Halfway to Reverse
    if (stepsRemaining < doorSteps && directionChange == 0) {
      motorDirection *= -1;
      directionChange = 1;
    }

    //Adjust Delay Time
    delayTime = (abs(stepsRemaining - doorSteps) < 25000) ? maxDelayTime : minDelayTime;

    //Maintain equal timing
    unsigned long now = micros();
    if (now - lastStepTime >= delayTime) {
        lastStepTime = now;

        //Step one step
        currentStep = (currentStep + motorDirection + 8) % 8;
        digitalWrite(pin1, steps[currentStep][0]);
        digitalWrite(pin2, steps[currentStep][1]);
        digitalWrite(pin3, steps[currentStep][2]);
        digitalWrite(pin4, steps[currentStep][3]);

        stepsRemaining--;

        // When done power off coils
        if (stepsRemaining == 0) {
            digitalWrite(pin1, LOW);
            digitalWrite(pin2, LOW);
            digitalWrite(pin3, LOW);
            digitalWrite(pin4, LOW);
            Serial.println("[DOOR] Done.");
            directionChange = 0;
        }
    }
}

// --- WiFi setup ---
void wifiSetup() {
    WiFi.mode(WIFI_STA);
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(200);
    }
    Serial.println();
    Serial.printf("[WIFI] Connected! IP: %s\n", WiFi.localIP().toString().c_str());
}

void setup() {
    Serial.begin(115200);

    // Set stepper pins
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);
    pinMode(pin4, OUTPUT);

    Serial.printf("pin1=%d pin2=%d pin3=%d pin4=%d\n", pin1, pin2, pin3, pin4);

    wifiSetup();

    SinricProSwitch &door = SinricPro[SINRIC_DEVICE_ID];
    door.onPowerState([](const String &deviceId, bool &state) {
        Serial.printf("[SINRIC] Switch command: %s\n", state ? "ON" : "OFF");
        stepsRemaining = doorSteps * 2;
        if (state) {
            Serial.println("Command OPEN");
            motorDirection = 1;
        } else {
            Serial.println("Command CLOSE");
            motorDirection = -1;
        }
        SinricProSwitch &d = SinricPro[SINRIC_DEVICE_ID];
        d.sendPowerStateEvent(state);
        return true;
    });

    SinricPro.onConnected([]() { Serial.println("[SINRIC] Connected!"); });
    SinricPro.onDisconnected([]() { Serial.println("[SINRIC] Disconnected."); });
    SinricPro.begin(SINRIC_APP_KEY, SINRIC_APP_SECRET);
}

void loop() {
    SinricPro.handle();
    runMotor();
    loopCount++;
    if (loopCount > 50000) {
        loopCount = 0;
        stepsDone = doorSteps * 2 - stepsRemaining;
        Serial.printf("Steps Done: %ld | Direction: %i | Direction Changed: %i\n", stepsDone, motorDirection, directionChange);
    }
}