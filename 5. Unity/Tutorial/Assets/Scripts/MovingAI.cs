using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingAI : MonoBehaviour
{
    [Range(0, 50)]
    public float distance = 5.0f;

    public GameObject Lidar;

    private Ray[] rays = new Ray[8];
    private RaycastHit[] rayHits;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        MakeRays();
        LidarRotate();
    }

    void LidarRotate()
    {
        float rotateSpeed = 45.0f;
        Lidar.transform.Rotate(Vector3.up, rotateSpeed * Time.deltaTime);
    }

    void MakeRays()
    {
        for(int i = 0; i< 8;i++)
        {
            rays[i].origin = Lidar.transform.position;
        }

        rays[0].direction = Lidar.transform.forward;
        rays[1].direction = Lidar.transform.forward + Lidar.transform.right;
        rays[2].direction = Lidar.transform.right;
        rays[3].direction = Lidar.transform.right - Lidar.transform.forward;
        rays[4].direction = -Lidar.transform.forward;
        rays[5].direction = -Lidar.transform.forward - Lidar.transform.right;
        rays[6].direction = -Lidar.transform.right;
        rays[7].direction = -Lidar.transform.right + Lidar.transform.forward;

    }

    private void OnDrawGizmos() // ¾À Ã¢¿¡¸¸ º¸¿©Áü
    {

        for (int i = 0; i < 8; i++)
        {
            Gizmos.color = Color.red;
            Gizmos.DrawLine(rays[i].origin, rays[i].direction * distance + rays[i].origin);
        }

        Gizmos.color = Color.blue;
        Gizmos.DrawSphere(rays[0].origin, 0.1f);
        
    }
}
