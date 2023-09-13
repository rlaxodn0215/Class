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

        // Start is called before the first frame update
        void Start()
        {
            titletext.text = "쀍";
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

        // UI 이미지 확대 시 그림이 깨질 수 있다. 따라서 해당 image의 sprite editor의 border을 설정 해서 부분 확대를 한다.
        //Input Field의 Content Type에서 비밀번호 처럼 입력 가능 ******
    }
}