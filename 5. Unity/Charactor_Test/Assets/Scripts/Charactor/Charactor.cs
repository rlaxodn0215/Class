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

        // <스킬 슬롯, 해당 스킬>
        protected Dictionary<string, Ability> Skills;

        //플레이어 이동, 컨트롤
        //키 입력 -> 해당 스킬 슬롯 실행
        // 마우스로 시점 이동은 따로 스크립트

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
            // 입력된 스킬 슬롯 에 따라 해당 스킬 사용 // 디자인패턴 이용
        }

    }
}