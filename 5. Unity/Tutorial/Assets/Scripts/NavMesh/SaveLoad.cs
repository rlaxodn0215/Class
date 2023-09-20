using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System;

[System.Serializable]
public class SaveInformation
{
    public string name;
    public float posX;
    public float posY;
    public float posZ;
}

public class SaveLoad : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        SaveLoad_Test();
    }
    void SaveLoad_Test()
    {
        //레지스트리에 값 저장됨

        if (Input.GetKeyDown(KeyCode.A))
        {
            if (PlayerPrefs.HasKey("ID"))
            {
                string getID = PlayerPrefs.GetString("ID");
                Debug.Log(string.Format("ID : {0}", getID));
            }

            else
            {
                Debug.Log("ID : 없음");
            }
        }

        if (Input.GetKeyDown(KeyCode.B))
        {
            string setID = "2023inha";
            PlayerPrefs.SetString("ID", setID);
            Debug.Log(string.Format("Saved ID : " + setID));
        }

        if (Input.GetKeyDown(KeyCode.C))
        {
            PlayerPrefs.SetInt("Score", 33);
            PlayerPrefs.SetFloat("Exp", 44.4f);

            int getScore = 0;
            if(PlayerPrefs.HasKey("Score"))
            {
                getScore = PlayerPrefs.GetInt("Score");
            }

            float getExp = 0;
            if(PlayerPrefs.HasKey("Exp"))
            {
                getExp = PlayerPrefs.GetFloat("Exp");
            }

            Debug.Log("Score : " + getScore.ToString());
            Debug.Log("Exp : " + getExp.ToString());
        }

        if (Input.GetKeyDown(KeyCode.S))
        {
            SaveBinary();
        }

        if (Input.GetKeyDown(KeyCode.D))
        {
            string getID = PlayerPrefs.GetString("ID2", "NONE"); //ID2가 없으면 default 값으로 NONE
            int getScore = PlayerPrefs.GetInt("Score2", 100);
            float getExp = PlayerPrefs.GetFloat("Exp2", 4.44f);

            Debug.Log(getID);
            Debug.Log(getScore);
            Debug.Log(getExp);
        }
    }

    void SaveBinary()
    {
        //==========
        SaveInformation setInfo = new SaveInformation();
        setInfo.name = "2023INHA";
        setInfo.posX = 0.0f;
        setInfo.posY = 4.0f;
        setInfo.posZ = 0.8f;
        Debug.Log(setInfo);
        //================

        //============ save Binary
        BinaryFormatter formatter = new BinaryFormatter();
        MemoryStream memStream = new MemoryStream();
        formatter.Serialize(memStream, setInfo);
        byte[] bytes = memStream.GetBuffer();
        String memStr = Convert.ToBase64String(bytes);
        Debug.Log(memStr);
        PlayerPrefs.SetString("SaveInformation", memStr);
        //=============

        //============ load
        string getInfo = PlayerPrefs.GetString("SaveInformation");
        Debug.Log(getInfo);

        byte[] getBytes = Convert.FromBase64String(getInfo);
        MemoryStream getMemStream = new MemoryStream(getBytes);

        BinaryFormatter formatter2 = new BinaryFormatter();
        SaveInformation getInformation =  (SaveInformation)formatter2.Deserialize(getMemStream);

        Debug.Log(getInformation);
        Debug.Log(getInformation.name);
        Debug.Log(getInformation.posX);
        Debug.Log(getInformation.posY);
        Debug.Log(getInformation.posZ);

        //============
    }


}
