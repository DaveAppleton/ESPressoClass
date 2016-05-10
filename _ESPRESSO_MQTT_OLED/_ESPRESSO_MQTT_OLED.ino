#include <ESPert.h>

ESPert espert;

const char* mqtt_server = "mqtt.espert.io";

String inTopic = "ESPert/" + String(espert.info.getChipId()) + "/OLED";

void callback(char* topic, byte* payload, unsigned int length) {
  String strPayload = String((char*)payload).substring(0, length);
  espert.println("Receive: " + strPayload);

  if (espert.json.init(strPayload)) {
    if (espert.json.containsKey("message")) {
      espert.oled.println(espert.json.get("message"));
      espert.oled.update();
    }
    if (espert.json.containsKey("clear")) {
      espert.oled.clear();
      espert.oled.update();
    }
  }
}

void setup() {
  espert.init();
  espert.mqtt.init(mqtt_server, 1883, callback);

  espert.oled.init();
  delay(2000);

  espert.println("Press USER button to turn on LED.");

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
  }
}

void loop() {
  if (espert.mqtt.connect()) {
    espert.println("MQTT: Connected");
    espert.mqtt.subscribe(inTopic);
    Serial.println("MQTT: Subscribed " + inTopic);
  }

}
