/*
*
* WORKING TEST AJAX WITH JSON NODEMCU sketch
* Author: John Glatts
* Date: 4/17/19
*
*    ToDo
 *    - Include a new and improved .h file
 *      - A header file with .cpp function
 *      - Make a LIBRARY!
*     - Add a stats.txt and use it to keep track of uptime etc
*/
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>
#include <NPNControls.h>
// JS-HTML file
#include "htmlpage.h"


// neo-pixel pins
#define NPN_PIN 4
#define pix_pin 5
#define NUM_PIX 12
// MFRC522 pins
#define SS_PIN  2
#define RST_PIN  0
// MFRC522 Card
#define RFID_CARD_UID "C6 FB BD EF"


// Replace with your network credentials
const char* ssid = "your-network";
const char* password = "your-network";

// set up various instances
ESP8266WebServer server(80);
MFRC522 mfrc522(SS_PIN, RST_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIX, pix_pin, NEO_GRB + NEO_KHZ800);
NPN npn(NPN_PIN);

// global vars
String text, time_text, calc_time_page, index_page;
String rfid_status;
bool rfid_connection_status = false; // flag for RFID tag
unsigned long data, finish_time, elapsed_time, mod, motor_mins, motor_secs;


void setup(void){
    delay(1000);
    randomSeed(analogRead(0));  // seed for random(), used for random PIXEL colors
    pixels.begin();
    pixels.show();
    SPI.begin();
    mfrc522.PCD_Init();
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
    serverOnEveryThing();
    server.begin();
    Serial.println("Web server started!");
}


/* Map the href's, and improve readability */
void serverOnEveryThing() {
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
    server.on("/MotorOn", turnMotorOn);
    server.on("/stats.json", updateStatsXML);
    server.on("/Stats", displayStats);
    //server.on("/Pixel", controlPixel);
    server.on("/pixel-control.json", updatePixelColor);
    server.on("/about.json", updateAboutXML);
    server.on("/About", displayAbout);
    server.on("/RFID", rfidAccess);
    server.on("/RFID.json", rfidUpdate);
    server.on("/resetUID.json", rfidReset);
    server.on("/Reboot", espReboot);
    server.on("/", landingPage);
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
    turnOffPixel();
    // turn motor off
    npn.turnOffNPN();
    index_page = page;
    server.send(200, "text/html", index_page);
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
    // light up the pixel, here the argument is the elapsed time
    motor_mins >= 1 ? lightUpPixel(motor_mins) : turnOffPixel();
}


/* Receive color commands from the server to display on the neopixel */
/*
void controlPixel() {
    String pix_ctrl_page = pixel_control_page;
    Server.send(200, "text/html", pix_ctrl_page);
};
*/


/* Collect the color code from the HTML-page and display */
void updatePixelColor() {
    // add a separate string for new JS fn()s to update the .json page
    server.send(200, "text/html", index_page);
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
    stats["local_ip"] = String(WiFi.localIP());

    serializeJson(stats, stats_xml);
    serializeJsonPretty(stats, Serial);
    server.send(200, "application/json", stats_xml);
}


/* Update some 'About' info to a XML page */
void updateAboutXML() {
    String about_xml;

    StaticJsonDocument<500> about;

    about["author"] = "John Glatts";
    about["created"] = "4-21-2019";
    about["brief"] = "Nodemcu sketch with some Ajax to make it fun ;)";
    about["version"] = "1.0";

    serializeJson(about, about_xml);
    serializeJsonPretty(about, Serial);
    server.send(200, "application/json", about_xml);
}


/* Parse the JSON Stats object and display on a html page */
void displayStats() {
    // get the header
    String stats_page;

    stats_page = board_stats_page;
    server.send(200, "text/html", stats_page);
}


/* Display the 'About' Page */
void displayAbout() {
    // get the header
    String about_page;

    about_page = board_about_page;
    server.send(200, "text/html", about_page);
}


/* Turn the small motor on, using a NPN transitor */
void turnMotorOn() {
    npn.turnOnNPN();
    server.send(200, "text/html", index_page);
}


/* Testing the rfid module with the webserver
 *  - Display current card readings
 * */
void rfidAccess() {
    String rfid_page = rfid_page_html;
    server.send(200, "text/html", rfid_page);
}


/* Testing the rfid module with the webserver
 *  - Updates JSon
 *  - Todo:
 *      - Improve readability and add some helper fn()s
 *      - Works as intended right now, stops checking for cards if the register one has already been swipedS
 * */
void rfidUpdate() {
    String rfid_status_xml, content;
    byte letter;

    // Make sure the card/tag has NOT been verified
    if (rfid_connection_status) {
        displayCardInfo("John Is Checked In", RFID_CARD_UID);
    }
    else {
        // Look for new cards
        if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
        {
            displayCardInfo("No Card Present", "none");
        }
        else {
            // Get the UID from the card
            for (byte i = 0; i < mfrc522.uid.size; i++)
            {
                content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
                content.concat(String(mfrc522.uid.uidByte[i], HEX));
            }
            content.toUpperCase();
            if (content.substring(1) == RFID_CARD_UID) {
                rfid_connection_status = true;
                lightUpPixel(NUM_PIX);
                delay(1000);
            }
            else   {
                displayCardInfo("Access Denied", content.substring(1));
            }
            // Make sure Pixel is off
            turnOffPixel();
        }
    }
}


/* Testing the rfid module with the webserver
 *  - Updates JSON to 'Access Denied' when no card is present
 * */
void displayCardInfo(String user_card, String card_id) {
    String user_card_xml;

    StaticJsonDocument<500> new_card;
    new_card["user"] = user_card;
    card_id == "none" ? new_card["tag_card_id"]="N/A": new_card["tag_card_id"]=card_id;

    serializeJson(new_card, user_card_xml);
    server.send(200, "application/json", user_card_xml);
}


/* Testing the rfid module with the webserver
 *  - Reset the module, allowing new cards to be presented
 * */
void rfidReset() {
    rfid_connection_status = false;
}


/* Turn on the Pixel, displaying the elapsed time (in mins.) or turn on all LEDs */
void lightUpPixel(int count) {
    // light up the pixel
    for (int i = 0; i < count; ++i) {
        pixels.setPixelColor(i, pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
        pixels.show();
    }
}


/* Clear the Pixel */
void turnOffPixel() {
    for (int i = 0; i < NUM_PIX; ++i) {
        pixels.setPixelColor(i, 0);
        pixels.show();
    }
}


/* ESP Restart */
void espReboot() {
    ESP.reset();
}


/* Run the server and handle incoming clients */
void loop(void){
    server.handleClient();
}
