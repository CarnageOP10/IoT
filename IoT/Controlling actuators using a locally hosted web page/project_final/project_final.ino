#include <WiFi.h>

#include <WebServer.h>

#define ssid "ESP32_AP"
#define password "12345678"

#define blueLedPin 22
#define redLedPin 23
#define buzzer 5

IPAddress local_ip (192, 168, 1, 1);
IPAddress gateway (192, 168, 1, 1); 
IPAddress subnet (255, 255, 255, 0); 
WebServer server (80);
int Status = 0;


void handle_OnConnect(){
  Status = 0;
  Serial.println("LED Status : OFF");
  Serial.println("LED2 Status : OFF");
  Serial.println("Buzzer Status : LOW");
  server.send(200, "text/html", getHTML());
}

void handle_ledON(){
  Status = 1;
  Serial.println("LED Status : ON");
  server.send(200, "text/html", getHTML());
}

void handle_ledOFF(){
  Status = 2;
  Serial.println("LED Status : OFF");
  server.send(200, "text/html", getHTML());
}

void handle_led2ON(){
  Status = 3;
  Serial.println("LED2 Status : ON");
  server.send(200, "text/html", getHTML());
}

void handle_led2OFF(){
  Status = 4;
  Serial.println("LED2 Status : OFF");
  server.send(200, "text/html", getHTML());
}

void handle_buzzerON(){
  Status = 5;
  Serial.println("Buzzer Status : HIGH");
  server.send(200, "text/html", getHTML());
}

void handle_buzzerOFF(){
  Status = 6;
  Serial.println("Buzzer Status : LOW");
  server.send(200, "text/html", getHTML());
}

void handle_NotFound(){
  server.send(404,"text/plain", "Not found");
}

void setup() {

Serial.begin(115200);

pinMode (blueLedPin, OUTPUT);
pinMode (redLedPin, OUTPUT);
pinMode (buzzer, OUTPUT);
  digitalWrite(redLedPin, LOW);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(buzzer, LOW);

WiFi.softAP (ssid, password);
WiFi.softAPConfig (local_ip, gateway, subnet);
delay(1000);

server.on("/", handle_OnConnect);
server.on("/ledon", handle_ledON);
server.on("/ledoff", handle_ledOFF);
server.on("/led2on", handle_led2ON);
server.on("/led2off", handle_led2OFF);
server.on("/buzzeron", handle_buzzerON);
server.on("/buzzeroff", handle_buzzerOFF);
server.onNotFound(handle_NotFound);
server.begin();
Serial.println("HTTP Server Started");
}


