using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sensor : MonoBehaviour
{
    int num = 0;
    //string passed = "";
    private void OnTriggerEnter(Collider other)
    {
        



        //if (passed != other.attachedRigidbody.name)
        //{

            //Debug.Log(other.attachedRigidbody.name);
            //passed = other.attachedRigidbody.name;
            GameManager.Instance.Names[num] = other.attachedRigidbody.name;
            GameManager.Instance.Times[num] = GameManager.Instance.timer;
            //GameManager.Instance.CheckSensors[other.attachedRigidbody.name]++;

            //Debug.Log("Rank: " + (num + 1) + ", Name: " + GameManager.Instance.Names[num] + ", Time: " + GameManager.Instance.Times[num]);

            //num++;
            //if (num >= 4)
            //{
            //    num = 0;
            //}

        //}

    }
}
