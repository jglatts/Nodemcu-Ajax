/*
 *
 * Nodemcu Ajax sketch with Neopixel support
 * Author: John Glatts
 * Date: 4/6/19
 *
 */
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// JS-HTML file
#include "htmlpage.h"


// neo-pixel stuff
#define pix_pin 5
#define NUM_PIX 12


// Replace with your network credentials
const char* ssid = "";
const char* password = "";


ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIX, pix_pin, NEO_GRB + NEO_KHZ800);


String text = "";
String time_text = "";
String calc_time_page = "";
String index_page = "";
unsigned long data, finish_time, elapsed_time, mod, motor_mins, motor_secs;


void setup(void){
    delay(1000);
    randomSeed(analogRead(0));  // seed for random(), used for random PIXEL colors
    pixels.begin();
    pixels.show();
    Serial.begin(115200);
    WiFi.begin(ssid, password); //begin WiFi connection
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.onNotFound(handleNotFound);
    server.on("/data.txt", [](){
        data = millis();
        text = (String)data;
        server.send(200, "text/html", text);
    });
    server.on("/time.txt", [](){
        // calc. elapsed time and update xml
        finish_time = millis();
        elapsed_time = finish_time - data;
        motor_mins = int(elapsed_time / 60000);
        mod = elapsed_time % 60000;
        motor_secs = int(mod / 1000);
        time_text = String(motor_mins);
        time_text += "||";  // delimiter
        time_text += String(motor_secs);
        // light up the pixel
        if (motor_mins >= 1) {
            for (int i = 0; i < motor_mins; ++i) {
                pixels.setPixelColor(i, pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
                pixels.show();
            }
        }
        server.send(200, "text/html", time_text);
    });
    server.on("/Time", calcTime);
    server.on("/", [](){
        index_page = page;
        server.send(200, "text/html", index_page);
    });

    server.begin();
    Serial.println("Web server started!");
}


/* URL not found */
void handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    // spit out and display the URL that's not found
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
}

void calcTime() {
    calc_time_page = time_page;
    server.send(200, "text/html", calc_time_page);
}


void loop(void){
    server.handleClient();
}
