using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Coin_Spawner : MonoBehaviour
    {
        public GameObject coin;
        private float spawnRangeX = 400;
        private float spawnRangeY = 250;
        IEnumerator Start()
        {
            while (true)
            {
                Instantiate(coin, new Vector3(Random.Range(-spawnRangeX, spawnRangeX), Random.Range(-spawnRangeY, spawnRangeY)), Quaternion.identity);
                yield return new WaitForSeconds(3);
            }
        }
    }
}