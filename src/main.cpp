#include <Controllino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    String fromPi = Serial.readString();
    Serial.print("I got:");
    Serial.println(fromPi);
    
    // Simulating sensor data for testing
    String temp1 = "5.4";
    String temp2 = "3.3";
    String ph = "5.5";
    String hum = "50%";
    String ec = "200";
    String tds = "300";
    String orp = "-200";
    String co2 = "500";
    
    // Send sensor data back to the web app
    String response = temp1 + "&" + temp2 + "&" + ph + "&" + hum + "&" + ec + "&" + tds + "&" + orp + "&" + co2;
    Serial.println(response);
  }
}
