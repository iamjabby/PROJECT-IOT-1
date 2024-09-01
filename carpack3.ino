#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 

#define ir_car1  5
#define ir_car2  6

#define led_car1 7
#define led_car2 8

int S1 = 0, S2 = 0;
int slot = 2;

void setup() {
  Serial.begin(9600); 

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);

  pinMode(led_car1, OUTPUT);
  pinMode(led_car2, OUTPUT);

  lcd.init();        
  lcd.backlight();    

  lcd.setCursor(0, 1);
  lcd.print("    Car  parking  ");
  lcd.setCursor(0, 2);
  lcd.print("       System     ");
  delay(2000);
  lcd.clear();

  Read_Sensor();
  slot -= (S1 + S2);
}

void loop() {
  Read_Sensor(); 

  lcd.setCursor(0, 0);
  lcd.print("  Have Slot: "); 
  lcd.print(slot);
  lcd.print("    ");
  
  lcd.setCursor(0, 1);
  lcd.print(S1 == 1 ? "S1:Fill " : "S1:Free"); 
  
  lcd.setCursor(9, 1);
  lcd.print(S2 == 1 ? "S2:Fill " : "S2:Free"); 

  digitalWrite(led_car1, S1);
  digitalWrite(led_car2, S2); 
}

void Read_Sensor() {
  S1 = digitalRead(ir_car1) == 0 ? 1 : 0; 
  S2 = digitalRead(ir_car2) == 0 ? 1 : 0;

  int occupiedSlots = S1 + S2;
  slot = 2 - occupiedSlots; // คำนวณจำนวนช่องว่างใหม่ทุกครั้งตามจำนวนช่องที่ถูกครอบครอง
}
