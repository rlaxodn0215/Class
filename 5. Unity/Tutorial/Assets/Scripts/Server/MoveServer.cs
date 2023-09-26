using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using Photon.Pun;
using Photon.Realtime;

public class MoveServer : MonoBehaviour
{
    [SerializeField]
    [Range(0, 10)]
    public float moveSpeed = 10.0f;

    PhotonView pv;

    // Start is called before the first frame update
    void Start()
    {
        pv = GetComponent<PhotonView>();
    }

    // Update is called once per frame
    void Update()
    {
        Input_Move();
    }

    void Input_Move()
    {
        if (!pv.IsMine) return;

        if(Input.GetKey(KeyCode.W))
        {
            float moveDelta = moveSpeed * Time.deltaTime;
            transform.Translate(Vector3.forward * moveDelta);
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        Debug.Log("Collision");

        if(pv !=null && pv.IsMine)
        {
            Debug.Log("Collision 1");
            PhotonView otherPV = collision.gameObject.GetComponent<PhotonView>();
            if(otherPV !=null && !otherPV.IsMine)
            {
                Debug.Log("Collision 2");
                pv.RPC("TTTT", RpcTarget.All, pv.ViewID, otherPV.ViewID, 100);
            }
        }
    }

    [PunRPC]
    void TTTT(int myID, int otherID, int damaged)
    {
        Debug.Log("damaged");
    }
}
