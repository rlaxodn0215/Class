using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EndUI : MonoBehaviour
{

    public GameObject Name;
    private Text[] names = new Text[4];

    public GameObject Time;
    private Text[] times = new Text[4];

    private void Start()
    {
        Initalize();
        ShowRankings();
    }

    void Initalize()
    {
        for (int i = 0; i < 4; i++)
        {
            names[i] = Name.transform.GetChild(i).GetComponent<Text>();
            times[i] = Time.transform.GetChild(i).GetComponent<Text>();
        }
    }


    void ShowRankings()
    {
        for (int i = 0; i < 4; i++)
        {
            names[i].text = GameManager.Instance.Names[i];
            times[i].text = string.Format("{0:N2}", GameManager.Instance.CarTimes[i]);
            if(GameManager.Instance.Names[i]=="Player")
            {
                break;
            }
        }
    }
}