using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Heath : MonoBehaviour
{
    public int health;

    [Header("UI")]
    public Text healthText;

    [Photon.Pun.PunRPC]
    public void TakeDamage(int damage)
    {
        health -= damage;

        healthText.text = health.ToString();

        if(health<=0)
        {
            Destroy(gameObject);
        }
    }
}
