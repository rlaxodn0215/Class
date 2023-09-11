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

    const int playerNum = 4;
    public int PlayerNum { get { return playerNum; } }

    public Status curStatus = Status.TITLE;

    public GameObject Charactors;
    public List<Transform> Cars = new List<Transform>();

    public float timer = 2.99f;

    public float bornTimer = 7.99f;
    public bool showWarningCount = false;

    public int Loop = 3;

    public GameObject SpawnPoint;
    private Transform[] Points = new Transform[10];

    public int Rank = 0;
    public string[] Names = new string[playerNum];
    public float[] CarTimes = new float[playerNum];
    public Dictionary<string, int> PassNum = new Dictionary<string, int>(playerNum);

    public bool GamePlaying = false;
    public bool waiting = true;

    private void Start()
    {
        LoadUI();
        LoadCharactors();
        LoadSensor();
    }

    private void Update()
    {
        MakeTimer();
        CheckFinish();
    }


    void LoadSensor()
    {
        for(int i = 0; i < 10; i++)
        {
            Points[i] = SpawnPoint.transform.GetChild(i);
        }
    }

    void ReBorn()
    {

        if(!(Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D) ||
            Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.S)))
        {
            bornTimer -= Time.deltaTime;
            if(bornTimer<=2.99f)
            {
                //Debug.Log("warning");
                showWarningCount = true;
                if(bornTimer<=0)
                {
                    // ºÎÈ°
                    Cars[0].transform.position = Points[PassNum["Player"]].position;
                    Cars[0].GetComponent<CarControl>().moveVertical = 0.0f;
                    Cars[0].transform.localRotation = Quaternion.Euler(0.0f, 0.0f, 0.0f);
                    showWarningCount = false;
                    bornTimer = 7.99f;
                }

            }

            else
            {
                showWarningCount = false;
            }
        }

        else
        {
            showWarningCount = false;
            bornTimer = 7.99f;
        }
    }

    private void LoadCharactors()
    {
        for(int i = 0; i < Charactors.transform.childCount; i++)
        {
            Cars.Add(Charactors.transform.GetChild(i));
            PassNum[Charactors.transform.GetChild(i).name] = 0;
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
                Cars[0].GetChild(5).gameObject.SetActive(true);
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
                ReBorn();
            }

            
        }
    }

}
