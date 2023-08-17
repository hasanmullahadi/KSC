const int ledPin = 9;
unsigned long previousMillis = 0;
const long interval = 5;  // Time between brightness adjustments. Decreased for faster transitions.
int brightness = 128;  // Initial brightness
int targetBrightness = random(80, 255);  // Decreased minimum value for stronger effect.
int step = 3;  // Increase the step value for more noticeable changes.

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // If current brightness is close to target, get a new target
    if (abs(targetBrightness - brightness) <= step) {
      targetBrightness = random(80, 255);  // Adjust range for stronger effect.
    }

    // Determine the direction to adjust brightness
    if (brightness < targetBrightness) {
      brightness += step;
      if (brightness > 255) brightness = 255;  // Ensure brightness doesn't exceed max value.
    } else if (brightness > targetBrightness) {
      brightness -= step;
      if (brightness < 0) brightness = 0;  // Ensure brightness doesn't go below min value.
    }

    analogWrite(ledPin, brightness);
  }
}
