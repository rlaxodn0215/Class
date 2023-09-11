using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EndScene : MonoBehaviour
{
    public Text score;

    void Start()
    {
        int num = FlappyBirdManager.Instance.Points;
        score.text = string.Format("{0}", num);
    }

}
