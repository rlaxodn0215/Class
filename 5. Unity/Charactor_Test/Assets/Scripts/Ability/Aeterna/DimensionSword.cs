using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class DimensionSword : Ability
    {
        private Aeterna Player;
        private Animator animator;
        private GameObject Sword;
        public DimensionSword(Aeterna player)
        {
            Player = player;
            //animator = player.GetComponent<Animator>();
            //Sword = player.DimensionSword;
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