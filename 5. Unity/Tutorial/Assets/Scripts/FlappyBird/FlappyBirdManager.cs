using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class FlappyBirdManager : SingletonTemplate<FlappyBirdManager>
{
    public GameObject player;
    public int Points = 0;
    public Text showPoints;
    public bool gameOver { get; private set; }

    // Start is called before the first frame update
    void Start()
    {
        gameOver = false;
    }

    // Update is called once per frame
    void Update()
    {
        ShowPoints();
    }

    public void GetPoint()
    {
        Points++;
    }

    void ShowPoints()
    {
        if(!gameOver)
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
