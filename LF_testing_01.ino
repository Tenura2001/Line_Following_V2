#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// IR sensor pins
const int irPins[7] = {13, 14, 27, 26, 25, 33, 32};
int irValues[7];

// Buzzer
const int BUZZER_PIN = 2;

// Buttons
const int BTN_INC = 34;
const int BTN_DEC = 39;
const int BTN_RESET = 36;

// Speed variable
int speedValue = 0;
const int speedStep = 10;
const int speedMax = 100;
const int speedMin = 0;

void setup() {
  Serial.begin(115200);

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Set IR pins
  for (int i = 0; i < 7; i++) {
    pinMode(irPins[i], INPUT);
  }

  // Buttons with pull-up
  pinMode(BTN_INC, INPUT_PULLUP);
  pinMode(BTN_DEC, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

void loop() {
  // Read IR sensors
  for (int i = 0; i < 7; i++) {
    irValues[i] = analogRead(irPins[i]);
  }

  // Button control
  if (digitalRead(BTN_INC) == LOW) {
    speedValue = min(speedMax, speedValue + speedStep);
    tone(BUZZER_PIN, 1000, 100);
    delay(200);
  }

  if (digitalRead(BTN_DEC) == LOW) {
    speedValue = max(speedMin, speedValue - speedStep);
    tone(BUZZER_PIN, 500, 100);
    delay(200);
  }

  if (digitalRead(BTN_RESET) == LOW) {
    speedValue = 0;
    tone(BUZZER_PIN, 800, 100);
    delay(200);
  }

  // Display IR values
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("IR: ");
  for (int i = 0; i < 7; i++) {
    display.print(irValues[i]);
    display.print(" ");
  }

  display.setCursor(0, 50);
  display.print("Speed: ");
  display.print(speedValue);

  display.display();
  delay(100);
}
