#include <Controllino.h>
#include <SoftwareSerial.h>
#include <Ultrasonic.h>

String sensorstring;

#define mySerial Serial1
//const byte water_level_trig_pin = 5;     // Digital 3   X1
//const byte water_level_echo_pin = 6;     // Digital 4   X1

Ultrasonic ultrasonic(6);

String fromPi;

long duration;
int distance;
int av_dist;
int water_level;
int waterLevel();

void setup() {

  //pinMode(water_level_trig_pin, OUTPUT);
  //pinMode(water_level_echo_pin, INPUT);

  // put your setup code here, to run once:
  Serial.begin(19200);
  mySerial.begin(19200);
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
    String wlvl = String(waterLevel());
    String ph = "2";
    String h2O2 = "3";
    String co = "4";
    String wtemp1 = "5";
    String ec = "6";
    String atemp1 = "7";
    String rh1 = "8";
    String wtemp2 = "9";
    String orp = "10";
    String atemp2 = "-11";
    String rh2 = "12";

    if (fromPi != ""){
      fromPi = mySerial.readString();
      //mySerial.print("I got:");
      //mySerial.println(fromPi);
    }
    else{
      ;
    }
    //sensorstring += fromPi;
    // Send sensor data back to the web app
    String response = wlvl + "&" + ph + "&" + h2O2 + "&" + co + "&" + wtemp1 + "&" + ec + "&" + atemp1 + "&" + 
    rh1 + "&" + wtemp2 + "&" + orp + "&" + atemp2 + "&" + rh2;
    mySerial.println(response);
    //waterLevel(); 
  }
  //mySerial.print(sensorstring);
}

int waterLevel(){
    // 200 ms
    float water_level_sum = 0; // sum declaration
    for (int i=0 ; i<5 ; i++){ // 5 samples are taken
    /*
      digitalWrite(water_level_trig_pin, LOW); // Clears the water_level_trig_pin condition first
      delayMicroseconds(2);
      digitalWrite(water_level_trig_pin, HIGH); // Sets the water_level_trig_pin HIGH (ACTIVE) for 10 microseconds (time for 8 cycle sonic bursts)
      delayMicroseconds(10); 
      digitalWrite(water_level_trig_pin, LOW);
      duration = pulseIn(water_level_echo_pin, HIGH); // Reads the water_level_echo_pin, returns the sound wave travel time in microseconds
      distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      water_level_sum = water_level_sum + distance; // Sum calculation
      */
    distance = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    water_level_sum = water_level_sum + distance;
    }
    av_dist = round(water_level_sum / 5.0); // one average value of distance in cm
    water_level = map(av_dist, 2, 230, 100, 0); // one average value of distance in % | sensor"s range starts from 2 cm (fixed)
    //mySerial.print("  Distance in cm: "); // prints average of 5 samples in cm
    //mySerial.println(av_dist);
    //mySerial.print("\t Distance in %: "); // prints average of 5 samples in %
    return water_level; 
}