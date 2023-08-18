// Define pin connections
const int irPin = 10;
const int activeLedPin = 13;
const int inactiveLedPin = 12;

void setup() {
  pinMode(irPin, INPUT);          // Set the IR sensor pin as input
  pinMode(activeLedPin, OUTPUT);  // Set the active LED pin as output
  pinMode(inactiveLedPin, OUTPUT); // Set the inactive LED pin as output
}

void loop() {
  int irValue = digitalRead(irPin); // Read the value from the IR sensor

  // If IR sensor detects an object, it usually sends LOW (depending on the type of sensor, some might send HIGH)
  if (irValue == LOW) {
    digitalWrite(activeLedPin, HIGH);   // Turn the active LED on
    digitalWrite(inactiveLedPin, LOW);  // Turn the inactive LED off
  } else {
    digitalWrite(activeLedPin, LOW);    // Turn the active LED off
    digitalWrite(inactiveLedPin, HIGH); // Turn the inactive LED on
  }
}
