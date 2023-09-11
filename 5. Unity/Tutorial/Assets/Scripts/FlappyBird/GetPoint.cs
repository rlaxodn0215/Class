using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GetPoint : MonoBehaviour
{ 
    private void OnTriggerExit(Collider other)
    {
        FlappyBirdManager.Instance.Points++;
        Debug.Log("GetPoint");
    }
}
