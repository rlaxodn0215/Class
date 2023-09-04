using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotate : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        transform.eulerAngles = new Vector3(0.0f, 45.0f, 0.0f); // ���Ϸ� �� -> ������ �߻�

    }

    // Update is called once per frame
    void Update()
    {
        Rotate_2();
    }

    void Rotate_1()
    {
        Quaternion target = Quaternion.Euler(0.0f, 45.0f, 0.0f); // world ����
        transform.rotation = target;
    }

    void Rotate_2()
    {
        transform.Rotate(Vector3.up, 45.0f) ;
    }
}
