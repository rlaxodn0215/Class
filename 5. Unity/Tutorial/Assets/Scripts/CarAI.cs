using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarAI : MonoBehaviour
{
    [Range(0, 50)]
    public float lidarDistance = 20.0f;

    public GameObject Lidar;

    private Ray[] rays = new Ray[2];
    private RaycastHit[] rayHits = new RaycastHit[2];
    private float[] distances = new float[2];

    public float moveSpeed = 20.0f;
    public float rotateSpeed = 45.0f;
    private float E = 1.0f;

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        MakeRays();
        RayHits();
        ControlingCar();
    }

    void MakeRays()
    {
        for (int i = 0; i < 2; i++)
        {
            rays[i].origin = Lidar.transform.position;
        }

        rays[0].direction = Lidar.transform.right + Lidar.transform.forward; // left, forward
        rays[1].direction = Lidar.transform.right - Lidar.transform.forward; // right, forward

    }

    void RayHits()
    {
        for (int i = 0; i < 2; i++)
        {
            Physics.Raycast(rays[i].origin, rays[i].direction, out rayHits[i], lidarDistance);
            //예외 조건 필요
            distances[i] = Vector3.Distance(rays[i].origin, rayHits[i].point);
        }

        //Debug.Log(distances[0]);
    }

    private void OnDrawGizmos() // 씬 창에만 보여짐
    {

        for (int i = 0; i < 2; i++)
        {
            Gizmos.color = Color.red;
            Gizmos.DrawLine(rays[i].origin, rays[i].direction * lidarDistance + rays[i].origin);

            Gizmos.color = Color.cyan;
            Gizmos.DrawSphere(rayHits[i].point, 0.1f);
        }

        Gizmos.color = Color.blue;
        Gizmos.DrawSphere(rays[0].origin, 0.1f);
        
    }


    void ControlingCar()
    {
        float moveHorizontal = 0.0f;
        float moveVertical = 1.0f;

        if (distances[0] - distances[1] > E)
        {
            moveHorizontal = -1.0f;
        }

        else if(distances[0] - distances[1] < -E)
        {
            moveHorizontal = 1.0f;
        }

        //Debug.Log(moveHorizontal);

        Move(moveVertical, moveHorizontal);
    }

    void Move(float moveVertical, float moveHorizontal)
    {
        transform.Translate(Vector3.right * moveSpeed * Time.deltaTime * moveVertical);
        transform.Rotate(Vector3.up, rotateSpeed * Time.deltaTime * moveHorizontal);
    }



}

