using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OperateHelicopter : MonoBehaviour
{
    public float moveSpeed = 10.0f;
    public float rotateSpeed = 45.0f;
    public float wingRotateSpeed = 145.0f;

    public GameObject Wing;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        HelicopterConrol();
    }

    void HelicopterConrol()
    {
        float moveHorizontal = 0.0f;
        float moveVertical = 0.0f;
        float TiltVertical = 0.0f;
        float UpVertical = 0.0f;

        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D))
        {
            moveHorizontal = Input.GetAxis("Horizontal");
        }

        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.S))
        {
            moveVertical = Input.GetAxis("Vertical");
        }

        if (Input.GetKey(KeyCode.UpArrow) || Input.GetKey(KeyCode.DownArrow))
        {
            TiltVertical = Input.GetAxis("Vertical");
        }

        if(Input.GetKey(KeyCode.Space))
        {
            UpVertical = 1.0f;
        }

        Move(moveVertical, moveHorizontal, TiltVertical, UpVertical);

        RotateWing(moveHorizontal);
    }


    void Move(float moveVertical, float moveHorizontal, float TiltVertical, float UpVertical)
    {
        transform.Translate(Vector3.left * moveSpeed * Time.deltaTime * moveVertical);
        transform.Translate(Vector3.up * moveSpeed * Time.deltaTime * UpVertical);
        transform.Rotate(Vector3.up * rotateSpeed * Time.deltaTime * moveHorizontal);
        transform.Rotate(Vector3.forward * rotateSpeed * Time.deltaTime * TiltVertical);
    }

    void RotateWing(float moveHorizontal)
    {
        Wing.transform.Rotate(Vector3.up, (wingRotateSpeed - moveHorizontal*rotateSpeed)*Time.deltaTime);
        //Debug.Log((1 + Mathf.Abs(moveHorizontal)) * Time.deltaTime * wingRotateSpeed);
        //Debug.Log(Mathf.Abs(moveHorizontal));

    }
}
