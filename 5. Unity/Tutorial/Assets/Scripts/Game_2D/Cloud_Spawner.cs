using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Cloud_Spawner : MonoBehaviour
    {
        public GameObject Cloud;
        private float spawnRange = 320;

        IEnumerator Start()
        {
            while (true)
            {
                Instantiate(Cloud, new Vector3(transform.position.x, Random.Range(-spawnRange, spawnRange)), Quaternion.identity);
                yield return new WaitForSeconds(1);
            }
        }

    }
}
