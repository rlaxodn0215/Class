using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player.Aeterna
{
    public class DimensionSword : Player.Aeterna.Aeterna, Player.Ability
    {
        public bool IsPossible { get; set; }

        public void Execution()
        {
            //���� �ִϸ��̼� ���, Į Ȱ��ȭ
            //���� Ÿ���� ���ٸ� ���Ÿ� ����
            //animator.SetBool("")
            Debug.Log("DimensionSword!");
        }
    }
}