#include <WiFi.h>
#include <time.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

/* ===== CONFIG ===== */

#define WIFI_SSID "Weiye"
#define WIFI_PASS "11112222"

#define LOAD_PIN 5

const char* AWS_ENDPOINT = "a27vwl8grwujoi-ats.iot.us-east-2.amazonaws.com";
const char* CLIENT_ID    = "ESP32_Device_01";

const char* TOPIC_CMD    = "esp32/ESP32_Device_01/cmd";
const char* TOPIC_SCHED  = "esp32/ESP32_Device_01/schedule";
const char* TOPIC_PUB    = "esp32/ESP32_Device_01/tele";

const char* TZ = "EST5EDT,M3.2.0/2,M11.1.0/2";

/* ===== CERTS ===== */

extern const char AWS_CERT_CA[] PROGMEM;
extern const char AWS_CERT_CRT[] PROGMEM;
extern const char AWS_CERT_PRIVATE[] PROGMEM;

/* ===== OBJECTS ===== */

WiFiClientSecure net;
PubSubClient mqtt(net);

/* ===== SCHEDULE STATE ===== */

int schedOnHour  = 20;
int schedOffHour = 23;

/* ===== WIFI + TIME ===== */

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) delay(250);
}

void syncTime() {
  setenv("TZ", TZ, 1);
  tzset();
  configTzTime(TZ, "pool.ntp.org");

  // TLS requires valid time
  while (time(nullptr) < 1700000000UL) delay(200);
}

/* ===== MQTT CALLBACK ===== */

void onMessage(char* topic, byte* payload, unsigned int len) {

  char msg[128];
  memcpy(msg, payload, len);
  msg[len] = '\0';

  /* --- Manual ON/OFF Command --- */
  if (strcmp(topic, TOPIC_CMD) == 0) {

    if ((msg[0] | 32) == 'o') {      // handles ON / OFF case-insensitive
      if ((msg[1] | 32) == 'n') {
        digitalWrite(LOAD_PIN, HIGH);
        mqtt.publish(TOPIC_PUB, "LOAD=ON");
      }
      if ((msg[1] | 32) == 'f') {
        digitalWrite(LOAD_PIN, LOW);
        mqtt.publish(TOPIC_PUB, "LOAD=OFF");
      }
    }
  }

  /* --- Cloud Schedule Update --- */
  if (strcmp(topic, TOPIC_SCHED) == 0) {

    // expects: {"on_hour":20,"off_hour":23}
    sscanf(msg, "{\"on_hour\":%d,\"off_hour\":%d}",
           &schedOnHour, &schedOffHour);

    mqtt.publish(TOPIC_PUB, "Schedule Updated");
  }
}

/* ===== AWS CONNECT ===== */

void connectAWS() {

  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  mqtt.setServer(AWS_ENDPOINT, 8883);
  mqtt.setCallback(onMessage);

  while (!mqtt.connected()) {
    mqtt.connect(CLIENT_ID);
    delay(500);
  }

  mqtt.subscribe(TOPIC_CMD);
  mqtt.subscribe(TOPIC_SCHED);

  mqtt.publish(TOPIC_PUB, "boot");
}

/* ===== SCHEDULER ===== */

void checkSchedule() {

  time_t now = time(nullptr);
  struct tm* t = localtime(&now);

  int hour = t->tm_hour;

  // If schedule wraps past midnight (e.g., 22 → 3)
  if (schedOnHour < schedOffHour) {
    digitalWrite(LOAD_PIN,
      (hour >= schedOnHour && hour < schedOffHour) ? HIGH : LOW);
  } else {
    digitalWrite(LOAD_PIN,
      (hour >= schedOnHour || hour < schedOffHour) ? HIGH : LOW);
  }
}

/* ===== SETUP ===== */

void setup() {

  pinMode(LOAD_PIN, OUTPUT);
  digitalWrite(LOAD_PIN, LOW);

  Serial.begin(115200);

  connectWiFi();
  syncTime();
  connectAWS();
}

/* ===== LOOP ===== */

void loop() {

  if (WiFi.status() != WL_CONNECTED) return;
  if (!mqtt.connected()) connectAWS();

  mqtt.loop();

  checkSchedule();   // continuously enforce schedule
}
