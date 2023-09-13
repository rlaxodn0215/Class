using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Enemy_bullet : MonoBehaviour
    {
        Rigidbody2D rigidbody;
        private float bulletSpeed = 800f;
        private void Start()
        {
            rigidbody = GetComponent<Rigidbody2D>();
            Invoke("Die", 2f);
        }
        // Update is called once per frame
        void Update()
        {
            Move();
        }

        void Move()
        {
            Vector3 position = rigidbody.transform.position;
            position = new Vector3(position.x - (bulletSpeed * Time.deltaTime), rigidbody.transform.position.y);

            rigidbody.MovePosition(position);
        }

        void Die()
        {
            DestroyImmediate(gameObject);
        }
    }
}