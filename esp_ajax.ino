/*
 *
 * WORKING TEST AJAX NODEMCU sketch
 * Author: John Glatts
 * Date: 4/6/19
 *
 * ToDo:
 *      - Add a .h file and place all the html stuff there
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


// Replace with your network credentials
const char* ssid = "your-wifi";
const char* password = "your-wifi";
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)


String page = "";
String time_page = "";
String text = "";
String time_text = "";
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
        page = "<h1>Sensor to Node MCU Web Server</h1>\r\n";
        // change the JS here to record the time ONLY when the Time It link has been clicked
        page += "<br><a href=\"Time\" onclick=\"\">Time It</a>\r\n";
        page += "<script>\r\n";
        page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
        page += "function loadData(url, callback){\r\n";
        page += "var xhttp = new XMLHttpRequest();\r\n";
        page += "xhttp.onreadystatechange = function(){\r\n";
        page += " if(this.readyState == 4 && this.status == 200){\r\n";
        page += " callback.apply(xhttp);\r\n";
        page += " }\r\n";
        page += "};\r\n";
        page += "xhttp.open(\"GET\", url, true);\r\n";
        page += "xhttp.send();\r\n";
        page += "}\r\n";
        page += "function updateData(){\r\n";
        page += " console.log(this.responseText);\r\n";
        page += "}\r\n";
        page += "</script>\r\n";
        server.send(200, "text/html", page);
    });

    server.begin();
    Serial.println("Web server started!");
}


void calcTime() {
    time_page = "<h1>Sensor to Node MCU Web Server</h1>";
    time_page += "<h1 style=\"display:inline;\">Time: </h1><h1 id=\"mins\" style=\"display:inline;\">""</h1><h1 style=\"display:inline;\"> mins </h1>";
    time_page += "<h1 style=\"display:inline;\"> and </h1><h1 id=\"secs\" style=\"display:inline;\">""</h1>";
    time_page += "<h1 style=\"display:inline;\"> secs. </h1>\r\n";
    time_page += "<script>\r\n";
    time_page += "var x = setInterval(function() {loadTime(\"time.txt\",updateTime)}, 1000);\r\n";
    time_page += "function loadTime(url, callback){\r\n";
    time_page += "var xhttp_time = new XMLHttpRequest();\r\n";
    time_page += "xhttp_time.onreadystatechange = function(){\r\n";
    time_page += " if(this.readyState == 4 && this.status == 200){\r\n";
    time_page += " callback.apply(xhttp_time);\r\n";
    time_page += " }\r\n";
    time_page += "};\r\n";
    time_page += "xhttp_time.open(\"GET\", url, true);\r\n";
    time_page += "xhttp_time.send();\r\n";
    time_page += "}\r\n";
    time_page += "function updateTime(){\r\n";
    time_page += "var timeArray = this.responseText.split(\"||\");\r\n";
    time_page += "console.log(timeArray[0]);\r\n";
    time_page += "console.log(timeArray[1]);\r\n";
    time_page += "console.log(\"----------- \");\r\n";
    time_page += "document.getElementById(\"mins\").innerHTML = timeArray[0];\r\n";
    time_page += "document.getElementById(\"secs\").innerHTML = timeArray[1];\r\n";
    time_page += "}\r\n";
    time_page += "</script>\r\n";
    server.send(200, "text/html", time_page);
}


void loop(void){
    delay(1000);
    server.handleClient();
}
