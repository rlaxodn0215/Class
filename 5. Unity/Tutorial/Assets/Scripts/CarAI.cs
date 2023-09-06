using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarAI : MonoBehaviour
{
    [Range(0, 50)]
    public float lidarDistance = 20.0f;

    public GameObject Lidar;

    private Ray[] rays = new Ray[4];
    private RaycastHit[] rayHits = new RaycastHit[4];
    private float[] distances = new float[4];

    public float moveSpeed = 20.0f;
    public float rotateSpeed = 45.0f;
    private float E = 1.0f;

    Rigidbody rigidbody;

    // Start is called before the first frame update
    void Start()
    {
        rigidbody = gameObject.GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        MakeRays();
        RayHits();
        
    }

    private void FixedUpdate()
    {
        ControlingCar();
    }

    void MakeRays()
    {
        for (int i = 0; i < 4; i++)
        {
            rays[i].origin = Lidar.transform.position;
        }

        rays[0].direction = Lidar.transform.right + Lidar.transform.forward; // left, forward
        rays[1].direction = Lidar.transform.right - Lidar.transform.forward; // right, forward
        rays[2].direction = Lidar.transform.forward; // left
        rays[3].direction = - Lidar.transform.forward; // right

    }

    void RayHits()
    {
        for (int i = 0; i < 4; i++)
        {
            Physics.Raycast(rays[i].origin, rays[i].direction, out rayHits[i], lidarDistance);
            distances[i] = Vector3.Distance(rays[i].origin, rayHits[i].point);
        }

        //Debug.Log(distances[0]);
    }

    private void OnDrawGizmos() // ¾À Ã¢¿¡¸¸ º¸¿©Áü
    {

        for (int i = 0; i < 4; i++)
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

        if (distances[0] - distances[1] > E  && distances[2] - distances[3] > E)
        {
            moveHorizontal = -1.0f;
        }

        else if(distances[0] - distances[1] < -E && distances[2] - distances[3] < -E)
        {
            moveHorizontal = 1.0f;
        }

        //Debug.Log(distances[0]);
        //Debug.Log(distances[1]);
        //Debug.Log(distances[0] - distances[1]);
        //Debug.Log(moveHorizontal);

        Move(moveVertical, moveHorizontal);
    }

    void Move(float moveVertical, float moveHorizontal)
    {

        // rotation
        Quaternion deltaRot = Quaternion.Euler(new Vector3(0, moveHorizontal, 0) * rotateSpeed * Time.deltaTime);
        rigidbody.MoveRotation(rigidbody.rotation * deltaRot);

        //movement
        Vector3 move = transform.right * moveVertical;
        Vector3 newPos = rigidbody.position + move * moveSpeed * Time.deltaTime;
        rigidbody.MovePosition(newPos);

        //transform.Translate(Vector3.right * moveSpeed * Time.deltaTime * moveVertical);
        //transform.Rotate(Vector3.up, rotateSpeed * Time.deltaTime * moveHorizontal);
    }



}

