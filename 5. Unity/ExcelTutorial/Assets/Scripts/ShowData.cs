using System.Collections;
using System.Collections.Generic;
using UnityEngine;
public class ShowData : MonoBehaviour
{
    [SerializeField]
    private TestDB testDB;

    // Start is called before the first frame update
    void Start()
    {
        // 엑셀 데이터 읽기 전용만 가능 (쓰기는 어려움)
        testDB.캐릭터[0].순위= 10;
        testDB.Spec[0].HP = 45;
        Invoke("Show", 1.0f);
    }

    void Show()
    {
        Debug.Log(testDB.캐릭터[0].순위);
        Debug.Log(testDB.Spec[0].HP);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
