using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Enemy_Spawner : MonoBehaviour
    {
        public GameObject enemy;
        private float spawnRange = 200;
        IEnumerator Start()
        {
            while (true)
            {
                Instantiate(enemy, new Vector3(transform.position.x, Random.Range(-spawnRange, spawnRange)), Quaternion.identity);
                yield return new WaitForSeconds(2.5f);
            }
        }
    }
}