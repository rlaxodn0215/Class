using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : Charactor, IAction
{

    [SerializeField]
    private int attack = 2;

    [SerializeField]
    private int allowSteps = 1;

    private Vector3 destin;
    public Vector3 Destin { get; set; }

    void Start()
    {
        HP = 100;
        Attack = 10;
    }

    void Update()
    {

    }

    public Vector3 EnemyDest()
    {
        Vector3 diff = GameManager.Instance.Dest - transform.position;
        Vector3 min = new Vector3(0, 0, 100);

        for (int i = -allowSteps; i <= allowSteps; i++)
        {
            for (int j = -allowSteps; j <= allowSteps; j++)
            {
                if (transform.position.x + i >= 0 && transform.position.x + i < 20 &&
                    transform.position.z + i >= 0 && transform.position.z + i < 30)
                {
                    if (Mathf.Abs(i) + Mathf.Abs(j) <= allowSteps && CheckNearbyObj(i,j))
                    {
                        Vector3 temp = new Vector3(i, 0, j);
                        Vector3 temp1 = diff - temp;
                        min = (Vector3.Magnitude(diff - min) < Vector3.Magnitude(temp1)) ? min : temp;

                    }
                }

            }
        }

        return (min + transform.position);
    }

    public bool EnemyMoveable(Vector3 dest)
    {

        if (Vector3.Magnitude(dest - transform.position) > 0)
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    public override IEnumerator Move()
    {
        this.transform.position = Vector3.MoveTowards(transform.position, Destin, 0.025f);
        yield return null;
    }

    public bool CheckNearbyObj(int i, int j)
    {
        Vector3 point = transform.position + new Vector3(i, 0, j);
        
        foreach(GameObject obj in GameManager.Instance.enemys)
        {
            if(obj.transform.position == point)
            {
                return false;
            }
        }

        if(GameManager.Instance.Dest == point)
        {
            AttackOther();
            return false;
        }


        return true;

    }

    public override void CheckNearby()
    {
        throw new System.NotImplementedException();
    }

    public void AttackOther()
    {
        GameManager.Instance.PlayerObj.GetComponent<Player>().PlayerHP -= Attack;
        Debug.LogWarning("플레이어가 공격을 받았다!! 현재 HP: " + GameManager.Instance.PlayerObj.GetComponent<Player>().PlayerHP);
    }

    void IAction.Attack()
    {
        throw new System.NotImplementedException();
    }
}
