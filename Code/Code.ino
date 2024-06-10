#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
const char* ssid = "Test";
const char* password = "teststte";

// OpenWeatherMap API
const char* apiKey = "teststestset";
const char* cityID = "2775220";
String weatherURL = "http://api.openweathermap.org/data/2.5/weather?id=" + String(cityID) + "&appid=" + String(apiKey) + "&units=metric";

// Pin definitions
#define DHTPIN 4
#define LED_PIN 18
#define BUTTON1_PIN 14
#define BUTTON2_PIN 27

// DHT22 sensor
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LED strip
#define NUM_LEDS 30
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables to store weather data
float apiTemp = 0.0;
float apiHumidity = 0.0;
String apiWeather = "N/A";

// Variable to keep track of which data to display
bool showAPIData = true;
uint8_t brightness = 128; // Initial brightness

// Last button states
bool lastButton1State = HIGH;
bool lastButton2State = HIGH;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Initialize LED strip
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Initialize buttons
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Fetch initial weather data
  fetchWeatherData();
  displayWeatherData();
}

void loop() {
  // Read button states
  bool button1State = digitalRead(BUTTON1_PIN);
  bool button2State = digitalRead(BUTTON2_PIN);

  // Check if Button 1 is pressed to toggle data display
  if (button1State == LOW && lastButton1State == HIGH) {
    showAPIData = !showAPIData;
    Serial.println("Button 1 pressed, toggling data display");

    // Update the display
    if (showAPIData) {
      displayWeatherData();
    } else {
      displayLocalData();
    }

    // Debounce delay
    delay(200);
  }

  // Check if Button 2 is pressed to change brightness
  if (button2State == LOW && lastButton2State == HIGH) {
    // Cycle through brightness levels: 64, 128, 192, 255
    if (brightness == 64) {
      brightness = 128;
    } else if (brightness == 128) {
      brightness = 192;
    } else if (brightness == 192) {
      brightness = 255;
    } else {
      brightness = 64;
    }

    strip.setBrightness(brightness);
    strip.show();

    Serial.println("Button 2 pressed, changing brightness to " + String(brightness));

    // Debounce delay
    delay(200);
  }

  // Update the last button states
  lastButton1State = button1State;
  lastButton2State = button2State;

  // Periodically update weather data
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 60000) { // Update every 60 seconds
    fetchWeatherData();
    lastUpdate = millis();
    if (showAPIData) {
      displayWeatherData();
    }
  }
}

void fetchWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(weatherURL);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      StaticJsonDocument<1024> doc;
      deserializeJson(doc, payload);

      apiTemp = doc["main"]["temp"].as<float>();
      apiHumidity = doc["main"]["humidity"].as<float>();
      apiWeather = String(doc["weather"][0]["description"].as<const char*>());

    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void displayWeatherData() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("W: " + apiWeather);
  lcd.setCursor(0, 1);
  lcd.print("Temp: " + String(apiTemp) + "C");
}

void displayLocalData() {
  float localTemp = dht.readTemperature();
  float localHumidity = dht.readHumidity();

  if (isnan(localTemp) || isnan(localHumidity)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Local Temp: " + String(localTemp) + "C");
  lcd.setCursor(0, 1);
  setLEDColor(localTemp);
  lcd.print("Humidity: " + String(localHumidity) + "%");
}

void setLEDColor(float temp) {
  uint32_t color;
  if (temp < 0) {
    color = strip.Color(0, 0, 255);  // Blue
  } else if (temp > 30) {
    color = strip.Color(255, 0, 0);  // Red
  } else {
    int blue = (30 - temp) / 30 * 255;
    int red = temp / 30 * 255;
    color = strip.Color(red, 0, blue);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
