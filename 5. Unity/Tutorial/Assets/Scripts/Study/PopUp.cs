using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Game_2D
{
    public class PopUp : MonoBehaviour
    {
        public Text titletext = null;
        public InputField inputText = null;
        public Toggle toggleBGM = null;
        public GameObject[] Backgrounds;

        public GameObject radioGroupObj=null;
        Toggle[] toggleRadio;

        void Start()
        {
            titletext.text = "쀍";

            toggleRadio = radioGroupObj.GetComponentsInChildren<Toggle>();
        }

        // Update is called once per frame
        void Update()
        {

        }

        void OnClickOK()
        {
            Debug.Log("OnClickOK()");
            titletext.text = "OnClickOK()";
            gameObject.SetActive(false);
            Time.timeScale = 1;

        }

        void OnClickCancel()
        {
            gameObject.SetActive(false);
            Time.timeScale = 1;
        }

       void onTextChanged()
       {
            titletext.text = inputText.text;
       }

       void onEditEnd()
       {
           titletext.text = inputText.text;
       }

        public void onToggleBGM()
        {
            if(toggleBGM.isOn)
            {
                Debug.Log("BGM on");
            }

            else
            {
                Debug.Log("BGM off");
            }
        }

        public void onToggleRadio()
        {
            if (toggleRadio[0].isOn)
            {
                Backgrounds[0].GetComponent<SpriteRenderer>().color = Color.green;
                Backgrounds[1].GetComponent<SpriteRenderer>().color = Color.green;
                //Debug.Log("1번 선택");
            }

            else if (toggleRadio[1].isOn)
            {
                Backgrounds[0].GetComponent<SpriteRenderer>().color = Color.red;
                Backgrounds[1].GetComponent<SpriteRenderer>().color = Color.red;
                //Debug.Log("2번 선택");
            }

            else if (toggleRadio[2].isOn)
            {
                Backgrounds[0].GetComponent<SpriteRenderer>().color = Color.blue;
                Backgrounds[1].GetComponent<SpriteRenderer>().color = Color.blue;
                //Debug.Log("3번 선택");
            }
        }

        // UI 이미지 확대 시 그림이 깨질 수 있다. 따라서 해당 image의 sprite editor의 border을 설정 해서 부분 확대를 한다.
        //Input Field의 Content Type에서 비밀번호 처럼 입력 가능 ******
    }
}