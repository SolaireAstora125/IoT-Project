#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// setup I/O sensor nodemcu---------------------------------
#define ldr_sensor A0
#define sm_sensor 5
// global variable------------------------------------------
int sm = 0;       //moisture percentage
int ldr = 0;       //light intensity
unsigned long lastTime = 0;
unsigned long timerDelay = 5000; //set timer to 5s
// WiFi detail----------------------------------------------
const char* ssid = "Mi 10T";
const char* password = "ziyadanas";
const char* serverName = "https://agriculture-iot.onrender.com/reading";
//----------------------------------------------------------

void wificlient(){
  WiFiClient client;
  HTTPClient http;
 
  http.begin(client, serverName); //Specify the URL
  String httpData = "&sm="+String(sm)+"&ldr="+String(ldr);
  
  int httpResponseCode = http.POST(httpData); //post http request
  if (httpResponseCode > 0) { //Check for the returning code
    String payload = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(payload+"\n");
    Serial.println("Moisture        : "+String(sm)+"%");
    Serial.println("Light Intensity : "+String(ldr)+"%");
  }
  else {
    Serial.print("Error Code: ");
    Serial.println(httpResponseCode);
  }
  //http.end(); //Free the resources
}

void setup(){
  Serial.begin(115200);
  // Setup pinmode-----------------------------
  //pinMode(ldr_sensor, INPUT);
  //pinMode(sm_sensor, INPUT);
  // Connect to WiFi network-------------------
  Serial.println();
  Serial.println();
  Serial.println("Connecting to "+String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address---------------------
  Serial.print("Network IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  //------------------------------------------
}

void loop(){
  // read input sensor-----------------------------------------------------------
  //sm = digitalRead(sm_sensor);
  sm = random(0,100);
  //ldr = (analogRead(ldr_sensor)/1023)*100;
  ldr = random(0,100);
  // check WiFi connection-------------------------------------------------------
  if((millis() - lastTime) > timerDelay){
    if(WiFi.status() == WL_CONNECTED) wificlient();
    else Serial.println("WiFi Disconnected");
  }
  lastTime = millis();
  //-----------------------------------------------------------------------------
}