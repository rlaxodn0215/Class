using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayCasts : MonoBehaviour
{
    [Range(0, 50)] //�����̵� �ٷ� ���� ����
    public float distance = 10.0f;
    private RaycastHit rayHit;
    private Ray ray;

    private RaycastHit[] rayHits;

    void Start()
    {
        ray = new Ray();
        //ray = new Ray(transform.position, transform.forward);
    }

    // Update is called once per frame
    void Update()
    {
        Ray_4();
    }

    void Ray_4()
    {
        ray.origin = transform.position;
        ray.direction = transform.forward;

        rayHits = Physics.RaycastAll(ray, distance);

        for (int index = 0; index < rayHits.Length; index++)
        {
            if(rayHits[index].collider.gameObject.layer == LayerMask.NameToLayer("Box"))
                Debug.Log(rayHits[index].collider.gameObject.name + " hit!! - Layer");

            if (rayHits[index].collider.gameObject.tag == "Sphere")
                Debug.Log(rayHits[index].collider.gameObject.name + " hit!! - Tag");
        }
    }

    void Ray_3() // SphereCastAll ��ü ������� rayCast // physics.overlapSphere -> ����ź, �������� ���� ���� ���� ����
    {
        rayHits = Physics.SphereCastAll(ray, 2.0f,distance);
        string objName = "";
        foreach(RaycastHit hit in rayHits)
        {
            objName += hit.collider.name + ", ";
        }

        print(objName);
    }

    void Ray_2() // ������ �浹
    {
        rayHits = Physics.RaycastAll(ray, distance);
        
        for(int index = 0; index < rayHits.Length; index++)
        {
            Debug.Log(rayHits[index].collider.gameObject.name + " hit!!");
        }
    }

    void Ray_1() // �ϳ��� �浹
    {
        if(Physics.Raycast(ray.origin,ray.direction,out rayHit,distance))
        {
            Debug.Log(rayHit.collider.gameObject.name);
        }
    }

    private void OnDrawGizmos() // �� â���� ������
    {
        //Debug.DrawRay(ray.origin, ray.direction * distance, Color.red);
        Gizmos.DrawLine(ray.origin, ray.direction * distance + ray.origin);

        Gizmos.color = Color.yellow;
        Gizmos.DrawSphere(ray.origin, 0.1f);


        if(rayHits !=null) // �浹 ��ġ Ȯ��
        {
            for(int i = 0; i<rayHits.Length;i++)
            {
                // �浹 ��ġ
                Gizmos.color = Color.red;
                Gizmos.DrawSphere(rayHits[i].point,0.1f);

                // �´� ��ü�� ���� �� �׸���
                Gizmos.color = Color.cyan;
                Gizmos.DrawLine(transform.position, transform.forward * rayHits[i].distance + ray.origin);

                // normal vector
                Gizmos.color = Color.yellow;
                Gizmos.DrawLine(rayHits[i].point, rayHits[i].point + rayHits[i].normal);

                // reflection vector
                Gizmos.color = new Color(1.0f, 0.0f, 1.0f);
                Vector3 reflect = Vector3.Reflect(transform.forward, rayHits[i].normal); // ������ �� ã�ƺ���!! // Vector3, Physics, Mathf

                Gizmos.DrawLine(rayHits[i].point, rayHits[i].point + reflect);


            }
        }
    }
}
