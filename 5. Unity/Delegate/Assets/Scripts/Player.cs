using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public delegate void Callback_OnDied(int id); // GameCenter과 연결되지 않았지만, 신호를 보낸다
    Callback_OnDied onDied; 

    public int ID { get; private set; } // 객체마다 고유 ID가 있어야 한다

    public int MaxHP { get; private set; } //max, current
    public int CurHP { get; private set; } //max, current

    public enum State { ALIVE,DIE,}
    public State CurState { get;private set;}

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void SetData(int id, int maxHP)
    {
        if (ID != 0)
        {
            Debug.LogWarning(string.Format("[Player ID : {0}] 이미 설정됨 SetData() - name : {1} ",ID,name));
            return;
        }

        ID = id;
        MaxHP = maxHP;
        CurHP = maxHP;
        CheckAlive();
    }

    public void SetCallback(Callback_OnDied callback_OnDied)
    {
        if(onDied != null)
        {
            Debug.LogWarning(string.Format("[Player ID : {0}] 이미 설정됨 SetCallback() - name : {1} ", ID, name));
            return;
        }

        onDied = callback_OnDied;
        //onDied += callback_OnDied;
        //onDied += Die;
    }

    void Die(int id)
    {
        Debug.Log("죽었다 예제");
    }

    public void Hurt(int amount)
    {
        CurHP -= amount;
        Debug.Log(string.Format("[Player ID: {0}] Hurt ({1}) - curHP({2}) ",ID,amount,CurHP));
        CheckAlive();
    }
    void CheckAlive()
    {
        if(CurHP<=0)
        {
            CurHP = 0;
            //죽었다
            ChangeState(State.DIE);
            //if(onDied != null) onDied(ID);
            onDied?.Invoke(ID);
            return;
        }

        //살았다
        ChangeState(State.ALIVE);
    }

    void ChangeState(State newState)
    {
        if (CurState == newState) return;
        Debug.Log(string.Format("[PlayerID : {0}] Change State : {1} -> {2}", ID, CurState, newState));
        CurState = newState;
    }
}
