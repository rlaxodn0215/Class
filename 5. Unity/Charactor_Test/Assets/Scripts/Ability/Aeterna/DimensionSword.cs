using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class DimensionSword : Ability
    {
        private Aeterna Player;
        public DimensionSword(Aeterna player)
        {
            Player = player;
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