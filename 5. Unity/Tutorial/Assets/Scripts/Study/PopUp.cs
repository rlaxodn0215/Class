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
            titletext.text = "��";
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

        // UI �̹��� Ȯ�� �� �׸��� ���� �� �ִ�. ���� �ش� image�� sprite editor�� border�� ���� �ؼ� �κ� Ȯ�븦 �Ѵ�.
        //Input Field�� Content Type���� ��й�ȣ ó�� �Է� ���� ******
    }
}