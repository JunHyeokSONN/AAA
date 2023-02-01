#include <Arduino.h>
#line 1 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Set the OLED display dimensions
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 64

// Set the I2C address of the OLED display
#define OLED_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(OLED_DISPLAY_WIDTH, OLED_DISPLAY_HEIGHT, &Wire, OLED_I2C_ADDRESS);

int trig = 3;
int echo = 2;
int sensorPin = 4;
int ledPin = 7;
int sensor = LOW;
int prev_state = LOW;
unsigned long detection_time = 0;
unsigned long update_time = 0;
const int DETECTION_PERIOD = 5200;
const int UPDATE_PERIOD = 200;

float duration;
float distance;

#line 28 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino"
void setup();
#line 50 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino"
void loop();
#line 28 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino"
void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);
  
    // Initialize the OLED display
    display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Distance (cm):");
  
    // Set the pin modes of the ultrasonic sensor pins
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    pinMode(ledPin, OUTPUT);
  
    // Set the pin mode of the PIR sensor pin
    pinMode(sensorPin, INPUT);
}

void loop() {
    // Read the ultrasonic sensor
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = (duration / 2) / 29.1;
    
    // Continuously read the PIR sensor
    sensor = digitalRead(sensorPin);

    if (millis() - detection_time > DETECTION_PERIOD) {
        detection_time = millis();
        if (sensor != prev_state) {
            prev_state = sensor;
        }
    }

    if (millis() - update_time > UPDATE_PERIOD) {
        update_time = millis();
        display.clearDisplay();
        display.setCursor(10, 5);
        display.println("Distance (cm):");
        display.setCursor(10, 21);
        display.print(distance);
        display.println(" cm");
        display.setCursor(10, 37);
        if (distance < 15 && sensor == HIGH){            
            display.print("Dangerous");
            pinMode(ledPin, OUTPUT);
            digitalWrite(ledPin, LOW);
        }else{
            display.print("Non-Hazardous");
            digitalWrite(ledPin, HIGH);
        }
        if(sensor == HIGH){
            display.setCursor(10, 53);
            display.println("PIR : Detection");
        }
        else{
            display.setCursor(10, 53);
            display.println("PIR : Non-Detection");
        }
        display.display();
    }
}
#line 1 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\test_2.ino"
/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
}

#line 1 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\test_ar.ino"

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);   
  // wait for a second
  delay(100);                       
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);    
  // wait for a second
  delay(100);                       
}
