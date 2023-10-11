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
            PlayerSkillInput();
            CharactorUpdate();
        }

        void OnMove(InputValue value)
        {
            input = transform.TransformVector(new Vector3(value.Get<Vector2>().x, 0, value.Get<Vector2>().y));
            input.Normalize();
        }

        void OnJump()
        {
            if (grounded)
            {
                rigidbody.velocity = new Vector3(rigidbody.velocity.x, jumpHeight, rigidbody.velocity.z);
                grounded = false;
            }
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

        protected void OnCollisionEnter(Collision collision)
        {
            if(collision.gameObject.tag == "Enemy")
            {
                //��ô����
                //PlayerDamaged(collision.gameObject.playerName,10);
                //destory
            }
        }

        protected virtual void PlayerSkillInput(){}

        public void IsLocalPlayer()
        {
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