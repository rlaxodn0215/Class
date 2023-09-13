using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager_2D : SingletonTemplate<GameManager_2D>
{
    public GameObject player;
    public int Score = 0;
    public Text point;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {


        point.text = string.Format("Points : {0}", Score);
    }

    public void AddCoinScore()
    {
        Score+=100;
        
    }

    public void AddKillScore()
    {
        Score += 300;
    }
}
