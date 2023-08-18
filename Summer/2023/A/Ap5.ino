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




// define servro
#include <Servo.h>
#define SERVO_PIN 8  // attach pwm
Servo myServo;       //creating a servo object (any custom name could be used)




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(F("Hello from Distance"));

  myServo.attach(SERVO_PIN);  // sets the pin as output

  initSensor();
  displayInit();
  displayWelcom();

  myServo.write(90);
}



int angleMaxDist = 0;
int maxDist = 0;

int closestDistance = 0;  // Will store the distance of the closest object


#define SERVO_MIN_ANGLE 45
#define SERVO_MAX_ANGLE 135
#define ANGLE_INCREMENT 5


void loop() {
  int angleClosestDist = 0;  // Resetting values
  int minDist = 9999;        // Start with a high value

  // Step 1: Sweep the servo across its range
  for (int angle = SERVO_MIN_ANGLE; angle <= SERVO_MAX_ANGLE; angle += ANGLE_INCREMENT) {
    myServo.write(angle);  // Move the servo to the current angle
    delay(100);            // Allow the servo some time to move

    // Step 2: Measure the distance at this angle
    sensor.startAsync(100000);
    while (!sensor.isFinished()) {
      delay(10);  // Wait for the sensor to finish
    }
    int currentDistance = sensor.getDist_cm();

    // Update the min distance and corresponding angle if this is the shortest we've seen so far
    if (currentDistance < minDist) {
      minDist = currentDistance;
      angleClosestDist = angle;
      closestDistance = currentDistance;  // Save the distance of the closest object
    }
  }

  // Step 3 & 4: Determine which angle had the shortest distance and move the servo to that angle
  myServo.write(angleClosestDist);  // Move the servo to the angle of the closest object
  delay(300);
  // Display the closest object's distance on the OLED
  displayWelcom();
  displayDistance();
  display.display();

  delay(2000);  // Delay for a while before scanning again
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
  display.print(closestDistance);  // Display the closest distance
  display.print("cm, ");
}


void initSensor() {
  sensor.beginAsync();
  sensor.startAsync(100000);
}
