using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace MazeGame
{
    public class Coin : MonoBehaviour
    {
        private void OnTriggerEnter(Collider other)
        {
            if (other.tag == "Player")
            {
                MazeGameManager.Instance.PlayerPoints++;
                MazeGameManager.Instance.SpawnCoin();
                gameObject.SetActive(false);
            }

            else 
            {
                MazeGameManager.Instance.SpawnCoin();
                gameObject.SetActive(false);
            }
        }
    }
}