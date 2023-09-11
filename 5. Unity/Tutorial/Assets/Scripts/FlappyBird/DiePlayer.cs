using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DiePlayer : MonoBehaviour
{
    private void OnCollisionEnter(Collision collision)
    {
        FlappyBirdManager.Instance.GameOver();
        Debug.Log("GameOver");
    }
}
