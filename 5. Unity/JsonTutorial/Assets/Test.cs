using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 1. ������(�ڵ� = Ŭ����)�� ������ �� => ������ ������ ����
// 2. �� �����͸� Json���� ��ȯ (�ù� ���ڷ� ����)
// =============================================================
// 1. Json�� ���� �ڵ�� ��ȯ

class Data
{
    public string nickName = "none";
    public int Level = 0;
    public int coin = 100;
    public bool skill = false;
    //��Ÿ ���...
}

public class Test : MonoBehaviour
{
    Data player = new Data()
    { 
        nickName = "���¿�",
        Level = 50,
        coin = 200,
        skill = false
    };

    // Start is called before the first frame update
    void Start()
    {
        // ����� �ҷ����� (���� �Ǵ� �������� ��Ʈ)
        string jsonData= JsonUtility.ToJson(player);
        Data player2 = JsonUtility.FromJson<Data>(jsonData);
       // print(player2.nickName);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
