using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    public float moveSpeed = 5.0f;
    public float rotateSpeed = 60.0f;
    public float jumpHeight = 30f;

    private Rigidbody rigidbody;
    private Animator animator;
    private bool grounded = false;

    // Start is called before the first frame update
    void Start()
    {
        Init();
    }
    
    void Init()
    {
        rigidbody = GetComponent<Rigidbody>();
        animator = GetComponentInChildren<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        PlayerAni();
    }

    void FixedUpdate()
    {
        PlayerControl();
    }

    void PlayerControl()
    {
        Vector3 input = transform.TransformVector(new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical")));
        input.Normalize();

        rigidbody.MovePosition(rigidbody.transform.position + input * moveSpeed * Time.deltaTime);

    }

    void PlayerAni()
    {

    }
}