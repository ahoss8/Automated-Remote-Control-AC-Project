#include <IRremote.h> // Importing Remote Control Library
#include <LiquidCrystal_74HC595.h> // Importing LCD 74HC595 Library
#include <DHT.h> // Importing Temperature/Humidity Sensor Library
#define Type DHT11 // Defining Type For DHT Sensor

int delaytime = 500;

const int sensorPin = 5; // Sensor Pin For Temperature/Humidity
float temperature;
float humidity;
DHT HT(sensorPin, Type); // Creating HT Object From DHT Class

const int latchPin = 7; // Shift Register Latch Pin 
const int clockPin = 13; // Shift Register Clock Pin For Coordinating The Timing of Data Transfer
const int dataPin = 11; // Shift Register Serial Data Input Pin

LiquidCrystal_74HC595 lcd(dataPin, clockPin, latchPin, 1, 3, 4, 5, 6, 7); // Creating LCD Object From LCD Class

const int IRpin = 3; // Remote Control Sensor Pin
IRrecv IR(IRpin); // Initializing Remote Sensor
decode_results cmd; 
String myCom;

const int speedPin1 = 10; // DC Motor Pins For Speed (Analog), Direction 1 (Digital), and Direction 2 (Digital)
const int dir1 = 9;
const int dir2 = 8;

const int speedPin2 = 6;
const int dir3 = 12;
const int dir4 = 4;

int fanSpeed = 150;
bool fanOn;
int sp;

const int buzzPin = 2;

