using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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
        if(other.tag == "EnemySword")
        {
           // Hp -= GameManager_3D.Instance.EnemySwordDamage;
            //color.g-=

            if(Hp<=0)
            {
                DestroyImmediate(gameObject);
                GameManager_3D.Instance.CollumDead();
            }
        }
    }
}
