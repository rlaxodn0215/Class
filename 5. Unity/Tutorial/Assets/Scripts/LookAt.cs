using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LookAt : MonoBehaviour
{
    public GameObject target = null;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        LookAt_3();
        
    }

    void LookAt_1()
    {
        Vector3 dirToTarget = target.transform.position - transform.position;
        transform.forward = dirToTarget.normalized;
    }

    void LookAt_2()
    {
        Vector3 dirToTarget = target.transform.position - transform.position;
        transform.LookAt(dirToTarget.normalized);
    }

    void LookAt_3()
    {
        Vector3 dirToTarget = target.transform.position - transform.position;
        transform.rotation = Quaternion.LookRotation(dirToTarget, Vector3.up);
        //Debug.Log(dirToTarget.normalized);
    }
}
