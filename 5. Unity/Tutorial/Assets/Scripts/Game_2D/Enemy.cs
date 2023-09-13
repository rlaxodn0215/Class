using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Game_2D
{
    public class Enemy : MonoBehaviour
    {
        public GameObject Enemy_bullet;
        private Rigidbody2D rigidbody;
        float maxSpeed = 350f;
        bool Damaged = false;
        private Animator animator;
        public GameObject effect;
        public Image imgHpbar = null;

        [SerializeField]
        private int Hp = 20;

        private bool dead = false;

        // Start is called before the first frame update
        void Start()
        {
            animator = GetComponent<Animator>();
            rigidbody = GetComponent<Rigidbody2D>();
            StartCoroutine(Shoot());
            Invoke("Die", 25f); 
        }

        // Update is called once per frame
        void Update()
        {
            EnemyMove(Damaged);
            ShowHpBar(Hp);
        }

        void ShowHpBar(int hp)
        {
            imgHpbar.fillAmount = (float)hp / 20.0f;
        }

        void EnemyMove(bool damaged)
        {
            if (!damaged)
            {
                Vector3 position = rigidbody.transform.position;
                position = new Vector3(position.x - (maxSpeed * Time.deltaTime), position.y);
                rigidbody.MovePosition(position);
            }
        }

        IEnumerator Shoot()
        {
            while (true)
            {
                Instantiate(Enemy_bullet, transform.position, Quaternion.identity);
                yield return new WaitForSeconds(1f);
            }
        }

        // GameManager_2D.Instance.AddKillScore();

        void Die()
        {
            Destroy(gameObject, 0.2f);
        }

        private void OnTriggerEnter2D(Collider2D collision)
        {
            if(collision.gameObject.tag=="Player_Bullet")
            {
                animator.SetBool("Damaged", true);
                GetComponent<SpriteRenderer>().color = Color.red;
                Instantiate(effect, collision.transform.position, Quaternion.identity);
                Destroy(collision.gameObject,0.0f);
                Hp -= 4;
                if(Hp<=0 && !dead)
                {
                    dead = true;
                    GameManager_2D.Instance.AddKillScore();
                    Die();
                }
                Damaged = true;
                Invoke("ColorReturn", 0.2f);
            }
        }

        private void OnTriggerStay2D(Collider2D collision)
        {
            if (collision.gameObject.tag == "Player_Dynamite")
            {
                animator.SetBool("Damaged", true);
                GetComponent<SpriteRenderer>().color = Color.red;
                Hp -= 4;
                if (Hp <= 0 && !dead)
                {
                    dead = true;
                    GameManager_2D.Instance.AddKillScore();
                    Die();
                }
                Damaged = true;
                Invoke("ColorReturn", 0.2f);
            }
        }

        void ColorReturn()
        {
            animator.SetBool("Damaged", false);
            GetComponent<SpriteRenderer>().color = Color.white;
            Damaged = false;
        }
    }
}