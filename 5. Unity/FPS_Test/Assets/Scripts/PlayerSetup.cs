using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerSetup : MonoBehaviour
{
    public PlayerMove playerMove;
    public GameObject camera;
    public GameObject UIs;
    public void IsLocalPlayer()
    {
        playerMove.enabled = true;
        camera.SetActive(true);
        UIs.SetActive(true);
    }
}
