using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireEffect : MonoBehaviour
{
    private float timer = 0.5f;
    void Start()
    {
        Destroy(gameObject, timer);
    }

}
