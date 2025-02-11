
/*
        Introducing the cutting-edge AI and IoT-based vehicle monitoring system by Salman Sardar. Revolutionizing vehicle safety and management, our innovative solution combines artificial intelligence and Internet of Things technologies to offer unparalleled features. 
  From preventing accidents and detecting fuel theft to monitoring fuel consumption and ensuring driver sobriety with our drink and drive detection by AI integration, our system prioritizes safety and efficiency. With real-time tracking of vehicle location and comprehensive data analysis accessible through a secure server, supplemented by SMS alerts, our solution empowers you with full control and peace of mind over your fleet's 
  operations. Experience the future of vehicle monitoring with Salman Sardar's advanced AI and IoT solution.
  Contacts- salman151397@gmail.com;   9804*******/



  /* Install this libraries
  ********Blynk 1.3.2**************
  **********TinyGPS 13.0.3***********
  **********DHT sensor library by adafruit******
  **********LiquidCrystal I2C******************
*/
// Replace with Blynk template ID, template name, and auth token
#define BLYNK_TEMPLATE_ID "TMPL0XXXXXX"
#define BLYNK_TEMPLATE_NAME "AI DRIVEN"
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXX"

#include <DHT.h>
#include <BlynkSimpleEsp32.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

HardwareSerial neogps(0);
HardwareSerial gsm(2);

//Setup GPS and GSM
#define RXD0 3      //connect gpsModule TXD pin to GPIO 3
#define TXD0 1      //connect gpsModule RXD pin to GPIO 1
#define RXD2 16     // connect gsmModule TXD pin to GPIO 16
#define TXD2 17     // Connect gsmModule RXD pin GPIO 17


TinyGPSPlus gps;
#define BLYNK_PRINT Serial

char ssid[] = "AIDRIVEN";   //WiFi name
char pass[] = "98041513";   //WiFi Password


#define MOBILE_NUMBER "+91*********"      //Mobile Number for Receive Call and Emergency Notification
// Variable setup
int buttonState = 0;     // Current state of the button
int lastButtonState = 0; // Previous state of the button
int lcdState = 0;
unsigned long lastUpdateTime = 0;

#define alcoholPIN 39
// Setup adxl335 x, y , z pin
#define xAxis 35
#define yAxis  32
#define zAxis  33
#define buzzer 23
#define Switch1 13
#define Switch2 12
#define potPin 34
#define ldr 36 
#define greenLed 14
#define redLed 27



/**************Configure DHT11 sensor*************/
#define DHTPIN 4 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;
void switchFunction(){
  
    bool switch1Read = digitalRead(Switch1);
    if(switch1Read==HIGH){
      digitalWrite(greenLed, LOW);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(greenLed, HIGH);
       gsm.println("AT+COLP=1"); // Show caller ID
     delay(1000);
     digitalWrite(greenLed, LOW);
     digitalWrite(buzzer, LOW);


  //Make a call to the predefined mobile number
  Serial.println("Making a call...");
  gsm.print("ATD");
  gsm.print(MOBILE_NUMBER);
  gsm.println(";");
  delay(2000);
  digitalWrite(greenLed, HIGH);
    
  }
}

void setup()
{   
  pinMode(buzzer, OUTPUT);
  pinMode(Switch1, INPUT);
  pinMode(Switch2, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
  
  Serial.begin(115200);
  //Setup gsm pin 16 as RXD2 a 17 as TXD2
  neogps.begin(9600, SERIAL_8N1, RXD0, TXD0);
  gsm.begin(9600, SERIAL_8N1, RXD2, TXD2);

  lcd.begin();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("...Welcome to...");
  delay(200);
  lcd.setCursor(0, 1);
  lcd.print("....AI DRIVEN...");
    //*********0123456789012345
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
  timer.setInterval(500L, sendSensor);
  timer.setInterval(5000L, sendSensor2);
  delay(2000);
  lcd.clear();
  }

void loop()
{
 Blynk.run();
 timer.run();
 send_location();
 switchFunction();
 lcdFunction();
 }

 void lcdFunction(){
  buttonState = digitalRead(Switch2);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      lcdState++;
      if (lcdState >= 5) {
        lcdState = 0; // Reset to turn off all LEDs
      }
      //updateLCDs();
    }
    delay(50); // Debounce delay
  }
  unsigned long currentMillis = millis(); // Get the current time

  // Check if one second has elapsed since the last update
  if (currentMillis - lastUpdateTime >= 1500) {
    lastUpdateTime = currentMillis; // Update the last update time
  updateLCDs();
  }

  lastButtonState = buttonState;
}

