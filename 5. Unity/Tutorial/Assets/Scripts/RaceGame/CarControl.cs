using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarControl : MonoBehaviour
{
    public float moveSpeed = 10.0f;

    public float angleLimit = 35.0f;
    public float rotateSpeed = 45.0f;

    float moveHorizontal = 0.0f;
    public float moveVertical = 0.0f;

    public GameObject Wheels;

    [SerializeField]
    private List<Transform> frontWheels = new List<Transform>();

    Rigidbody rigidbody;

    private float SpeedControl = 1.5f;

    // Start is called before the first frame update
    void Start()
    {
        Initalize();
        rigidbody = gameObject.GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        ControlingCar();
    }

    void Initalize()
    {
        for(int i = 0; i< 2;i++)
        {
            frontWheels.Add(Wheels.transform.GetChild(i));
        }
    }

    void ControlingCar()
    {
        moveHorizontal = 0.0f;

        // Hand Control
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D))
        {
            moveHorizontal = Input.GetAxis("Horizontal");
        }

        if (Input.GetKey(KeyCode.W))
        {
            moveVertical += SpeedControl*Time.deltaTime;
            if (moveVertical > 1.0f)
            {
                moveVertical = 1.0f;
            }
        }

        if(Input.GetKey(KeyCode.S))
        {
            moveVertical -= SpeedControl * Time.deltaTime;
            if(moveVertical < -1.0f)
            {
                moveVertical = -1.0f;
            }
        }

        else
        {
            if(moveVertical < 0.02f)
            {
                moveVertical += SpeedControl / 10 * Time.deltaTime;
            }

            else if(moveVertical > 0.02f)
            {
                moveVertical -= SpeedControl / 10 * Time.deltaTime;
            }

            else
            {
                moveVertical = 0.0f;
            }
        }

         //Debug.Log(moveVertical);

        Move(moveVertical, moveHorizontal);
    }

    void Move(float moveVertical, float moveHorizontal)
    {
        float fixAngle = AngleFix(frontWheels[0].localRotation.eulerAngles.y, angleLimit);

        WheelRotate(moveVertical);
        WheelTurn(moveHorizontal,fixAngle,angleLimit);

        Vector3 temp = new Vector3(Mathf.Cos(fixAngle * Mathf.Deg2Rad), 0, -Mathf.Sin(fixAngle * Mathf.Deg2Rad));
        Vector3 way = (Vector3.right + temp).normalized;

        //transform.Translate(way * moveSpeed * Time.deltaTime * moveVertical);
        //transform.Rotate(Vector3.up, Time.deltaTime * fixAngle * moveVertical);

        // rotation
        Quaternion deltaRot = Quaternion.Euler(new Vector3(0, moveVertical, 0) * fixAngle * Time.deltaTime);
        rigidbody.MoveRotation(rigidbody.rotation * deltaRot);

        //movement
        Vector3 move = transform.right * moveVertical;
        Vector3 newPos = rigidbody.position + move * moveSpeed * Time.deltaTime;
        rigidbody.MovePosition(newPos);
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

        for (int i = 0; i < 2; i++)
        {
            Wheels.transform.GetChild(i).transform.GetChild(0).Rotate(Vector3.down, Mathf.Rad2Deg * 2 * moving);
        }

        for(int i = 2; i<4;i++)
        {
            Wheels.transform.GetChild(i).Rotate(Vector3.down, Mathf.Rad2Deg * 2 * moving);
        }
    }
}
