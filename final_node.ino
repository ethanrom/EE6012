
#include <ESP8266WiFi.h> // wifi lib
#include <ESP8266HTTPClient.h> // http lib
#include <WiFiClient.h>  
#include <NTPClient.h> // NTP server 
#include <WiFiUdp.h>   // NTP server 
#include <SoftwareSerial.h> // Serial communication 
SoftwareSerial s(12,14); // (RX,TX)



// define NTP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
 
// ssid & pass
const char* ssid     = "Yasas_103569";
const char* password = "Yasas@760";

// server url 
const char* serverName = "http://esoft-water-meter.000webhostapp.com/post-esp-data_h.php";

//api key
String apiKeyValue = "tPmAT5Ab3j7F9";

String NIC = "951111600v"; // user id
//int val_1; 
String adata; // arduino data
unsigned long oldTime; // for timer
String METER_VALUE = "1.7894";


void setup() {
s.begin(9600); //  arduin commo
Serial.begin(115200);
WiFi.begin(ssid, password); // wifi connect
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // initiali 
  timeClient.begin();
  timeClient.setTimeOffset(19800);
  pinMode(5,OUTPUT);
  oldTime           = 0;

  
}
 
void loop() {

  
  s.write("s");

  if (s.available()>0)
  {
    adata= s.read();
    Serial.print ("Arduino value:   ");
    Serial.println(adata);
    delay (1);
     }
timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
 // Serial.print("Formatted Time: ");
  //Serial.println(formattedTime);  

   int currentHour = timeClient.getHours(); // Pass time (h)
   int currentMinute = timeClient.getMinutes(); // Pass time (m)


 if(WiFi.status()== WL_CONNECTED){
    digitalWrite (5,HIGH);
    
        }
   else {
    
        digitalWrite (5,LOW);
    }    

 // set time to send data to the data base 
  
// if (currentHour == 1,3,5,7,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 && currentMinute == 30,32,34,36,38,40,42 ) {

  if((millis() - oldTime) > 5000) {
    
    Serial.println ("Sending data to Database");

//Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

      // url path
   http.begin(client, serverName);
    
    
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    //  HTTP POST request 
    String httpRequestData = "api_key=" + apiKeyValue + "&nicnumber=" + NIC + "&metervalue=" + adata + "";

    //String httpRequestData = "api_key=" + apiKeyValue + "&nicnumber=" + NIC
                          + "&metervalue=" + METER_VALUE + "";
                         
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
   
    int httpResponseCode = http.POST(httpRequestData);
     
            
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 12 seconds

    delay(10);  
oldTime = millis();

}

delay(10);
}
