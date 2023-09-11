using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public GameObject wallPrefab;
    public float interval = 2.0f;
    public float spaceInterval = 20.0f;

    IEnumerator Start()
    {
        while (true && !FlappyBirdManager.Instance.gameOver)
        {
            Instantiate(wallPrefab, transform.position + new Vector3(0.0f, Random.Range(-spaceInterval,spaceInterval),0.0f), transform.rotation);
            yield return new WaitForSeconds(interval);
        }
    }

}
