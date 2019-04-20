/*
*
* AJAX WITH JSON NODEMCU sketch
* Author: John Glatts
* Date: 4/17/19
*/
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
// JS-HTML file
#include "JSONHTMLpage.h"


// neo-pixel stuff
#define pix_pin 5
#define NUM_PIX 12


// Replace with your network credentials
const char* ssid = "network";
const char* password = "network";


ESP8266WebServer server(80);   // instantiate server at port 80
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
    WiFi.begin(ssid, password); // begin WiFi connection
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
        // calculate elapsed time and update XML
        pixelCalc();
        server.send(200, "text/html", time_text);
    });
    server.on("/Time", displayElapsedTime);
    server.on("/stats.json", updateStatsXML);
    server.on("/Stats", displayStats);
    server.on("/", landingPage);
    server.begin();
    Serial.println("Web server started!");
}


/* URL not found, Display whatever the arguments were */
void handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    // display the URL that's not found
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
}


/* HTML landing page */
void landingPage(){
    // Turn the Neopixel off
    for (int i = 0; i < motor_mins; ++i) {
        pixels.setPixelColor(i, 0);
        pixels.show();
    }
    index_page = page;
    server.send(200, "text/html", index_page);
}


/* Turn on the pixel to display time */
void lightUpPixel() {
    for (int i = 0; i < motor_mins; ++i) {
        pixels.setPixelColor(i, pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
        pixels.show();
    }
}


/* Turn off the pixel if time > 12 */
void turnOffPixel() {
    for (int i = 0; i < NUM_PIX; ++i) {
        pixels.setPixelColor(i, 0);
        pixels.show();
    }
}


/* Get the elapsed time and display it on the html page and the neopixel */
void pixelCalc() {
    elapsed_time = millis() - data;
    motor_mins = int(elapsed_time / 60000);
    mod = elapsed_time % 60000;
    motor_secs = int(mod / 1000);
    time_text = String(motor_mins);
    time_text += "||";  // add the delimiter
    time_text += String(motor_secs);
    // light up the pixel
    motor_mins >= 1 ? lightUpPixel(): turnOffPixel();
}


/* Display the elapsed time */
void displayElapsedTime() {
    calc_time_page = time_page;
    server.send(200, "text/html", calc_time_page);
}


/* Put the board stats (JSON) on an XML page, to be parsed by a JS script */
void updateStatsXML() {
    String stats_xml;

    // declare a new JSON document
    StaticJsonDocument<500> stats;

    // ESP board info
    stats["chipID"] = String(ESP.getChipId());
    stats["sketch_hash"] = ESP.getSketchMD5();
    stats["mac_address"] = String(WiFi.macAddress());
    stats["wifi_mode"] = String(WiFi.getMode());

    serializeJson(stats, stats_xml);
    serializeJson(stats, Serial);
    server.send(200, "application/json", stats_xml);
}


/* Parse the JSON Stats object and display on a html page */
void displayStats() {
    // get the header
    String stats_page;

    stats_page = board_stats_page;
    server.send(200, "text/html", stats_page);
}


/* Run the server and handle incoming clients */
void loop(void){
    server.handleClient();
}
