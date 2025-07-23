#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// MPU6050 sensor
Adafruit_MPU6050 mpu;

// Pin definitions
#define BUTTON1 34
#define BUTTON2 39
#define BUTTON3 36
#define BUZZER_PIN 2

// Tone frequencies (in Hz)
#define TONE1 500
#define TONE2 1000
#define TONE3 1500

void setup() {
  Serial.begin(115200);

  // Button input with pull-up
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);

  // Buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // MPU6050 setup
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (true);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(1000);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Accel X: "); display.println(a.acceleration.x);
  display.print("Accel Y: "); display.println(a.acceleration.y);
  display.print("Accel Z: "); display.println(a.acceleration.z);
  display.display();

  // Button actions with different tones
  if (digitalRead(BUTTON1) == LOW) {
    tone(BUZZER_PIN, TONE1);
    delay(200);
    noTone(BUZZER_PIN);
  }

  if (digitalRead(BUTTON2) == LOW) {
    tone(BUZZER_PIN, TONE2);
    delay(200);
    noTone(BUZZER_PIN);
  }

  if (digitalRead(BUTTON3) == LOW) {
    tone(BUZZER_PIN, TONE3);
    delay(200);
    noTone(BUZZER_PIN);
  }

  delay(100);
}
