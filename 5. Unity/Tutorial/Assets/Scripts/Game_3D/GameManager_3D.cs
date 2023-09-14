using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager_3D : SingletonTemplate<GameManager_3D>
{
    public GameObject player;

    public GameObject enemySpawner;
    public float Timer;
    public int PlayerSwordDamage { get; private set; }
    public int EnemySwordDamage { get; private set; }

    // Start is called before the first frame update
    void Start()
    {
        PlayerSwordDamage = 20;
        EnemySwordDamage = 5;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void EnemyDead()
    {

    }

    public void CollumDead()
    {

    }
}
