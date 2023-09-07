using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayUI : MonoBehaviour
{
    public Text StartCounting;
    public Text Timer;

    public GameObject Ranks;

    private Text[] Rank = new Text[GameManager.Instance.PlayerNum];
    int ShowRankNum = 0;

    private int preRanking = GameManager.Instance.Rank;
    private int curRanking = GameManager.Instance.Rank;

    private string[] Names = new string[GameManager.Instance.PlayerNum];
    private float[] CarTimes = new float[GameManager.Instance.PlayerNum];
    private int FirstTimeIndex = 0;
    private float ShowTimer = 3.5f;

    public Text Loops;

    private void Start()
    {
        for(int i = 0; i < GameManager.Instance.PlayerNum;i++)
        {
            Rank[i] = Ranks.transform.GetChild(i).GetComponent<Text>();
        }
    }

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

        RankUpdate();

    }

    void RankUpdate()
    {
        curRanking = GameManager.Instance.Rank;

        if (preRanking != curRanking)
        {
            ShowRank();
            preRanking = curRanking;
        }

        Names = GameManager.Instance.Names;
        CarTimes = GameManager.Instance.CarTimes;

        if (Rank[0].IsActive())
        {
            if (GameManager.Instance.timer > CarTimes[FirstTimeIndex] + ShowTimer)
            {
                for (int j = 0; j < ShowRankNum - 1; j++)
                {
                    Rank[j].text = Rank[j + 1].text;
                }

                Rank[--ShowRankNum].gameObject.SetActive(false);
                FirstTimeIndex++;
            }
        }

        else
        {
            if(FirstTimeIndex>= GameManager.Instance.PlayerNum)
                FirstTimeIndex = 0;
        }

    }

    void ShowRank()
    {
        Rank[ShowRankNum].text = string.Format("{0}. " + Names[curRanking-1] + " {1:N2}", curRanking, CarTimes[curRanking-1]);
        //Debug.Log(Rank[ShowRankNum].IsActive());
        Rank[ShowRankNum].gameObject.SetActive(true);
        //Debug.Log(Rank[ShowRankNum].IsActive());
        ShowRankNum++;
    }

}
