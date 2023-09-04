using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotate : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        transform.eulerAngles = new Vector3(0.0f, 45.0f, 0.0f); // 오일러 각 -> 집벌락 발생

    }

    // Update is called once per frame
    void Update()
    {
        Rotate_2();
    }

    void Rotate_1()
    {
        Quaternion target = Quaternion.Euler(0.0f, 45.0f, 0.0f); // world 기준
        transform.rotation = target;
    }

    void Rotate_2()
    {
        transform.Rotate(Vector3.up, 45.0f) ;
    }
}
