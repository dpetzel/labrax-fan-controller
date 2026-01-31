#include <DHT.h> // Requires installation of "DHT sensor library by Adafruit"

// PWM settings
const int PWM_FREQ = 25000;    // 25 kHz frequency for computer fans
const int PWM_RESOLUTION = 8;  // 8-bit resolution (0-255)

// Pin definitions
#define PWM_PIN 14 // Attached to the Fan's PWM terminal for speed control
#define DHT22_PIN 13 // Attached to the DT22 Sensor's Data Pin
#define ONBOARD_LED_PIN 2 // The onboard LED is tied to GPIO2

#define LOOP_DELAY_MS 2000 // How long to wait between each polling loop
#define LED_PERIOD_MS 50 // How long should the onboard LED remain on each polling loop

// When the temperature is below this value
// the fan will be turned off
const float TEMP_LOW_THRESHOLD_CELSIUS = 35;

// Kick the fan to 100% over this threshold
const float TEMP_HIGH_THRESHOLD_CELSIUS = 50;

DHT dht22(DHT22_PIN, DHT22);

void setFanSpeed(int percent) {
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;

  int maxDuty = (1 << PWM_RESOLUTION) - 1;
  int duty = (percent * maxDuty) / 100;

  ledcWrite(PWM_PIN, duty);
}

void setup() {
  Serial.begin(115200);
  dht22.begin();

  // pinMode(TACH_PIN, INPUT_PULLUP);
  pinMode(ONBOARD_LED_PIN, OUTPUT);

  // Configure PWM
  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);
  setFanSpeed(0);

  delay(1000);
  Serial.println("System ready!"); 
}

void loop() {
  // Flip the LED on to indicate we are doing some work.
  digitalWrite(ONBOARD_LED_PIN, HIGH);  // LED ON

  float humi  = dht22.readHumidity();
  float tempC = dht22.readTemperature();
  float tempF = dht22.readTemperature(true);

  if (tempC <= TEMP_LOW_THRESHOLD_CELSIUS) {
    Serial.println("Turning off Fan");
    setFanSpeed(0);
  } else if (tempC >= TEMP_HIGH_THRESHOLD_CELSIUS) {
    Serial.println("Setting fan to max!");
    setFanSpeed(100);
  } else {
    Serial.println("Turning on Fan");
    setFanSpeed(25);
  }

  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.print("%");

  Serial.print("  |  ");

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print("°C  ~  ");
  Serial.print(tempF);
  Serial.println("°F");

  delay(LED_PERIOD_MS);
  // Turn off the onboard LED
  digitalWrite(ONBOARD_LED_PIN, LOW);
  delay(LOOP_DELAY_MS);
}
