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

        // Start is called before the first frame update
        void Start()
        {
            rigidbody = GetComponent<Rigidbody2D>();
            StartCoroutine(Shoot());
            Invoke("Die", 25f);
        }

        // Update is called once per frame
        void Update()
        {
            EnemyMove();
        }

        void EnemyMove()
        {
            Vector3 position = rigidbody.transform.position;
            position = new Vector3(position.x - (maxSpeed * Time.deltaTime), position.y);

            rigidbody.MovePosition(position);

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
    }
}