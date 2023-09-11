using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public GameObject wallPrefab;
    public float interval = 1.0f;

    IEnumerator Start()
    {
        while (true)
        {
            yield return new WaitForSeconds(interval);
        }
    }

}
