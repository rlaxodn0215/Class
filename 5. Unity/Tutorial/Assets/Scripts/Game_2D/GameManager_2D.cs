using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager_2D : SingletonTemplate<GameManager_2D>
{
    public GameObject player;
    public int Score = 0;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void AddCoinScore()
    {
        Score+=100;
        Debug.Log(GameManager_2D.Instance.Score);
    }
}
