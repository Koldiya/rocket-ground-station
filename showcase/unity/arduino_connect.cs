using System;
using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using UnityEngine;
using UnityEngine.UI;

public enum DataType
{
    Integer,
    Float
}

public struct DataPacket
{
    public DataType type;
    public int intValue;
    public int intValue_2;
    public float floatValue;
}

public class arduino_connect : MonoBehaviour
{
    public static arduino_connect instance { get; set; }


    SerialPort serialPortGelen;
    SerialPort serialPortGiden;

    public int takimID;
    public int sayac;
    public float irtifa;
    public float roket_gps_irtifa;
    public float roket_enlem;
    public float roket_boylam_irtifa;
    public float gorev_yuku_gps_irtifa;
    public float gorev_yuku_enlem;
    public float gorev_yuku_boylam_irtifa;
    public float jiroskop_x;
    public float jiroskop_y;
    public float jiroskop_z;
    public float ivme_x;
    public float ivme_y;
    public float ivme_z;
    public float aci;
    public int parasut_durum;


    int PACKET_GIDEN_SIZE = 78;//15
    int PACKET_GELEN_SIZE = 78;//12

    bool veri_yollanıyor = false;





    void Awake()
    {
        instance = this;
    }

    public void connect()
    {
        serialPortGelen = new SerialPort("COM" + canvas_manager.instance.connect_alici_field.text, 19200);
        serialPortGiden = new SerialPort("COM" + canvas_manager.instance.connect_verici_field.text, 19200);
        try
        {
            serialPortGelen.Open();
            // Serial port başarıyla açıldı, devam edin.
            canvas_manager.instance.connect_btn.image.color = Color.green;

            
        }
        catch (Exception ex)
        {
            Debug.LogError("serialPortGelen açılırken hata oluştu: " + ex.Message);
            // Hata durumunu ele alın.
            canvas_manager.instance.alici_warring_text.text = "Alıcı port açılırken hata oluştu: " + ex.Message;
            StartCoroutine(canvas_manager.instance.warring_ac(canvas_manager.instance.alici_warring_text.gameObject));
            //canvas_manager.instance.open_alici_warring_text();

            canvas_manager.instance.connect_btn.image.color = Color.white;

        }

        try
        {
            serialPortGiden.Open();
            // Serial port başarıyla açıldı, devam edin.
            canvas_manager.instance.connect_btn.image.color = Color.green;
        }
        catch (Exception ex)
        {
            Debug.LogError("serialPortGiden açılırken hata oluştu: " + ex.Message);
            // Hata durumunu ele alın.
            canvas_manager.instance.verici_warring_text.text = "Verici port açılırken hata oluştu: " + ex.Message;
            StartCoroutine(canvas_manager.instance.warring_ac(canvas_manager.instance.verici_warring_text.gameObject));
            //canvas_manager.instance.open_verici_warring_text();

            canvas_manager.instance.connect_btn.image.color = Color.white;

        }
    }

    void Update()
    {
        //veri_yolla();

        
        try
        {
            veri_al();
        }
        catch (Exception ex)
        {
            Debug.LogError("serialPortGelen açılırken hata oluştu: " + ex.Message);
            // Hata durumunu ele alın.
            canvas_manager.instance.alici_warring_text.text = "Alıcı port açılırken hata oluştu: " + ex.Message;
            StartCoroutine(canvas_manager.instance.warring_ac(canvas_manager.instance.alici_warring_text.gameObject));
            //canvas_manager.instance.open_alici_warring_text();


            canvas_manager.instance.connect_btn.image.color = Color.white;

            OnDestroy();

        }

        //canvas_manager.instance.veri_yenile();

        if (serialPortGelen != null && serialPortGelen.IsOpen)
        {
            canvas_manager.instance.alici_image.color = Color.green;
        }
        else
        {
            canvas_manager.instance.alici_image.color = Color.red;
        }

        if (serialPortGiden != null && serialPortGiden.IsOpen)
        {
            canvas_manager.instance.verici_image.color = Color.green;
        }
        else
        {
            canvas_manager.instance.verici_image.color = Color.red;
        }
    }

