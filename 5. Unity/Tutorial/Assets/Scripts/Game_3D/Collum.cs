using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_3D
{

    public class Collum : MonoBehaviour
    {
        public int Hp = 100;
        private Color color;

        private void Start()
        {
            //color = GetComponent<Material>().color;
        }

        private void OnTriggerEnter(Collider other)
        {
            if (other.tag == "EnemySword")
            {
                Hp -= GameManager_3D.Instance.EnemySwordDamage;
               //Debug.Log(GetComponent<Material>().color.g);

                if (Hp <= 0)
                {
                    Destroy(gameObject);
                    GameManager_3D.Instance.CollumDead();
                }
            }
        }
    }
}
