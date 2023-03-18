#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>

#define DHTPIN 2
#define DHTTYPE DHT11 

SoftwareSerial Bluetooth(10, 11); 
DHT_Unified dht(DHTPIN, DHTTYPE);

int BluetoothData;
uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  dht.begin();
  sensor_t sensor;
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Bluetooth.println(("Error reading temperature!"));
  }
  else {
    Bluetooth.print("Temperature: ");
    Bluetooth.print(event.temperature);
    Bluetooth.print(F("C"));
    Bluetooth.println();

  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Bluetooth.println("Error reading humidity!");
  }
  else {
    Bluetooth.print("Humidity: ");
    Bluetooth.print(event.relative_humidity);
    Bluetooth.print(F("%"));
    Bluetooth.println();
  }
}