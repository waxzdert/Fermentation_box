int JoyStick_X = A0; // x
int JoyStick_Y = A1; // y
int JoyStick_Z = 3; // z

int initial_temp = 35;
int initial_hour = 1;
int initial_min = 1;
int set_mode_id = 0;


char setting_mode[12] = {};


void setup ()
{
  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);
  pinMode (JoyStick_Z, INPUT_PULLUP);
  Serial.begin (9600); // 9600 bps
}

void loop ()
{
  int x, y, z;

  
  x = analogRead (JoyStick_X) ;
  y = analogRead (JoyStick_Y) ;
  z = digitalRead (JoyStick_Z);
  Serial.print(x);
  //Serial.print(y);
  //Serial.print(z);
  if(!z){
    Serial.print("\nChoose the setting mode?\n");
    while(1){
      delay(125);
      x = analogRead (JoyStick_X) ;
      z = !digitalRead (JoyStick_Z);
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
  }
  delay(100);
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

  Serial.print("\nNow, set the temperature\n");
  while(1){
    delay(125);
    y = analogRead (JoyStick_Y) ;
    z = !digitalRead (JoyStick_Z);
    if(y>3000){
      set_temp++;
      Serial.print(set_temp);
      Serial.print("\n");
      delay(100);
    }
    else if(y<2000){
      set_temp--;
      Serial.print(set_temp);
      Serial.print("\n");
      delay(100);
    }
    else if(z){
      break;
    }
  }
  Serial.print("set temp!\n");
  return set_temp;
}

int set_hour(int set_hour){
  int JoyStick_Y = A1;
  int JoyStick_Z = 3;
  pinMode (JoyStick_Y, INPUT);  
  pinMode (JoyStick_Z, INPUT_PULLUP);
  int y = analogRead (JoyStick_Y) ;
  int z = digitalRead (JoyStick_Z);

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
      delay(100);
    }
    else if(z){
      break;
    }
  }
  Serial.print("set hour!\n");
  return set_hour;
}

int set_min(int set_min){
  int JoyStick_Y = A1;
  int JoyStick_Z = 3;
  pinMode (JoyStick_Y, INPUT);  
  pinMode (JoyStick_Z, INPUT_PULLUP);
  int y = analogRead (JoyStick_Y) ;
  int z = digitalRead (JoyStick_Z);

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
      delay(100);
    }
    else if(z){
      break;
    }
  }
  Serial.print("set Minutes!\n");
  return set_min;
}
void choose_mode(int cho_mod_id){
      switch(cho_mod_id){
      case 0:
        Serial.print("Temperature\n");
        delay(150);
        break;
      case 1:
        Serial.print("Hour\n");
        delay(150);
        break;
      case 2:
        Serial.print("Minute\n");
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

