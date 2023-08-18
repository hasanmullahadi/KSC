const int ledPin = 9;
const int analogPin = A0;  // Analog input pin
unsigned long previousMillis = 0;
const long interval = 5;  
int brightness = 128;  
int targetBrightness = random(0, 255);  
int step = 3;  

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(analogPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Read the analog pin to determine the max brightness value
  int maxBrightness = analogRead(analogPin) / 4;  // Convert the range 0-1023 to 0-255

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // If current brightness is close to target, get a new target
    if (abs(targetBrightness - brightness) <= step) {
      targetBrightness = random(0, maxBrightness);
    }

    // Determine the direction to adjust brightness
    if (brightness < targetBrightness) {
      brightness += step;
      if (brightness > 255) brightness = 255;
    } else if (brightness > targetBrightness) {
      brightness -= step;
      if (brightness < 0) brightness = 0;
    }

    analogWrite(ledPin, brightness);
  }
}
