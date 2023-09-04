using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotate : MonoBehaviour
{
    public float speed = 10.0f;

    public GameObject target = null;

    // Start is called before the first frame update
    void Start()
    {
        //transform.eulerAngles = new Vector3(0.0f, 45.0f, 0.0f); // ���Ϸ� �� -> ������ �߻�
    }

    // Update is called once per frame
    void Update()
    {
        //Rotate_4();
        Rotate_Around();
    }

    void Rotate_Around()
    {
        float rot = speed * Time.deltaTime;
        //transform.RotateAround(new Vector3(0, 0.5f, 0), Vector3.up, rot);
        transform.RotateAround(target.transform.position, Vector3.up, rot);
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

    void Rotate_3()
    {
        float rot = speed * Time.deltaTime;
        transform.rotation *= Quaternion.AngleAxis(rot, Vector3.up);
    }

    void Rotate_4()
    {
        float rot = speed * Time.deltaTime;
        transform.Rotate(rot * Vector3.up);
    }
}
