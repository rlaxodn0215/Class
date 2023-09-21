using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerWithIK : MonoBehaviour
{
    [Range(0, 1)]
    public float posWeight = 1;

    [Range(0, 1)]
    public float rotWeight = 1;

    public enum PlayerState { GROUND, WALL }

    public float moveSpeed = 7.0f;
    public float rotateSpeed = 240.0f;
    public PlayerState playerState = PlayerState.GROUND;

    public GameObject IKs;
    private Dictionary<string, GameObject> ik = new Dictionary<string, GameObject>();
    private Dictionary<string, Vector3> ikFirstPos = new Dictionary<string, Vector3>();
    private float climbTimer = 0.0f;

    private Animator animator;
    private Rigidbody rigidbody;
    private float climbMagnitude = 0.2f;

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
        transform.Translate(Vector3.up * v * moveSpeed/2 * Time.deltaTime);
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

        if(startAtUp)
            ik[name].transform.localPosition = ikFirstPos[name] + new Vector3(0, Magnitude * Mathf.Cos(climbTimer), 0.3f);
        else
            ik[name].transform.localPosition = ikFirstPos[name] + new Vector3(0, Magnitude * Mathf.Sin(climbTimer), 0.3f);

        yield return null;
    }

    private void OnAnimatorIK(int layerIndex)
    {
        if (animator)
        {

            if (IKs != null)
            {
                ////ÃÖÀûÈ­
                //for(int i = 0; i < 4; i++)
                //{

                //}

                // Right Hand
                animator.SetIKPositionWeight(AvatarIKGoal.RightHand, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.RightHand, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.RightHand, ik["RightHand"].transform.position);

                Quaternion RightHandRotation = Quaternion.LookRotation(ik["RightHand"].transform.position - transform.position);
                animator.SetIKRotation(AvatarIKGoal.RightHand, RightHandRotation);

                //Left Hand
                animator.SetIKPositionWeight(AvatarIKGoal.LeftHand, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.LeftHand, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.LeftHand, ik["LeftHand"].transform.position);

                Quaternion LeftHandRotation = Quaternion.LookRotation(ik["LeftHand"].transform.position - transform.position);
                animator.SetIKRotation(AvatarIKGoal.LeftHand, LeftHandRotation);

                //Right Foot
                animator.SetIKPositionWeight(AvatarIKGoal.RightFoot, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.RightFoot, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.RightFoot, ik["RightFoot"].transform.position);

                Quaternion RightFootRotation = Quaternion.LookRotation(ik["RightFoot"].transform.position - transform.position);
                animator.SetIKRotation(AvatarIKGoal.RightFoot, RightFootRotation);

                //Left Foot
                animator.SetIKPositionWeight(AvatarIKGoal.LeftFoot, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.LeftFoot, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.LeftFoot, ik["LeftFoot"].transform.position);

                Quaternion LeftFootRotation = Quaternion.LookRotation(ik["LeftFoot"].transform.position - transform.position);
                animator.SetIKRotation(AvatarIKGoal.LeftFoot, LeftFootRotation);
            }
        }
    }


    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag =="Wall")
        {
            Debug.Log("Contact Wall");
            playerState = PlayerState.WALL;
            rigidbody.useGravity = false;
        }

        else
        {
            Debug.Log("Contact Ground");
            playerState = PlayerState.GROUND;
            rigidbody.useGravity = true;
            climbTimer = 0.0f;
        }
    }

}
