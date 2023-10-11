using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

namespace Player
{
    public enum PlayerCharactor
    {
        Aeterna,
        ElementalOrder
    }

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

        //[HideInInspector]
        public int Hp;
        [HideInInspector]
        public float moveSpeed;
        [HideInInspector]
        public float jumpHeight;
        [HideInInspector]
        public PlayerCharactor charactor;
        [HideInInspector]
        public PlayerData playerData;
        [HideInInspector]
        public Animator animator;
        [HideInInspector]
        public Rigidbody rigidbody;
        [HideInInspector]
        public Dictionary<string, Ability> Skills;

        private Vector3 input;
        private bool jumping;
        private bool grounded;

        protected void Start()
        {
            Initialize();
            CharactorInitialize();
        }

        void Initialize()
        {
            animator = GetComponent<Animator>();
            rigidbody = GetComponent<Rigidbody>();
            Skills = new Dictionary<string, Ability>();
            playerData = new PlayerData(playerName, "");
        }

        protected virtual void CharactorInitialize() { }

        protected void Update()
        {
            // 키 매니저
            input = transform.TransformVector(new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical")));
            input.Normalize();
            jumping = Input.GetKey(KeyCode.Space);

            PlayerSkillInput();
            CharactorUpdate();
        }

        protected virtual void CharactorUpdate() { }

        protected void FixedUpdate()
        {
            PlayerMove();
        }

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

        // 타워 거점 힐링 만들기
        //protected void 

        protected virtual void PlayerSkillInput(){}

    }
}