void playNote(int frequency, int duration) {
  tone(buzzer, frequency, duration);
  delay(duration + 50); // Add a small delay to avoid overlap
  noTone(buzzer);
}
void playTune() {
  playNote(261, 500); // C (261 Hz)
  delay(200); // Short pause

  playNote(293, 500); // D (293 Hz)
  delay(200); // Short pause

  playNote(329, 500); // E (329 Hz)
  delay(200); // Short pause

  playNote(349, 500); // F (349 Hz)
  delay(200); // Short pause

  playNote(392, 500); // G (392 Hz)
  delay(200); // Short pause

  playNote(440, 500); // A (440 Hz)
  delay(200); // Short pause

  playNote(493, 500); // B (493 Hz)
  delay(200); // Short pause

  playNote(523, 1000); // C (523 Hz)
  delay(400); // Short pause

  playNote(587, 500); // D (587 Hz)
  delay(200); // Short pause

  playNote(659, 500); // E (659 Hz)
  delay(200); // Short pause

  playNote(698, 500); // F (698 Hz)
  delay(200); // Short pause

  playNote(783, 500); // G (783 Hz)
  delay(200); // Short pause
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
if(Status == 1){
  digitalWrite(blueLedPin, HIGH);
  delay(1000);
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, HIGH);
  delay(1000);
  digitalWrite(redLedPin, LOW);
}
else if(Status == 2){
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

if(Status == 3){
  digitalWrite(blueLedPin, HIGH);
  digitalWrite(redLedPin, HIGH);
}
else if(Status == 4){
  digitalWrite(blueLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

if(Status == 5){
 playTune();
  delay(1000);
}
else if(Status == 6){
  digitalWrite(buzzer, LOW);
}

}


String getHTML() {
    String htmlcode = "<!DOCTYPE html><html lang=\"en\">\n";
    htmlcode += "<head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Local webserver</title>\n";
    htmlcode += "<style>@import url('https://fonts.googleapis.com/css2?family=Lato:ital@1&display=swap');\n";
    htmlcode += "body {font-family: 'Lato', sans-serif; background-color: #212121;\n";
    htmlcode += "color: aliceblue;}\n";
    htmlcode += ".head {font-size: 5em;font-style: italic;position: absolute;left: 15%;top: 30%;}\n";
    htmlcode += ".h2 {font-size: 1.5em;position: absolute;top: 85%;right: 200px;}\n";
    htmlcode += ".led1 {font-size: 30px;position: absolute;top: 30%;right: 20%;}\n";
    htmlcode += ".led2 {font-size: 30px;position: absolute;top: 40%;right: 20%;}\n";
    htmlcode += ".led3 {font-size: 30px;position: absolute;top: 50%;right: 20%;}\n";
    htmlcode += ".btn1 {display: inline-block;padding: 10px 20px;font-size: 17px;font-weight: bold;color: #fff;background-color: #12e835;border: none;border-radius: 5px;cursor: pointer;box-shadow: 0px 3px 5px rgba(0, 0, 0, 0.2);transition: background-color 0.3s ease, transform 0.2s ease, box-shadow 0.3s ease;}\n";
    htmlcode += ".btn1:hover {background-color: #e20909;transform: scale(1.05);box-shadow: 0px 6px 8px rgba(0, 0, 0, 0.3);}\n";
    htmlcode += ".btn2 {display: inline-block;padding: 10px 20px;padding-left: 35px;font-size: 17px;font-weight: bold;color: #fff;background-color: #12e835;border: none;border-radius: 5px;cursor: pointer;box-shadow: 0px 3px 5px rgba(0, 0, 0, 0.2);transition: background-color 0.3s ease, transform 0.2s ease, box-shadow 0.3s ease;}\n";
    htmlcode += ".btn2:hover {background-color: #e20909;transform: scale(1.05);box-shadow: 0px 6px 8px rgba(0, 0, 0, 0.3);}\n";
    htmlcode += ".btn3 {display: inline-block;padding: 10px 20px;padding-left: 46px;padding-right: 46px;font-size: 17px;font-weight: bold;color: #fff;background-color: #12e835;border: none;border-radius: 5px;cursor: pointer;box-shadow: 0px 3px 5px rgba(0, 0, 0, 0.2);transition: background-color 0.3s ease, transform 0.2s ease, box-shadow 0.3s ease;}\n";
    htmlcode += ".btn3:hover {background-color: #e20909;transform: scale(1.05);box-shadow: 0px 6px 8px rgba(0, 0, 0, 0.3);}\n";
    htmlcode += "</style></head>\n";
    htmlcode += "<body>\n";
    htmlcode += "<div class=\"head\">\n";
    htmlcode += "WELCOME\n";
    htmlcode += "<br>\n";
    htmlcode += "TO OUR LOCAL\n";
    htmlcode += "<br>\n";
    htmlcode += "WEB SERVER\n";
    htmlcode += "</div>\n";
    htmlcode += "<br>\n";
    htmlcode += "<div class=\"h2\">\n";
    htmlcode += "Created by:  -\n";
    htmlcode += "Team.eXe\n";
    htmlcode += "</div><div class=\"led1\">\n";

    // LED1 button logic
    if (Status != 1) {
        htmlcode += "<a href=\"/ledon\"><button class=\"btn1\">Turn On Blinking Light</button></a>\n";
    } 
    else if(Status == 1){
        htmlcode += "<a href=\"/ledoff\"> <button class=\"btn1\">Turn Off Blinking Light</button></a>\n";
    }

htmlcode +="</div><div class=\"led2\">";
if(Status != 3){

 htmlcode += "<a href=\"/led2on\"> <button class=\"btn2\">Turn Both Lights On</button></a>\n";
}
else if(Status == 3){

 htmlcode += "<a href=\"/led2off\"><button class=\"btn2\">Turn Both Lights Off</button></a>\n";
}

htmlcode += "</div><div class=\"led3\">\n";
if(Status != 5){

 htmlcode += "<a href=\"/buzzeron\"><button class=\"btn3\">Turn On Buzzer</button></a>\n";
}
else if(Status == 5){
 htmlcode += "<a href=\"/buzzeroff\"><button class=\"btn3\">Turn off Buzzer</button></a>\n";
}
htmlcode += "</div></body></html>";

return htmlcode;
}




