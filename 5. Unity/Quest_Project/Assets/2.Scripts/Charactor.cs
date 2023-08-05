using System.Collections;
using System.Collections.Generic;
using UnityEngine;

abstract public class Charactor : MonoBehaviour
{
    public int HP;
    public int Attack;
    abstract public IEnumerator Move();
    abstract public void CheckNearby();

}

interface IAction
{
    void Attack();
}
