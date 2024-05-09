void barometre_baslangic_deger()
{
   sicaklik = ms5611.readTemperature(true);
  basinc = ms5611.readPressure(true);
  irtifa = ms5611.getAltitude(basinc);

  baslangic_metre_deger = irtifa;
}

void barometre_oku()
{
  sicaklik = ms5611.readTemperature(true);
  basinc = ms5611.readPressure(true);
  irtifa = ms5611.getAltitude(basinc);

  gercek_irtifa = irtifa - baslangic_metre_deger;
}