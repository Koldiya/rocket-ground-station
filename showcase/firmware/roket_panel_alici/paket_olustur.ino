// Union kullanimi ile alakali daha fazla bilgi icin: https://www.learn-c.org/en/Unions
typedef union{
	float           sayi;
	unsigned char   array[4];
}
FLOAT32_UINT8_DONUSTURUCU;
 
unsigned char check_sum_hesapla(){
    int check_sum = 0;
    
    for(int i = 4; i < 75; i++){
        check_sum += packetBytes[i];
    }
    
    return (unsigned char) (check_sum % 256); 
}



void paket_olustur()
{
  packetBytes[0] = 0xFF; // Sabit
  packetBytes[1] = 0xFF; // Sabit
  packetBytes[2] = 0x54; // Sabit
  packetBytes[3] = 0x52; // Sabit
    
  packetBytes[4] = 16;//map(analogRead(A0), 0, 1023, 0, 255);//16;   // Takim ID = 0
  packetBytes[5] = sayac; // Sayac degeri = 0
    
  FLOAT32_UINT8_DONUSTURUCU irtifa_float32_uint8_donusturucu;
  irtifa_float32_uint8_donusturucu.sayi = MyData.irtifa; // Irtifa degerinin atamasini yapiyoruz.
	packetBytes[6] = irtifa_float32_uint8_donusturucu.array[0]; 
  packetBytes[7] = irtifa_float32_uint8_donusturucu.array[1];
  packetBytes[8] = irtifa_float32_uint8_donusturucu.array[2];
  packetBytes[9] = irtifa_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU roket_gps_irtifa_float32_uint8_donusturucu;
  roket_gps_irtifa_float32_uint8_donusturucu.sayi = MyData.gps_irtifa; // Roket GPS Irtifa degerinin atamasini yapiyoruz.
	packetBytes[10] = roket_gps_irtifa_float32_uint8_donusturucu.array[0]; 
  packetBytes[11] = roket_gps_irtifa_float32_uint8_donusturucu.array[1];
  packetBytes[12] = roket_gps_irtifa_float32_uint8_donusturucu.array[2];
  packetBytes[13] = roket_gps_irtifa_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU roket_enlem_float32_uint8_donusturucu;
  roket_enlem_float32_uint8_donusturucu.sayi = MyData.enlem; // Roket enlem degerinin atamasini yapiyoruz.
	packetBytes[14] = roket_enlem_float32_uint8_donusturucu.array[0]; 
  packetBytes[15] = roket_enlem_float32_uint8_donusturucu.array[1];
  packetBytes[16] = roket_enlem_float32_uint8_donusturucu.array[2];
  packetBytes[17] = roket_enlem_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU roket_boylam_irtifa_float32_uint8_donusturucu;
  roket_boylam_irtifa_float32_uint8_donusturucu.sayi = MyData.boylam; // Roket boylam degerinin atamasini yapiyoruz.
	packetBytes[18] = roket_boylam_irtifa_float32_uint8_donusturucu.array[0]; 
  packetBytes[19] = roket_boylam_irtifa_float32_uint8_donusturucu.array[1];
  packetBytes[20] = roket_boylam_irtifa_float32_uint8_donusturucu.array[2];
  packetBytes[21] = roket_boylam_irtifa_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU gorev_yuku_gps_irtifa_float32_uint8_donusturucu;
  gorev_yuku_gps_irtifa_float32_uint8_donusturucu.sayi = 1361.61; // Gorev yuku GPS irtifa degerinin atamasini yapiyoruz.
	packetBytes[22] = gorev_yuku_gps_irtifa_float32_uint8_donusturucu.array[0]; 
  packetBytes[23] = gorev_yuku_gps_irtifa_float32_uint8_donusturucu.array[1];
  packetBytes[24] = gorev_yuku_gps_irtifa_float32_uint8_donusturucu.array[2];
  packetBytes[25] = gorev_yuku_gps_irtifa_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU gorev_yuku_enlem_float32_uint8_donusturucu;
  gorev_yuku_enlem_float32_uint8_donusturucu.sayi = 41.104593; // Gorev yuku enlem degerinin atamasini yapiyoruz.
	packetBytes[26] = gorev_yuku_enlem_float32_uint8_donusturucu.array[0]; 
  packetBytes[27] = gorev_yuku_enlem_float32_uint8_donusturucu.array[1];
  packetBytes[28] = gorev_yuku_enlem_float32_uint8_donusturucu.array[2];
  packetBytes[29] = gorev_yuku_enlem_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU gorev_yuku_boylam_irtifa_float32_uint8_donusturucu;
  gorev_yuku_boylam_irtifa_float32_uint8_donusturucu.sayi = 29.024411; // Gorev yuku boylam degerinin atamasini yapiyoruz.
	packetBytes[30] = gorev_yuku_boylam_irtifa_float32_uint8_donusturucu.array[0]; 
  packetBytes[31] = gorev_yuku_boylam_irtifa_float32_uint8_donusturucu.array[1];
  packetBytes[32] = gorev_yuku_boylam_irtifa_float32_uint8_donusturucu.array[2];
  packetBytes[33] = gorev_yuku_boylam_irtifa_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU kademe_gps_irtifa_float32_uint8_donusturucu;
  kademe_gps_irtifa_float32_uint8_donusturucu.sayi = 0; // Kademe GPS Irtifa degerinin atamasini yapiyoruz.
	packetBytes[34] = kademe_gps_irtifa_float32_uint8_donusturucu.array[0]; 
  packetBytes[35] = kademe_gps_irtifa_float32_uint8_donusturucu.array[1];
  packetBytes[36] = kademe_gps_irtifa_float32_uint8_donusturucu.array[2];
  packetBytes[37] = kademe_gps_irtifa_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU kademe_enlem_float32_uint8_donusturucu;
  kademe_enlem_float32_uint8_donusturucu.sayi = 0; // Kademe enlem degerinin atamasini yapiyoruz.
	packetBytes[38] = kademe_enlem_float32_uint8_donusturucu.array[0]; 
  packetBytes[39] = kademe_enlem_float32_uint8_donusturucu.array[1];
  packetBytes[40] = kademe_enlem_float32_uint8_donusturucu.array[2];
  packetBytes[41] = kademe_enlem_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU kademe_boylam_irtifa_float32_uint8_donusturucu;
  kademe_boylam_irtifa_float32_uint8_donusturucu.sayi = 0; // Kademe boylam degerinin atamasini yapiyoruz.
	packetBytes[42] = kademe_boylam_irtifa_float32_uint8_donusturucu.array[0]; 
  packetBytes[43] = kademe_boylam_irtifa_float32_uint8_donusturucu.array[1];
  packetBytes[44] = kademe_boylam_irtifa_float32_uint8_donusturucu.array[2];
  packetBytes[45] = kademe_boylam_irtifa_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU jiroskop_x_float32_uint8_donusturucu;
  jiroskop_x_float32_uint8_donusturucu.sayi = MyData.PitchAngle; // Jiroskop X degerinin atamasini yapiyoruz.
	packetBytes[46] = jiroskop_x_float32_uint8_donusturucu.array[0]; 
  packetBytes[47] = jiroskop_x_float32_uint8_donusturucu.array[1];
  packetBytes[48] = jiroskop_x_float32_uint8_donusturucu.array[2];
  packetBytes[49] = jiroskop_x_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU jiroskop_y_float32_uint8_donusturucu;
  jiroskop_y_float32_uint8_donusturucu.sayi = MyData.RollAngle; // Jiroskop Y degerinin atamasini yapiyoruz.
	packetBytes[50] = jiroskop_y_float32_uint8_donusturucu.array[0]; 
  packetBytes[51] = jiroskop_y_float32_uint8_donusturucu.array[1];
  packetBytes[52] = jiroskop_y_float32_uint8_donusturucu.array[2];
  packetBytes[53] = jiroskop_y_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU jiroskop_z_float32_uint8_donusturucu;
  jiroskop_z_float32_uint8_donusturucu.sayi = MyData.YawAngle; // Jiroskop Z degerinin atamasini yapiyoruz.
	packetBytes[54] = jiroskop_z_float32_uint8_donusturucu.array[0]; 
  packetBytes[55] = jiroskop_z_float32_uint8_donusturucu.array[1];
  packetBytes[56] = jiroskop_z_float32_uint8_donusturucu.array[2];
  packetBytes[57] = jiroskop_z_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU ivme_x_float32_uint8_donusturucu;
  ivme_x_float32_uint8_donusturucu.sayi = MyData.ivme_x_send; // Ivme X degerinin atamasini yapiyoruz.
	packetBytes[58] = ivme_x_float32_uint8_donusturucu.array[0]; 
  packetBytes[59] = ivme_x_float32_uint8_donusturucu.array[1];
  packetBytes[60] = ivme_x_float32_uint8_donusturucu.array[2];
  packetBytes[61] = ivme_x_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU ivme_y_float32_uint8_donusturucu;
  ivme_y_float32_uint8_donusturucu.sayi = MyData.ivme_y_send; // Ivme Y degerinin atamasini yapiyoruz.
	packetBytes[62] = ivme_y_float32_uint8_donusturucu.array[0]; 
  packetBytes[63] = ivme_y_float32_uint8_donusturucu.array[1];
  packetBytes[64] = ivme_y_float32_uint8_donusturucu.array[2];
  packetBytes[65] = ivme_y_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU ivme_z_float32_uint8_donusturucu;
  ivme_z_float32_uint8_donusturucu.sayi = MyData.ivme_z_send; // Ivme Z degerinin atamasini yapiyoruz.
	packetBytes[66] = ivme_z_float32_uint8_donusturucu.array[0]; 
  packetBytes[67] = ivme_z_float32_uint8_donusturucu.array[1];
  packetBytes[68] = ivme_z_float32_uint8_donusturucu.array[2];
  packetBytes[69] = ivme_z_float32_uint8_donusturucu.array[3];
    
  FLOAT32_UINT8_DONUSTURUCU aci_float32_uint8_donusturucu;
  aci_float32_uint8_donusturucu.sayi = 5.08; // Aci degerinin atamasini yapiyoruz.
	packetBytes[70] = aci_float32_uint8_donusturucu.array[0]; 
  packetBytes[71] = aci_float32_uint8_donusturucu.array[1];
  packetBytes[72] = aci_float32_uint8_donusturucu.array[2];
  packetBytes[73] = aci_float32_uint8_donusturucu.array[3];
    
  packetBytes[74] = 1; // Durum bilgisi = Iki parasut de tetiklenmedi
     
  packetBytes[75] = check_sum_hesapla(); // Check_sum = check_sum_hesapla();
  packetBytes[76] = 0x0D; // Sabit
  packetBytes[77] = 0x0A; // Sabit

  sayac++;
  if(sayac >= 256)
    sayac = 0;
}