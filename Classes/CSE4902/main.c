#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <time.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <strings.h>
#include "certs.h"

#define LOAD_PIN 5
#define STATUS_LED 2

#define ADC_PIN_VOLT 34
#define ADC_PIN_CURR 35

const char* AP_SSID = "LightController_Setup";
const char* AP_PASS = "setup1234";

const char* AWS_ENDPOINT = "a27vwl8grwujoi-ats.iot.us-east-2.amazonaws.com";
const char* CLIENT_ID    = "ESP32_Device_01";

const char* TOPIC_CMD    = "esp32/ESP32_Device_01/cmd";
const char* TOPIC_SCHED  = "esp32/ESP32_Device_01/schedule";
const char* TOPIC_PUB    = "esp32/ESP32_Device_01/tele";
const char* TOPIC_STATUS = "esp32/ESP32_Device_01/status";

const char* TZ_STRING = "EST5EDT,M3.2.0/2,M11.1.0/2";

const unsigned long WIFI_CONNECT_TIMEOUT_MS = 15000;
const unsigned long TELE_INTERVAL_MS = 5000;

const int ADC_SAMPLES = 100;
const float ADC_REF_V = 3.3f;
const float ADC_MAX   = 4095.0f;

const float VOLTAGE_SCALE  = 100.0f;
const float CURRENT_SCALE  = 10.0f;
const float VOLTAGE_OFFSET = 0.0f;
const float CURRENT_OFFSET = 0.0f;

extern const char AWS_CERT_CA[] PROGMEM;
extern const char AWS_CERT_CRT[] PROGMEM;
extern const char AWS_CERT_PRIVATE[] PROGMEM;

enum DeviceState {
  PROVISIONING,
  NORMAL_OPERATION
};

DeviceState deviceState = PROVISIONING;

WiFiClientSecure net;
PubSubClient mqtt(net);
WebServer server(80);
Preferences prefs;

String wifiSSID = "";
String wifiPASS = "";

int schedOnHour  = 20;
int schedOffHour = 23;

bool manualOverride = false;
bool manualState = false;

unsigned long lastTeleMs = 0;
unsigned long lastLedMs = 0;
bool ledState = false;

bool loadWiFiCreds();
void saveWiFiCreds(const String& ssid, const String& pass);
void clearWiFiCreds();
String htmlPage();
void startProvisioningMode();
bool connectWiFi();
void syncTime();
void publishStatus(const char* statusMsg);
void connectAWS();
void onMessage(char* topic, byte* payload, unsigned int len);
float readAverageVoltageADC();
float readAverageCurrentADC();
float readVoltage();
float readCurrent();
void checkSchedule();
void publishTelemetry();
void updateStatusLed();

bool loadWiFiCreds() {
  prefs.begin("wifi", true);
  wifiSSID = prefs.getString("ssid", "");
  wifiPASS = prefs.getString("pass", "");
  prefs.end();
  return wifiSSID.length() > 0;
}

void saveWiFiCreds(const String& ssid, const String& pass) {
  prefs.begin("wifi", false);
  prefs.putString("ssid", ssid);
  prefs.putString("pass", pass);
  prefs.end();
}

void clearWiFiCreds() {
  prefs.begin("wifi", false);
  prefs.clear();
  prefs.end();
}

String htmlPage() {
  String page;
  page += "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<title>WiFi Setup</title></head><body>";
  page += "<h2>ESP32 Lighting Controller Setup</h2>";
  page += "<p>Connect this device to local WiFi.</p>";
  page += "<form action='/save' method='POST'>";
  page += "SSID:<br><input name='ssid'><br><br>";
  page += "Password:<br><input name='pass' type='password'><br><br>";
  page += "<input type='submit' value='Save'>";
  page += "</form>";
  page += "<br><form action='/clear' method='POST'><input type='submit' value='Clear Saved WiFi'></form>";
  page += "</body></html>";
  return page;
}

