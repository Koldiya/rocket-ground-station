using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using DG.Tweening;

public class canvas_manager : MonoBehaviour
{
    public static canvas_manager instance { get; set; }

    Tween open_alici_warring_tween, close_alici_warring_tween;
    Tween open_verici_warring_tween, close_verici_warring_tween;


    [SerializeField] GameObject roket_gyro_obj, roket_irtifa_obj, roket_parasut;

    [SerializeField] GameObject turkiye_map, turkiye_nokta, turkiye_map_mask;

    bool harita_guncellendi = false;

    [Space(15)]


    public InputField connect_alici_field;
    public InputField connect_verici_field;
    public Image alici_image, verici_image;

    public Button connect_btn;

    public Text alici_warring_text, verici_warring_text;

    [SerializeField] Text roket_irtifa_text;



    [Space(25)]


    [SerializeField] Text takim_id_deger_text;
    [SerializeField] Text sayac_deger_text;
    [SerializeField] Text irtifa_deger_text;
    [SerializeField] Text roket_gps_irtifa_deger_text, roket_enlem_deger_text, roket_boylam_deger_text;
    [SerializeField] Text gorev_yuklu_gps_irtifa_deger_text, gorev_yuklu_enlem_deger_text, gorev_yuklu_boylam_deger_text;

    [SerializeField] Text jiroskop_x_deger_text, jiroskop_y_deger_text, jiroskop_z_deger_text;
    [SerializeField] Text ivme_x_deger_text, ivme_y_deger_text, ivme_z_deger_text;
    [SerializeField] Text aci_deger_text;
    [SerializeField] Text durum_deger_text;

    [SerializeField] Text jyro_x_deger_gosterge_text, jyro_y_deger_gosterge_text, jyro_z_deger_gosterge_text;

    void Awake()
    {
        instance = this;

        roket_parasut.SetActive(false);
        turkiye_nokta.SetActive(false);
    }
    public void veri_yenile()
    {
        takim_id_deger_text.text = arduino_connect.instance.takimID.ToString();
        sayac_deger_text.text = arduino_connect.instance.sayac.ToString();
        irtifa_deger_text.text = arduino_connect.instance.irtifa.ToString();
        roket_gps_irtifa_deger_text.text = arduino_connect.instance.roket_gps_irtifa.ToString();
        roket_enlem_deger_text.text = arduino_connect.instance.roket_enlem.ToString();
        roket_boylam_deger_text.text = arduino_connect.instance.roket_boylam_irtifa.ToString();
        gorev_yuklu_gps_irtifa_deger_text.text = arduino_connect.instance.gorev_yuku_boylam_irtifa.ToString();
        gorev_yuklu_enlem_deger_text.text = arduino_connect.instance.gorev_yuku_enlem.ToString();
        gorev_yuklu_boylam_deger_text.text = arduino_connect.instance.gorev_yuku_boylam_irtifa.ToString();

        jiroskop_x_deger_text.text = arduino_connect.instance.jiroskop_x.ToString();
        jiroskop_y_deger_text.text = arduino_connect.instance.jiroskop_y.ToString();
        jiroskop_z_deger_text.text = arduino_connect.instance.jiroskop_z.ToString();
        ivme_x_deger_text.text = arduino_connect.instance.ivme_x.ToString();
        ivme_y_deger_text.text = arduino_connect.instance.ivme_y.ToString();
        ivme_z_deger_text.text = arduino_connect.instance.ivme_z.ToString();
        aci_deger_text.text = arduino_connect.instance.aci.ToString();
        durum_deger_text.text = arduino_connect.instance.parasut_durum.ToString();

        roket_gyro_obj.transform.localRotation = Quaternion.Euler(arduino_connect.instance.jiroskop_y/2, -arduino_connect.instance.jiroskop_x/2, -arduino_connect.instance.jiroskop_z);

        jyro_x_deger_gosterge_text.text = arduino_connect.instance.jiroskop_x.ToString();
        jyro_y_deger_gosterge_text.text = arduino_connect.instance.jiroskop_y.ToString();
        jyro_z_deger_gosterge_text.text = "Z: " + arduino_connect.instance.jiroskop_z.ToString();

        irtifa_simulator();

        
        if(arduino_connect.instance.irtifa > 0.3f /*gerçekte böyle olcak 3*/ && arduino_connect.instance.roket_enlem != 0 && arduino_connect.instance.roket_boylam_irtifa != 0)
        {
            harita_simulator();
        }
    }

