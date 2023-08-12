using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : Charactor, IAction
{
    [SerializeField]
    private int allowSteps = 1;
    public int AllowSteps { get { return allowSteps; } }

    private Vector3 destin;
    public Vector3 Destin { get{ return destin; } set { destin = value; } }

    public int hp { get { return HP; } set { HP = value; } }

    void Start()
    {
        HP = 20;
        Attack = 10;
    }
    public override void Move()
    {
        this.transform.position = Vector3.MoveTowards(transform.position, Destin, 0.025f);
    }

    public override bool AttackOther(int length)
    {
        GameManager.Instance.PlayerObj.GetComponent<Player>().PlayerHP -= Attack;
        Debug.LogWarning("플레이어가 공격을 받았다!! 현재 HP: " + GameManager.Instance.PlayerObj.GetComponent<Player>().PlayerHP);
        return true;
    }
}
