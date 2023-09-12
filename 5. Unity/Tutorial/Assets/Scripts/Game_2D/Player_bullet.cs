using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Player_bullet : MonoBehaviour
    {
        Rigidbody2D rigidbody;
        private float bulletSpeed = 1300f;
        private void Start()
        {
            rigidbody = GetComponent<Rigidbody2D>();

            Invoke("Die", 4);
        }
        // Update is called once per frame
        void Update()
        {
            Move();
        }

        void Move()
        {
            Vector3 position = rigidbody.transform.position;
            position = new Vector3(position.x + (bulletSpeed * Time.deltaTime), rigidbody.transform.position.y);
            rigidbody.MovePosition(position);
        }

        void Die()
        {
            DestroyImmediate(gameObject);
        }
    }
}