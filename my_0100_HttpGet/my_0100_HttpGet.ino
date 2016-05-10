#include <ESPert.h>

ESPert espert;

const char *host = "eth.nanopool.org";
const int httpPort = 80;
const char *path = "/api/balance/0x8f79f76381aad7b98c19af55ee75fdfeeb012211";

void setup() {
  espert.init();
  espert.oled.init();
  delay(2000);

  espert.oled.clear();
  espert.oled.println(espert.info.getId());
  espert.oled.println();

  int mode = espert.wifi.init();

  if (mode == ESPERT_WIFI_MODE_CONNECT) {
    espert.println(">>> WiFi mode: connected.");
    espert.oled.println("WiFi: connected.");
    espert.oled.print("IP..: ");
    espert.oled.println(espert.wifi.getLocalIP());
  } else if (mode == ESPERT_WIFI_MODE_DISCONNECT) {
    espert.println(">>> WiFi mode: disconnected.");
    espert.oled.println("WiFi: not connected.");
  } else if (mode == ESPERT_WIFI_MODE_SMARTCONFIG) {
    espert.println(">>> WiFi mode: smart config.");
  } else if (mode == ESPERT_WIFI_MODE_SETTINGAP) {
    espert.println(">>> WiFi mode: access point.");
  }
  delay(2000);
}

void loop() {
  espert.loop();
  
  String str = espert.wifi.getHTTP(host, path);
  //espert.println(str);
  if (espert.json.init(str)) {
    if (espert.json.containsKey("data")) {
      espert.oled.clear();
      espert.oled.println( espert.json.get("data"));
      espert.oled.update();
      espert.println("OK");
      espert.println(espert.json.get("data"));
    } else {
      espert.println("data not found");
    }
  } else {
    espert.println("json init fail");
  }
  delay(5000);
}
