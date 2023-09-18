using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Game_3D
{
    public class GameManager_3D : SingletonTemplate<GameManager_3D>
    {
        public GameObject player;

        public GameObject enemy;
        [SerializeField]
        private Dictionary<int, GameObject> Enemys = new Dictionary<int, GameObject>();
        [SerializeField]
        private Queue<int> EnemysID = new Queue<int>();

        public int PlayerPoint = 0;
        public int MaxEnemyNum = 10;
        public float Timer = 0.0f;
        int colNum = 5;

        private float SpawnTimer = 0.0f;
        private float SpawnInterval = 3.0f;
        public int PlayerSwordDamage { get; private set; }
        public int EnemySwordDamage { get; private set; }

        public Text timer;
        public Text score;
        public GameObject gameOver;

        // Start is called before the first frame update
        void Start()
        {
            PlayerSwordDamage = 20;
            EnemySwordDamage = 5;
            InitEnemys();
        }

        void InitEnemys()
        {
            for (int i = 1; i <= MaxEnemyNum; i++)
            {
                GameObject obj = Instantiate(enemy, transform);
                obj.GetComponent<Enemy>().ID = i;
                obj.name = "Enemy - " + i;
                obj.gameObject.SetActive(false);
                Enemys.Add(i, obj);
                EnemysID.Enqueue(i);
            }
        }

        // Update is called once per frame
        void Update()
        {
            Timeing();
            SpawnEnemys();
            ShowTimer();
            ShowScore();
        }

        void SpawnEnemys()
        {
            if(SpawnTimer>=SpawnInterval)
            {
                SpawnTimer = 0;

                if (EnemysID.Count == 0)
                    return;

                Enemy temp =  Enemys[EnemysID.Peek()].GetComponent<Enemy>();
                temp.Alive = true;
                temp.Hp = 50;
                temp.transform.position = new Vector3(35, 0.5f, Random.Range(-12, 12));
                temp.transform.rotation = Quaternion.Euler(0,-90,0);
                temp.gameObject.SetActive(true);
                EnemysID.Dequeue();
            }
        }

        private void OnTriggerEnter(Collider other) //³«»ç...
        {
            if (other.tag == "Enemy")
            {
                PlayerPoint += 100;
            }

            else if (other.tag == "Player")
            {
                player.transform.position = new Vector3(-30, 0, 0);
                player.transform.rotation = Quaternion.Euler(0, 90, 0);
            }

        }

        private void Timeing()
        {
            Timer += Time.deltaTime;
            SpawnTimer += Time.deltaTime;
        }

        public void EnemyDead(int ID)
        {
            EnemysID.Enqueue(ID);
        }

        public void CollumDead()
        {
            colNum--;
            if(colNum<=0)
            {
                GameOver();
            }
        }

        void ShowTimer()
        {
            timer.text = string.Format("{0:N2}", Timer);
        }

        void ShowScore()
        {
            score.text = string.Format("Score : {0}", PlayerPoint);
        }

        public void GameOver()
        {
            gameOver.SetActive(true);
        }


    }
}