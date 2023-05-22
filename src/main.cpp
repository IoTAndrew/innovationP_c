#include <Controllino.h>
#include <SoftwareSerial.h>

String sensorstring;

#define mySerial Serial1
const byte water_level_trig_pin = 5;     // Digital 3   X1
const byte water_level_echo_pin = 6;     // Digital 4   X1

String fromPi;

long duration;
int distance;
int av_dist;
int water_level;
void waterLevel();

void setup() {

  pinMode(water_level_trig_pin, OUTPUT);
  pinMode(water_level_echo_pin, INPUT);
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
    String temp1 = "5.4";
    String temp2 = "3.3";
    String ph = "5.5";
    String hum = "50%";
    String ec = "200";
    String tds = "300";
    String orp = "-200";
    String co2 = "500";
    if (fromPi != ""){
      fromPi = mySerial.readString();
      mySerial.print("I got:");
      mySerial.println(fromPi);
    }
    else{
      ;
    }
    //sensorstring += fromPi;
    // Send sensor data back to the web app
    String response = temp1 + "&" + temp2 + "&" + ph + "&" + hum + "&" + ec + "&" + tds + "&" + orp + "&" + co2;
    //mySerial.println(response);
    waterLevel(); 
    delay(1000);
  }
  //mySerial.print(sensorstring);
}

void waterLevel(void){
    // 200 ms
    float water_level_sum = 0; // sum declaration
    for (int i=0 ; i<5 ; i++){ // 5 samples are taken
      digitalWrite(water_level_trig_pin, LOW); // Clears the water_level_trig_pin condition first
      delayMicroseconds(2);
      digitalWrite(water_level_trig_pin, HIGH); // Sets the water_level_trig_pin HIGH (ACTIVE) for 10 microseconds (time for 8 cycle sonic bursts)
      delayMicroseconds(10); 
      digitalWrite(water_level_trig_pin, LOW);
      duration = pulseIn(water_level_echo_pin, HIGH); // Reads the water_level_echo_pin, returns the sound wave travel time in microseconds
      distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      water_level_sum = water_level_sum + distance; // Sum calculation
    }
    av_dist = round(water_level_sum / 5.0); // one average value of distance in cm
    water_level = map(av_dist, 2, 22, 100, 0); // one average value of distance in % | sensor's range starts from 2 cm (fixed)
    mySerial.print("  Distance in cm: "); // prints average of 5 samples in cm
    mySerial.print(av_dist);
    mySerial.print("\t Distance in %: "); // prints average of 5 samples in %
    mySerial.println(water_level); 
}