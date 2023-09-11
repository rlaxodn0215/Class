using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sensor : MonoBehaviour
{
    int num = 0;
    //string passed = "";
    private void OnTriggerEnter(Collider other)
    {
        GameManager.Instance.Rank = num + 1;
        GameManager.Instance.Names[num] = other.attachedRigidbody.name;
        GameManager.Instance.CarTimes[num] = GameManager.Instance.timer;
        GameManager.Instance.PassNum[other.attachedRigidbody.name]++;

        Debug.Log("Rank: " + (num + 1) + ", Name: " + GameManager.Instance.Names[num] + ", Time: " + GameManager.Instance.CarTimes[num]);

        num++;
        if (num >= 4)
        {
            num = 0;
        }
    }
}
