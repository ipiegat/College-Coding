// Wi-Fi support for ESP32
#include <WiFi.h>

// Time functions (NTP, timestamps) — required for TLS
#include <time.h>

// TLS-enabled TCP client
#include <WiFiClientSecure.h>

// MQTT client library
#include <PubSubClient.h>

/* ===================== CONFIG ===================== */

// Wi-Fi network name
#define WIFI_SSID "Weiye"

// Wi-Fi password
#define WIFI_PASS "11112222"

// GPIO pin for onboard LED
#define LED_PIN 2

// AWS IoT Core endpoint (unique per account/region)
const char* AWS_ENDPOINT = "a27vwl8grwujoi-ats.iot.us-east-2.amazonaws.com";

// MQTT client identifier (must be unique per device)
const char* CLIENT_ID   = "ESP32_Device_01";

// MQTT topic for telemetry publishes
const char* TOPIC_PUB   = "esp32/ESP32_Device_01/tele";

// MQTT topic for receiving commands
const char* TOPIC_SUB   = "esp32/ESP32_Device_01/cmd";

// Timezone string (Eastern Time with daylight savings)
const char* TZ = "EST5EDT,M3.2.0/2,M11.1.0/2";

// ADC pin for voltage measurement
#define ADC_VOLT 34

// ADC pin for current measurement
#define ADC_CURR 35

// ESP32 ADC reference voltage
const float ADC_REF_V = 3.3;

// Max ADC value for 12-bit resolution
const int   ADC_MAX  = 4095;

// Voltage divider ratio (scales ADC voltage to real voltage)
const float VOLT_DIV = 11.0;

// Current sensor sensitivity (mV per amp)
const float CURR_MV_PER_A = 100.0;

/* ===================== CERTIFICATES ===================== */

// Root CA certificate (verifies AWS server identity)
extern const char AWS_CERT_CA[] PROGMEM;

// Device certificate (verifies ESP32 to AWS)
extern const char AWS_CERT_CRT[] PROGMEM;

// Device private key (proves ownership of certificate)
extern const char AWS_CERT_PRIVATE[] PROGMEM;

/* ===================== OBJECTS ===================== */

// Secure TLS socket
WiFiClientSecure net;

// MQTT client running over the secure socket
PubSubClient mqtt(net);

/* ===================== HELPERS ===================== */

// Synchronize system time using NTP
// TLS requires correct system time to validate certificates
void syncTime() {
  // Set local timezone
  setenv("TZ", TZ, 1);
  tzset();

  // Start NTP time synchronization
  configTzTime(TZ, "pool.ntp.org");

  // Block until time is valid (after ~2023)
  while (time(nullptr) < 1700000000UL) {
    delay(200);
  }
}

// Connect to Wi-Fi (blocking until successful)
void connectWiFi() {
  // Set ESP32 to station mode
  WiFi.mode(WIFI_STA);

  // Start Wi-Fi connection
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
}

// Callback triggered when MQTT message is received
void onMessage(char* topic, byte* payload, unsigned int len) {

  // Ignore messages not on the command topic
  if (strcmp(topic, TOPIC_SUB) != 0 || len < 2) return;

  // Convert first character to lowercase and check for 'o'
  if ((payload[0] | 32) == 'o') {

    // Check second character: 'n' or 'f'
    if ((payload[1] | 32) == 'n') {
      // Turn LED ON
      digitalWrite(LED_PIN, HIGH);

      // Send confirmation back to AWS
      mqtt.publish(TOPIC_PUB, "LED=ON");
    }

    if ((payload[1] | 32) == 'f') {
      // Turn LED OFF
      digitalWrite(LED_PIN, LOW);

      // Send confirmation back to AWS
      mqtt.publish(TOPIC_PUB, "LED=OFF");
    }
  }
}

// Establish secure MQTT connection to AWS IoT Core
void connectAWS() {

  // Load TLS certificates into secure client
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Set MQTT server address and TLS port
  mqtt.setServer(AWS_ENDPOINT, 8883);

  // Register callback for incoming messages
  mqtt.setCallback(onMessage);

  // Retry connection until successful
  while (!mqtt.connected()) {
    mqtt.connect(CLIENT_ID);
    delay(500);
  }

  // Subscribe to command topic
  mqtt.subscribe(TOPIC_SUB);

  // Publish boot message
  mqtt.publish(TOPIC_PUB, "boot");
}

/* ===================== ADC ===================== */

// Read and convert voltage measurement
float readVoltage() {

  // Read raw ADC value
  float raw = analogRead(ADC_VOLT);

  // Convert ADC count to voltage
  float v = (raw / ADC_MAX) * ADC_REF_V;

  // Scale by voltage divider ratio
  return v * VOLT_DIV;
}

// Read and convert current measurement
float readCurrent() {

  // Read raw ADC value
  float raw = analogRead(ADC_CURR);

  // Convert ADC count to voltage
  float v = (raw / ADC_MAX) * ADC_REF_V;

  // Remove mid-supply offset and convert to millivolts
  float mv = (v - ADC_REF_V / 2.0) * 1000.0;

  // Convert mV to amps
  return mv / CURR_MV_PER_A;
}

/* ===================== SETUP ===================== */

void setup() {

  // Configure LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Turn LED off initially
  digitalWrite(LED_PIN, LOW);

  // Initialize serial output for debugging
  Serial.begin(115200);

  // Configure ADC resolution to 12 bits
  analogReadResolution(12);

  // Set ADC attenuation for higher voltage range
  analogSetAttenuation(ADC_11db);

  // Connect to Wi-Fi
  connectWiFi();

  // Synchronize system time
  syncTime();

  // Connect to AWS IoT Core
  connectAWS();
}

/* ===================== LOOP ===================== */

// Timestamp of last telemetry publish
unsigned long lastTele = 0;

void loop() {

  // If Wi-Fi is lost, do nothing
  if (WiFi.status() != WL_CONNECTED) return;

  // If MQTT disconnected, reconnect
  if (!mqtt.connected()) connectAWS();

  // Process incoming/outgoing MQTT traffic
  mqtt.loop();

  // Publish telemetry every 5 seconds
  if (millis() - lastTele >= 5000) {
    lastTele = millis();

    // Read voltage and current
    float V = readVoltage();
    float I = readCurrent();

    // Compute power
    float P = V * I;

    // Create JSON telemetry payload
    char msg[128];
    snprintf(msg, sizeof(msg),
      "{\"uptime\":%lu,\"V\":%.2f,\"I\":%.3f,\"P\":%.2f}",
      millis() / 1000, V, I, P);

    // Publish telemetry to AWS IoT
    mqtt.publish(TOPIC_PUB, msg);
  }
}
