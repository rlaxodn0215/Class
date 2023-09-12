using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Player2D : MonoBehaviour
    {
        private Rigidbody2D rigidbody;
        float maxSpeed = 800f;
        new SpriteRenderer renderer;
        public GameObject Player_bullet;

        // Start is called before the first frame update
        void Start()
        {
            rigidbody = GetComponent<Rigidbody2D>();
            renderer = GetComponent<SpriteRenderer>();
        }

        // Update is called once per frame
        void Update()
        {
            float x = Input.GetAxis("Horizontal");
            float y = Input.GetAxis("Vertical");

            Flip_2D(x);
            Move_2(x, y);
            Shoot();


        }

        void Shoot()
        {
            if(Input.GetKeyDown(KeyCode.Space))
            {
                Instantiate(Player_bullet, transform.position, Quaternion.identity);
            }
        }

        void Flip_2D(float x)
        {
            if (Mathf.Abs(x) > 0)
            {
                if (x >= 0)
                    renderer.flipX = false;
                else
                    renderer.flipX = true;
            }
        }


        void Move_2(float x, float y)
        {
            Vector3 position = rigidbody.transform.position;
            position = new Vector3(position.x + (x * maxSpeed * Time.deltaTime),
                                   position.y + (y * maxSpeed * Time.deltaTime));

            rigidbody.MovePosition(position);
        }
        

        private void OnTriggerEnter2D(Collider2D collision)
        {
            if (collision.gameObject.tag == "Coin")
            {
                GameManager_2D.Instance.AddCoinScore();
            }
        }

        //void Move_1(float x, float y)
        //{
        //    rigidbody.AddForce(new Vector2(x * maxSpeed * Time.deltaTime, y * maxSpeed * Time.deltaTime));
        //}

        //private void OnCollisionEnter2D(Collision2D collision)
        //{
        //    if (collision.gameObject.tag == "Enemy")
        //    {
        //        Destroy(collision.gameObject, 0.5f);
        //    }
        //}
    }
}