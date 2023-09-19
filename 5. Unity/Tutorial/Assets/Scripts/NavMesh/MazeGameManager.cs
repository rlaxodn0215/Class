using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace MazeGame
{
    public class MazeGameManager : SingletonTemplate<MazeGameManager>
    {
        public GameObject Player;
        public GameObject Arrow;
        public GameObject CoinSpawners;
        public int PlayerPoints = 0;

        private List<GameObject> spawnPoints = new List<GameObject>();
        public Vector3 coinPoint;

        void Start()
        {
            CoinPointInit();
            SpawnCoin();
        }

        void CoinPointInit()
        {
            for(int i = 0; i < CoinSpawners.transform.childCount; i++)
            {
                CoinSpawners.transform.GetChild(i).gameObject.SetActive(false);
                spawnPoints.Add(CoinSpawners.transform.GetChild(i).gameObject);
            }
        }

        // Update is called once per frame
        void Update()
        {

        }

        public void SpawnCoin()
        {
            GameObject temp = spawnPoints[Random.Range(0, spawnPoints.Count - 1)];
            temp.SetActive(true);
            coinPoint = temp.transform.position;

        }

    }
}