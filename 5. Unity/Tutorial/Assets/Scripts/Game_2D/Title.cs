using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Title : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Time.timeScale = 0;
    }
    
    public void StartGame()
    {
        Time.timeScale = 1;
        gameObject.SetActive(false);
    }
}