void setup() {
  Serial.begin(9600);
  IR.enableIRIn();
  lcd.begin(16, 2);
  HT.begin();
     
  pinMode(speedPin1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(speedPin2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir4, OUTPUT);

  pinMode(buzzPin, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);  
}


void loop() {
  digitalWrite(dir1, HIGH); // Setting The Directions of DC Motors
  digitalWrite(dir2, LOW);

  digitalWrite(dir3, HIGH);
  digitalWrite(dir4, LOW);

  temperature = HT.readTemperature();
  humidity = HT.readHumidity();

  while (IR.decode(&cmd)==0){  // Empty Loop Used To Wait And Receive Data From The Remote Control
  }
  delay(1500);
  IR.resume();
   
  if (cmd.value==0xFF6897){    // If Statements Used To Convert Hexadecimal Remote Button Readings To String Defintions
    myCom="zero";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF30CF){
    myCom="one";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF18E7){
    myCom="two";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF7A85){
    myCom="three";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF10EF){
    myCom="four";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF38C7){
    myCom="five";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF5AA5){
    myCom="six";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF42BD){
    myCom="seven";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF4AB5){
    myCom="eight";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF52AD){
    myCom="nine";
    Serial.println(myCom); 
  }
   
  if (cmd.value==0xFFA25D){
    myCom="pwr";
    Serial.println(myCom); 
  }
  if (cmd.value==0xFF629D){
    myCom="v+";
    Serial.println(myCom);
  }
  if (cmd.value==0xFFE21D){
    myCom="fun";
    Serial.println(myCom);
  }
  if (cmd.value==0xFF22DD){
    myCom="rew";
    Serial.println(myCom);
  }
  if (cmd.value==0xFF02FD){
    myCom="play";
    Serial.println(myCom);
  }
  if (cmd.value==0xFFC23D){
    myCom="ff";
    Serial.println(myCom);
  }
  if (cmd.value==0xFFE01F){
    myCom="dn";
    Serial.println(myCom);
  }
  if (cmd.value==0xFFA857){
    myCom="v-";
    Serial.println(myCom);
  }
  if (cmd.value==0xFF906F){
    myCom="up";
    Serial.println(myCom);
  }
  if (cmd.value==0xFF9867){
    myCom="eq";
    Serial.println(myCom);
  }
  if (cmd.value==0xFFB04F
  ){
    myCom="st";
    Serial.println(myCom);
  }

  if (myCom == "ff") {
    lcd.setCursor(0,0);
    lcd.print("HUMIDITY: ");
    lcd.print(humidity);   
    lcd.print("%"); 
  }
  if (myCom == "rew") {
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURE:");
    lcd.print(temperature);    
  }

  if (myCom == "pwr"){    // Turning Power Of Fan On With Power Button On Remote
    digitalWrite(buzzPin, HIGH);   // Activating Buzz Noise To Indicate Fan On
    delay(150);
    digitalWrite(buzzPin, LOW);
    fanOn = true;
    lcd.setCursor(0,1);
    lcd.print("FAN ON         ");
    delay(4000); 
  }  
  
  if (fanOn) {   
    if (temperature >= 26.5) {
      analogWrite(speedPin1, 170);
      analogWrite(speedPin2, 170);
      fanSpeed = 170;
    }
    if (myCom == "fun"){
      analogWrite(speedPin1, 0);
      analogWrite(speedPin2, 0);
      fanSpeed = 0;
      digitalWrite(buzzPin, HIGH); // Activating Buzz Noise To Indicate Fan Off
      delay(150);
      digitalWrite(buzzPin, LOW);
      fanOn = false;
      lcd.print("              ");
      lcd.setCursor(0,1);
      lcd.print("FAN OFF           ");
      delay(4000);

    }    
    else if (myCom == "zero"){
      analogWrite(speedPin1, 0);
      analogWrite(speedPin2, 0);
      fanSpeed = 0;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 0      ");
      delay(4000);      
    }
    else if (myCom == "one"){
      analogWrite(speedPin1, 90);
      analogWrite(speedPin2, 90);
      fanSpeed = 90;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 1      ");
      delay(4000);
    }
    else if (myCom == "two"){
      analogWrite(speedPin1, 110);
      analogWrite(speedPin2, 110);
      fanSpeed = 110;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 2      ");
      delay(4000);
    
    }
    else if (myCom == "three"){
      analogWrite(speedPin1, 130);
      analogWrite(speedPin2, 130);
      fanSpeed = 130;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 3      ");
      delay(4000);
    }
    else if (myCom == "four"){
      analogWrite(speedPin1, 150);
      analogWrite(speedPin2, 150);
      fanSpeed = 150;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 4      ");
      delay(4000);
    }
    else if (myCom == "five"){
      analogWrite(speedPin1, 170);
      analogWrite(speedPin2, 170);
      fanSpeed = 170;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 5      ");
      delay(4000);
    }
    else if (myCom == "six"){
      analogWrite(speedPin1, 190);
      analogWrite(speedPin2, 190);
      fanSpeed = 190;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 6      ");
      delay(4000);
    }
    else if (myCom == "seven"){
      analogWrite(speedPin1, 210);
      analogWrite(speedPin2, 210);
      fanSpeed = 210;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 7      ");
      delay(4000);
    }
    else if (myCom == "eight"){
      analogWrite(speedPin1, 230);
      analogWrite(speedPin2, 230);
      fanSpeed = 230;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 8      ");
      delay(4000);
    }
    else if (myCom == "nine"){
      analogWrite(speedPin1, 250);
      analogWrite(speedPin2, 250);
      fanSpeed = 250;
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: 9      ");
      delay(4000);
    }
    else if (myCom == "up"){
      fanSpeed = fanSpeed + 20;
      if (fanSpeed > 250) {
        fanSpeed = 250;
      }
      analogWrite(speedPin1, fanSpeed);
      analogWrite(speedPin2, fanSpeed);
      sp = map(fanSpeed, 90, 250, 1, 9); // Maps Analog Reading To Speed Associated With Fan Settings
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: ");
      lcd.print(sp);
      delay(4000);
    }
    else if (myCom == "dn"){
      fanSpeed = fanSpeed - 20;
      if (fanSpeed < 90) {
        fanSpeed = 0;
      }
      analogWrite(speedPin1, fanSpeed);
      analogWrite(speedPin2, fanSpeed);
      sp = map(fanSpeed, 90, 250, 1, 9);
      lcd.setCursor(0,1);
      lcd.print("  ");
      lcd.print("Fan Speed: ");
      lcd.print(sp);
      delay(4000);
    }
  
  }


}
