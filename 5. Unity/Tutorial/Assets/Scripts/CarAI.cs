using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarAI : MonoBehaviour
{
    [Range(0, 50)]
    public float lidarDistance = 20.0f;

    public GameObject Lidar;

    private Ray[] rays = new Ray[5];
    private RaycastHit[] rayHits = new RaycastHit[5];
    private float[] distances = new float[5];

    float moveHorizontal = 0.0f;
    float moveVertical = 0.0f;

    public float moveSpeed = 10.0f;

    public float angleLimit = 35.0f;
    public float rotateSpeed = 45.0f;

    public GameObject Wheels;

    [SerializeField]
    private List<Transform> frontWheels = new List<Transform>();

    // Start is called before the first frame update
    void Start()
    {
        Initalize();
    }

    // Update is called once per frame
    void Update()
    {
        MakeRays();
        RayHits();
        ControlDirection();
        Move(moveVertical, moveHorizontal);
    }

    void ControlDirection()
    {
        // 벽 사이 간격 동일
        float e = 0.05f;

        if (distances[1] > distances[2] + e)
        {
            moveHorizontal = -1.0f;
        }

        else if (distances[2] > distances[1] + e)
        {
            moveHorizontal = 1.0f;
        }

        //이동 로직

        //if()
    }

    void MakeRays()
    {
        for(int i = 0; i< 5;i++)
        {
            rays[i].origin = Lidar.transform.position;
        }

        rays[0].direction = Lidar.transform.right;      //forward
        rays[1].direction = Lidar.transform.forward;    //left
        rays[2].direction = - Lidar.transform.forward;  //right

        rays[3].direction = Lidar.transform.right + Lidar.transform.forward; // left, forward
        rays[4].direction = Lidar.transform.right - Lidar.transform.forward; // right, forward

    }

    void RayHits()
    {
        for (int i = 0; i < 5; i++)
        {
            Physics.Raycast(rays[i].origin, rays[i].direction, out rayHits[i], lidarDistance);
            //예외 조건 필요
            distances[i] = Vector3.Distance(rays[i].origin, rayHits[i].point);
        }

        //Debug.Log(distances[0]);
    }

    private void OnDrawGizmos() // 씬 창에만 보여짐
    {

        for (int i = 0; i < 5; i++)
        {
            Gizmos.color = Color.red;
            Gizmos.DrawLine(rays[i].origin, rays[i].direction * lidarDistance + rays[i].origin);

            Gizmos.color = Color.cyan;
            Gizmos.DrawSphere(rayHits[i].point, 0.1f);
        }

        Gizmos.color = Color.blue;
        Gizmos.DrawSphere(rays[0].origin, 0.1f);
        
    }

    void Initalize()
    {
        for (int i = 0; i < 2; i++)
        {
            frontWheels.Add(Wheels.transform.GetChild(i));
        }
    }

    void Move(float moveVertical, float moveHorizontal)
    {
        float fixAngle = AngleFix(frontWheels[0].localRotation.eulerAngles.y, angleLimit);

        WheelRotate(moveVertical);
        WheelTurn(moveHorizontal, fixAngle, angleLimit);

        Vector3 temp = new Vector3(Mathf.Cos(fixAngle * Mathf.Deg2Rad), 0, -Mathf.Sin(fixAngle * Mathf.Deg2Rad));
        Vector3 way = (Vector3.right + temp).normalized;

        transform.Translate(way * moveSpeed * Time.deltaTime * moveVertical);
        transform.Rotate(Vector3.up, Time.deltaTime * fixAngle * moveVertical);
    }


    float AngleFix(float angle, float limit)
    {
        float ans = angle;
        if (ans >= 180) ans -= 360;
        return ans;
    }

    void WheelTurn(float moveHorizontal, float angle, float limit)
    {
        foreach (Transform frontwheel in frontWheels)
        {
            if (angle > limit)
            {
                //if (Input.GetKey(KeyCode.A))
                {
                    frontwheel.Rotate(Vector3.up, rotateSpeed * Time.deltaTime * moveHorizontal);
                }
            }

            else if (angle < -limit)
            {
                //if (Input.GetKey(KeyCode.D))
                {
                    frontwheel.Rotate(Vector3.up, rotateSpeed * Time.deltaTime * moveHorizontal);
                }
            }

            else
            {
                frontwheel.Rotate(Vector3.up, rotateSpeed * Time.deltaTime * moveHorizontal);
            }
        }
    }

    void WheelRotate(float move)
    {
        float moving = moveSpeed * Time.deltaTime * move;

        for (int i = 0; i < 1; i++)
        {
            for (int j = 0; j < 1; j++)
                Wheels.transform.GetChild(i).transform.GetChild(j).Rotate(Vector3.down, Mathf.Rad2Deg * 2 * moving);
        }

        for (int i = 2; i < 4; i++)
        {
            Wheels.transform.GetChild(i).Rotate(Vector3.down, Mathf.Rad2Deg * 2 * moving);
        }
    }
}

