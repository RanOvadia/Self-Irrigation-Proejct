# Self-Irrigation-Project
Developing an Arduino automatic irrigation system based on soil moisture percentage for our final project on 'AgroTech Laboratory' course.
On top of the Irrigation system we've built an experiment to check the Leaf temperature depending on the amounts of irrigation.

Thingspeak channel - https://thingspeak.com/channels/1776277/private_show

## GOALS :
1. Reading soil moisture percentage frequently.
2. Creating an automatic switch that responds to the soil moisture percentage.
3. Reading ambient and leaf surface temperature.
4. Checking for correlation between leaf surface temperature by soil moisture percentage.


## HARDWARE :
1. ESP32 x2 (https://espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
2. Bread Board
3. Adafruit_MLX90614 x2 (infrared temperature sensor) (https://www.melexis.com/en/documents/documentation/datasheets/datasheet-mlx90614)
4. Capacitive Soil Moisture Sensor x2 (https://esp32io.com/tutorials/esp32-soil-moisture-sensor)
5. ESP32 Relay Module x2 (https://randomnerdtutorials.com/esp32-relay-module-ac-web-server/)
6. Power-Supply 12V
7. Buck (https://datasheet.lcsc.com/lcsc/1811081616_XLSEMI-XL4015E1--_C51661.pdf)
8. Solenoid Valve x2 (https://bc-robotics.com/tutorials/controlling-a-solenoid-valve-with-arduino/)  

![image](https://user-images.githubusercontent.com/93939949/179560114-43d2c68d-a230-4f88-bf8b-c65c97cde381.png)

(תמונה של אלקטרוניקה)

(תמונה של המעגל החשמלי)


### How do we set up the electronics? 
1. Capacitive Soil sensors are connected to 3.3V, Ground, Pin 35+34.
2. Temp sensors are connected to 3.3V, Ground, pin 22 (SCL), pin 21 (SDA).
3. Buck is connected to 12V (inside-greenhouse power) and to 5V (outside-arduino).
4. ESP32 Relay Module connected to 3.3V, Ground, pin 32+25 (INSIDE-arduino) | 12V, ground (outside-greenhouse power).
5. Solenoid valves connected to 12V, ground.


### How did we start up the project?
1. Calibrate the Capacitive Soil sensors for wet and dry values (http://www.esp32learning.com/code/esp32-and-soil-moisture-sensor-example.php)
2. Change the Wi-Fi credentials in the code
3. Open a thingspeak channel and change the thingspeak credentials accordingly
4. Direct the temperature sensors to the plants canopy
5. Place the soil moisture sensors inside the plant's soil
6. Connect the irrigation system and open the tap
