void displayInfo()
{

    if (gps.location.isValid())
    {
      enlem=gps.location.lat();
      boylam=gps.location.lng();
      gps_irtifa=gps.altitude.meters();

    }
    else
    Serial.println( "error");

  smartDelay(1000);
  
}
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (gpsSerial.available())
      gps.encode(gpsSerial.read());
  } while (millis() - start < ms);
}