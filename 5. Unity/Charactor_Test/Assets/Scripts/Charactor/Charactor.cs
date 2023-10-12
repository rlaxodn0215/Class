using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.InputSystem;
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
        public GameObject camera;
        public GameObject UI;

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
        private bool grounded;

        protected void Start()
        {
            //gameObject.tag = "Friendly";
            Initialize();
            CharactorStart();
        }
        protected void Update()
        {
            PlayerSkillInput();
            CharactorUpdate();
        }

        protected void FixedUpdate()
        {
            PlayerMove();
            CharactorFixedUpdate();
        }
        // ĳ���Ϳ� ���� �ʱ�ȭ
        protected virtual void CharactorStart() { }
        // ĳ���Ϳ� ���� Update
        protected virtual void CharactorUpdate() { }
        protected virtual void PlayerSkillInput() { }
        protected virtual void CharactorFixedUpdate() { }

        void Initialize()
        {
            animator = GetComponent<Animator>();
            rigidbody = GetComponent<Rigidbody>();
            Skills = new Dictionary<string, Ability>();
            playerData = new PlayerData(playerName, "");
        }

        void OnMove(InputValue value)
        {
            input = transform.TransformVector(new Vector3(value.Get<Vector2>().x, 0, value.Get<Vector2>().y));
            input.Normalize();
        }

        protected void PlayerMove()
        {
            rigidbody.MovePosition(rigidbody.transform.position + input * moveSpeed * Time.deltaTime);
        }

        void OnJump()
        {
            if (grounded)
            {
                rigidbody.velocity = new Vector3(rigidbody.velocity.x, jumpHeight, rigidbody.velocity.z);
                grounded = false;
            }
        }

        //�ٴ� �ݶ��̴� ���� Ȯ��
        protected void OnTriggerEnter(Collider other)
        {
            grounded = true;
        }

        protected void OnCollisionEnter(Collision collision)
        {
            if (collision.gameObject.tag == "Enemy")
            {
                //��ô����
                //PlayerDamaged(collision.gameObject.playerName,10);
                //destory
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
        public void IsLocalPlayer()
        {
            GetComponent<PlayerInput>().enabled = true;
            camera.SetActive(true);
            UI.SetActive(true);
        }

        [PunRPC]
        public void PlayerDamaged(string enemy ,int damage)
        {
            Hp-=damage;
            if (Hp <= 0)
            {
                // ��ô ���⿡ �� ��� �̸� ����
                // playerData.murder = tag.gameObject.playerName;
                // ��Ʈ ��ĵ�� ��� RPC�� �� ��� �̸� �Ű������� ����
                // ���� �� ������ ���� 
                //GetComponent<PhotonView>().RPC("TakeDamage", RpcTarget.All, );
            }
        }

        //public void PlayerDead(PlayerData data)
        //{
        //    Debug.Log("player dead");
        //}

    }
}