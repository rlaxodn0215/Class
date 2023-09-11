using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisonTest : MonoBehaviour
{
    float speedMove = 10.0f;
    float speedRotate = 100.0f;
    Rigidbody rigidbody;

    // Start is called before the first frame update
    void Start()
    {
        rigidbody = gameObject.GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        //float rot = Input.GetAxis("Horizontal");
        //float mov = Input.GetAxis("Vertical");

        //rot = rot * speedRotate * Time.deltaTime;
        //mov = mov * speedMove * Time.deltaTime;

        //gameObject.transform.Rotate(Vector3.up * rot);
        //gameObject.transform.Translate(Vector3.forward * mov);
    }

    private void FixedUpdate()
    {
        float rot = Input.GetAxis("Horizontal");
        float mov = Input.GetAxis("Vertical");

        // rotation
        Quaternion deltaRot = Quaternion.Euler(new Vector3(0, rot, 0) * speedRotate * Time.deltaTime);
        rigidbody.MoveRotation(rigidbody.rotation * deltaRot);

        //movement
        Vector3 move = transform.forward * mov;
        Vector3 newPos = rigidbody.position + move * speedMove * Time.deltaTime;
        rigidbody.MovePosition(newPos);

    }

    private void OnCollisionEnter(Collision collision)
    {
        GameObject hitObject = collision.gameObject;
        print("Collison �浹 : " + hitObject.name + "�� �浹 ����");
    }
    private void OnCollisionStay(Collision collision)
    {
        GameObject hitObject = collision.gameObject;
        print("Collison �浹 : " + hitObject.name + "�� �浹 ��");
    }

    private void OnCollisionExit(Collision collision)
    {
        GameObject hitObject = collision.gameObject;
        print("Collison �浹 : " + hitObject.name + "�� �浹 ��");
    }

    private void OnTriggerEnter(Collider other)
    {
        GameObject hitObject = other.gameObject;
        print("Trigger �浹 : " + hitObject.name + "�� Ʈ���� ����");
    }

    private void OnTriggerStay(Collider other)
    {
        GameObject hitObject = other.gameObject;
        print("Trigger �浹 : " + hitObject.name + "�� Ʈ���� ��");
    }

    private void OnTriggerExit(Collider other)
    {
        GameObject hitObject = other.gameObject;
        print("Trigger �浹 : " + hitObject.name + "�� Ʈ���� ��");
    }
}
