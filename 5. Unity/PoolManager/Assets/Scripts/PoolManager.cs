using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PoolManager : Singleton<PoolManager>
{
    [SerializeField]
    GameObject Obj;

    [SerializeField]
    Transform ObjRoot;

    [SerializeField]
    int InitObjectNum;

    [SerializeField]
    int SpawnObjectNum;

    [SerializeField]
    private List<Object> Objs = new List<Object>();

    [SerializeField]
    private Queue<int> ObjIDs = new Queue<int>();

    int AddObjectNum;

    // Start is called before the first frame update
    void Start()
    {
        CreateObjects(InitObjectNum);
    }

    // Update is called once per frame
    void Update()
    {
        KeyInput();
    }

    void CreateObjects(int objectNum)
    {
        Debug.Log("[PoolManager] CreatePlayers : #" + objectNum);
        AddObjectNum = objectNum;
        for(int i = 0; i<objectNum;i++)
        {
            int id = i + 1; 
            Objs.Add(CreateObject(id));
        }
    }

    Object CreateObject(int id)
    {
        GameObject gb = Instantiate(Obj, ObjRoot); //부모 아래에 소환
        gb.name = "Object -  " + id;
        gb.transform.position = ObjRoot.position;
        gb.transform.rotation = ObjRoot.rotation;

        ///////////////////////////////////////
        Object obj = gb.GetComponent<Object>();
        obj.SetID(id);
        obj.SetCallback(AddID);
        //////////////////////////////////////
        
        gb.SetActive(false);

        ObjIDs.Enqueue(id);

        Debug.Log("[PoolManager] Created Object ID : " + id);

        return obj;
    }

    Object CreateNewObject(int id)
    {
        GameObject gb = Instantiate(Obj, ObjRoot); //부모 아래에 소환
        gb.name = "Object -  " + id;
        gb.transform.position = ObjRoot.position;
        gb.transform.rotation = ObjRoot.rotation;

        Object obj = gb.GetComponent<Object>();
        obj.SetID(id);
        obj.SetCallback(AddID);

        Debug.Log("[PoolManager] Created new Object ID : " + id);

        return obj;
    }

    Object GetObject()
    {
        if (ObjIDs.Count > 0)
        {
            var ob = Objs.Find(item=>item.ObjID == ObjIDs.Peek());
            ObjIDs.Dequeue();
            ob.gameObject.SetActive(true);
            return ob;
        }

        else
        {
            var ob = CreateNewObject(++AddObjectNum);
            Objs.Add(ob);
            return (ob);
        }
    }

    void AddID(int id)
    {
        ObjIDs.Enqueue(id);
    }

    void KeyInput()
    {
        if(Input.GetKeyDown(KeyCode.Space))
        {
            GetObject();
        }
    }
}
