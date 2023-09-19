using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace MazeGame
{
    public class MazeGameManager : SingletonTemplate<MazeGameManager>
    {
        public GameObject Player;
        public GameObject Arrow;
        public GameObject CoinSpawners;
        public Text score;
        public GameObject damagedImage;
        public int PlayerPoints = 0;

        private List<GameObject> spawnPoints = new List<GameObject>();
        public Vector3 coinPoint;

        void Start()
        {
            CoinPointInit();
            SpawnCoin();
            ShowScore();
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
            PointingCoin();
        }

        public void ShowScore()
        {
            score.text = string.Format("Score : {0}", PlayerPoints);
        }

        public void SpawnCoin()
        {
            GameObject temp = spawnPoints[Random.Range(0, spawnPoints.Count)];
            temp.SetActive(true);
            coinPoint = temp.transform.position;
        }

        void PointingCoin()
        {
            Vector3 temp = coinPoint - Arrow.transform.position;
            Vector3 cr = Vector3.Cross(Player.transform.forward, temp);
            float angle = Vector3.Angle(Player.transform.forward, temp);

            if(Vector3.Dot(Player.transform.up, cr) < 0)
            {
                angle *= -1;
            }

            //Debug.Log(angle);

            Arrow.transform.localRotation = Quaternion.Euler(new Vector3(-90, angle,0));
        }

        public void Damaged()
        {
            damagedImage.SetActive(true);
            StartCoroutine(Healing());
        }

        IEnumerator Healing()
        {
            yield return new WaitForSeconds(2.5f);
            damagedImage.SetActive(false);
        }


    }
}