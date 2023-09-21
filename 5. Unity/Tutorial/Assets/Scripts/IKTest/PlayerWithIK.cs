using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerWithIK : MonoBehaviour
{
    [Range(0, 1)]
    public float posWeight = 1;

    [Range(0, 1)]
    public float rotWeight = 1;

    //[Range(0, 359)]
    //public float xRot = 0.0f;
    //[Range(0, 359)]
    //public float yRot = 0.0f;
    //[Range(0, 359)]
    //public float zRot = 0.0f;

    public enum PlayerState { GROUND, WALL }

    public float moveSpeed = 7.0f;
    public float rotateSpeed = 240.0f;
    public PlayerState playerState = PlayerState.GROUND;

    public GameObject IKs;
    protected Dictionary<string, GameObject> ik = new Dictionary<string, GameObject>();
    protected Dictionary<string, Vector3> ikFirstPos = new Dictionary<string, Vector3>();
    protected float climbTimer = 0.0f;

    protected Animator animator;
    protected Rigidbody rigidbody;
    protected float climbMagnitude = 0.2f;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        rigidbody = GetComponent<Rigidbody>();
        InitIKs();
    }

    void InitIKs()
    {
        for(int i = 0; i < IKs.transform.childCount; i++)
        {
            ik[IKs.transform.GetChild(i).name] = IKs.transform.GetChild(i).gameObject;
            ikFirstPos[IKs.transform.GetChild(i).name] = IKs.transform.GetChild(i).localPosition;
        }
    }

    // Update is called once per frame
    void Update()
    {
        PlayerControl(playerState);
    }

    void PlayerControl(PlayerState state)
    {
        switch (state)
        {
            case PlayerState.GROUND:
                MoveGround();
                break;
            case PlayerState.WALL:
                MoveWall();
                break;
        }
    }
    
    void MoveGround()
    {
        float h = Input.GetAxis("Horizontal");
        float v = Input.GetAxis("Vertical");

        transform.Translate(Vector3.forward * v * moveSpeed * Time.deltaTime);
        transform.Rotate(Vector3.up, h * rotateSpeed * Time.deltaTime);

        animator.SetFloat("Speed", Mathf.Abs(v));
    }

    void MoveWall()
    {
        animator.SetFloat("Speed", 0.0f);
        float v = Input.GetAxis("Vertical");
        transform.Translate(Vector3.up * v * moveSpeed/13 * Time.deltaTime);
        MoveAni(v);
    }

    void MoveAni(float v)
    {
        if (v > 0.02f) // Move Up
        {
            StartCoroutine(Alternating("RightHand", true, climbMagnitude));
            StartCoroutine(Alternating("LeftHand", false, climbMagnitude));
            StartCoroutine(Alternating("LeftFoot", true, climbMagnitude));
            StartCoroutine(Alternating("RightFoot", false, climbMagnitude));

        }

        else if (v < -0.02f) // Move Down
        {
            StartCoroutine(Alternating("RightHand", false, climbMagnitude));
            StartCoroutine(Alternating("LeftHand", true, climbMagnitude));
            StartCoroutine(Alternating("LeftFoot", false, climbMagnitude));
            StartCoroutine(Alternating("RightFoot", true, climbMagnitude));
        }

        else //Stay
        {

        }

    }

    IEnumerator Alternating(string name, bool startAtUp, float Magnitude)
    {
       climbTimer += Time.deltaTime;
        //Debug.Log(climbTimer);

        if (startAtUp)
        {
            ik[name].transform.localPosition = ikFirstPos[name] + new Vector3(0, Magnitude * Mathf.Cos(1.5f * climbTimer), 0.05f);
        }
        else
        {
            ik[name].transform.localPosition = ikFirstPos[name] + new Vector3(0, Magnitude * Mathf.Sin(1.5f * climbTimer), 0.05f);
        }

        yield return null;
    }


    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag =="Wall")
        {
            Debug.Log("Contact Wall");
            playerState = PlayerState.WALL;

            if (rigidbody != null)
                rigidbody.useGravity = false;
            GetComponent<IKAnimator>().enabled = true;
        }

        else
        {
            Debug.Log("Contact Ground");
            playerState = PlayerState.GROUND;

            if(rigidbody !=null)
                rigidbody.useGravity = true;
            climbTimer = 0.0f;
            GetComponent<IKAnimator>().enabled = false;
        }
    }

}
