using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Loading
{
    public class Loading : MonoBehaviour
    {
        AsyncOperation async;

        // Start is called before the first frame update
        void Start()
        {
            StartCoroutine(LoadingNextScene(GameManager.Instance.nextSceneName));
        }

        void Update()
        {
            DelayTime();
        }

        IEnumerator LoadingNextScene(string sceneName)
        {
            async = SceneManager.LoadSceneAsync(sceneName);
            async.allowSceneActivation = false;

            while(async.progress < 0.9f)
            {
                yield return true;
            }

            while(async.progress>=0.9f)
            {
                yield return new WaitForSeconds(0.1f);

                if(delayTime > 2.0f) // �ε� ������ 2���� ����
                {
                    break;
                }
            }

            async.allowSceneActivation = true;
        }

        float delayTime = 0.0f;

        void DelayTime()
        {
            delayTime += Time.deltaTime;
        }

    }
}