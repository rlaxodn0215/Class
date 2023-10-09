using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Photon.Pun;


public class DestroyPartical : MonoBehaviour
{
    IEnumerator Start()
    {
        yield return new WaitForSeconds(1f);
        GetComponent<PhotonView>().RPC("Gone", RpcTarget.AllBuffered);
    }

    [PunRPC]
    public void Gone()
    {
        Destroy(gameObject);
    }

}