    void irtifa_simulator()
    {
        roket_irtifa_text.text = arduino_connect.instance.irtifa.ToString() + " M";

        float hedef_y = Mathf.Lerp(-460f, 260f, Mathf.InverseLerp(0f, 2000f, arduino_connect.instance.irtifa));

        roket_irtifa_obj.GetComponent<RectTransform>().anchoredPosition = new Vector2(-45, hedef_y);

        if (arduino_connect.instance.parasut_durum == 4)
        {
            roket_parasut.SetActive(true);
        }
        else
        {
            roket_parasut.SetActive(false);
        }
    }

    void harita_simulator()
    {
        float target_map_x = Mathf.Lerp(-246.8f, 237.21f, Mathf.InverseLerp(25.6f, 45f, arduino_connect.instance.roket_boylam_irtifa));
        float target_map_y = Mathf.Lerp(-91.4f, 114.1f, Mathf.InverseLerp(35.48f, 42.06f, arduino_connect.instance.roket_enlem));

        turkiye_nokta.SetActive(true);
        RectTransform map_target_rect = turkiye_nokta.GetComponent<RectTransform>();

        map_target_rect.anchoredPosition = new Vector2(target_map_x, target_map_y);



        RectTransform map_rect = turkiye_map.GetComponent<RectTransform>();
        
        turkiye_map.GetComponent<RectTransform>().DOAnchorPos(new Vector2(-261.1667f, -135.1667f) - map_target_rect.anchoredPosition, 1.5f).SetEase(Ease.OutCubic);

        turkiye_map_mask.GetComponent<RectTransform>().DOScale(new Vector2(6, 6), 2f).SetEase(Ease.OutCubic);
        map_target_rect.DOScale(new Vector2(0.025f, 0.025f), 1f);
    }


    public void open_alici_warring_text()
    {
        open_alici_warring_tween.Kill();
        close_alici_warring_tween.Kill();
        alici_warring_text.transform.localScale = Vector3.zero;
        open_alici_warring_tween = alici_warring_text.transform.DOScale(new Vector3(0.1f, 0.1f, 1), 1);
        StartCoroutine(close_alici_warring_text(7.5f));
    }
    public IEnumerator warring_ac(GameObject obj)
    {
        obj.SetActive(true);
        yield return new WaitForSeconds(6);
        obj.SetActive(false);
    }
    public IEnumerator close_alici_warring_text(float delay)
    {
        yield return new WaitForSeconds(delay);
        open_alici_warring_tween.Kill();
        close_alici_warring_tween.Kill();
        alici_warring_text.transform.localScale = new Vector3(0.1f, 0.1f, 1);
        close_alici_warring_tween = alici_warring_text.transform.DOScale(Vector3.zero, 1);
        close_alici_warring_tween.SetAutoKill(false);
    }


    public void open_verici_warring_text()
    {
        open_verici_warring_tween.Kill();
        close_verici_warring_tween.Kill();
        verici_warring_text.transform.localScale = Vector3.zero;
        open_verici_warring_tween = verici_warring_text.transform.DOScale(new Vector3(0.1f, 0.1f, 1), 1);
        StartCoroutine(close_verici_warring_text(7.5f));
    }

    public IEnumerator close_verici_warring_text(float delay)
    {
        yield return new WaitForSeconds(delay);
        open_verici_warring_tween.Kill();
        close_verici_warring_tween.Kill();
        verici_warring_text.transform.localScale = new Vector3(0.1f, 0.1f, 1);
        close_verici_warring_tween = verici_warring_text.transform.DOScale(Vector3.zero, 1);
        close_verici_warring_tween.SetAutoKill(false);
    }
}
