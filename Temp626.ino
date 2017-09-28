// This sketch is for the base node in 626 room. It monitors Stinol freezer in 626 and ChuFreezer01 in 631
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#define BLYNK_PRINT Serial // Enables Serial Monitor
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Data wire is plugged into port D1/MOSI/D7 on the WEMOS D1 (not mini)
#define ONE_WIRE_BUS 13

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Authorization token for the base node is d2db...4a3c
char auth[] = "d2db9a9442eb44dda8aaa8e302024a3c";

// If the temperature goes above the threshold value, the node sends e-mail alarm and phone notification
int threshold = -10;
float TempCF03, TempAbFridge, TempCF04;
//WidgetBridge bridge1(V6);
//WidgetBridge bridge2(V7);
/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  Blynk.begin(auth, "LUK", "FastFreeze273");
  //if (Blynk.connect()){
   // 625 node
  // bridge1.setAuthToken("252498e2fcf940d7ade26399d6e13fa4");
   // 634 node
  // bridge2.setAuthToken("794ef83801be46598caca23e79ec6b35");
  //}
  // Start up the library
  sensors.begin();
}

//BLYNK_WRITE(V7){
//  TempCF03 = param[0].asFloat();
//  TempAbFridge = param[1].asFloat();
//  TempCF04 = param[2].asFloat();
//  Blynk.virtualWrite(V8, TempCF03);
//  Blynk.virtualWrite(V9, TempAbFridge);
//  Blynk.virtualWrite(V10, TempCF04);
//}
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
  
  Blynk.virtualWrite(V0, Temp1);
  Blynk.virtualWrite(V1, Temp2);
  
  
  // Blynk.virtualWrite(V5, Temp3);
  if (Temp1 >= threshold)
  {
    Blynk.email("TemperatureAlarm", "Температура в морозилке в 631 выше -10!");
    Blynk.notify("631 freezer temp is above -10 degrees!");
  }
  if (Temp2 >= threshold)
  {
    Blynk.email("TemperatureAlarm", "Температура в морозилке в 626 выше -10!");
    Blynk.notify("626 freezer temp is above -10 degrees!");
  }
  
}

