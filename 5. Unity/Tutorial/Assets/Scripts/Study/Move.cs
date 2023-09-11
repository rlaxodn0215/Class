using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    public float moveSpeed = 10.0f;

    // Start is called before the first frame update
    void Start()
    {
        //this.transform.position = new Vector3(0.0f, 5.0f, 0.0f); //world ¡¬«• ±‚¡ÿ
        transform.Translate(0.0f, 5.0f, 0.0f); // local ¡¬«• ±‚¡ÿ
    }

    // Update is called once per frame
    void Update()
    {
        //Move_1();
        //Move_2();
        Move_Control();
    }

    void Move_Control()
    {
        float move = Input.GetAxis("Vertical");
        transform.Translate(Vector3.forward * Time.deltaTime * moveSpeed * move);
    }


    void Move_1()
    {
        float moveDelta = moveSpeed * Time.deltaTime;
        Vector3 pos = this.transform.position;
        pos.z += moveDelta;
        transform.position = pos;
    }

    void Move_2()
    {
        float moveDelta = moveSpeed * Time.deltaTime;
        transform.Translate(Vector3.forward * moveDelta);
    }
}
