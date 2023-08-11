using System.Collections;
using System.Collections.Generic;
using UnityEngine;

abstract public class Charactor : MonoBehaviour
{
    public int HP;
    public int Attack;
    abstract public void Move();
    abstract public void AttackOther();
}

interface IAction
{

}
