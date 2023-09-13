using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Coin : MonoBehaviour
    {
        // Start is called before the first frame update
        void Start()
        {
            Invoke("Die", 7);
        }
        
        void Die()
        {
            DestroyImmediate(gameObject);
        }

        private void OnTriggerEnter2D(Collider2D collision)
        {
            if (collision.gameObject.tag == "Player")
            {
                GameManager_2D.Instance.AddCoinScore();
                gameObject.SetActive(false);
            }
        }
    }
}