using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Enemy : MonoBehaviour
    {
        public GameObject Enemy_bullet;
        private Rigidbody2D rigidbody;
        float maxSpeed = 350f;
        bool Damaged = false;
        private Animator animator;

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

        void Die()
        {
            DestroyImmediate(gameObject);
        }

        private void OnTriggerEnter2D(Collider2D collision)
        {
            if(collision.gameObject.tag=="Player_Bullet")
            {
                animator.SetBool("Damaged", true);
                GetComponent<SpriteRenderer>().color = Color.red;
                Destroy(collision.gameObject);
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