using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlappyBird : MonoBehaviour
{
    public float jumpPower = 5.0f;
    public float rotationAngle = 20.0f;
    public float maxRotationAngle = 65.0f;
    Rigidbody rigidbody;

    private Transform charactor;

    // Start is called before the first frame update
    void Start()
    {
        rigidbody = GetComponent<Rigidbody>();
        charactor = transform.GetChild(0);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space) && !FlappyBirdManager.Instance.gameOver)
        {
            if(transform.position.y <= 4.5f)
                rigidbody.velocity = new Vector3(0.0f, jumpPower, 0.0f);
        }

        if(transform.position.y < -5.5f )
        {
            FlappyBirdManager.Instance.GameOver();
        }

    }

    private void FixedUpdate()
    {
        charactor.Rotate(Vector3.left, rotationAngle * rigidbody.velocity.y * Time.deltaTime);
    }

    float AngleFix(float angle)
    {
        float ans = angle;
        if (ans >= 180) ans -= 360;
        return ans;
    }
}
