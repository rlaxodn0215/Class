using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class EndScene : MonoBehaviour
{
    public Text score;

    void Start()
    {
        if(FlappyBirdManager.Instance !=null)
            score.text = string.Format("{0}", FlappyBirdManager.Instance.Points);
    }

}
