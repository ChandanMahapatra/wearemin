// This #include statement was automatically added by the Particle IDE.

#include "SparkFunLSM9DS1/SparkFunLSM9DS1.h"

/*****************************************************************
LSM9DS1_Basic_I2C.ino
SFE_LSM9DS1 Library Simple Example Code - I2C Interface
Jim Lindblom @ SparkFun Electronics
Original Creation Date: April 30, 2015
https://github.com/sparkfun/SparkFun_LSM9DS1_Particle_Library
The LSM9DS1 is a versatile 9DOF sensor. It has a built-in
accelerometer, gyroscope, and magnetometer. Very cool! Plus it
functions over either SPI or I2C.
This Photon sketch is a demo of the simple side of the
SFE_LSM9DS1 library. It'll demo the following:
* How to create a LSM9DS1 object, using a constructor (global
  variables section).
* How to use the begin() function of the LSM9DS1 class.
* How to read the gyroscope, accelerometer, and magnetometer
  using the readGryo(), readAccel(), readMag() functions and 
  the gx, gy, gz, ax, ay, az, mx, my, and mz variables.
* How to calculate actual acceleration, rotation speed, 
  magnetic field strength using the calcAccel(), calcGyro() 
  and calcMag() functions.
* How to use the data from the LSM9DS1 to calculate 
  orientation and heading.
Hardware setup: This library supports communicating with the
LSM9DS1 over either I2C or SPI. This example demonstrates how
to use I2C. 
If you have the Photon IMU shield, no extra wiring is required.
If you're using a breakout, the pin-out is as follows:
    LSM9DS1 --------- Photon
     SCL -------------- D1 (SCL)
     SDA -------------- D0 (SDA)
     VDD ------------- 3.3V
     GND ------------- GND
(CSG, CSXM, SDOG, and SDOXM should all be pulled high. 
Jumpers on the breakout board will do this for you.)
Development environment specifics:
    IDE: Particle Build
    Hardware Platform: Particle Photon
                       SparkFun Photon IMU Shield
This code is released under the MIT license.
Distributed as-is; no warranty is given.
*****************************************************************/
#include "SparkFunLSM9DS1/SparkFunLSM9DS1.h"
#include "math.h"
//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////
// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;
///////////////////////
// Example I2C Setup //
///////////////////////
// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M   0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW
////////////////////////////
// Sketch Output Settings //
////////////////////////////
#define PRINT_CALCULATED
//#define PRINT_RAW
#define PRINT_SPEED 250 // 250 ms between prints
// Earth's magnetic field varies by location. Add or subtract 
// a declination to get a more accurate heading. Calculate 
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination

#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

int prox = A0;
int state = 0;
int dist = 0;
int x = 0;
int speakerPin = D2; //The speaker output pin
unsigned long lastTime = 0UL; //For publishing data
char publishNote[64];
void setup() 
{
  Serial.begin(115200);
  // Before initializing the IMU, there are a few settings
  // we may need to adjust. Use the settings struct to set
  // the device's communication mode and addresses:
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  // The above lines will only take effect AFTER calling
  // imu.begin(), which verifies communication with the IMU
  // and turns it on.
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1)
      ;
  }
  pinMode(speakerPin, OUTPUT);
  pinMode(prox,INPUT_PULLDOWN);
}
void loop()
{
    printValues();
    Serial.println();
    //playSound();
    delay(PRINT_SPEED);
}
void printValues()
{
    float limitp=80.0f,limitr=80.0f;//limits for the pitch and roll
    imu.readAccel();//read the values from accelerometer
    //float roll = atan2(imu.ay, imu.az);//calculate roll
    float pitch = atan2(-imu.ax, sqrt(imu.ay * imu.ay + imu.az * imu.az));//calculate pitch
    
      //char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};
  
  
    dist = analogRead(prox)/16;
    // Convert everything from radians to degrees:
    pitch *= 180.0 / M_PI;
    //roll  *= 180.0 / M_PI;
    //limit the values
    pitch=(pitch>limitp)?limitp:((pitch<-limitp)?-limitp:pitch);
    //roll=(roll>limitr)?limitr:((roll<-limitr)?-limitr:roll);
    pitch+=limitp;
    pitch*=2;
    //roll+=limitr;
    //print the values
    Serial.println("g  g a  g c b");
    //For Testing
    
    Serial.println("C b a g f e d c ");
    //Serial.print("Tone: ");
    Serial.print("Pitch ");
    Serial.println(pitch, 2);
  
        
    if (pitch>80.0f && pitch<100.0f)     
    {
         x=262;//tone(speakerPin, 262, 0);
         Serial.println("c");
             // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>50UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"262");
        Spark.publish("Notes",publishNote);
    }
    
    }
    else if(pitch>=100.0f && pitch<120.0f) 
    {
     x=294;//tone(speakerPin, 294, 0);
        Serial.println("d");
         // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>50UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"294");
        Spark.publish("Notes",publishNote);
    }
    
    }
    else if(pitch>=120.0f && pitch<140.0f) 
    {
     x=330;//tone(speakerPin, 330, 0);
        Serial.println("e");
              // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>50UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"330");
        Spark.publish("Notes",publishNote);
    }
    
    }
    else if(pitch>=140.0f && pitch<160.0f) 
    {
     x=349;//tone(speakerPin, 349, 0);
      Serial.println("f");
               // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>50UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"349");
        Spark.publish("Notes",publishNote);
    }
    
    }
    else if(pitch>=160.0f && pitch<180.0f) 
    {
     x=392;//tone(speakerPin, 392, 0);
        Serial.println("g");
              // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>50UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"392");
        Spark.publish("Notes",publishNote);
    }
    
    }
    else if(pitch>=180.0f && pitch<200.0f) 
    {
     x=440;//tone(speakerPin, 440, 0);
     Serial.println("a");
              // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>50UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"440");
        Spark.publish("Notes",publishNote);
    }
    
    }
    else if(pitch>=200.0f && pitch<220.0f) 
    {
        x=494;
     //tone(speakerPin, 494, 0);
     Serial.println("b");
              // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>50UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"494");
        Spark.publish("Notes",publishNote);
    }
    
    }
    else if(pitch>=220.0f && pitch<240.0f) 
    {
     x=523;//tone(speakerPin, 523, 0);
        Serial.println("C");
                // For Publishing Data
     unsigned long now = millis();
    if (now-lastTime>350UL) {
        lastTime = now;
        // now is in milliseconds
        sprintf(publishNote,"523");
        Spark.publish("Notes",publishNote); 
    }
    
    }
    else
    {
        noTone(speakerPin);
    }
    if((digitalRead(prox)==HIGH))//&&(state==0))
    {
        Serial.println("State Change");
        state=1;
        tone(speakerPin,x, 0);
        delay(200);
    }
    else
    {
        noTone(speakerPin);
    }
    
}