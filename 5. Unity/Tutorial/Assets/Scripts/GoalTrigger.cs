using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoalTrigger : MonoBehaviour
{
    int num = 0;
    bool firstStart = true;
    private void OnTriggerEnter(Collider other)
    {
        if (firstStart)
        {
            num++;
            if (num >= 4)
            {
                num = 0;
                firstStart = false;
            }
        }

        else
        {
            GameManager.Instance.Rank = num + 1;
            GameManager.Instance.Names[num] = other.attachedRigidbody.name;
            GameManager.Instance.CarTimes[num] = GameManager.Instance.timer;

            if ((++GameManager.Instance.PassNum[other.attachedRigidbody.name]) >= 10)
            {
                GameManager.Instance.Loop--;
                GameManager.Instance.PassNum[other.attachedRigidbody.name] = 0;
            }

            Debug.Log("Rank: " + (num + 1) + ", Name: " + GameManager.Instance.Names[num] + ", Time: " + GameManager.Instance.CarTimes[num]);

            num++;
            if (num >= 4)
            {
                num = 0;
            }

        }
    }
}
