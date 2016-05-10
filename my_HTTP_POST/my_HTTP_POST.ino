#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid     = "hackerspace.sg";
const char* password = "0xta1l50up";






void setup() {
   WiFi.begin(ssid, password);
   Serial.begin(115200);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;
  http.begin("http://192.168.6.243/posts");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("title=foo&body=bar&userId=1");
  http.writeToStream(&Serial);
  http.end();
 delay(10000);
}
