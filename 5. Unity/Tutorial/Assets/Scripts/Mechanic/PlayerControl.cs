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

        private bool readyForShoot = false;

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
                if (animator.GetCurrentAnimatorStateInfo(2).IsName("Empty"))
                {
                    if (isSword)
                    {
                        animator.SetTrigger("UnLoadSword");
                    }

                    else if (isBow)
                    {
                        animator.SetTrigger("ChangeToSword");
                    }

                    else
                    {
                        animator.SetTrigger("LoadSword");

                    }
                }
            }

            else if (Input.GetKeyDown(KeyCode.Alpha2))
            {
                if (animator.GetCurrentAnimatorStateInfo(2).IsName("Empty"))
                {
                    if (isBow)
                    {
                        animator.SetTrigger("UnLoadBow");
                    }

                    else if (isSword)
                    {
                        animator.SetTrigger("ChangeToBow");
                    }

                    else
                    {
                        animator.SetTrigger("LoadBow");
                    }
                }
            }

            if(Input.GetMouseButton(0))
            {
                if (animator.GetCurrentAnimatorStateInfo(1).IsName("Empty"))
                {
                    if (isSword)
                    {
                        animator.SetTrigger("AttackSword") ;
                    }

                    else if(isBow)
                    {
                        animator.SetBool("DrawArrow", true);
                        //Debug.Log("Drawing...");

                        if (animator.GetCurrentAnimatorStateInfo(2).IsName("Draw Arrow")
                            && animator.GetCurrentAnimatorStateInfo(2).normalizedTime >= 0.95f)
                        {
                            //Debug.Log("Ready For Shoot");
                            readyForShoot = true;
                        }
                    }

                    else
                    {
                         animator.SetTrigger("AttackPunch");
                    }
                }

            }

            if(Input.GetMouseButtonUp(0))
            {
                if (isSword)
                {
                    animator.SetBool("AttackSword", false);
                }

                else if (isBow)
                {
                    if (readyForShoot)
                    {
                        animator.SetTrigger("ShootArrow");
                        Debug.Log("Shoot!!");
                        readyForShoot = false;
                    }

                    animator.SetBool("DrawArrow", false);
                }

                else
                {
                    animator.SetBool("AttackPunch",false);
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

            if(v>=0)
                transform.Translate(Vector3.forward * v * runSpeed * Time.deltaTime);
            else
                transform.Translate(Vector3.forward * v/2 * runSpeed * Time.deltaTime);

            transform.Rotate(Vector3.up, h*rotateSpeed * Time.deltaTime);

            animator.SetFloat("Speed", v * runSpeed);

        }

        //private void OnControllerColliderHit(ControllerColliderHit hit)
        //{
        //    if(hit.collider.tag == "EnemySword")
        //    {
        //        MazeGame.MazeGameManager.Instance.Damaged();
        //    }
        //}

        private void OnTriggerEnter(Collider other)
        {
            if (other.tag == "EnemySword")
            {
                MazeGame.MazeGameManager.Instance.Damaged();
                Debug.Log("Damaged");
            }
        }

        //private void OnCollisionEnter(Collision collision)
        //{
        //    if (collision.gameObject.tag == "EnemySword")
        //    {
        //        MazeGame.MazeGameManager.Instance.Damaged();
        //    }
        //}
    }
}
