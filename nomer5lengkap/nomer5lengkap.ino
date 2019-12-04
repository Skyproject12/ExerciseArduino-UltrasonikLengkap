#include<I2CIO.h>
#include<LCD.h>
#include<LiquidCrystal.h>
#include<LiquidCrystal_I2C.h> 
#include<LiquidCrystal_SR.h>
#include<LiquidCrystal_SR_LCD3.h> 
#include<NewPing.h> 

int PIN_LCD_STROBE= 2; 
int PIN_LCD_DATA=4; 
int buzzerPin= A5; 
int btnPin= 7; 
int PIN_LCD_CLOCK=3; 
int ledPin=6; 
long duration, cm; 
boolean lockLow= true;  
int stage=0;

LiquidCrystal_SR_LCD3 lcd(PIN_LCD_DATA, PIN_LCD_CLOCK, PIN_LCD_STROBE); 
int pingPin=13; 
int echoPin=12;

void setup() {
  Serial.begin(9600); 
  lcd.begin(16, 2); 
  pinMode(buzzerPin, OUTPUT); 
  pinMode(ledPin, OUTPUT); 
  pinMode(btnPin, INPUT); 
  digitalWrite(ledPin, LOW); 
  pinMode(pingPin, OUTPUT);

}

void loop() {
  // buat defauld adalah kosong 
  int beforeState= stage; 
  // ketika button di klik  
  if(digitalRead(btnPin)==LOW){  
    switch(stage){ 
      case 0: 
        calibratePING(); 
        //ubah status stage menjadi satu artinya sudah di klik satu kali  
        stage=1; 
        break; 
      case 1: 
        stage=2; 
        break; 
      case 2: 
        lockLow= true; 
        stage=3; 
        break; 
      case 3: 
        stage=1; 
        break; 
    }  
  } 
  // membuat fungsi dari stage satu sampai tiga 
  switch(stage){ 
    case 1: 
      if(beforeState!=1){ 
        // mengeset virtual treminal menjadi active
        Serial.println("Stand By, Sensor Active"); 
        lcd.print("Stand By, Sensor Active"); 
        digitalWrite(ledPin, LOW); 
        delay(1000);   
      }   
      break; 
     case 2: 
      calibratePING(); 
      printLcd("Jarak:"+cm); 
      // ketika jarak lebih dari 50  
      if(cm>50){  
        // menyalakan lampu 
        digitalWrite(ledPin, HIGH); 
        lockLow= false;  
        // mengaktifkan buzzer
        digitalWrite(buzzerPin, HIGH); 
        Serial.println("Buzzer Actived"); 
        Serial.println("Awas Tabrakan"); 
        lcd.print("Awas Tabrakan !"); 
        delay(1000);  
        // menonaktifkan buzzer 
        digitalWrite(buzzerPin, LOW); 
        delay(1000); 
        digitalWrite(btnPin, HIGH); 
        delay(1000);  
        // membersihkan lcd
        lcd.clear(); 
      } 
      break;  
      // mengeset virtual terminal 
      Serial.println("Stand By, LED will be actived"); 
      // mengeprint di lcd  
      lcd.print("Stand By, LED will be actived"); 
      // mematikan lampu 
      digitalWrite(ledPin, LOW);   
      delay(1000);  
     case 3: 
      calibratePING(); 
      if(cm>50){ 
        digitalWrite(ledPin, LOW); 
        digitalWrite(buzzerPin, HIGH); 
        Serial.println("Awas Tabrakan!"); 
        Serial.println("Buzzer active"); 
        lcd.print("Awas Tabrakan! "); 
        delay(1000); 
        lcd.clear(); 
        digitalWrite(buzzerPin, LOW); 
        delay(1000); 
        digitalWrite(ledPin, HIGH); 
        delay(1000); 
        digitalWrite(btnPin, HIGH); 
        delay(00);
      } 
  }
} 
long microsecondsToCentimeters(long microseconds){ 
  // mengeset jarak  
  return microseconds/29/2;  
} 
// mengeset lcd
void printLcd(String text){ 
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print(text);  
} 
void calibratePING(){ 
  digitalWrite(pingPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(pingPin, HIGH); 
  delayMicroseconds(10);  
  digitalWrite(pingPin, LOW); 
  pinMode(echoPin, INPUT); 
  duration= pulseIn(echoPin, HIGH); 
  cm= microsecondsToCentimeters(duration); 
  Serial.print("jarak :"); 
  Serial.print("\t"); 
  Serial.print(cm); 
  Serial.print("cm"); 
  Serial.println(); 
  delay(500);  
}
