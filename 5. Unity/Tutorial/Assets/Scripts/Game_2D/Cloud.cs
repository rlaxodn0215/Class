using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class Cloud : MonoBehaviour
    {
        private float maxSpeed = 200.0f;

        private void Start()
        {
            Invoke("Die", 10);
        }

        void Update()
        {
            Move(Random.Range(0,maxSpeed));
        }

        void Move(float speed)
        {
            transform.Translate(new Vector3(-speed * Time.deltaTime, 0));
        }

        void Die()
        {
            DestroyImmediate(gameObject);
        }
    }
}