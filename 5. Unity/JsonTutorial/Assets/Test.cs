using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 1. 데이터(코드 = 클래스)를 만들어야 함 => 저장할 데이터 생성
// 2. 그 데이터를 Json으로 변환 (택배 상자로 포장)
// =============================================================
// 1. Json을 원래 코드로 변환

class Data
{
    public string nickName = "none";
    public int Level = 0;
    public int coin = 100;
    public bool skill = false;
    //기타 등등...
}

public class Test : MonoBehaviour
{
    Data player = new Data()
    { 
        nickName = "김태우",
        Level = 50,
        coin = 200,
        skill = false
    };

    // Start is called before the first frame update
    void Start()
    {
        // 저장과 불러오기 (서버 또는 스프레드 시트)
        string jsonData= JsonUtility.ToJson(player);
        Data player2 = JsonUtility.FromJson<Data>(jsonData);
       // print(player2.nickName);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
