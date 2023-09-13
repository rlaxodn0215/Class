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

        public GameObject radioGroupObj=null;
        Toggle[] toggleRadio;

        void Start()
        {
            titletext.text = "��";

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
        }

        void OnClickCancel()
        {
            gameObject.SetActive(false);
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
            if(toggleRadio[0].isOn)
            {
                Debug.Log("1�� ����");
            }

            else if(toggleRadio[1].isOn)
            {
                Debug.Log("2�� ����");
            }
        }

        // UI �̹��� Ȯ�� �� �׸��� ���� �� �ִ�. ���� �ش� image�� sprite editor�� border�� ���� �ؼ� �κ� Ȯ�븦 �Ѵ�.
        //Input Field�� Content Type���� ��й�ȣ ó�� �Է� ���� ******
    }
}