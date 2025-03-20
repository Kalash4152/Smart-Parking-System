#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// LCD settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your LCD's I2C address if needed

// Define pins
const int ldrPin = A0; // Analog pin for LDR
const int redLEDPin = 9; // Digital pin for red LED

// Light intensity threshold
const int lightThreshold = 200; // Adjust this value based on your setup

void setup() {
  Serial.begin(115200);
  
  // Initialize OLED display
  display.begin(SSD1306_I2C_ADDRESS, 0x3C); // Change address if needed
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  
  // Initialize red LED pin
  pinMode(redLEDPin, OUTPUT);
  digitalWrite(redLEDPin, HIGH); // Turn on the red LED
}

void loop() {
  // Display directions on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Directions:");
  display.setCursor(0, 10);
  display.print("1. Go Straight");
  display.setCursor(0, 20);
  display.print("2. Turn Left");
  display.setCursor(0, 30);
  display.print("3. Turn Right");
  display.display();
  
  // Read the light intensity from the LDR
  int lightIntensity = analogRead(ldrPin);
  
  // Check if the light intensity is below the threshold
  if (lightIntensity < lightThreshold) {
    lcd.clear();
    lcd.print("Car is Parked");
  } else {
    lcd.clear();
    lcd.print("No Car Detected");
  }

  delay(500); // Small delay for stability
}