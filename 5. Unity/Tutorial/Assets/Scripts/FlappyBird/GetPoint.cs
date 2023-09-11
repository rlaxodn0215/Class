using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GetPoint : MonoBehaviour
{ 
    private void OnTriggerExit(Collider other)
    {
        FlappyBirdManager.Instance.GetPoint();
        Debug.Log("GetPoint");
    }
}