void startProvisioningMode() {
  deviceState = PROVISIONING;

  mqtt.disconnect();
  WiFi.disconnect(true, true);
  delay(500);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);

  server.stop();

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlPage());
  });

  server.on("/save", HTTP_POST, []() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    if (ssid.length() == 0) {
      server.send(400, "text/html", "<html><body><h3>SSID cannot be empty.</h3><a href='/'>Back</a></body></html>");
      return;
    }

    saveWiFiCreds(ssid, pass);
    server.send(200, "text/html", "<html><body><h3>Saved. Rebooting...</h3></body></html>");
    delay(1500);
    ESP.restart();
  });

  server.on("/clear", HTTP_POST, []() {
    clearWiFiCreds();
    server.send(200, "text/html", "<html><body><h3>Saved WiFi cleared. Rebooting...</h3></body></html>");
    delay(1500);
    ESP.restart();
  });

  server.begin();
}

bool connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSSID.c_str(), wifiPASS.c_str());

  Serial.print("Connecting to WiFi");

  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - start < WIFI_CONNECT_TIMEOUT_MS) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected, IP: ");
    Serial.println(WiFi.localIP());
    return true;
  }

  Serial.println("WiFi connection FAILED");
  return false;
}

void syncTime() {
  setenv("TZ", TZ_STRING, 1);
  tzset();
  configTzTime(TZ_STRING, "pool.ntp.org", "time.nist.gov", "time.google.com");

  while (time(nullptr) < 1700000000UL) {
    delay(200);
  }
}

void publishStatus(const char* statusMsg) {
  if (!mqtt.connected()) return;

  char msg[256];
  String ip = WiFi.isConnected() ? WiFi.localIP().toString() : "0.0.0.0";

  snprintf(
    msg,
    sizeof(msg),
    "{\"device\":\"%s\",\"status\":\"%s\",\"ip\":\"%s\",\"uptime\":%lu}",
    CLIENT_ID,
    statusMsg,
    ip.c_str(),
    millis() / 1000UL
  );

  mqtt.publish(TOPIC_STATUS, msg);
}

void onMessage(char* topic, byte* payload, unsigned int len) {
  char msg[256];
  if (len >= sizeof(msg)) len = sizeof(msg) - 1;
  memcpy(msg, payload, len);
  msg[len] = '\0';

  if (strcmp(topic, TOPIC_CMD) == 0) {
    if (strcasecmp(msg, "ON") == 0) {
      manualOverride = true;
      manualState = true;
      digitalWrite(LOAD_PIN, HIGH);
      publishStatus("manual_on");
    } else if (strcasecmp(msg, "OFF") == 0) {
      manualOverride = true;
      manualState = false;
      digitalWrite(LOAD_PIN, LOW);
      publishStatus("manual_off");
    } else if (strcasecmp(msg, "AUTO") == 0) {
      manualOverride = false;
      publishStatus("auto_mode");
    }
  }

  if (strcmp(topic, TOPIC_SCHED) == 0) {
    int onH, offH;
    if (sscanf(msg, "{\"on_hour\":%d,\"off_hour\":%d}", &onH, &offH) == 2) {
      if (onH >= 0 && onH <= 23 && offH >= 0 && offH <= 23) {
        schedOnHour = onH;
        schedOffHour = offH;
        publishStatus("schedule_updated");
      }
    }
  }
}

void connectAWS() {

  IPAddress ip;
  if (WiFi.hostByName(AWS_ENDPOINT, ip)) {
    Serial.print("AWS IP: ");
    Serial.println(ip);
  } else {
    Serial.println("DNS lookup failed");
  }

  Serial.print("Current epoch: ");
  Serial.println(time(nullptr));

  // net.setInsecure();
   
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  


  mqtt.setServer(AWS_ENDPOINT, 8883);
  mqtt.setCallback(onMessage);

  while (!mqtt.connected()) {
    Serial.println("Connecting to AWS...");

    if (mqtt.connect(CLIENT_ID)) {
      Serial.println("AWS Connected!");
    } else {
      Serial.print("MQTT failed, rc=");
      Serial.println(mqtt.state());
    }

    delay(2000);
  }

  mqtt.subscribe(TOPIC_CMD);
  mqtt.subscribe(TOPIC_SCHED);

  publishStatus("boot");
  publishStatus("online");
}

