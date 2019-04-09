/*
 *
 * WORKING TEST AJAX NODEMCU sketch
 * Author: John Glatts
 * Date: 4/6/19
 *
 * ToDo:
 *      - :)
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// JS-HTML file
#include "htmlpage.h"


// Replace with your network credentials
const char* ssid = "your-network";
const char* password = "your-network";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)


String text = "";
String time_text = "";
String calc_time_page = "";
String index_page = "";
unsigned long data, finish_time, elapsed_time, mod, motor_mins, motor_secs;


void setup(void){
    delay(1000);
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


void calcTime() {
    calc_time_page = time_page;
    server.send(200, "text/html", calc_time_page);
}


void loop(void){
    server.handleClient();
}
