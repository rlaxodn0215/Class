using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Photon.Pun;
using Photon.Realtime;
public class RotateServer : MonoBehaviour
{

    public GameObject target = null;
    float rotateSpeed = 100.0f;

    PhotonView pv;

    // Start is called before the first frame update
    void Start()
    {
        pv = GetComponent<PhotonView>();
    }

    // Update is called once per frame
    void Update()
    {
        Input_Rotate();
    }

    void Input_Rotate()
    {
        if (!pv.IsMine) return;
        if (Input.GetKey(KeyCode.A))
        {
            float rot = rotateSpeed * Time.deltaTime;
            transform.Rotate(Vector3.up, -rot);
        }

        if (Input.GetKey(KeyCode.D))
        {
            float rot = rotateSpeed * Time.deltaTime;
            transform.Rotate(Vector3.up, rot);
        }
    }
}
