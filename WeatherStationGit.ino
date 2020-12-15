// Internet Based Weather Station v2.5A May 2019 - JAllen
// RemoteMe **www.remoteme.org**
// NodeMCU 1.0 ESP8266 Board
// MUST USE 2.5.2 ESP8266 Board Version

//WIFI Definitions
//Set your SSID and Wifi Password according to your router
//Token obtains from RemoteMe
//Device setup at RemoteMe
#define WIFI_NAME ""
#define WIFI_PASSWORD ""
#define DEVICE_ID 1
#define DEVICE_NAME ""
#define TOKEN ""

//Libraries Required
#include <RemoteMe.h> //https://github.com/remoteme/RemoteMeArduinoLibrary
#include <RemoteMeSocketConnector.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>



LiquidCrystal_I2C lcd(0x3F, 16, 2); // Defines I2C LCD Display Address, Row Count, Column Count 
int16_t i, i1, i2, temp, pres;
String fc;
const int timeZone = 0;
int buttonPin1= D5;
int buttonPin2 = D6;
int prevButtonState1;
int prevButtonState2;
int tm_isdst = 0;

RemoteMe& remoteMe = RemoteMe::getInstance(TOKEN, DEVICE_ID);

void setup() {
    Serial.begin(9600);
    lcd.init(); // initialize LCD                     
    lcd.backlight(); // turn on LCD backlight 
    Serial.print("Connecting Weather Station Ver 2.5A");
    lcd.clear();
    lcd.print("Connecting...");
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("Allen Elec 2.5A 1120");
    lcd.setCursor(0,0);
    delay(3000);
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);
    digitalWrite(buttonPin1, LOW);
    digitalWrite(buttonPin2,LOW);
    
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }

    WiFi.softAPdisconnect (true);
    
    remoteMe.getVariables()->observeSmallInteger2Text2("Weather" ,onWeatherChange);

    remoteMe.setConnector(new RemoteMeSocketConnector());

    remoteMe.sendRegisterDeviceMessage(DEVICE_NAME);

    Serial.print("Connected... \n");
    lcd.clear();
    lcd.print("Connected :)");
    lcd.setCursor(0,1);
    lcd.print(WIFI_NAME " ");
    delay(3000);
	lcd.clear();
    lcd.print(WiFi.localIP());
	delay(2000);

    configTime(-1 * 3600, tm_isdst, "pool.ntp.org", "time.nist.gov");
    Serial.println("\nWaiting for time");
    while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
    
}
}

void onWeatherChange(int16_t i1, int16_t i2,String s1,String s2) {
    Serial.printf("onWeatherChange: i1: %d,i2: %d,s1: %s,s2: %s\n",i1,i2,s1.c_str(),s2.c_str());
    temp = i1; //storing temperature  
    pres = i2; //Storing Pressure 
    fc  = s2; //Storing Forecast
}

void loop() {
int buttonState1 = digitalRead(buttonPin1);
int buttonState2 = digitalRead(buttonPin2);

if (buttonState1 == LOW && prevButtonState1== HIGH){
  Serial.printf("Temparature : %d °C\n", temp);
  Serial.printf("Pressure : %d Pa\n", pres);
  lcd.clear();
  lcd.printf("Temp:%dC", temp);
  lcd.setCursor(0,1);
  lcd.printf("Pressure:%d Pa", pres);
  lcd.setCursor(0,0);
  delay(5000);
  prevButtonState1 = buttonState1;
 }
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
 }
 else{
   prevButtonState1 = buttonState1;
   prevButtonState2 = buttonState2;
      remoteMe.loop();
      time_t now;
      struct tm * timeinfo;
      time(&now);
      timeinfo = localtime(&now);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.printf("%02d", timeinfo->tm_hour+1);
      lcd.print(":");
      lcd.printf("%02d", timeinfo->tm_min);
      lcd.print(":");
      lcd.printf("%02d", timeinfo->tm_sec);
      lcd.setCursor(0,1);
	  lcd.print("IP:");
	  lcd.print(WiFi.localIP());
      delay(250);

}
}
