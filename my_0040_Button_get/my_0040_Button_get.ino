#include <ESPert.h>

ESPert espert;
bool currentSwitch = true;

const char *host = "192.168.6.243";
const int httpPort = 8086;
const String path = "/classStuff?ID=";

void initWifi() {
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
}

void setup() {
  espert.init();
  espert.oled.init();
  espert.button.init(5);
  initWifi();
  espert.println("Press USER button to turn on LED.");
}

void loop() {
  bool buttonPressed = espert.button.isOn();
  String newPath = path+ espert.info.getId()+ "&Value=";
  if (buttonPressed != currentSwitch) {
    if (buttonPressed) {
      espert.println("Button: On");
      newPath = newPath + "on";
      espert.led.on();
    } else {
      espert.println("Button: Off");
      newPath = newPath + "off";
      espert.led.off();
    }
     espert.wifi.getHTTP(host, newPath.c_str());

    currentSwitch = buttonPressed;
  }
}
