using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System;

namespace MazeGame
{
    [System.Serializable]
    public class SaveInformation
    {
        public string name;
        public float posX;
        public float posY;
        public float posZ;
    }

    public class MazeGameManager : SingletonTemplate<MazeGameManager>
    {
        public GameObject EnterName;
        public GameObject Player;
        public GameObject Arrow;
        public GameObject CoinSpawners;
        public Text score;
        public GameObject damagedImage;
        public int PlayerPoints = 0;

        private List<GameObject> spawnPoints = new List<GameObject>();
        public Vector3 coinPoint;

        public AudioClip getCoinSound;
        private AudioSource audioSource;
        private SaveInformation setInfo = new SaveInformation();

        void Start()
        {
            Time.timeScale = 0;
            audioSource = GetComponent<AudioSource>();
            audioSource.clip = getCoinSound;
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
            SaveLoad();
        }
        void SaveLoad()
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                SaveBinary();
            }

        }

        void SaveBinary()
        {
            setInfo.posX = Player.transform.position.x;
            setInfo.posY = Player.transform.position.y;
            setInfo.posZ = Player.transform.position.z;

            //============ save Binary
            BinaryFormatter formatter = new BinaryFormatter();
            MemoryStream memStream = new MemoryStream();
            formatter.Serialize(memStream, setInfo);
            byte[] bytes = memStream.GetBuffer();
            String memStr = Convert.ToBase64String(bytes);
            //Debug.Log(memStr);
            PlayerPrefs.SetString("SaveInformation", memStr);
            //=============

            //============ load
            string getInfo = PlayerPrefs.GetString("SaveInformation");
            //Debug.Log(getInfo);

            byte[] getBytes = Convert.FromBase64String(getInfo);
            MemoryStream getMemStream = new MemoryStream(getBytes);

            BinaryFormatter formatter2 = new BinaryFormatter();
            SaveInformation getInformation = (SaveInformation)formatter2.Deserialize(getMemStream);

            Debug.Log(getInformation);
            Debug.Log(getInformation.name);
            Debug.Log(getInformation.posX);
            Debug.Log(getInformation.posY);
            Debug.Log(getInformation.posZ);

            //============
        }

        public void NameOK()
        {
            setInfo.name = EnterName.GetComponentInChildren<InputField>().text;
            Debug.Log("Player name : " + setInfo.name);
            Time.timeScale = 1;
            EnterName.SetActive(false);
        }

        public void ShowScore()
        {
            score.text = string.Format("Score : {0}", PlayerPoints);
        }

        public void SpawnCoin()
        {
            GameObject temp = spawnPoints[UnityEngine.Random.Range(0, spawnPoints.Count)];
            temp.SetActive(true);
            coinPoint = temp.transform.position;
            audioSource.Play();
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