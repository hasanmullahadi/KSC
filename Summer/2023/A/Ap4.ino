#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// To install liblary, look up SSD1306
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
// To install liblary, look up HC_SR04
#define ECHO 2  //support interrupts
#define TRIG 9
HC_SR04<ECHO> sensor(TRIG);




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Hello from Distance"));



  initSensor();
  displayInit();
  displayWelcom();
}





void loop() {

  if (sensor.isFinished()) {
    displayWelcom();
    displayDistance();
    display.display();
    delay(250);
  }
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
  display.println("You are at");
}

void displayDistance() {

  display.setCursor(0, 16);
  display.print(sensor.getDist_cm());
  display.print("cm, ");

  sensor.startAsync(100000);
}

void initSensor() {
  sensor.beginAsync();
  sensor.startAsync(100000);
}
