using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player2D : MonoBehaviour
{
    private Rigidbody2D rigidbody;
    float maxSpeed = 800f;
    new SpriteRenderer renderer;

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
    }

    void Flip_2D(float x)
    {
        if(Mathf.Abs(x) > 0)
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

    void Move_1(float x, float y)
    {
        rigidbody.AddForce(new Vector2(x * maxSpeed * Time.deltaTime, y *maxSpeed*Time.deltaTime));
    }
}
