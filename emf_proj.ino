#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int button_select=9;
int button_cancel=2;
int led_danger=3;
int led_info=4;
int potentiometer=5;
int beep=6;
int emf_pin=7;
int gas_pin=0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(button_select,INPUT);
  pinMode(button_cancel,INPUT);
  pinMode(led_danger,OUTPUT);
  pinMode(led_info,OUTPUT);
  pinMode(potentiometer,INPUT);
  pinMode(beep,OUTPUT);
  
  digitalWrite(led_info,HIGH);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,4);
  lcd.print("MAGOCHI CONTROLLER!");
  lcd.setCursor(1,3);
  lcd.print("Loading..please wait");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,5);
  lcd.print("Running..");
  digitalWrite(led_danger,HIGH);
  tone(beep,1000);
  delay(1000);
  noTone(beep);
  digitalWrite(led_danger,LOW);

}

void loop() {
  String current_menu="";
  int current_value=0;
  bool is_selected=false;
  int temporary_select=0;
  bool is_main_menu=false;
  int gasvalue=analogRead(gas_pin);
  int current_air=gas_pin;
  String sp="";
  int max_air=200;
  int max_emf=7;
  int current_emf=constrain(analogRead(emf_pin),0,100);
  
  
  int menu_selection=digitalRead(button_select);
  int cancel=digitalRead(button_cancel);
  int potentiometer_values=map(potentiometer,0,1024,0,180);

//------------------swith main menu -----------------
  if(button_select==HIGH && is_main_menu==false){
    is_main_menu==true;
    }
    //-------------------------------------------

    //----process main menu...
    
  if(button_select==HIGH && is_main_menu==true){
    

  
     if(potentiometer_values >0 && potentiometer_values<75){
          current_menu="Air Sensor Sel.";
          temporary_select=1;
          }
     if(potentiometer_values >=75 && potentiometer_values<150){
          current_menu="EMF Meter Adjust";
          temporary_select=2;
          }
      if(potentiometer_values >300){
          current_menu="..PTM mode vals->";
          temporary_select=7;
          }
          
      switch(temporary_select){
        case 1:
        lcd.clear();
        lcd.setCursor(0,5);
        lcd.print(current_menu);
        lcd.setCursor(1,5);
        sp="danger mark >";
        lcd.print(sp.concat(potentiometer_values));
        if(button_cancel==HIGH){
          max_air=potentiometer_values;
          lcd.clear();
            lcd.setCursor(0,5);
            lcd.print(current_menu);
            lcd.setCursor(1,5);
            lcd.print("Limit Set..Running");
            
          }
          if(current_air >=max_air){
            lcd.clear();
            lcd.setCursor(0,5);
            lcd.print("Bad Air Alert!!");
            lcd.setCursor(1,5);
            digitalWrite(led_danger,HIGH);
              tone(beep,1000);
              delay(1000);
              noTone(beep);
              digitalWrite(led_danger,LOW);
              delay(2000);
            }
        
        break;
    
        case 2:
        
        if(button_cancel==HIGH){
          current_emf=potentiometer_values;
          
          }
        lcd.clear();
        lcd.setCursor(0,5);
        lcd.print(current_menu);
        if(current_emf >=max_emf){
          lcd.clear();
            lcd.setCursor(0,5);
            lcd.print("High  EMF Rad!!");
            lcd.setCursor(1,5);
            digitalWrite(led_info,HIGH);
              tone(beep,1000);
              delay(1000);
              noTone(beep);
              digitalWrite(led_danger,LOW);
              delay(2000);
          }
        break;
    
        case 3:
        lcd.clear();
        lcd.setCursor(0,5);
        lcd.print(current_menu);
        
        break;
    
        case 4:
        lcd.clear();
        lcd.setCursor(0,5);
        lcd.print(current_menu);
        
        break;

        case 7:
        lcd.clear();
        lcd.setCursor(0,5);
        lcd.print(current_menu);
        lcd.setCursor(1,5);
        lcd.print(potentiometer_values);
        digitalWrite(led_danger,HIGH);
        tone(beep,1000);
        delay(1000);
        noTone(beep);
        digitalWrite(led_danger,LOW);
        
        break;

        case 0:
        is_main_menu=true;
        lcd.clear();
        lcd.setCursor(0,5);
        lcd.print("Home | Welcome");
        lcd.setCursor(1,5);
        lcd.print("--Menu--");
        digitalWrite(led_danger,HIGH);
        delay(2000);
        digitalWrite(led_danger,LOW);
        break;
        
        default:
        break;
        }
  }
  

}
