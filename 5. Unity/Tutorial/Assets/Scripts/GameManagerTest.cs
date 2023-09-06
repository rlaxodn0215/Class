using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class GameManagerTest : MonoBehaviour
{
    private static GameManagerTest sInstance;

    public static GameManagerTest Instance
    {
        get
        {
            if (sInstance == null)
            {
                GameObject newGameObject = new GameObject("_GameManagerTest");
                sInstance = newGameObject.AddComponent<GameManagerTest>();
            }

            return sInstance;
        }
    }

    public int changeScene = 0;
        
    private void Awake()
    {
        if(sInstance !=null && sInstance !=this)
        {
            Destroy(gameObject);
            return;
        }

        sInstance = this;
        DontDestroyOnLoad(gameObject);
    }

    public void ChangeScene()
    {
        int scene = changeScene++ % 2; // 인덱스로 접근
        //string sceneName = string.Format("Scene_ {0:2d}", scene); // 이름으로 접근
        SceneManager.LoadScene(scene);
    }

    public void ChangeScene(string sceneName)
    {
        SceneManager.LoadScene(sceneName);
    }


}
