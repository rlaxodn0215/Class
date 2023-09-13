using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Game_2D
{
    public class DefaultUI : MonoBehaviour
    {
        public GameObject popupObj;

        void Start()
        {
            if(popupObj)
                popupObj.SetActive(false);
        }

        void Update()
        {

        }

        void onPopUp()
        {

            if (popupObj == null) return;

            if(popupObj.activeSelf)
            {
                popupObj.SetActive(false);
            }

            else
            {
                popupObj.SetActive(true);
            }
        }
    }
}