    void veri_al()
    {
        // Her Update() döngüsünde seri porttan veri oku
        if (serialPortGelen != null && serialPortGelen.IsOpen && serialPortGelen.BytesToRead >= PACKET_GELEN_SIZE)
        {
            // Veri paketini oku
            byte[] packetBytes = new byte[PACKET_GELEN_SIZE];//arduinodaki değer ile aynı olmalı
            serialPortGelen.Read(packetBytes, 0, PACKET_GELEN_SIZE);

            // Gelen verinin geçerli olduğunu kontrol et
            if (DogrulaChecksum(packetBytes))
            {
                takimID = packetBytes[4];
                sayac = packetBytes[5];
                irtifa = BitConverter.ToSingle(packetBytes, 6);
                roket_gps_irtifa = BitConverter.ToSingle(packetBytes, 10);
                roket_enlem = BitConverter.ToSingle(packetBytes, 14);
                roket_boylam_irtifa = BitConverter.ToSingle(packetBytes, 18);
                gorev_yuku_gps_irtifa = BitConverter.ToSingle(packetBytes, 22);
                gorev_yuku_enlem = BitConverter.ToSingle(packetBytes, 26);
                gorev_yuku_boylam_irtifa = BitConverter.ToSingle(packetBytes, 30);
                jiroskop_x = BitConverter.ToSingle(packetBytes, 46);
                jiroskop_y = BitConverter.ToSingle(packetBytes, 50);
                jiroskop_z = BitConverter.ToSingle(packetBytes, 54);
                ivme_x = BitConverter.ToSingle(packetBytes, 58);
                ivme_y = BitConverter.ToSingle(packetBytes, 62);
                ivme_z = BitConverter.ToSingle(packetBytes, 66);
                aci = BitConverter.ToSingle(packetBytes, 70);
                parasut_durum = packetBytes[74];

                canvas_manager.instance.veri_yenile();

                //paketi burda ttl e yolla
                if(serialPortGiden != null && serialPortGiden.IsOpen && !veri_yollanıyor)
                {
                    StartCoroutine(delay_ile_veri_yolla(packetBytes));
                }
            }
            else
            {
                // Geçersiz veri, hata ver veya uygun şekilde işle
                Debug.LogError("serialPortGelen açılırken hata oluştu: " + "Geçersiz veri paketi!");
                // Hata durumunu ele alın.
                canvas_manager.instance.alici_warring_text.text = "Alıcı portta hata oluştu: " + "Geçersiz veri paketi!";
                //canvas_manager.instance.open_alici_warring_text();
                StartCoroutine(canvas_manager.instance.warring_ac(canvas_manager.instance.alici_warring_text.gameObject));



                // Seri porttan yeni veri almak için bu kısmı çağır
                serialPortGelen.DiscardInBuffer(); // Mevcut tamponu temizle
                serialPortGelen.DiscardOutBuffer();
            }

        }
    }

    // Arduino'dan gelen veri paketinin checksum'unu doğrula
    bool DogrulaChecksum(byte[] packetBytes)
    {
        // Arduino'dan gelen checksum'u hesapla
        int checkSum = 0;
        for (int i = 4; i < 75; i++)
        {
            checkSum += packetBytes[i];
        }
        byte arduinoChecksum = (byte)(checkSum % 256);

        // Unity'de hesaplanan checksum ile Arduino'dan gelen checksum'u karşılaştır
        return arduinoChecksum == packetBytes[75];
    }

    public IEnumerator delay_ile_veri_yolla(byte[] veri_dizisi)
    {
        veri_yollanıyor = true;
        yield return new WaitForSeconds(0.1f);
        serialPortGiden.Write(veri_dizisi, 0, veri_dizisi.Length);
        veri_yollanıyor = false;
    }

    void veri_yolla()
    {
        // Veri paketi oluşturma
        DataPacket dataPacket = new DataPacket();
        dataPacket.type = DataType.Integer;

        dataPacket.intValue = 0;// (int)floatGelenValue; // intValue;
        dataPacket.intValue_2 = 0;//intValue_2;
        dataPacket.floatValue = 0;//floatValue;

        // Veriyi gönderme
        SendData(dataPacket);
        string str = serialPortGiden.ReadExisting();
        if (!string.IsNullOrEmpty(str))
        {
            string[] veriler = str.Split('#');
            string[] vericikler = veriler[0].Split("|");
            if (vericikler.Length == 3)
            {
                Debug.Log(veriler[0]);
            }
        }
    }
    void SendData(DataPacket dataPacket)
    {
        // Veri paketini byte dizisine dönüştürme
        byte[] packetBytes = new byte[PACKET_GIDEN_SIZE]; // int 4 byte + float 4 byte = 8 byte, artı 3 byte ayırma işareti
        packetBytes[0] = (byte)dataPacket.type;
        byte[] intBytes = System.BitConverter.GetBytes(dataPacket.intValue);
        byte[] intBytes_2 = System.BitConverter.GetBytes(dataPacket.intValue_2);
        byte[] floatBytes = System.BitConverter.GetBytes(dataPacket.floatValue);

        // Int değerini byte dizisine kopyala
        System.Buffer.BlockCopy(intBytes, 0, packetBytes, 1, 4);
        System.Buffer.BlockCopy(intBytes_2, 0, packetBytes, 5, 4);
        // Float değerini byte dizisine kopyala
        System.Buffer.BlockCopy(floatBytes, 0, packetBytes, 9, 4); // 5 indeksten itibaren

        // Son olarak, byte dizisini uygun şekilde seri porta yaz
        serialPortGiden.Write(packetBytes, 0, packetBytes.Length);
    }


    void veri_resetle()
    {
        takimID = 0;
        sayac = 0;
        irtifa = 0;
        roket_gps_irtifa = 0;
        roket_enlem = 0;
        roket_boylam_irtifa = 0;
        gorev_yuku_gps_irtifa = 0;
        gorev_yuku_enlem = 0;
        gorev_yuku_boylam_irtifa = 0;
        jiroskop_x = 0;
        jiroskop_y = 0;
        jiroskop_z = 0;
        ivme_x = 0;
        ivme_y = 0;
        ivme_z = 0;
        aci = 0;
        parasut_durum = 0;

        canvas_manager.instance.veri_yenile();
    }

    public void OnDestroy()
    {
        if (serialPortGelen != null && serialPortGelen.IsOpen)
        {
            serialPortGelen.Close();
        }
        if (serialPortGiden != null && serialPortGiden.IsOpen)
        {
            serialPortGiden.Close();
        }
        canvas_manager.instance.connect_btn.image.color = Color.white;
        veri_resetle();
    }

    private void OnApplicationQuit()
    {
        if (serialPortGelen != null && serialPortGelen.IsOpen)
        {
            serialPortGelen.Close();
        }
        if (serialPortGiden != null && serialPortGiden.IsOpen)
        {
            serialPortGiden.Close();
        }
    }
}
