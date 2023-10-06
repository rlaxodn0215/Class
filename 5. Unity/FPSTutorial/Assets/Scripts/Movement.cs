using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour
{
    public float walkSpeed = 8f;
    public float sprintSpeed = 14f;
    public float maxVelocityChange = 10f;
    [Space]
    public float airControl = 0.5f;

    [Space]
    public float jumpHeight = 30f;

    private Vector2 input;
    private Rigidbody rigidbody;

    private bool sprinting;
    private bool jumping;

    private bool grounded = false;

    // Start is called before the first frame update
    void Start()
    {
        rigidbody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        input = new Vector2(x: Input.GetAxis("Horizontal"), y: Input.GetAxisRaw("Vertical"));
        input.Normalize();

        sprinting = Input.GetButton("Sprint");
        jumping = Input.GetButton("Jump");
    }

    private void OnTriggerStay(Collider other)
    {
        grounded = true;
    }

    private void FixedUpdate()
    {
        if (grounded)
        {
            if (jumping)
            {
                rigidbody.velocity = new Vector3(rigidbody.velocity.x, jumpHeight, rigidbody.velocity.z);
            }
            else
            {
                rigidbody.AddForce(CalculateMovement(sprinting ? sprintSpeed : walkSpeed), ForceMode.VelocityChange);
            }
        }

        else
        {
            rigidbody.AddForce(CalculateMovement(sprinting ? sprintSpeed*airControl : walkSpeed*airControl), ForceMode.VelocityChange);
        }

        grounded = false;
    }

    Vector3 CalculateMovement(float speed)
    {
        Vector3 targetVelocity = new Vector3(input.x, y: 0, z: input.y);
        targetVelocity = transform.TransformDirection(targetVelocity);

        targetVelocity *= speed;

        Vector3 velocity = rigidbody.velocity;

        if(input.magnitude > 0.5f)
        {
            Vector3 velocityChange = targetVelocity - velocity;
            velocityChange.x = Mathf.Clamp(value: velocityChange.x, min: -maxVelocityChange, max: maxVelocityChange);
            velocityChange.y = Mathf.Clamp(value: velocityChange.y, min: -maxVelocityChange, max: maxVelocityChange);

            velocityChange.y = 0;

            return velocityChange;
        }

        else
        {
            return new Vector3();
        }
    }
}
