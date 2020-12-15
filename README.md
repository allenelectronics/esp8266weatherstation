# esp8266weatherstation

The code is compiled in the Arduino IDE and needs some configuration to work
Firstly, you need to install the ESP8266 Board to the IDE in order to upload code to it.

Comprehensive instructions on how to do this are here: https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/
To get the weather functionality, I chose to use RemoteMe which collects the weather data direct from API and generates code which can be inserted into your code. You will need to register and set up the data stream on their website: https://remoteme.org 

Documentation about RemoteMe can be found here: https://remoteme.org/public/documentation/sources/#introduction 
There are some specific definitions that are unique to your setup that you will need to complete before upload:
#define WIFI_NAME "SSID GOES HERE"
#define WIFI_PASSWORD "PASSWORD GOES HERE”
#define DEVICE_ID 1
#define DEVICE_NAME "OBTAIN FROM REMOTEME.ORG"
#define TOKEN "OBTAIN FROM REMOTEME.ORG"
The definitions here need to be set by you based on your wifi details and the token you get from RemoteMe.
You need to make sure all these libraries are installed and included in the code. I have included links to the ones that are more difficult to get. 
#include <RemoteMe.h> //https://github.com/remoteme/RemoteMeArduinoLibrary
#include <RemoteMeSocketConnector.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
The last part that needs changing is your location as this project does not use GPS. You need to modify the “LOCATION” string:
else if(buttonState2 == LOW && prevButtonState2== HIGH){
  Serial.print("LOCATION\n");
  Serial.println(fc);
  lcd.clear();
  lcd.print("LOCATION");
  lcd.setCursor(0,1);
  lcd.print(fc);
  lcd.setCursor(0,0);
  delay(5000);
  prevButtonState2 = buttonState2;
