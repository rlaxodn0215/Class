using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class FlappyBirdManager : SingletonTemplate<FlappyBirdManager>
{
    public int Points = 0;

     public GameObject player;
     public GameObject Spawner;
     public Text showPoints;
     public Text countdown;

    public bool gameOver { get; set; }
    public float countDown = 4.0f;

    // Start is called before the first frame update
    void Start()
    {
        gameOver = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (!gameOver)
        {
            ShowPoints();
            CountDown();
            countdown.text = string.Format("{0:N0}", countDown + 1);
        }
    }

    private void CountDown()
    {
        if (countDown >= 0.0f)
            countDown -= Time.deltaTime;
        else if(countDown < 1.0f)
        {
            countdown.enabled = false;
            GameStart();
        }
    }

    public void GameStart()
    {
        Spawner.SetActive(true);
        if (player.GetComponent<Rigidbody>() == null)
            player.AddComponent<Rigidbody>();
        player.GetComponent<FlappyBird>().enabled = true;
    }

    public void GetPoint()
    {
        Points++;
    }

    void ShowPoints()
    {
        if(!gameOver && showPoints != null)
        showPoints.text = string.Format("{0}", Points);
    }

    public void GameOver()
    {
        gameOver = true;
        player.GetComponent<BoxCollider>().isTrigger = true;
        Invoke("EndScene", 2.0f);
    }

    private void EndScene()
    {
        SceneManager.LoadScene("EndScene");
    }
}
