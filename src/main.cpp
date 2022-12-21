// @author PoofyPloop

// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

// Sensor address variable
DeviceAddress sensorAddress;
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  Serial.println("\nTemperature Application");
  
  // condition that indicated whether the sensor is disconnected or not. if connected, returns sensor address
  if (!DS18B20.getAddress(sensorAddress, 0)) 
  {
    Serial.println("No DS18B20 temperature sensores are installed");
  }
  else {
    Serial.print("Found DS18B20 sensor with address: ");
    for (uint8_t i = 0; i < 8 ; i++) {
      if (sensorAddress[i] < 16) {}
        Serial.print(sensorAddress[i], HEX);
    }
    Serial.println();
  }
} 
 
void loop() {   
  float fTemp; // temperature variable
  String judge; // coolness indicator variable

  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0);  

  // disconnected sensor returns a blank
  if (!DS18B20.getAddress(sensorAddress, 0) || fTemp == DEVICE_DISCONNECTED_C) 
  {
  }
  // connected sensore return values
  else {
    if (fTemp <= 10)
    {
      judge = "Cold!";
    }
    else if (fTemp > 10 && fTemp <= 15)
    {
      judge = "Cool";
    }
    else if (fTemp > 15 && fTemp <= 25)
    {
      judge = "Perfect";
    }
    else if (fTemp > 25 && fTemp <= 30)
    {
      judge = "Warm";
    }
    else if (fTemp > 30 && fTemp <= 35)
    {
      judge = "Hot";
    }
    else if (fTemp > 35)
    {
      judge = "Too Hot!";
    }

    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + judge); 

    // wait 2s (2000ms) before doing this again 
    delay(2000); 
  }
} 
