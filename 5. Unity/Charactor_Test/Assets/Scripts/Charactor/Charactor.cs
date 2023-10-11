using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

namespace Player
{
    // 플레이어 캐릭터 종류 파악
    public enum PlayerCharactor
    {
        Aeterna,
        ElementalOrder
    }

    // 서버에 사망 및 살인자를 알리기 위한 코드
    public struct PlayerData
    {
        public string playerName;
        public string murder;

        public PlayerData(string name, string murder)
        {
            this.playerName = name;
            this.murder = murder;
        }
    }

    public class Charactor : MonoBehaviour
    {
        public string playerName;
        public int Hp;
        public PlayerCharactor charactor;

        [HideInInspector]
        public float moveSpeed;
        [HideInInspector]
        public float jumpHeight;
        [HideInInspector]
        public PlayerData playerData;
        [HideInInspector]
        public Animator animator;
        [HideInInspector]
        public Rigidbody rigidbody;

        // 능력 넣는 Dictionary   
        [HideInInspector]
        public Dictionary<string, Ability> Skills;

        private Vector3 input;
        private bool jumping;
        private bool grounded;

        protected void Start()
        {
            Initialize();
            CharactorStart();
        }

        void Initialize()
        {
            animator = GetComponent<Animator>();
            rigidbody = GetComponent<Rigidbody>();
            Skills = new Dictionary<string, Ability>();
            playerData = new PlayerData(playerName, "");
        }

        // 캐릭터에 따른 초기화
        protected virtual void CharactorStart() { }

        protected void Update()
        {
            input = transform.TransformVector(new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical")));
            input.Normalize();
            jumping = Input.GetKey(KeyCode.Space);

            PlayerSkillInput();
            CharactorUpdate();
        }

        // 캐릭터에 따른 Update
        protected virtual void CharactorUpdate() { }

        protected void FixedUpdate()
        {
            PlayerMove();
        }

        //바닥 콜라이더 접촉 확인
        protected void OnTriggerEnter(Collider other)
        {
            grounded = true;
        }

        protected void PlayerMove()
        {
            rigidbody.MovePosition(rigidbody.transform.position + input * moveSpeed * Time.deltaTime);

            if (jumping && grounded)
            {
                rigidbody.velocity = new Vector3(rigidbody.velocity.x, jumpHeight, rigidbody.velocity.z);
                grounded = false;
            }
        }

        // 타워 거점 힐링
        protected void OnCollisionStay(Collision collision)
        {
            //if(collision.gameObject.tag == "탑")

            if(Input.GetKey(KeyCode.F))
            {
                Debug.Log("Healing");
            }
        }

        protected virtual void PlayerSkillInput(){}

    }
}