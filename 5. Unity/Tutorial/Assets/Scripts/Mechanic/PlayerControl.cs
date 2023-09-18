using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Mechanic
{
    public class PlayerControl : MonoBehaviour
    {
        public float runSpeed = 10.0f;
        public float rotateSpeed = 360.0f;

        public GameObject UnSword;
        public GameObject UnBow;

        public GameObject Weapon;

        private List<GameObject> weapons = new List<GameObject>();
        

        private bool isSword = false;
        private bool isBow = false;

        CharacterController pcController;
        Animator animator;

        // Start is called before the first frame update
        void Start()
        {
            pcController = GetComponent<CharacterController>();
            animator = GetComponent<Animator>();

            for(int i = 0; i < Weapon.transform.childCount; i++)
            {
                weapons.Add(Weapon.transform.GetChild(i).gameObject);
            }
        }

        // Update is called once per frame
        void Update()
        {
            MoveControl();
            InputControl();
        }

        void InputControl()
        {
            if(Input.GetKeyDown(KeyCode.Alpha1))
            {
                
                if (isSword)
                {
                    animator.SetTrigger("UnLoadSword");
                }

                else if(isBow)
                {
                    animator.SetTrigger("ChangeToSword");
                }

                else
                {
                    animator.SetTrigger("LoadSword");
                    
                }
            }

            else if (Input.GetKeyDown(KeyCode.Alpha2))
            {
                if (isBow)
                {
                    animator.SetTrigger("UnLoadBow");
                }

                else if(isSword)
                {
                    animator.SetTrigger("ChangeToBow");
                }

                else
                {
                    animator.SetTrigger("LoadBow");
                }
            }

            else if(Input.GetMouseButtonDown(0))
            {
                if(isSword)
                {
                    animator.SetTrigger("AttackSword");
                }

                else
                {
                    animator.SetTrigger("AttackPunch");
                }
            }
            

        }

        void OnLoadBow()
        {
           UnBow.SetActive(false);
           weapons[1].SetActive(true);
           isBow = true;
        }

        void UnLoadBow()
        {
           UnBow.SetActive(true);
           weapons[1].SetActive(false);
           isBow = false;
        }

        void OnLoadSword()
        {
            UnSword.SetActive(false);
            weapons[0].SetActive(true);
            isSword = true;
        }

        void UnLoadSword()
        {
            UnSword.SetActive(true);
            weapons[0].SetActive(false);
            isSword = false;
        }

        void MoveControl()        
        {
            float v = Input.GetAxis("Vertical");
            float h = Input.GetAxis("Horizontal");

            transform.Translate(Vector3.forward * v * runSpeed * Time.deltaTime);
            transform.Rotate(Vector3.up * h * rotateSpeed * Time.deltaTime);

            animator.SetFloat("Speed", v * runSpeed);
        }
    }
}
