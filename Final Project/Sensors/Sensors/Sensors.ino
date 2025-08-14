#include <OneWire.h>
#include <DallasTemperature.h>

// --- Temperature Sensor Setup ---
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

// --- Turbidity Sensor Setup ---
const int turbidityPin = A0;  // Turbidity sensor connected to A0
const int ledPin = 7;         // LED connected to D7

// --- pH Sensor Setup ---
const int pHPin = A1;         // pH sensor connected to A1
int pH_Value;
float Voltage;

void setup() {
  Serial.begin(9600);

  pinMode(turbidityPin, INPUT);
  pinMode(pHPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize temperature sensor
  Serial.println("Initializing Dallas Temperature Sensor...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" device(s).");

  if (!sensors.getAddress(insideThermometer, 0))
    Serial.println("Unable to find address for Device 0");
  else {
    Serial.print("Device 0 Address: ");
    printAddress(insideThermometer);
    Serial.println();

    sensors.setResolution(insideThermometer, 9);
    Serial.print("Device 0 Resolution: ");
    Serial.println(sensors.getResolution(insideThermometer), DEC);
  }
}

void loop() {
  // --- Read Turbidity ---
  int turbidityValue = analogRead(turbidityPin);
  Serial.print("Turbidity Sensor Value: ");
  Serial.println(turbidityValue);

  if (turbidityValue < 500) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Warning: High Turbidity Detected!");
  } else {
    digitalWrite(ledPin, LOW);
  }

  // --- Read Temperature ---
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(insideThermometer);
  if (tempC == DEVICE_DISCONNECTED_C) {
    Serial.println("Error: Could not read temperature data");
  } else {
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" °C / ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.println(" °F");
  }

  // --- Read pH Sensor ---
  pH_Value = analogRead(pHPin);
  Voltage = pH_Value * (5.0 / 1023.0);
  Serial.print("pH Sensor Voltage: ");
  Serial.println(Voltage);

  Serial.println("-----------------------------");
  delay(2000);
}

// Helper function to print device address
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i],HEX);
}
}
