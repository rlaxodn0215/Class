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
                MazeGameManager.Instance.PlayerPoints+=100;
                MazeGameManager.Instance.SpawnCoin();
                MazeGameManager.Instance.ShowScore();
                gameObject.SetActive(false);
            }

            else if(other.tag == "Enemy")
            {
                MazeGameManager.Instance.SpawnCoin();
                gameObject.SetActive(false);
            }
        }
    }
}