void updateLCDs() {

    lcd.clear();
    switch (lcdState) {
      case 0:{
        int speed = analogRead(potPin);
        speed = map(speed, 0, 4095, 0, 200);
        speed = (200-speed);
        int alcoholLevel = analogRead(alcoholPIN);
        alcoholLevel = map(alcoholLevel, 0, 4095, 5, 100);
        lcd.setCursor(0,0);
        lcd.print("SPEED: ");
        lcd.print(speed);
        lcd.print(" km/h  ");
        lcd.setCursor(0,1);
        lcd.print("Alcohol Lvl: ");
        lcd.print(alcoholLevel);
        
        break;
      }
      case 1:{
        lcd.setCursor(0, 0);
        lcd.print("TEMP: ");
        lcd.print(dht.readTemperature(), 2);
        lcd.print(" C");
        lcd.setCursor(0, 1);
        lcd.print("Humitity: ");
        lcd.print(dht.readHumidity(), 2);
        lcd.print(" %");
        break;}
      case 2:{
        int x = analogRead(xAxis);
        x = map(x, 1380, 2190, 90, -90);
        int y = analogRead(yAxis);
        y = map(y, 1380, 2175, 90, -90);
        int z = analogRead(zAxis);
        z = map(z, 2160, 1360, 0, 180);
        lcd.setCursor(0,0);
        lcd.print("AXIS ");
        lcd.print(" Z: ");
        lcd.print(z);
        lcd.setCursor(0, 1);
        lcd.print(" X: ");
        lcd.print(x);
        lcd.print("    Y: ");
        lcd.print(y);
        break;}
      case 3:
       { String latitude = "22.345270"; // Initialize latitude with a default value
        String longitude = "88.463597";

        while (neogps.available() > 0) {
    if (gps.encode(neogps.read())) {
      
        if (gps.location.isValid()) {
        latitude = String(gps.location.lat(), 6);
        longitude = String(gps.location.lng(), 6);
      break;}
       }
     }
   
        lcd.setCursor(0,0);
        lcd.print("Lat: ");
        lcd.print(latitude);
        lcd.setCursor(0, 1);
        lcd.print("Long: ");
        lcd.print(longitude);
        break;
       }

        case 4:{
        int lightIntensity = analogRead(ldr);
        lightIntensity= map(lightIntensity, 0, 4095, 0, 100);
       lcd.setCursor(0, 0);
        lcd.print("...AI DRIVEN...");
        lcd.setCursor(0, 1);
        lcd.print("   Light: ");
        lcd.print(lightIntensity);
        break;
        }

      default:
        break;
    }
  
}

 


 void sendSensor2(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
   if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int speed = analogRead(potPin);       // We use a Potentiometer to change speed
        speed = map(speed, 0, 4095, 0, 200);  // Speed limit 0 to 200 km/h
        
  int y = analogRead(yAxis);
  y = map(y, 1380, 2175, -90, 90);
  int z = analogRead(zAxis);
   z= map(z, 2160, 1360, 0, 180);
    

        while (neogps.available() > 0) {
    if (gps.encode(neogps.read())) {
      
        if (gps.location.isValid()) {
        String latitude = String(gps.location.lat(), 6);
        String longitude = String(gps.location.lng(), 6);
             //  Upload Location to Blynk Server
        Blynk.virtualWrite(V7, latitude);
        Blynk.virtualWrite(V8, longitude);
      break;
         }
       }
    }
  
  Serial.print("   Temperature: ");
  Serial.print(t);
  Serial.print("   Humidity:");
  Serial.println(h);
  Serial.print("   Y: ");
  Serial.print(y);
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, z);
  Blynk.virtualWrite(V5, y);
  Blynk.virtualWrite(V9, speed);
  
  
 }

 void sendSensor(){
  // MQ06 Value
  int gasLevel = analogRead(alcoholPIN);
  gasLevel = map(gasLevel, 0, 4095, 0, 100);   // Assuming 0-100% range for gas sensor
 
    int x = analogRead(xAxis);
 
  x = map(x, 1380, 2190, -90, 90);        // Calibration minimum to maximum value maped to -90 to 90

  Serial.print("Gas: ");
  Serial.print(gasLevel);
  Serial.print("X: ");
  Serial.print(x);
  Blynk.virtualWrite(V4, x); 
  Blynk.virtualWrite(V0, gasLevel);
    }

