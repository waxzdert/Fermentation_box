//oled
#include <Wire.h>
#include <SeeedOLED.h>
#include <Grove_LED_Bar.h>
#include <LWiFi.h>
#include <PubSubClient.h>
Grove_LED_Bar __bar2(7, 4, 0);
// DHT
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
//joystick
int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = 3; // z

//variables
int initial_temp = 35;
int initial_hour = 1;
int initial_min = 1;
int set_mode_id = 0;


char setting_mode[12] = {};


void setup ()
{
  //joystick
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT_PULLUP);
  //oled
  __bar2.begin();
  Wire.begin();
  SeeedOled.init();  
  SeeedOled.clearDisplay();  //清除螢幕
  SeeedOled.setNormalDisplay(); //設定螢幕為正常模式(非反白)
  SeeedOled.setTextXY(0,0); //設定啟始坐標
  SeeedOled.putString("Temp & Humi %"); 
  //DHT
  dht.begin();
  
  Serial.begin (9600); // 9600 bps
}

void loop ()
{
  //joystick
  int x, y, z;
  x = analogRead (JoyStick_X) ;
  y = analogRead (JoyStick_Y) ;
  z = digitalRead (JoyStick_Z);
  //DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  char temp[70];
  sprintf(temp, "%3.2f", t);
  char hum[70];
  sprintf(hum, "%3.2f", h);

  /*
  Serial.print("Class_Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Class_Temperature: "); 
  Serial.print(t);
  Serial.println(" *C\t");
  */

  SeeedOled.setTextXY(1,0); //設定啟始坐標
  SeeedOled.putString("Temp: "); 
  SeeedOled.putNumber(t); 
  SeeedOled.putString(" *C"); 
  SeeedOled.setTextXY(2,0); //設定啟始坐標
  SeeedOled.putString("Humi: "); 
  SeeedOled.putNumber(h); 
  SeeedOled.putString(" %");
  delay(50);
  
  if(!z){
    Serial.print("\nChoose the setting mode?\n");
    while(1){
      delay(125);
      x = analogRead (JoyStick_X) ;
      z = !digitalRead (JoyStick_Z);
      SeeedOled.setTextXY(3,0);
      SeeedOled.putString("Mode:"); 
      if(x>3000 || x<2000){
        ++set_mode_id;
        set_mode_id = set_mode_id%3;
        
        Serial.print("You choose the mode : ");
        choose_mode(set_mode_id);
        delay(100);
      }
      /*
      else if(x<2000){
        --set_mode_id;
        set_mode_id = (set_mode_id+1)%3;

        Serial.print("You choose the mode : ");
        if(set_mode_id<0){
          set_mode_id = -1* set_mode_id;
        }
        choose_mode(set_mode_id);
        delay(100);
      }*/
      else if(z)
        break;
    }
    enter_mode(set_mode_id);
    SeeedOled.setTextXY(3,0);
    SeeedOled.putString("     "); 
  }
  //delay(100);
}

/*
            initial_temp = set_temp(initial_temp);
            Serial.print("Set the temp : ");
            Serial.print(initial_temp);
            Serial.print(" °C\n");
            delay(500);
*/
int set_temp(int set_temp){
  int JoyStick_Y = A1;
  int JoyStick_Z = 3;
  pinMode (JoyStick_Y, INPUT);  
  pinMode (JoyStick_Z, INPUT_PULLUP);
  int y = analogRead (JoyStick_Y) ;
  int z = digitalRead (JoyStick_Z);
  //SeeedOled.clearDisplay();  //清除螢幕
  //SeeedOled.setNormalDisplay(); //設定螢幕為正常模式(非反白)
  SeeedOled.setTextXY(4,0); //設定啟始坐標
  SeeedOled.putString("Set temp:"); 
  SeeedOled.putString("  °C"); 
  
  while(1){
    delay(125);
    y = analogRead (JoyStick_Y) ;
    z = !digitalRead (JoyStick_Z);
    if(y>3000){
      set_temp++;
      //Serial.print(set_temp);
      SeeedOled.setTextXY(4,10);
      SeeedOled.putString("  ");
      SeeedOled.setTextXY(4,10);
      SeeedOled.putNumber(set_temp); 
      //Serial.print("\n");
      delay(100);
    }
    else if(y<2000){
      set_temp--;
      //Serial.print(set_temp);
      SeeedOled.setTextXY(4,10);
      SeeedOled.putString("  "); 
      SeeedOled.setTextXY(4,10);
      SeeedOled.putNumber(set_temp); 
      //Serial.print("\n");
      delay(100);
    }
    else if(z){
      break;
    }
  }
  Serial.print("set temp!\n");
  SeeedOled.setTextXY(5,0);
  SeeedOled.putString("Set the temp!"); 
  delay(2000);
  SeeedOled.setTextXY(4,0);
  SeeedOled.putString("                              ");
  SeeedOled.setTextXY(5,0);
  SeeedOled.putString("                              "); 
  return set_temp;
}

