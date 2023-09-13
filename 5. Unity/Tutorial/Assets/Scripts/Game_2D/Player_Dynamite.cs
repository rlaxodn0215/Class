using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player_Dynamite : MonoBehaviour
{
    Rigidbody2D rigidbody;
    private float bulletSpeed = 1300f;
    private void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();

        Invoke("Die", 3.5f);
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
        Destroy(gameObject, 0.0f);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Enemy_Bullet")
        {
            Destroy(collision.gameObject);
        }
    }
}
