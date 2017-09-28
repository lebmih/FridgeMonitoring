#include <Adafruit_ESP8266.h>

// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#define BLYNK_PRINT Serial // Enables Serial Monitor
//#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Auth token for 634 freezer node is 794e...6b35
char auth[] = "794ef83801be46598caca23e79ec6b35";
char basenodeauth[] = "d2db9a9442eb44dda8aaa8e302024a3c";
int threshold = -10;

WidgetBridge bridge1(V6);
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
  bridge1.setAuthToken(basenodeauth);
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
  
  Blynk.virtualWrite(V5, Temp1);
  bridge1.virtualWrite(V6, Temp1);
  if (Temp1 >= threshold)
  {
    Blynk.email("TemperatureAlarm", "Температура в морозилке 1 в сортерной выше -10!");
    Blynk.notify("CF01 temp is above -10 degrees!");
  }
 
}

