#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// to install liblary, look up SSD1306
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#include <dht.h>
// to install liblary, look up dhtlib
#define DHT11_PIN 7  // Define which pin the DHT11 is connected to. You can change this as needed.
dht DHT;


// define servro
#include <Servo.h>
#define SERVO_PIN 8  // attach pwm
Servo myServo;       //creating a servo object (any custom name could be used)

int g_Nodding = 0;




// put your name here:
String g_Name = "Fatmah";

void setup() {
  Serial.begin(9600);
  displayInit();
  myServo.attach(SERVO_PIN);  // sets the pin as output
  
} // end of setup

void loop() {
  // Wait a few seconds between measurements.

  int chk = DHT.read11(DHT11_PIN);






  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.println(DHT.humidity);

  displayHT();

  if (DHT.humidity >= 40) {
    NoddingBird();
  }


}//end of loop


void displayHT() {
  int chk = DHT.read11(DHT11_PIN);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);

  display.print("Hi ");
  display.println(g_Name);

  display.setCursor(0, 32);

  display.print("T: ");
  display.print(DHT.temperature);
  display.print("C,H: ");
  display.print(DHT.humidity);
  display.println("%");
  display.display();
  delay(500);

  display.clearDisplay();
}

void NoddingBird() {
  int start = 90;
  int end = 120;

  g_Nodding = 1;
  for (int pos = start; pos <= end; pos += 10) {
    myServo.write(pos);
    delay(100);
  }

  for (int pos = end; pos >= start; pos -= 10) {
    myServo.write(pos);
    delay(100);
  }
  g_Nodding = 0;
}

void displayInit() {


  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.display();  // the library initializes this with an Adafruit splash screen.
  delay(2000);        // Pause for 2 seconds

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
}
