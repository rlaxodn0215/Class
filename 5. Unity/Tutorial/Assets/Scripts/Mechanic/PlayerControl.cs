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

        public GameObject Sounds;

        [SerializeField]
        private Dictionary<string, GameObject> sound = new Dictionary<string, GameObject>();

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

            for(int i = 0; i < Sounds.transform.childCount; i++)
            {
                sound[Sounds.transform.GetChild(i).name] = Sounds.transform.GetChild(i).gameObject;
            }

            //audioSource = GetComponent<AudioSource>();

            ////Resources 폴더 안에 있어야 한다
            //audioClip = Resources.Load(string.Format("TestSound/foot/{0}", "army")) as AudioClip;

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
                transform.Translate(Vector3.forward * v/1.5f * runSpeed * Time.deltaTime);

            if(Mathf.Abs(v)>=0.02f)
            {
                PlaySound("Walk_Sound");
            }

            else
            {
                StopSound("Walk_Sound");
            }

            transform.Rotate(Vector3.up, h*rotateSpeed * Time.deltaTime);

            animator.SetFloat("Speed", v * runSpeed);

        }

        void PlaySound(string name)
        {
            sound[name].SetActive(true);
            if (sound[name].GetComponent<AudioSource>().isPlaying) return;
            sound[name].GetComponent<AudioSource>().Play();
            //sound[name].GetComponent<AudioSource>().PlayScheduled(time);
        }

        void StopSound(string name)
        {
            sound[name].GetComponent<AudioSource>().Stop();
            sound[name].SetActive(false);
        }

        //void PlaySound(AudioClip clip)
        //{
        //    //pitch로 Sound와 동작 맞추기
        //    if (audioSource.isPlaying) return;
        //    audioSource.PlayOneShot(clip);
        //    //audioSource.Play(2);
        //}

        //void StopSound()
        //{
        //    audioSource.Stop();
        //}

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
                PlaySound("Damaged_Sound");
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
