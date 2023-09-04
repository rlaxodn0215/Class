using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OperateCar : MonoBehaviour
{
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
        CarControl();
    }

    void Initalize()
    {
        for(int i = 0; i< 2;i++)
        {
            frontWheels.Add(Wheels.transform.GetChild(i));
        }
    }

    void CarControl()
    {
        float moveHorizontal = 0.0f;
        float moveVertical = 0.0f;

        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D))
        {
            moveHorizontal = Input.GetAxis("Horizontal");
        }

        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.S))
        {
            moveVertical = Input.GetAxis("Vertical");
        }

        Move(moveVertical, moveHorizontal);
    }

    void Move(float moveVertical, float moveHorizontal)
    {
        float fixAngle = AngleFix(frontWheels[0].localRotation.eulerAngles.y, angleLimit);

        WheelRotate(moveVertical);
        WheelTurn(moveHorizontal,fixAngle,angleLimit);

        Vector3 temp = new Vector3(Mathf.Cos(fixAngle * Mathf.Deg2Rad), 0, -Mathf.Sin(fixAngle * Mathf.Deg2Rad));
        Vector3 way = (Vector3.right + temp).normalized;

        transform.Translate(way * moveSpeed * Time.deltaTime * moveVertical);
        transform.Rotate(Vector3.up, Time.deltaTime* fixAngle * moveVertical);
    }


    float AngleFix(float angle, float limit)
    {
        float ans = angle;
        if (ans >= 180) ans -= 360;
        return ans;
    }

    void WheelTurn(float moveHorizontal,float angle ,float limit)
    {
        foreach(Transform frontwheel in frontWheels)
        {
            if (angle > limit)
            {
                if (Input.GetKey(KeyCode.A))
                {
                    frontwheel.Rotate(Vector3.up, rotateSpeed * Time.deltaTime * moveHorizontal);
                }
                //frontwheel.rotation = Quaternion.Euler(new Vector3(0, limit, 0));
            }

            else if (angle < -limit)
            {
                if(Input.GetKey(KeyCode.D))
                {
                    frontwheel.Rotate(Vector3.up, rotateSpeed * Time.deltaTime * moveHorizontal);
                }
                //frontwheel.rotation = Quaternion.Euler(new Vector3(0, -limit, 0));
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
            for(int j =0;j<1;j++)
                Wheels.transform.GetChild(i).transform.GetChild(j).Rotate(Vector3.down, Mathf.Rad2Deg * 2 * moving);
        }

        for(int i = 2; i<4;i++)
        {
            Wheels.transform.GetChild(i).Rotate(Vector3.down, Mathf.Rad2Deg * 2 * moving);
        }
    }
}