void send_location(){

  int gasLevel = analogRead(alcoholPIN);
  gasLevel = map(gasLevel, 0, 4095, 5, 100);
  int speed = analogRead(potPin);
        speed = map(speed, 0, 4095, 0, 200);
        speed = (200-speed);
        

  if(gasLevel >= 40  && speed >= 60){
        int light = analogRead(ldr);
        light = map(light, 0, 4095, 0, 100);
        String latitude = "N/A"; // Initialize latitude with a default value
        String longitude = "N/A"; // Initialize longitude with a default value
 // String altitude= "N/A";
  int year, day, month, hour, minute, seconds; 

      while (neogps.available() > 0) {
    if (gps.encode(neogps.read())) {
      
        if (gps.location.isValid()) {
          digitalWrite(redLed, LOW);
        latitude = String(gps.location.lat(), 6);
        longitude = String(gps.location.lng(), 6);
        year = gps.date.year();
        month = gps.date.month();
        day = gps.date.day();
        hour = (gps.time.hour() + 5); // Indiam time zone 5.30
        minute = (gps.time.minute() + 30);
        seconds = gps.time.second();

  if (minute >= 60) {
  minute -= 60;
  hour += 1;
}
if (hour >= 24){
  hour -= 24;
  day +=1;
}
      break;
       
     }
   }

    Serial.println("Gas Level is High, Sending sms");
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLed, LOW);
  gsm.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  digitalWrite(buzzer, LOW);
  digitalWrite(greenLed, HIGH);
  gsm.print("AT+CMGS=\"mobileNumber\"\r"); // Replace with phone number
  delay(1000);
  digitalWrite(buzzer, HIGH);
  digitalWrite(greenLed, LOW);
  gsm.print("Hi Salman, Detect Drink and Drive");
  gsm.print(" at speed :");
  gsm.print(speed);
  gsm.print(", Alcohol Level :");
  gsm.print(gasLevel);
  gsm.print(", Light Intensity : ");
  gsm.print(light);
  gsm.print(", Timestamps: ");
  gsm.print(hour);
  gsm.print(":");
  gsm.print(minute);
  gsm.print(":");
  gsm.print(seconds);
  gsm.print(" . Date :");
  gsm.print(day);
  gsm.print("/");
  gsm.print(month);
  gsm.print("/");
  gsm.print(year);
  gsm.print(". Please supervise your driver, Thank you.");
  gsm.write(" Vehicle Location is- ");
  gsm.write("https://www.google.com/maps/@");
  gsm.print(latitude);
  gsm.print(",");
  gsm.print(longitude);
  gsm.print(",16.34z?entry=ttu");
  gsm.write(26); // End of message character
  delay(1000);
    digitalWrite(buzzer, LOW);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
  


}

BLYNK_WRITE(V6) {
  bool m = param.asInt();
if (m == HIGH){
  lcd.noBacklight();
  }
  else
  lcd.backlight();
}
