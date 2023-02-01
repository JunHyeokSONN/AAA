# 1 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino"
# 2 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino" 2
# 3 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino" 2
# 4 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\US_OLED_PIR.ino" 2

// Set the OLED display dimensions



// Set the I2C address of the OLED display


Adafruit_SSD1306 display(128, 64, &Wire, 0x3C);

int trig = 3;
int echo = 2;
int sensorPin = 4;
int ledPin = 7;
int sensor = 0x0;
int prev_state = 0x0;
unsigned long detection_time = 0;
unsigned long update_time = 0;
const int DETECTION_PERIOD = 5200;
const int UPDATE_PERIOD = 200;

float duration;
float distance;

void setup() {
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);

    // Initialize the OLED display
    display.begin(0x02 /*|< Gen. display voltage from 3.3V*/, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(1 /*|< Draw 'on' pixels*/ /*|< Draw 'on' pixels*/);
    display.setCursor(0, 0);
    display.println("Distance (cm):");

    // Set the pin modes of the ultrasonic sensor pins
    pinMode(trig, 0x1);
    pinMode(echo, 0x0);

    pinMode(ledPin, 0x1);

    // Set the pin mode of the PIR sensor pin
    pinMode(sensorPin, 0x0);
}

void loop() {
    // Read the ultrasonic sensor
    digitalWrite(trig, 0x0);
    delayMicroseconds(2);
    digitalWrite(trig, 0x1);
    delayMicroseconds(10);
    digitalWrite(trig, 0x0);
    duration = pulseIn(echo, 0x1);
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
        if (distance < 15 && sensor == 0x1){
            display.print("Dangerous");
            pinMode(ledPin, 0x1);
            digitalWrite(ledPin, 0x0);
        }else{
            display.print("Non-Hazardous");
            digitalWrite(ledPin, 0x1);
        }
        if(sensor == 0x1){
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
# 1 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\test_ar.ino"
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
# 25 "c:\\Users\\JunHyeok\\AAAA\\AAA-2\\Arduino\\test_ar.ino"
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, 0x1);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, 0x1); // turn the LED on (HIGH is the voltage level)
  delay(1000); // wait for a second
  digitalWrite(13, 0x0); // turn the LED off by making the voltage LOW
  delay(1000); // wait for a second
}
