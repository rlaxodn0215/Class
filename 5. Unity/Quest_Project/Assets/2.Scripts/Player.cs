using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : Charactor, IAction
{
    [SerializeField]
    private int allowMoveSteps;
    public int AllowMoveSteps {get{return allowMoveSteps;}}

    private bool moveFinish;
    public bool MoveFinish{get{return moveFinish;} set{moveFinish = value;}}

    void Start()
    {
        HP = 100;
        Attack = 10;
        moveFinish = true;
    }

    public int PlayerHP { get { return HP; } set { HP = value; } }

    void Update()
    {

    }

    public void Walkable()
    {
        Vector3 diff = GameManager.Instance.Dest - gameObject.transform.position;
        float count = Mathf.Abs(diff.x) + Mathf.Abs(diff.z);

        if (count <= gameObject.GetComponent<Player>().AllowMoveSteps && count > 0)
        {
            //Debug.Log("걸을 수 있습니다.");
            gameObject.GetComponent<Player>().MoveFinish = false;
            GameManager.Instance.Steps -= (int)count;
            StartCoroutine(Move());
            //return true;
        }

        else
        {
            //Debug.Log("걸음 수가 부족합니다.");
            GameManager.Instance.ShowMoveableBlock();
            gameObject.GetComponent<Player>().MoveFinish = true;
            if (GameManager.Instance.Steps <= 0) GameManager.Instance.Turn();
            //return false;
        }


    }

    public override void CheckNearby()
    {

    }

    public override IEnumerator Move()
    {
        this.transform.position = Vector3.MoveTowards(transform.position,GameManager.Instance.Dest, 0.025f);
        yield return null;
    }

    void IAction.Attack()
    {

    }
}
