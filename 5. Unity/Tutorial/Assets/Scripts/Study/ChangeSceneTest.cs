using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangeSceneTest : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //if(Input.GetMouseButton(0))
        //{
        //    if (GameManager.Instance.changeScene == 0)
        //    {
        //        GameManager.Instance.ChangeScene();
        //    }
        //}

        if (Input.GetMouseButton(1))
        {
            if (GameManagerTest.Instance.changeScene == 0)
            {
                GameManagerTest.Instance.ChangeScene("End");
                GameManagerTest.Instance.changeScene++;
            }

            else if (GameManagerTest.Instance.changeScene == 1)
            {
                GameManagerTest.Instance.ChangeScene("Collision(2023_09_06)");
                GameManagerTest.Instance.changeScene++;
            }
        }
    }
    private void OnGUI()
    {
        if (GUI.Button(new Rect(100, 200, 200, 30), "¾À º¯°æ"))
        {

           if (GameManagerTest.Instance.changeScene == 0)
           {
                GameManagerTest.Instance.ChangeScene("End");
                GameManagerTest.Instance.changeScene++;
           }

           else if (GameManagerTest.Instance.changeScene == 1)
           {
                GameManagerTest.Instance.ChangeScene("Collision(2023_09_06)");
                GameManagerTest.Instance.changeScene++;
           }
            
        }
    }
}