int set_hour(int set_hour){
  int JoyStick_Y = A1;
  int JoyStick_Z = 3;
  pinMode (JoyStick_Y, INPUT);  
  pinMode (JoyStick_Z, INPUT_PULLUP);
  int y = analogRead (JoyStick_Y) ;
  int z = digitalRead (JoyStick_Z);
  SeeedOled.setTextXY(4,0); //設定啟始坐標
  SeeedOled.putString("Set hour:");
  SeeedOled.putString("    hr"); 

  Serial.print("\nNow, set the hour\n");
  while(1){
    delay(150);
    y = analogRead (JoyStick_Y) ;
    z = !digitalRead (JoyStick_Z);
    if(y>3000){
      set_hour++;
      if(set_hour>24){
        set_hour = 24;
      }
      else if(set_hour<0){
        set_hour = 0;
      }
      Serial.print(set_hour);
      Serial.print("\n");
      SeeedOled.setTextXY(4,10);
      SeeedOled.putString("  "); 
      SeeedOled.setTextXY(4,10);
      SeeedOled.putNumber(set_hour); 
      delay(100);
    }
    else if(y<2000){
      set_hour--;
      if(set_hour>24){
        set_hour = 24;
      }
      else if(set_hour<0){
        set_hour = 0;
      }
      Serial.print(set_hour);
      Serial.print("\n");
      SeeedOled.setTextXY(4,10);
      SeeedOled.putString("  "); 
      SeeedOled.setTextXY(4,10);
      SeeedOled.putNumber(set_hour); 
      delay(100);
    }
    else if(z){
      break;
    }
  }
  SeeedOled.setTextXY(5,0);
  SeeedOled.putString("Set the hour!"); 
  delay(2000);
  SeeedOled.setTextXY(4,0);
  SeeedOled.putString("                              ");
  SeeedOled.setTextXY(5,0);
  SeeedOled.putString("                              ");
  return set_hour;
}

int set_min(int set_min){
  int JoyStick_Y = A1;
  int JoyStick_Z = 3;
  pinMode (JoyStick_Y, INPUT);  
  pinMode (JoyStick_Z, INPUT_PULLUP);
  int y = analogRead (JoyStick_Y) ;
  int z = digitalRead (JoyStick_Z);
  SeeedOled.setTextXY(4,0); //設定啟始坐標
  SeeedOled.putString("Set min:");
  SeeedOled.putString("    min"); 

  Serial.print("\nNow, set the Minutes\n");
  while(1){
    delay(150);
    y = analogRead (JoyStick_Y) ;
    z = !digitalRead (JoyStick_Z);
    if(y>3000){
      set_min++;
      if(set_min>60){
        set_min = 60;
      }
      else if(set_min<0){
        set_min = 0;
      }
      Serial.print(set_min);
      Serial.print("\n");
      SeeedOled.setTextXY(4,9);
      SeeedOled.putString("  "); 
      SeeedOled.setTextXY(4,9);
      SeeedOled.putNumber(set_min); 
      delay(100);
    }
    else if(y<2000){
      set_min--;
      if(set_min>60){
        set_min = 60;
      }
      else if(set_min<0){
        set_min = 0;
      }
      Serial.print(set_min);
      Serial.print("\n");
      SeeedOled.setTextXY(4,9);
      SeeedOled.putString("  ");
      SeeedOled.setTextXY(4,9);
      SeeedOled.putNumber(set_min); 
      delay(100);
    }
    else if(z){
      break;
    }
  }
  Serial.print("set Minutes!\n");
  SeeedOled.setTextXY(5,0);
  SeeedOled.putString("Set the min!");
  delay(2000);
  SeeedOled.setTextXY(4,0);
  SeeedOled.putString("                              ");
  SeeedOled.setTextXY(5,0);
  SeeedOled.putString("                              "); 
  return set_min;
}
void choose_mode(int cho_mod_id){
      SeeedOled.setTextXY(4,0);
      SeeedOled.putString("                ");   
      switch(cho_mod_id){
      case 0:
        Serial.print("Temperature\n");
        SeeedOled.setTextXY(4,0); 
        SeeedOled.putString("Temperature");   
        delay(150);
        break;
      case 1:
        Serial.print("Hour\n");
        SeeedOled.setTextXY(4,0);     
        SeeedOled.putString("Hour");   
        delay(150);
        break;
      case 2:
        Serial.print("Minute\n");
        SeeedOled.setTextXY(4,0);
        SeeedOled.putString("Minute");   
        delay(150);
        break;
    }
}

void enter_mode(int cho_mod_id){
      switch(cho_mod_id){
      case 0:
        initial_temp = set_temp(initial_temp);
        delay(150);
        break;
      case 1:
        initial_hour = set_hour(initial_hour);
        delay(150);
        break;
      case 2:
        initial_min = set_min(initial_min);
        delay(150);
        break;
    }
}

