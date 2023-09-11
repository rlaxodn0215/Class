using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TitleUI : MonoBehaviour
{
    public void StartGame()
    {
        SceneManager.UnloadSceneAsync("TitleUI");
        GameManager.Instance.curStatus = GameManager.Status.PLAY;
        GameManager.Instance.LoadUI();
    }

    public void EndGame()
    {
        Application.Quit();
        Debug.Log("게임 종료");
    }
}
