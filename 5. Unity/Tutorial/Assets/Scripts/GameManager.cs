using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    private static GameManager sInstance;

    public static GameManager Instance
    {
        get
        {
            if (sInstance == null)
            {
                GameObject newGameObject = new GameObject("_GameManager");
                sInstance = newGameObject.AddComponent<GameManager>();
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
