#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_G/FX.h>
//#include <Adafruit_SSD1306.h>
#define CommonSenseMetricSystem
//#define ImperialNonsenseSystem
#define trigPin 7
#define echoPin 8
#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  //pinMode(13, OUTPUT);
 
  Serial.println(F("Initailizing System..."));
  delay(500);
  Serial.println("Press 'a' to Measure Temperature. Press 'b' to Measure Distance. Press 'c' to STOP the System"); // prompt user input
  
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//  display.clearDisplay();
}

void loop() {
  float tempSens = 0.0;
  float avgDiff = 2.61;
  if (Serial.available() > 0) { 
    String input = Serial.readString();
    if (input.compareTo("a\n") == 0) {
      Serial.print("\tInput was 'a'.\n");
      Serial.print("\tMeasuring Temperature\n");
       for(int i = 0; i < 25; i++){

        delay(2000);
        //float h = dht.readHumidity();
        float t = dht.readTemperature();
        float f = dht.readTemperature(true);
        if (/*isnan(h) ||*/ isnan(t) || isnan(f)) {
          Serial.println(F("Failed to read from DHT sensor!"));
          return;
        }
        
        //Serial.print(F(" Humidity: "));
        //Serial.print(h);
        
        Serial.print(F(" Temperature: "));
        Serial.print(t + avgDiff);
        //Serial.print(t);
        Serial.print(F("C "));
        Serial.print("\n");
        tempSens = tempSens + t + avgDiff; 
      }  
      Serial.print(F("Average Temperature : "));
      Serial.print(tempSens/25);
      Serial.print(F("C \n"));    
    }
    
    else if (input.compareTo("b\n") == 0) {
      Serial.print("\tInput was 'b'.\n");
        Serial.print("\t\nTurning Ultrasonic Sensor on.\n"); 
         /*for(int i = 0; i < 40; i++)*/ while (Serial.available() == 0) {
          long duration, distance;
          digitalWrite(trigPin, LOW);
          delayMicroseconds(2); 
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10); 
          digitalWrite(trigPin, LOW);
          
          duration = pulseIn(echoPin, HIGH);
          
          #ifdef CommonSenseMetricSystem
          distance = (duration/2) / 29.1;
          #endif
          //#ifdef ImperialNonsenseSystem
          //distance = (duration/2) / 73.914;
          //#endif
        
//          display.setCursor(25,10);
//          display.setTextSize(2);
//          display.setTextColor(WHITE);
//          display.println(distance);
//          display.setCursor(80,10);
//          display.setTextSize(2);
          #ifdef CommonSenseMetricSystem
//          display.println("cm");
          #endif
//          //#ifdef ImperialNonsenseSystem
//          //display.println("in");
//          //#endif
//          display.display();
          delay(500);
//          display.clearDisplay();
          Serial.print("Distance : ");
          Serial.print(distance);
          Serial.print(" cm");
          Serial.print("\n");
      }
    }  

    else if (input.compareTo("c\n") == 0) {
      Serial.print("\tInput was 'c'.\n");
        Serial.print("\t\nTurning Temperature and Ultrasonic Sensor off.\n"); 
    }
 
    else {
      Serial.print("\t\nInput not recognized.\n\tPlease try again.\n");
    }
    Serial.print("Press 'a' to Measure Temperature . Press 'b' to Measure Distance. Press 'c' to STOP the System"); // restate the user prompt
  }
}
