// MSP430F5529 LaunchPad + CC3100 BoosterPack: connect to Wi-Fi,
// print IP address, signal strength and MAC address over serial.

#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "hackathon";
char password[] = "att4hack";

void setup() {
    Serial.begin(9600);
    delay(500);
    Serial.println("\n--- CC3100 Wi-Fi test");

    Serial.print("Connecting to ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println(" connected");

    Serial.print("Waiting for IP");
    while (WiFi.localIP() == INADDR_NONE) {
        Serial.print(".");
        delay(300);
    }
    Serial.println();

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    uint8_t mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC address: ");
    for (int i = 0; i < 6; i++) {
        if (mac[i] < 0x10) Serial.print("0");
        Serial.print(mac[i], HEX);
        if (i < 5) Serial.print(":");
    }
    Serial.println();
}

void loop() {
}
