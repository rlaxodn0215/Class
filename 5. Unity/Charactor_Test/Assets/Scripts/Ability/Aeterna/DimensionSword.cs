using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class DimensionSword : Aeterna, Ability
    {
        public GameObject Sword;

        public DimensionSword(GameObject _gameObject)
        {
            Sword = _gameObject;
        }

        public void Execution()
        {
            //���� �ִϸ��̼� ���, Į Ȱ��ȭ
            //���� Ÿ���� ���ٸ� ���Ÿ� ����
            //animator.SetBool("")
            Debug.Log("DimensionSword!");
        }
    }
}