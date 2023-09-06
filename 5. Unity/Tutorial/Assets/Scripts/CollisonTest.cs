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
        float rot = Input.GetAxis("Horizontal");
        float mov = Input.GetAxis("Vertical");

        rot = rot * speedRotate * Time.deltaTime;
        mov = mov * speedMove * Time.deltaTime;

        gameObject.transform.Rotate(Vector3.up * rot);
        gameObject.transform.Translate(Vector3.forward * mov);
    }

    private void OnCollisionEnter(Collision collision)
    {
        GameObject hitObject = collision.gameObject;
        print("Collison 面倒 : " + hitObject.name + "客 面倒 矫累");
    }
    private void OnCollisionStay(Collision collision)
    {
        GameObject hitObject = collision.gameObject;
        print("Collison 面倒 : " + hitObject.name + "客 面倒 吝");
    }

    private void OnCollisionExit(Collision collision)
    {
        GameObject hitObject = collision.gameObject;
        print("Collison 面倒 : " + hitObject.name + "客 面倒 场");
    }

    private void OnTriggerEnter(Collider other)
    {
        GameObject hitObject = other.gameObject;
        print("Trigger 面倒 : " + hitObject.name + "客 飘府芭 矫累");
    }

    private void OnTriggerStay(Collider other)
    {
        GameObject hitObject = other.gameObject;
        print("Trigger 面倒 : " + hitObject.name + "客 飘府芭 吝");
    }

    private void OnTriggerExit(Collider other)
    {
        GameObject hitObject = other.gameObject;
        print("Trigger 面倒 : " + hitObject.name + "客 飘府芭 场");
    }
}
