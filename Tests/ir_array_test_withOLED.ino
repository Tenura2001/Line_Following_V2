#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// IR sensor pins
const int irPins[7] = {13, 14, 27, 26, 25, 33, 32};
int irValues[7];

void setup() {
  Serial.begin(115200);

  // IR sensor setup
  for (int i = 0; i < 7; i++) {
    pinMode(irPins[i], INPUT);
  }

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED not found"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  display.clearDisplay();

  // Read all 7 IR sensors
  for (int i = 0; i < 7; i++) {
    irValues[i] = analogRead(irPins[i]);
  }

  // Display on OLED
  for (int i = 0; i < 7; i++) {
    display.setCursor(0, i * 8);
    display.print("IR");
    display.print(i + 1);
    display.print(": ");
    display.println(irValues[i]);
  }

  display.display();
  delay(200);
}
