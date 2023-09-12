using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    private Rigidbody2D rigidbody;
    float maxSpeed = 100f;

    // Start is called before the first frame update
    void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        EnemyMove();
    }

    void EnemyMove()
    {
        Vector3 position = rigidbody.transform.position;
        position = new Vector3(position.x - (maxSpeed * Time.deltaTime),position.y);

        rigidbody.MovePosition(position);

    }
}
