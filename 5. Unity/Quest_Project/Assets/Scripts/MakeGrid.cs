using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MakeGrid : MonoBehaviour
{

    public GameObject obj;
    public int rows;
    public int collums;
    private float size = 1.5f;
    // Start is called before the first frame update
    void Awake()
    {
        if(obj !=null)
        {
            GenerateGrid();
        }

        else
        {
            Debug.LogError("바닥 오브젝트를 할당하세요");
        }
    }

    void GenerateGrid()
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<collums;j++)
            {
                GameObject temp = Instantiate(obj, new Vector3(transform.position.x + size*i,0,transform.position.z + size*j), Quaternion.identity);
                temp.transform.SetParent(gameObject.transform);
            }
        }
    }

}
