#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// ultrasonic sensor
#include <Arduino.h>
#include <HC_SR04.h>

#define ECHO 2  //support interrupts
#define TRIG 9
HC_SR04<ECHO> sensor(TRIG);

// DHT sensor
#include <dht.h>

dht DHT;

#define DHT11_PIN 7

// define servro
#include <Servo.h>
#define SERVO_PIN 8  // attach pwm
Servo myServo;       //creating a servo object (any custom name could be used)


#define LEDGREEN 12
#define LEDRED 13

#define MOTION 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Hello from Plant Buddy"));

  myServo.attach(SERVO_PIN);  // sets the pin as output

  initSensor();
  displayInit();
  displayWelcom();
}
float pos = 90;
float start = 90;
float incStart = 3.75;
float inc = 3.75;
int distance1 = 0;  // vertical distance at 90 deggrees
int distance2 = 0;
int mult = 16;

float Height = 0;
float distMeasur = 0.0;
int startMeasure = 0;
#define SensroHeight 6;

#define PI 3.14159265

double degreesToRadians(double degrees) {
  return degrees * PI / 180.0;
}



void loop() {


  displayWelcom();
  // displayDistance();
  displayHT();
  display.display();
  delay(100);


  if (digitalRead(MOTION)) {
    digitalWrite(LEDRED, 1);
    digitalWrite(LEDGREEN, 0);

    Serial.println("<<<<<<<<<<<<<<<<<<Motion Detected>>>>>>>>>>>>>>>>>>>>>>>>");
    startMeasure = 1;

  } else {
    digitalWrite(LEDGREEN, 1);
    digitalWrite(LEDRED, 0);
  }

  // if (pos >=(incStart*mult+start))
  // {
  //   inc = -1*incStart;
  // }

  // if (pos <=start )
  // {
  //   inc = incStart;
  // }
  if (startMeasure)
    Measure();
}



void Measure() {

  myServo.write(pos);

  if (sensor.isFinished()) {
    Serial.print("Dist: ");
    distMeasur = sensor.getDist_cm();
    Serial.print(sensor.getDist_cm());
    Serial.print(" cm, ");

    Serial.print("Angle: ");
    Serial.print(pos);
    Serial.println(" deg");

    displayDistance();

    if (pos == start) {
      distance1 = distMeasur;
      distance2 = distMeasur;
    }



    //Serial.println(F("Disance: %s",));
    if (distMeasur >= distance2* 1.25  && pos !=start)  // now we should stop the test
    {


      Serial.print("Height: ");
      Height = sin(degreesToRadians(pos)) * distance2 + SensroHeight;
      Serial.print(Height);
      Serial.println(" cm");


      Serial.print("Vertical Distance: ");
      Serial.print(distance1);
      Serial.println(" cm");
      startMeasure = 0;

      pos = start;
      inc = incStart;
      myServo.write(start);

      displayWelcom();
      displayHeight(Height,distance1);
      displayHT();
      display.display();
      delay(100);

    }

    distance2 = distMeasur;

    sensor.startAsync(100000);
    pos += inc;
  }

  if (pos >= (incStart * mult + start)) {
    // inc = -1*incStart; then we stop here
    startMeasure = 0;
    pos = start;
    inc = incStart;
  }
}


void initMotion() {

  pinMode(MOTION, INPUT);
}


void initLED() {
  pinMode(LEDGREEN, OUTPUT);
  pinMode(LEDRED, OUTPUT);
}


void displayInit() {
  Serial.println(F("Start to init LCD"));

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }



  display.display();  // the library initializes this with an Adafruit splash screen.
  delay(2000);        // Pause for 2 seconds

  display.clearDisplay();
  Serial.println(F("End init LCD"));
}

void displayWelcom() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.println("Plant Love");

  //display.display();
  //delay(2000);
}

void initSensor() {
  sensor.beginAsync();
  sensor.startAsync(100000);
}


void displayDistance() {

  display.setCursor(0, 16);
  display.print(sensor.getDist_cm());
  display.print("cm, ");
}


void displayHeight(float h, float d) {

  display.setCursor(0, 16);
  display.print("H:");
  display.print(h);
  display.print("cm,");
  display.print(d);
  display.print("cm");
}




void displayHT() {
  int chk = DHT.read11(DHT11_PIN);
  display.setCursor(0, 32);

  display.print("T: ");
  display.print(DHT.temperature);
  display.print("C, H: ");
  display.print(DHT.humidity);
  display.println("%");

  delay(500);
}
