#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
/////
//#define SCREEN_WIDTH 128    // OLED display width, in pixels
//#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET); 

  
#define RE 8
#define DE 7
  
//const byte code[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
const byte soil_ph[] = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0b};
const byte soil_moist[] = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0f};
const byte temp[] = {0x01, 0x03, 0x00, 0x12, 0x00, 0x02, 0x64, 0x0e};
const byte ec[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xce};

byte values[11];
SoftwareSerial mod(10,11);////// TX AND RX
  
void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);


    display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
   delay(500);
  display.clearDisplay();
   display.setCursor(25, 10);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("AR RoboTics");
  display.setCursor(25, 27);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" Soil  Sensor");
  display.setCursor(25, 40);
  display.setTextSize(1);
  display.print("Initializing");

  display.display();
  delay(1000);


  

}
  
void loop() {
  
  byte val1,val2,val3,val4,val5,val6,val7;
  val1 = nitrogen();
  delay(250);
  val2 = phosphorous();
  delay(250);
  val3 = potassium();
  delay(250);
  val4 = ph();
  delay(250);
  val5 = moist();
  delay(250);
  val6 = stemp();
  delay(250);
  val7 = econd();
  delay(250);
   
  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  Serial.print("Phosphorous: ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  Serial.print("Potassium: ");
  Serial.print(val3);
  Serial.println(" mg/kg");
  Serial.print("Soil pH: ");
  Serial.print(val4);
  Serial.println(" pH");
  Serial.print("Soil Moisture: ");
  Serial.print(val5);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(val6);
  Serial.println(" C");
  Serial.print("Electrical Conductivity: ");
  Serial.print(val7);
  Serial.println(" mS/m");
  delay(5000);

 /////
 display.clearDisplay();
  
 
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("N: ");
  display.print( val1);
  display.setTextSize(1);
  display.print(" mg/kg");
 
  display.setTextSize(1);
  display.setCursor(0, 9);
  display.print("P: ");
  display.print( val2);
  display.setTextSize(1);
  display.print(" mg/kg");
 
  display.setTextSize(1);
  display.setCursor(0,18);
  display.print("K: ");
  display.print( val3);
  display.setTextSize(1);
  display.print(" mg/kg");

    display.setTextSize(1);
    display.setCursor(0,27);
    display.print("PH: ");
    display.print(val4);
    display.setTextSize(1);
    display.print(" ph");
     
//
  display.setTextSize(1);
  display.setCursor(0,36);
  display.print("SM: ");
  display.print(val5);
  display.setTextSize(1);
  display.print(" %");

display.setTextSize(1);
 display.setCursor(0,45);
 display.print("T:  ");
 display.print( val6);
 display.setTextSize(1);
 display.print(" C");

 
//  display.display(); 
//     delay(3000);
    
   


 

 display.setTextSize(1);
 display.setCursor(0,54);
 display.print("EC: ");
 display.print(val7);
 display.setTextSize(1);
 display.print(" mS/m");

  
  display.display(); 

  delay(2000);

}
  
byte nitrogen(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(nitro,sizeof(nitro))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
  
byte phosphorous(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(phos,sizeof(phos))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}
  
byte potassium(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(pota,sizeof(pota))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}


byte ph(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(soil_ph,sizeof(soil_ph))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}


byte moist(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(soil_moist,sizeof(soil_moist))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}


byte stemp(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(temp,sizeof(temp))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}


byte econd(){
  digitalWrite(DE,HIGH);
  digitalWrite(RE,HIGH);
  delay(10);
  if(mod.write(ec,sizeof(ec))==8){
    digitalWrite(DE,LOW);
    digitalWrite(RE,LOW);
    for(byte i=0;i<7;i++){
    //Serial.print(mod.read(),HEX);
    values[i] = mod.read();
    Serial.print(values[i],HEX);
    }
    Serial.println();
  }
  return values[4];
}