using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerSetup : MonoBehaviour
{
    public Movement movement;

    public GameObject camera;

    public GameObject UIs;

    public void IsLocalPlayer()
    {
        movement.enabled = true;
        camera.SetActive(true);
        UIs.SetActive(true);
    }
}
