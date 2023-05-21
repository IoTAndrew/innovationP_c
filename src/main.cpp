#include <Controllino.h>
#include <SoftwareSerial.h>

String sensorstring;

#define mySerial Serial1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  sensorstring.reserve(50);
  
  while (!Serial) {
    ;
  }

  while (!mySerial) {
    ;
  }
}

void loop() {
  if (mySerial.available() > 0){
  // put your main code here, to run repeatedly: //probably switching to gpio

  
    String fromPi = (String)mySerial.readString(); //probably wrong format
    mySerial.print("I got:");
    mySerial.println(fromPi); //try displaying char array

    sensorstring += fromPi;
    
    
    
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
    //mySerial.println(response);
    delay(1000);
  }
  mySerial.print(sensorstring);
}
