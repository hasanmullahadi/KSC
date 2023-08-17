#include <dht.h>

#define DHT11_PIN 7    // Define which pin the DHT11 is connected to. You can change this as needed.


dht DHT;

void setup() {
  Serial.begin(9600);
 
}

void loop() {
  // Wait a few seconds between measurements.
  delay(500);
  int chk = DHT.read11(DHT11_PIN);


  Serial.print("T: ");
  Serial.print(DHT.temperature);
  Serial.print("C, H: ");
  Serial.print(DHT.humidity);
  Serial.println("%");

  

  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.println(DHT.humidity);
  


}
