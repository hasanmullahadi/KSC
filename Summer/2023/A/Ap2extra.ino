const int ledPins[] = {9, 10, 11};
const int analogPin = A0;
const int numLEDs = 3;

unsigned long previousMillis = 0;
const long interval = 5;

int brightness[numLEDs];
int targetBrightness[numLEDs];
int step = 3;

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    brightness[i] = 0;
    targetBrightness[i] = 0;
  }
  pinMode(analogPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read the analog pin to determine flame height
  int flameHeight = analogRead(analogPin) / 4;  // Convert 0-1023 range to 0-255

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    for (int i = 0; i < numLEDs; i++) {
      // Decide the brightness range based on flameHeight and LED position
      int maxBrightness = (flameHeight / numLEDs) * (i + 1);

      // Update target brightness for each LED
      if (abs(targetBrightness[i] - brightness[i]) <= step) {
        targetBrightness[i] = random(maxBrightness / 2, maxBrightness);
      }

      // Adjust the brightness of each LED towards the target
      if (brightness[i] < targetBrightness[i]) {
        brightness[i] += step;
        if (brightness[i] > 255) brightness[i] = 255;
      } else if (brightness[i] > targetBrightness[i]) {
        brightness[i] -= step;
        if (brightness[i] < 0) brightness[i] = 0;
      }

      // Write to the LED
      analogWrite(ledPins[i], brightness[i]);
    }
  }
}
