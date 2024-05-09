
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "EBYTE.h"
unsigned char packetBytes[78];
#define PIN_RX 2
#define PIN_TX 3
#define PIN_M0 6
#define PIN_M1 5
#define PIN_AX 4
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
unsigned long Last;
struct Orientation {
  float YawAngle;
  float PitchAngle;
  float RollAngle;
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

float enlem =0;
float boylam =0;
float  irtifa=0;
SoftwareSerial ESerial(PIN_RX, PIN_TX);

EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);
// Choose two Arduino pins to use for software serial

int sayac = 0;
double gps_zaman = 0;

void setup() 
{
  Serial.begin(19200);
  ESerial.begin(9600);
  // this init will set the pinModes for you
  Transceiver.init();

  Transceiver.PrintParameters();
}

void loop() 
{
  if (ESerial.available()) {

    // i highly suggest you send data using structures and not
    // a parsed data--i've always had a hard time getting reliable data using
    // a parsing method

    Transceiver.GetStruct(&MyData, sizeof(MyData));
  // You only really need this library to program these EBYTE units. 
  // For reading data structures, you can call readBytes directly on the EBYTE Serial object
  // ESerial.readBytes((uint8_t*)& MyData, (uint8_t) sizeof(MyData));
  
    // dump out what was just received
    /*Serial.print("yaw: "); Serial.println(MyData.YawAngle);
    Serial.print("pitch: "); Serial.println(MyData.PitchAngle);
    Serial.print("rol: "); Serial.println(MyData.RollAngle);
    Serial.print("enlem: "); Serial.println(MyData.enlem);
    Serial.print("boylam: "); Serial.println(MyData.boylam);
    Serial.print("irtifa: "); Serial.println(MyData.irtifa);
    // if you got data, update the checker*/
    Last = millis();

  }
  /*else {
    // if the time checker is over some prescribed amount
    // let the user know there is no incoming data
    if ((millis() - Last) > 1000) {
      Serial.println("Searching: ");
      Last = millis();
    }

  }*/
  paket_olustur();
  Serial.write(packetBytes, 78);
  delay(100);
  }