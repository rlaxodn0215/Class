using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StartScene : MonoBehaviour
{
    public void StartGame()
    {
        SceneManager.LoadScene("Flappy(2023_09_11)");
    }

    public void ExitGame()
    {
        Application.Quit(1);
        Debug.Log("게임 종료");
    }
}
