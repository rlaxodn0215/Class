using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Singleton<T> : MonoBehaviour where T :MonoBehaviour
{
    private static T instance;
    public static T Instance
    {
        get
        {
            if(instance==null) //�ν��Ͻ��� ������
            {
                instance = (T)FindObjectOfType(typeof(T)); //ã�´�

                if(instance==null) //�׷��� ������ ����
                {
                    GameObject obj = new GameObject(typeof(T).Name, typeof(T));
                    instance = obj.GetComponent<T>();
                }

            }

            return instance;
        }
    }

    private void Awake()
    {
        if(transform.parent !=null && transform.root !=null) // �Ŵ����� �ڽ����� �������� ��
        {
            DontDestroyOnLoad(this.transform.root.gameObject);
        }

        else
        {
            DontDestroyOnLoad(this.gameObject);
        }
    }
}
