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
        public int Hp;
        public string PlayerName;
        public PlayerStatus Status;

        public Animator animator;
        public Rigidbody rigidbody;

        // <��ų ����, �ش� ��ų>
        protected Dictionary<string, Ability> Skills;

        // �÷��̾� �̵�, ��Ʈ��
        // Ű �Է� -> �ش� ��ų ���� ����
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