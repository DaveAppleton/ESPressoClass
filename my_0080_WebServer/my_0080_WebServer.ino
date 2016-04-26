#include <ESPert.h>

ESPert espert;
ESP8266WebServer *server = NULL;

void init_server() {
  server = new ESP8266WebServer(80);

  server->on("/", []() {
    String html = "Failed to read temperature and humidity from DHT sensor!";
    bool isFarenheit = false;
    float t = espert.dht.getTemperature(isFarenheit);
    float h = espert.dht.getHumidity();

    if (!isnan(t) && !isnan(h)) {
      html = "Temperature: " + String((int)t) + (isFarenheit ? "°F" : "°C") + "<br>Humidity: " + String((int)h) + "%";
    } else if (espert.button.isOn()) {
      html += " but the button is pressed :-)";
    }

    server->send(200, "text/html", html);
  });

  server->on("/led", []() {
   String state=server->arg("state");
    if (state == "on") espert.led.on();
    else if (state == "off") espert.led.off();
    server->send(200, "text/plain", "Led is now " + state);
  } );

  server->begin();
}

void setup() {
  espert.init();
  espert.dht.init();

  espert.oled.init();
  delay(2000);

  espert.oled.clear();
  espert.oled.println(espert.info.getId());
  espert.oled.println();

  int mode = espert.wifi.init();

  if (mode == ESPERT_WIFI_MODE_CONNECT) {
    espert.oled.print("IP..: ");
    espert.oled.println(espert.wifi.getLocalIP());
    espert.oled.println("");
    init_server();
  } else if (mode == ESPERT_WIFI_MODE_DISCONNECT) {
    espert.oled.println("WiFi: not connected.");
  }
}

void loop() {
  espert.loop();

  if (server) {
    server->handleClient();
  }
}
