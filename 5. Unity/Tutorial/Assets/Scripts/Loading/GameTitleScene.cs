using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Loading
{
    public class GameTitleScene : MonoBehaviour
    {
        // Start is called before the first frame update
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {

        }

        void GoNextScene()
        {
            GameManager.Instance.nextSceneName = "MazeGame";
            SceneManager.LoadScene("Loading");
        }
    }
}