float readAverageVoltageADC() {
  long sum = 0;
  for (int i = 0; i < ADC_SAMPLES; i++) {
    sum += analogRead(ADC_PIN_VOLT);
    delayMicroseconds(200);
  }
  float avg = sum / (float)ADC_SAMPLES;
  return avg * ADC_REF_V / ADC_MAX;
}

float readAverageCurrentADC() {
  long sum = 0;
  for (int i = 0; i < ADC_SAMPLES; i++) {
    sum += analogRead(ADC_PIN_CURR);
    delayMicroseconds(200);
  }
  float avg = sum / (float)ADC_SAMPLES;
  return avg * ADC_REF_V / ADC_MAX;
}

float readVoltage() {
  float adcVolts = readAverageVoltageADC();
  float voltage = adcVolts * VOLTAGE_SCALE + VOLTAGE_OFFSET;
  if (voltage < 0) voltage = 0;
  return voltage;
}

float readCurrent() {
  float adcVolts = readAverageCurrentADC();
  float current = adcVolts * CURRENT_SCALE + CURRENT_OFFSET;
  if (current < 0) current = 0;
  return current;
}

void checkSchedule() {
  if (manualOverride) {
    digitalWrite(LOAD_PIN, manualState ? HIGH : LOW);
    return;
  }

  time_t now = time(nullptr);
  struct tm* t = localtime(&now);
  int hour = t->tm_hour;

  bool shouldBeOn;
  if (schedOnHour < schedOffHour) {
    shouldBeOn = (hour >= schedOnHour && hour < schedOffHour);
  } else {
    shouldBeOn = (hour >= schedOnHour || hour < schedOffHour);
  }

  digitalWrite(LOAD_PIN, shouldBeOn ? HIGH : LOW);
}

void publishTelemetry() {
  if (!mqtt.connected()) return;
  if (millis() - lastTeleMs < TELE_INTERVAL_MS) return;

  lastTeleMs = millis();

  float voltage = readVoltage();
  float current = readCurrent();
  float power = voltage * current;
  int loadState = digitalRead(LOAD_PIN);

  char msg[256];
  snprintf(
    msg,
    sizeof(msg),
    "{\"device\":\"%s\",\"uptime\":%lu,\"voltage\":%.2f,\"current\":%.2f,\"power\":%.2f,\"load\":%d,\"mode\":\"%s\",\"on_hour\":%d,\"off_hour\":%d}",
    CLIENT_ID,
    millis() / 1000UL,
    voltage,
    current,
    power,
    loadState,
    manualOverride ? "manual" : "auto",
    schedOnHour,
    schedOffHour
  );

  mqtt.publish(TOPIC_PUB, msg);
}

void updateStatusLed() {
  unsigned long interval = (deviceState == PROVISIONING) ? 200 : 1000;

  if (millis() - lastLedMs >= interval) {
    lastLedMs = millis();
    ledState = !ledState;
    digitalWrite(STATUS_LED, ledState ? HIGH : LOW);
  }
}

void setup() {
  pinMode(LOAD_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  digitalWrite(LOAD_PIN, LOW);
  digitalWrite(STATUS_LED, LOW);

  Serial.begin(115200);
  analogReadResolution(12);

  if (!loadWiFiCreds()) {
    startProvisioningMode();
    return;
  }

  if (!connectWiFi()) {
    clearWiFiCreds();
    startProvisioningMode();
    return;
  }

  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());
  deviceState = NORMAL_OPERATION;
  syncTime();
  connectAWS();
}

void loop() {
  updateStatusLed();

  if (deviceState == PROVISIONING) {
    server.handleClient();
    delay(10);
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    if (!connectWiFi()) {
      clearWiFiCreds();
      startProvisioningMode();
      return;
    }
    syncTime();
  }

  if (!mqtt.connected()) {
    connectAWS();
  }

  mqtt.loop();
  checkSchedule();
  publishTelemetry();
}