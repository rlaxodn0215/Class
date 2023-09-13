using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Game_2D
{
    public class Player2D : MonoBehaviour
    {
        private Rigidbody2D rigidbody;
        float maxSpeed = 800f;
        new SpriteRenderer renderer;
        public GameObject Player_bullet;
        public GameObject Player_Dynamite;

        [SerializeField]
        private int Hp = 100;

        private float skill = 1.0f;
        private float skillTime = 0.5f;
        
        public Image imgHpbar = null;
        public Image skillImage = null;

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

            Move_2(x, y);
            Shoot();
            ShowHpBar(Hp);
        }

        void ShowHpBar(int hp)
        {
            imgHpbar.fillAmount = (float)hp / 100.0f;
        }

        void Shoot()
        {
            if(Input.GetKeyDown(KeyCode.Space))
            {
                Instantiate(Player_bullet, transform.position, Quaternion.identity);
            }

            else if(Input.GetKey(KeyCode.Space))
            {
                if(skill > 0.0f)
                {
                    skill -= skillTime * Time.deltaTime;
                }
            }


            else if(Input.GetKeyUp(KeyCode.Space))
            {
                if(skill<=0.01f)
                {
                    //Debug.Log("필살기 사용");
                    Instantiate(Player_Dynamite, transform.position, Quaternion.identity);
                    skill = 1.0f;
                }
            }

            else
            {
                if (skill < 1.0f)
                {
                    skill += skillTime * Time.deltaTime;
                }
            }

            skillImage.fillAmount = skill;
        }



        //void Flip_2D(float x)
        //{
        //    if (Mathf.Abs(x) > 0)
        //    {
        //        if (x >= 0)
        //            renderer.flipX = false;
        //        else
        //            renderer.flipX = true;
        //    }
        //}


        void Move_2(float x, float y)
        {
            Vector3 position = rigidbody.transform.position;
            position = new Vector3(position.x + (x * maxSpeed * Time.deltaTime),
                                   position.y + (y * maxSpeed * Time.deltaTime));

            rigidbody.MovePosition(position);
        }
        

        private void OnTriggerEnter2D(Collider2D collision)
        {
            if(collision.gameObject.tag == "Enemy_Bullet")
            {
                GetComponent<SpriteRenderer>().color = Color.red;
                Invoke("ColorReturn", 0.2f);
                Hp -= 5;
                Destroy(collision.gameObject);
            }
        }


        void ColorReturn()
        {
            GetComponent<SpriteRenderer>().color = Color.white;
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