using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameCenter : MonoBehaviour
{
    [Header("������")]
    [SerializeField]
    GameObject playerPrefab;

    [SerializeField]
    GameObject monsterPrefab;

    [Header("�÷��̾� ����")]
    [SerializeField]
    int[] playerMaxHPs;

    [SerializeField]
    Transform playerRootTrans;

    [Header("���� ����")] // �߰�
    [SerializeField]
    int[] monsterMaxHPs;

    [SerializeField]
    Transform monsterRootTrans;

    Player[] players; 
    Monster[] mosnters;

    Dictionary<int, int> playerIdDic = new Dictionary<int, int>();

    // Start is called before the first frame update
    void Start()
    {
        CreatePlayers(playerMaxHPs.Length);
    }

    // Update is called once per frame
    void Update()
    {
//#if _DEBUG //����� �϶��� ������
        TEST_UpdateInputKey();
//#endif
    }


    void CreatePlayers(int count)
    {
        Debug.Log("[GAMECENTER] CreatePlayers : #" + count);
        players = new Player[count];
        for (int i = 0; i < count; i++)
        {
            int id = i + 1;
            players[i] = CreatePlayer(id, playerMaxHPs[i]);
            playerIdDic.Add(id, i);
        }
    }

    Player CreatePlayer(int id, int maxHP)
    {
        GameObject gb = Instantiate(playerPrefab, playerRootTrans); //�θ� �Ʒ��� ��ȯ
        gb.name = "player : " + id;
        gb.transform.position = playerRootTrans.position;
        gb.transform.rotation = playerRootTrans.rotation;

        Player player = gb.GetComponent<Player>();
        player.SetData(id, maxHP);
        // player.SetData(id, maxHP);//��� ����
        player.SetCallback(OnDied_Player);
        //player.SetCallback(OnDied_Player); // ��� ����


        Debug.Log("[GAMECENTER] Created Players ID : " + id);

        return player;
    }

    void AttackPlayer(int playerID, int amount)
    {
        int index = playerIdDic[playerID];
        players[index].Hurt(amount);
    }

    void OnDied_Player(int playerID)
    {
        Debug.Log("[GAMECENTER] OnDied_Player : " + playerID);
    }

    void TEST_UpdateInputKey()
    {
        if(Input.GetKeyDown(KeyCode.Space))
        {
            Debug.Log("[GAMECENTER] TEST_UpdateInputKey : " + KeyCode.Space);
            AttackPlayer(1, 10);
        }
    }

    void CheckGameEnd()
    {
        Debug.Log("���� ���� ���� �Ǵ�");
    }
}
