using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoalTrigger : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        if (other.transform.parent.gameObject.tag== "Player")
        {


            GameManager.Instance.Loop--;
            //Debug.Log("�÷��̾� ����!");
        }
    }
}
