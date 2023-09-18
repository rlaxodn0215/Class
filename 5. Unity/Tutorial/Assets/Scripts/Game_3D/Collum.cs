using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_3D
{

    public class Collum : MonoBehaviour
    {
        public int Hp = 100;
        private Renderer render;

        private void Start()
        {
            render = GetComponent<Renderer>();
        }

        private void OnTriggerEnter(Collider other)
        {
            if (other.tag == "EnemySword")
            {
                Hp -= GameManager_3D.Instance.EnemySwordDamage;
                int rand = Random.Range(0, 4);

                switch (rand)
                {
                    case 0:
                        render.material.color = Color.yellow;
                        break;
                    case 1:
                        render.material.color = Color.cyan;
                        break;
                    case 2:
                        render.material.color = Color.red;
                        break;
                    case 3:
                        render.material.color = Color.blue;
                        break;
                    case 4:
                        render.material.color = Color.black;
                        break;
                }

                if (Hp <= 0)
                {
                    Destroy(gameObject);
                    GameManager_3D.Instance.CollumDead();
                }
            }
        }
    }
}
