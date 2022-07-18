
#include <WiFi.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include "ThingSpeak.h"
#include <math.h>
#include <stdio.h>
#include <Adafruit_MLX90614.h>

//--------------------------------------------------------------------------------------------------------
  Adafruit_MLX90614 mlx = Adafruit_MLX90614();
  
  #define RELAY_PIN1 25 
  #define RELAY_PIN2 32 

//---------------------------------
// Wifi credentials ->

  WiFiClient client;
  const char* ssid = "agrotech-lab-1"; // your wifi SSID name
  const char* password = "1Afuna2Gezer"; // Wifi password

//---------------------------------

// Things Speak credentials ->
  const long myChannelNumber = 1776277;
  const char * myWriteAPIKey = "U52OQL49ISJ8ENZB";
  const char * server = "api.thingspeak.com";

//---------------------------------
// Soil Moisture calibrate ->

const int dryValueP34 = 1900;
const int wetValueP34 = 1200;  

const int dryValueP35 = 1600;  
const int wetValueP35 = 950;   

//---------------------------------
// Water Valves ->

boolean valve01;
boolean valve02;

// ------------------ ~~ SETUP ~~ --------------------------

void setup() {
  
  Serial.begin(9600);

//---------------------------------------------
  // initialize digital pin as an output ->
 
  pinMode(RELAY_PIN1, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);

//---------------------------------------------
  // connecting to Wifi & ThingSpeak ->

  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  ThingSpeak.begin(client);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();

//------------------------------------------ 
  // starting up the leaf temp sensor ->
  
  mlx.begin();
  
}

//------------------ ~~ LOOP ~~ -----------------------
void loop() {

  // Mesuring leaf temp sensor ->
  int ambientTemp = mlx.readAmbientTempC();
  int objectTemp = mlx.readObjectTempC();
  
  Serial.print("Ambient = "); Serial.print(ambientTemp); 
  Serial.print("*C\tObject = "); Serial.print(objectTemp); Serial.println("*C");

//---------------------------------------------
 // Soil Moisture read -> 60% TREATMENT (35)
 
  int soilMoistureValueP35 = analogRead(35); //Sensor Aout pin connected to pin of Ardiuno
  Serial.print("P35 SENSOR VALUE: ");Serial.println(soilMoistureValueP35);        // print the value in serial monitor
  int soilmoisturePercentP35 = map(soilMoistureValueP35, dryValueP35, wetValueP35, 0, 100);
  Serial.print("Soil Moisture P35 % = ");Serial.println(soilmoisturePercentP35);

 // Soil Moisture read -> 80% TREATMENT (34)
 
  int soilMoistureValueP34 = analogRead(34);//sensor Aout pin connected to pin of Ardiuno
  Serial.print("P34 SENSOR VALUE: ");Serial.println(soilMoistureValueP34);        // print the value in serial monitor
  int soilmoisturePercentP34 = map(soilMoistureValueP34, dryValueP34, wetValueP34, 0, 100);
  Serial.print("Soil Moisture P34 % = ");Serial.println(soilmoisturePercentP34);

//---------------------------------------------
  // Water Valve ->

  if (soilmoisturePercentP35 < 60) {
    digitalWrite(RELAY_PIN1, HIGH); // Open valve
    valve01 = true;
    Serial.print("S01 VALVE = ");Serial.println(valve01);    
  } else {
    digitalWrite(RELAY_PIN1, LOW); // Close valve
    valve01 = false;
    Serial.print("S01 VALVE = ");Serial.println(valve01);    
  };
   
  if (soilmoisturePercentP34 < 80) {
    digitalWrite(RELAY_PIN2, HIGH); // Open valve
    valve02 = true;
    Serial.print("S02 VALVE = ");Serial.println(valve02);    
  } else {
    digitalWrite(RELAY_PIN2, LOW); // Close valve
    valve02 = false;
    Serial.print("S02 VALVE = ");Serial.println(valve02);    
  };

//---------------------------------------------
  // ThingsSpeak Upload ->

  ThingSpeak.setField(1,valve01);
  ThingSpeak.setField(2,valve02);
  ThingSpeak.setField(3,soilmoisturePercentP35);
  ThingSpeak.setField(4,soilmoisturePercentP34);
  ThingSpeak.setField(5,ambientTemp);
  ThingSpeak.setField(6,objectTemp);
  
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  Serial.println("uploaded to Thingspeak server....");

  client.stop();

  Serial.println("Waiting to upload next reading...");
  Serial.println();

 
  delay(15000);
}

 
