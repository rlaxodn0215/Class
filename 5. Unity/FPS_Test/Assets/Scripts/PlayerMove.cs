using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    public float moveSpeed = 5.0f;
    public float jumpHeight = 30f;

    private Rigidbody rigidbody;

    private Vector3 input;
    private bool jumping;
    private bool grounded;

    // Start is called before the first frame update
    void Start()
    {
        Init();
    }

    void Init()
    {
        rigidbody = GetComponent<Rigidbody>();
    }

    private void OnTriggerEnter(Collider other)
    {
        grounded = true;
    }

    // Update is called once per frame
    void Update()
    {
        input = transform.TransformVector(new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical")));
        input.Normalize();
        jumping = Input.GetKey(KeyCode.Space);
    }

    void FixedUpdate()
    {
        PlayerControl();
    }

    void PlayerControl()
    {
        rigidbody.MovePosition(rigidbody.transform.position + input * moveSpeed * Time.deltaTime);

        if (jumping && grounded)
        {
            rigidbody.velocity = new Vector3(rigidbody.velocity.x, jumpHeight, rigidbody.velocity.z);
            grounded = false;
        }
    }


}
