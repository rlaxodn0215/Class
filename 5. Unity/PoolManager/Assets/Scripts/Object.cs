using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Object : MonoBehaviour
{
    public delegate void Callback_Disapear(int id);
    Callback_Disapear onDisapear;

    public int ObjID { get; private set; }

    private float time = 0f;
    private float randTime = 0f;

    void Start()
    {
        randTime = Random.Range(2.0f, 5.0f);
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
        transform.Translate(new Vector3(0.01f, 0, 0));
        DisActive();
    }

    public void SetID(int id)
    {
        ObjID = id;
    }
    
    void DisActive()
    {
        if(time> randTime)
        {
            time = 0f;
            transform.position = new Vector3(0, 0, 0);
            gameObject.SetActive(false);
            onDisapear(ObjID);
        }
    }

    public void SetCallback(Callback_Disapear callback_OnDisapear)
    {
        onDisapear = callback_OnDisapear;
    }
}