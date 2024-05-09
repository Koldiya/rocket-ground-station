
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "EBYTE.h"
#define PIN_RX 10
#define PIN_TX 11
#define PIN_M0 6
#define PIN_M1 5
#define PIN_AX 4

#include <Wire.h>
#include <MS5611.h>

MS5611 ms5611;

unsigned char packetBytes[78];
struct DATA {
  float YawAngle;
  float PitchAngle;
  float RollAngle;
  float enlem;
  float boylam;
  float gps_irtifa;
  float irtifa;
  float ivme_x_send;
  float ivme_y_send;
  float ivme_z_send;

};

int Chan;
DATA MyData;

struct Orientation {
  float YawAngle;
  float PitchAngle;
  float RollAngle;
  float ivme_x;
  float ivme_y;
  float ivme_z;
};

struct IMU_Values {
  bool Error;
  bool NewDataAvailable;
  unsigned long DeltaTime;
  struct Orientation CurrentOrientation;
};

float gyro_pitch = 0;
float gyro_rol = 0;
float gyro_yaw = 0;

int16_t ax, ay, az;

float enlem =0;
float boylam =0;
float irtifa=0;
float gercek_irtifa=0;
SoftwareSerial ESerial(PIN_RX, PIN_TX);

EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);
// Choose two Arduino pins to use for software serial
int RXPin = 8;
int TXPin = 9;

int GPSBaud = 9600;
float gps_irtifa = 0;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);
int sayac = 0;
double gps_zaman = 0;

float sicaklik = 0;
long basinc = 0;
float baslangic_metre_deger = 0;

void setup() 
{
  Serial.begin(19200);
  ESerial.begin(9600);
  gpsSerial.begin(9600);

  while(!ms5611.begin(MS5611_ULTRA_HIGH_RES))
  {
    delay(500);
  }

  delay(500);
  // this init will set the pinModes for you
  Transceiver.init();
  delay(500);
  initializeIMU();
  delay(500);
  Transceiver.PrintParameters();
  delay(500);
  barometre_baslangic_deger();
  delay(500);
}

void loop() 
{ 
  displayInfo();
      
      
//delay(1000);
  struct IMU_Values imuValues = GetIMU_Values();
  gyro_pitch = imuValues.CurrentOrientation.PitchAngle;
  gyro_rol = imuValues.CurrentOrientation.RollAngle;
  gyro_yaw = imuValues.CurrentOrientation.YawAngle;
//delay(1000);
  barometre_oku();
//delay(1000);
   veri_yolla();
   //delay(100);
}

void veri_yolla()
{
    MyData.YawAngle = gyro_yaw;
    MyData.PitchAngle = gyro_pitch;
    MyData.RollAngle = gyro_rol;
    MyData.enlem = enlem;
    MyData.boylam = boylam;
    MyData.irtifa = gercek_irtifa;
    MyData.gps_irtifa = gps_irtifa;
    MyData.ivme_x_send = ax;
    MyData.ivme_y_send = ay;
    MyData.ivme_z_send = az;
  Transceiver.SendStruct(&MyData, sizeof(MyData));
  delay(100);

}
