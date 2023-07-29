using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move : MonoBehaviour
{
    public GameObject player;
    public Camera cam;
    public int steps;

    float rotX;
    float rotY;

    float senX = 1.5f;
    float senY = 1.5f;

    Ray ray;
    RaycastHit hit;

    Vector3 mousePos;
    Vector3 dest;


    // Start is called before the first frame update
    void Start()
    {
        //ray = new Ray(transform.position, Input.mousePosition);
    }

    // Update is called once per frame
    void Update()
    {
        mousePos = Input.mousePosition;
        mousePos.z = 100;
        mousePos = cam.ScreenToWorldPoint(mousePos);

        Debug.DrawRay(cam.transform.position, mousePos - cam.transform.position, Color.blue);

        if (Input.GetMouseButtonDown(0))
        {
            ray = cam.ScreenPointToRay(Input.mousePosition);
            if (Physics.Raycast(ray, out hit, Mathf.Infinity))
            {
                Debug.Log(hit.transform.position);
                dest = hit.transform.position;
                Walk();

            }
        }
    }

    void Walk()
    {
        Vector3 diff = dest - player.transform.position;
        float count = (Mathf.Abs(diff.x)+ Mathf.Abs(diff.z)) / 1.5f;

        if(count<=steps)
        {
            Debug.Log("걸을 수 있습니다.");
            Debug.Log(count);
            player.transform.position = new Vector3(dest.x, 1.5f, dest.z);
        }

        else
        {
            Debug.Log("걸음 수가 부족합니다.");
           

        }

    }

}

