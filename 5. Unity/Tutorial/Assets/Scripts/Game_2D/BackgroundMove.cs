using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_2D
{
    public class BackgroundMove : MonoBehaviour
    {
        private GameObject[] Images = new GameObject[2];
        private float moveSpeed = 50.0f;

        void Start()
        {
            for (int i = 0; i < 2; i++)
            {
                Images[i] = transform.GetChild(i).gameObject;
            }
        }

        // Update is called once per frame
        void Update()
        {
            ImageMove();
        }

        void ImageMove()
        {
            for (int i = 0; i < 2; i++)
            {
                Images[i].transform.Translate(new Vector3(-moveSpeed * Time.deltaTime, 0));
                if (Images[i].transform.position.x <= -960)
                {
                    Images[i].transform.position = new Vector3(955, 0, 0);
                }
            }
        }
    }
}