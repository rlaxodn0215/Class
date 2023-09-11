using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveWall : MonoBehaviour
{
    public float moveSpeed = 10.0f;

    // Start is called before the first frame update
    void Start()
    {
        Invoke("Death", 10.0f);
    }

    // Update is called once per frame
    void Update()
    {
        if(!FlappyBirdManager.Instance.gameOver)
        transform.Translate(Vector3.back * moveSpeed * Time.deltaTime );
    }

    void Death()
    {
        if (!FlappyBirdManager.Instance.gameOver)
            DestroyImmediate(this.gameObject);
    }
}
