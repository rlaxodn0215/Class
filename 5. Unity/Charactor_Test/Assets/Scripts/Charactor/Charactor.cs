using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;
using Photon.Realtime;

namespace Player
{
    // �÷��̾� ĳ���� ���� �ľ�
    public enum PlayerCharactor
    {
        Aeterna,
        ElementalOrder
    }

    // ������ ��� �� �����ڸ� �˸��� ���� �ڵ�
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

        // �ɷ� �ִ� Dictionary   
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

        // ĳ���Ϳ� ���� �ʱ�ȭ
        protected virtual void CharactorStart() { }

        protected void Update()
        {
            input = transform.TransformVector(new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical")));
            input.Normalize();
            jumping = Input.GetKey(KeyCode.Space);

            PlayerSkillInput();
            CharactorUpdate();
        }

        // ĳ���Ϳ� ���� Update
        protected virtual void CharactorUpdate() { }

        protected void FixedUpdate()
        {
            PlayerMove();
        }

        //�ٴ� �ݶ��̴� ���� Ȯ��
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

        // Ÿ�� ���� ����
        protected void OnCollisionStay(Collision collision)
        {
            //if(collision.gameObject.tag == "ž")

            if(Input.GetKey(KeyCode.F))
            {
                Debug.Log("Healing");
            }
        }

        protected virtual void PlayerSkillInput(){}

    }
}