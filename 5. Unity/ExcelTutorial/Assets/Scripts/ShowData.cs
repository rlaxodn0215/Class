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
        // ���� ������ �б� ���븸 ���� (����� �����)
        testDB.ĳ����[0].����= 10;
        testDB.Spec[0].HP = 45;
        Invoke("Show", 1.0f);
    }

    void Show()
    {
        Debug.Log(testDB.ĳ����[0].����);
        Debug.Log(testDB.Spec[0].HP);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
