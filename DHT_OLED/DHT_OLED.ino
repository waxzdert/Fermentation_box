// OLED declaration
#include <Wire.h>
#include <SeeedOLED.h>
#include <Grove_LED_Bar.h>

// DHT declaration
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

// JoyStick declaration
int JoyStick_X = A0; 
int JoyStick_Y = A1; 
int JoyStick_Z = 3; 

void setup() {
  Serial.begin(9600);
  dht.begin();

  // OLED
  Wire.begin();
  SeeedOled.init();  
  SeeedOled.clearDisplay();  //清除螢幕
  SeeedOled.setNormalDisplay(); //設定螢幕為正常模式(非反白)
  SeeedOled.setTextXY(0,0); //設定啟始坐標

  // JoyStick
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT_PULLUP);
  
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int x, y, z;
  x = analogRead (JoyStick_X);
  y = analogRead (JoyStick_Y);
  z = digitalRead (JoyStick_Z);
  
  char temp[70];
  sprintf(temp, "%3.2f", t);
  char hum[70];
  sprintf(hum, "%3.2f", h);

  Serial.print("Class_Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Class_Temperature: "); 
  Serial.print(t);
  Serial.println(" *C\t");
  
  // OLED

  SeeedOled.setTextXY(0,0); //設定啟始坐標
  SeeedOled.putString("Temp_now: "); 
  SeeedOled.putNumber(t); 
  SeeedOled.putString(" *C"); 
  SeeedOled.setTextXY(1,0); //設定啟始坐標
  SeeedOled.putString("Humi_now: "); 
  SeeedOled.putNumber(h); 
  SeeedOled.putString(" %");

  //set temperture
  
  SeeedOled.setTextXY(3,0); //設定啟始坐標
  SeeedOled.putString("Temp_now: "); 
  SeeedOled.putNumber(t); 
  SeeedOled.putString(" *C"); 
  SeeedOled.setTextXY(4,0); //設定啟始坐標
  SeeedOled.putString("Humi_now: "); 
  SeeedOled.putNumber(h); 
  SeeedOled.putString(" %");
  
}
