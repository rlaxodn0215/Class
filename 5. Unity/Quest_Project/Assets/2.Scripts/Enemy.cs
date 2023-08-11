using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : Charactor, IAction
{
    [SerializeField]
    private int allowSteps = 2;
    public int AllowSteps { get { return allowSteps; } }

    private Vector3 destin;
    public Vector3 Destin { get{ return destin; } set { destin = value; } }

    void Start()
    {
        HP = 100;
        Attack = 10;
    }
    public override void Move()
    {
        this.transform.position = Vector3.MoveTowards(transform.position, Destin, 0.025f);
    }

    public override void AttackOther()
    {
        GameManager.Instance.PlayerObj.GetComponent<Player>().PlayerHP -= Attack;
        Debug.LogWarning("플레이어가 공격을 받았다!! 현재 HP: " + GameManager.Instance.PlayerObj.GetComponent<Player>().PlayerHP);
    }
}
