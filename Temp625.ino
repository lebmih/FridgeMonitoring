// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#define BLYNK_PRINT Serial // Enables Serial Monitor
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

char auth[] = "252498e2fcf940d7ade26399d6e13fa4";
char basenodeauth[] = "d2db9a9442eb44dda8aaa8e302024a3c";
int threshold = -10;

WidgetBridge bridge2(V7);
//WidgetBridge bridge3(V8);
//WidgetBridge bridge4(V9);
/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  Blynk.begin(auth, "LUK", "FastFreeze273");
  while (Blynk.connect() == false) {
    // Wait until Blynk is connected
  }
  bridge2.setAuthToken(basenodeauth);
  //bridge3.setAuthToken(basenodeauth);
  //bridge4.setAuthToken(basenodeauth);
  // Start up the library
  sensors.begin();
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  Blynk.run();
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  float Temp1 =  sensors.getTempCByIndex(0);
  float Temp2 =  sensors.getTempCByIndex(1);
  float Temp3 =  sensors.getTempCByIndex(2);
  
  Blynk.virtualWrite(V2, Temp1);
  Blynk.virtualWrite(V3, Temp2);
  Blynk.virtualWrite(V4, Temp3);
  bridge2.virtualWrite(V7, Temp1);
  bridge2.virtualWrite(V8, Temp2);
  bridge2.virtualWrite(V9, Temp3);
  if (Temp1 >= threshold)
  {
    Blynk.email("TemperatureAlarm", "Температура в морозилке 3 в 625 выше -10!");
    Blynk.notify("CF03 temp is above -10 degrees!");
  }
  if (Temp2 >= threshold)
  {
    Blynk.email("TemperatureAlarm", "Температура в морозилке холодильника для антител в 625 выше -10!");
    Blynk.notify("AbFridge temp is above -10 degrees!");
  }
  if (Temp3 >= threshold)
  {
    Blynk.email("TemperatureAlarm", "Температура в морозилке 4 в 625 выше -10!");
    Blynk.notify("CF04 temp is above -10 degrees!");
  }
}

