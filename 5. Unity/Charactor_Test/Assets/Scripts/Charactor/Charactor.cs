using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Player
{
    public enum PlayerStatus
    {
        Born,
        Damaged,
        Dead
    }

    public class Charactor : MonoBehaviour
    {
        [SerializeField]
        protected int Hp;
        [SerializeField]
        protected string PlayerName;
        [SerializeField]
        protected PlayerStatus Status;

        protected Animator animator;
        protected Rigidbody rigidbody;

        // <��ų ����, �ش� ��ų>
        protected Dictionary<string, Ability> Skills;

        //�÷��̾� �̵�, ��Ʈ��
        //Ű �Է� -> �ش� ��ų ���� ����
        // ���콺�� ���� �̵��� ���� ��ũ��Ʈ

        private void Start()
        {
            
        }

        private void Update()
        {
            
        }

        private void FixedUpdate()
        {
            
        }

        void PlayerMove()
        {

        }

        void PlayerAttack()
        {
            // �Էµ� ��ų ���� �� ���� �ش� ��ų ��� // ���������� �̿�
        }

    }
}