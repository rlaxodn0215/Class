using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;


public class GameManager : SingletonTemplate<GameManager>
{
    public enum Status { TITLE, PLAY, END};

    const string TITLE_UI = "TitleUI";
    const string PLAY_UI = "PlayUI";
    const string END_UI = "EndUI";

    public Status curStatus = Status.TITLE;


    public GameObject Charactors;
    private List<Transform> Cars = new List<Transform>();

    public float timer = 2.99f;
    public int Loop = 3;

    public int[] Ranks = new int[3];
    public float[] Times = new float[3];

    public GameObject GoalTrigger;

    public bool GamePlaying = false;
    public bool waiting = true;

    private void Start()
    {
        LoadUI();
        LoadCharactors();
    }

    private void Update()
    {
        MakeTimer();
        CheckRank();
        CheckFinish();
    }

    private void LoadCharactors()
    {
        for(int i = 0; i < Charactors.transform.childCount; i++)
        {
            Cars.Add(Charactors.transform.GetChild(i));
        }
    }

    public void LoadUI()
    {
        switch (curStatus)
        {
            case Status.TITLE:               
                SceneManager.LoadScene(TITLE_UI, LoadSceneMode.Additive);
                break;

            case Status.PLAY:
                Cars[0].GetChild(3).gameObject.SetActive(true);
                GamePlaying = true;
                SceneManager.UnloadSceneAsync(TITLE_UI);
                SceneManager.LoadScene(PLAY_UI, LoadSceneMode.Additive);
                break;

            case Status.END:
                CharactorsClear();
                GamePlaying = false;
                SceneManager.UnloadSceneAsync(PLAY_UI);
                SceneManager.LoadScene(END_UI, LoadSceneMode.Additive);
                break;
        }
    }

    private void RaceStart()
    {
        Cars[0].GetComponent<CarControl>().enabled = true;

        for(int i = 1; i < Charactors.transform.childCount; i++)
        {
            Cars[i].GetComponent<CarAI>().enabled = true;
        }

    }

    private void CharactorsClear()
    {
        Charactors.SetActive(false);
    }

    public void CheckFinish()
    {
        if(Loop<=0 && GamePlaying)
        {
            curStatus = Status.END;
            LoadUI();
        }
    }

    public void CheckRank()
    {

    }

    public void MakeTimer()
    {
        if (GamePlaying)
        {
            if (timer <= 0.0f)
            {
                RaceStart();
                waiting = false;
            }

            if (waiting)
            {
                timer -= Time.deltaTime;
            }

            else
            {
                timer += Time.deltaTime;
            }

            
        }
    }

}
