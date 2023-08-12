using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Player : Charactor, IAction
{
    [SerializeField]
    private int allowMoveSteps;
    public int AllowMoveSteps {get{return allowMoveSteps;}}

    private bool moveFinish;
    public bool MoveFinish { get { return moveFinish; } set { moveFinish = value; } }

    public int HP_potionNum = 0;
    public bool hasArrow = false;

    public string weapon;
    void Start()
    {
        HP = 100;
        Attack = 10;
        moveFinish = true;
        weapon = "FIST";
    }

    public int PlayerHP { get { return HP; } set { HP = value; } }

    public override void Move()
    {
        this.transform.position = Vector3.MoveTowards(transform.position,GameManager.Instance.Dest, 0.025f);
    }

    public override bool AttackOther(int length)
    {
        if (weapon == "FIST" && length == 1) return true;
        else if (weapon == "ARROW" && length == 2) return true;
        return false;
    }
}
