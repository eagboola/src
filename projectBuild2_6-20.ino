// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_VL53L0X.h>

/*
 * Project projectBuild
 * Description:
 * Author: Ekerin M.A.
 * Date: start.6/15/2017
 * Components
    Adafruit:
      - VL53L0X, Time of Flight Distance Sensor
        - library added
      - SPW2430, MEMS Microphone Breakout
      - Neopixels
        - library added
    Amazon:
      - Amazon Dot with Alexa Capabilites
 */

#define VL53L0X_LOG_ENABLE 0
uint32_t _trace_evel = TRACE_LEVEL_ALL;

#if defined(PARTICLE) && (SYSTEM_VERSION >= 0x00060000)
SerialLogHandler logHandler(LOG_LEVEL_ALL);
#endif

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int distVal = 0;

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 1
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
//int analogVal = 0;
// in this, analogVal is the distance from the distVal
int distValMapped = 0;
// in this, analogValMapped is the distVal mapped to the neopixel range
int counter = 0;
// Prototypes for local build, ok to leave in for Build IDE




// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Serial.begin(115200);

  Serial.println("Adafruit VL53L0X test");

  if  (!lox.begin())  {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
  Particle.variable("sensor", distVal);


  strip.begin();
  strip.show();


}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  strip.setPixelColor(1, 0, 255, 0);


  VL53L0X_RangingMeasurementData_t measure;

  Serial.print("Reading a measurement...");
  lox.rangingTest(&measure, true);  // pass in 'true' to et debug in data printout

  distVal = measure.RangeMilliMeter;
  //distVal= constrain(distVal, 10, 900);


  /*if(measure.RangeMilliMeter < 10)  {
    distVal = 0;
    strip.setBrightness
  }
  */

/*  if(measure.RangeMilliMeter > 900){
    distVal = 900;
    strip.setBrightness(0);
  }
  */


  if (distVal < 900)  {
    Serial.println("Distance (mm): " + measure.RangeMilliMeter);    //Serial.println(measure.RangeMilliMeter);
    Particle.publish("distance", String(distVal));
    strip.setBrightness(distVal);
  }

  else {
    Serial.println("No subject(s) witin range");
    Particle.publish("No subject(s) within range");
    strip.setBrightness(0);
  }

  //distValMapped = map(distVal, 0, 900, 255, 5);
  Serial.println("distance: " + String(distVal)); //Serial.println( String(distVal));
  Serial.println("seconds: "  + String(Time.second())); //Serial.println(millis());
  //strip.setBrightness(distValMapped);
  Particle.publish("mapped distance value", distValMapped);

  Serial.println("brightness: " + String(strip.getBrightness())); //Serial.println(String(strip.getBrightness()));





  delay(10);

}
