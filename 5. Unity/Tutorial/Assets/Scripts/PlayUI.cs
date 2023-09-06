using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayUI : MonoBehaviour
{
    public Text StartCounting;
    public Text Timer;
    public Text Ranking;
    public Text Loops;
    private void Update()
    {

        if (GameManager.Instance.waiting)
        {
            StartCounting.text = string.Format("{0:N0}", (int)GameManager.Instance.timer + 1);
        }

        else
        {
            StartCounting.gameObject.SetActive(false);
            Timer.text = string.Format("{0:N2}", GameManager.Instance.timer);
        }

        Loops.text = string.Format("{0:N0}", (int)GameManager.Instance.Loop);
        
    }

}
