using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_3D
{
    public class PlayerControl : MonoBehaviour
    {
        Animation spartanKing;

        public AnimationClip IDLE;
        public AnimationClip RUN;
        public AnimationClip ATTACK;

        CharacterController pcControl;
        public float runSpeed = 10.0f;
        Vector3 velocity;
        public float rotationSpeed = 60.0f;
        public GameObject objSword = null;

        public int Attack = 20;

        // Start is called before the first frame update
        void Start()
        {
            spartanKing = gameObject.GetComponentInChildren<Animation>();
            pcControl = gameObject.GetComponent<CharacterController>();
            objSword.SetActive(false);
        }

        // Update is called once per frame
        void Update()
        {
            Control();
        }

        void Control()
        {
            float v = Input.GetAxis("Vertical");
            float h = Input.GetAxis("Horizontal");

            if(!objSword.activeSelf)
                transform.Translate(Vector3.forward * v * runSpeed * Time.deltaTime);

            transform.Rotate( Vector3.up * h * rotationSpeed * Time.deltaTime);

            if(Mathf.Abs(v) > 0.02f)
            {
                if (!objSword.activeSelf)
                {
                    spartanKing.wrapMode = WrapMode.Loop;
                    spartanKing.CrossFade("run", 0.3f);
                }

                if (Input.GetKeyDown(KeyCode.Space))
                {
                    StartCoroutine(AttackToRun());
                }
            }

            else
            {
                if (!objSword.activeSelf)
                {
                    spartanKing.wrapMode = WrapMode.Loop;
                    spartanKing.CrossFade("idle", 0.3f);
                }

                if (Input.GetKeyDown(KeyCode.Space))
                {
                    StartCoroutine(AttackToIdle());
                }
            }

        }

        IEnumerator AttackToIdle()
        {
            if (spartanKing["attack"].enabled) yield break;

            objSword.SetActive(true);
            spartanKing.wrapMode = WrapMode.Once;
            spartanKing.CrossFade("attack", 0.3f);
            float delayTime = spartanKing.GetClip("attack").length - 0.3f;
            yield return new WaitForSeconds(delayTime);

            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade("idle", 0.3f);
            objSword.SetActive(false);
        }

        IEnumerator AttackToRun()
        {
            if (spartanKing["attack"].enabled) yield break;

            objSword.SetActive(true);
            spartanKing.wrapMode = WrapMode.Once;
            spartanKing.CrossFade("attack", 0.3f);
            float delayTime = spartanKing.GetClip("attack").length - 0.3f;
            yield return new WaitForSeconds(delayTime);

            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade("run", 0.3f);
            objSword.SetActive(false);
        }


//=============================================================================================================================================//

        void CharactorControl_Slerp()
        {
            Vector3 direction = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));

            if (direction.sqrMagnitude > 0.01f)
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade(RUN.name, 0.3f);

                Vector3 forward = Vector3.Slerp(transform.forward, direction, 
                    rotationSpeed * Time.deltaTime / Vector3.Angle(transform.forward, direction));


                transform.LookAt(transform.position + forward);
            }

            else 
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade("idle", 0.3f);
            }

            pcControl.Move(direction *runSpeed* Time.deltaTime + Physics.gravity * Time.deltaTime);
            //Debug.Log(velocity * Time.deltaTime + Physics.gravity * Time.deltaTime);
            //pcControl.SimpleMove(velocity);
        }

        IEnumerator AttackToIdle2()
        {
            //if (spartanKing.IsPlaying("attack")) yield break;
            if (spartanKing[ATTACK.name].enabled) yield break;

            objSword.SetActive(true);
            spartanKing.wrapMode = WrapMode.Once;
            spartanKing.CrossFade(ATTACK.name, 0.3f);
            float delayTime = spartanKing.GetClip(ATTACK.name).length - 0.3f;
            yield return new WaitForSeconds(delayTime);

            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade(IDLE.name, 0.3f);
            objSword.SetActive(false);
        }

        void CharactorControl()
        {
            velocity = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
            
            velocity *= runSpeed;

            if (velocity.magnitude > 0.5f)
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade(RUN.name, 0.3f);
                transform.LookAt(transform.position + velocity);
            }

            else
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade("idle", 0.3f);
            }

            //pcControl.Move(velocity * Time.deltaTime + Physics.gravity * Time.deltaTime);
            //Debug.Log(velocity * Time.deltaTime + Physics.gravity * Time.deltaTime);
            pcControl.SimpleMove(velocity);
        }

        void AnimationPlay_4()
        {
            if (Input.GetKeyDown(KeyCode.F))
            {
                StartCoroutine("AttackToIdle2");
            }

            if (Input.GetKeyDown(KeyCode.R))
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade(RUN.name, 0.3f);
            }

            if (Input.GetKeyDown(KeyCode.I))
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade(IDLE.name, 0.3f);
            }
        }

        void AnimationPlay_3()
        {
            if (Input.GetKeyDown(KeyCode.F))
            {
                StartCoroutine("AttackToIdle");
            }

            if (Input.GetKeyDown(KeyCode.R))
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade("run", 0.3f);
            }

            if (Input.GetKeyDown(KeyCode.I))
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade("idle", 0.3f);
            }
        }

        //IEnumerator AttackToIdle()
        //{
        //    //if (spartanKing.IsPlaying("attack")) yield break;
        //    if (spartanKing["attack"].enabled) yield break;

        //    spartanKing.wrapMode = WrapMode.Once;
        //    spartanKing.CrossFade("attack", 0.3f);
        //    float delayTime = spartanKing.GetClip("attack").length - 0.3f;
        //    yield return new WaitForSeconds(delayTime);

        //    spartanKing.wrapMode = WrapMode.Loop;
        //    spartanKing.CrossFade("idle", 0.3f);

        //}

        void AnimationPlay_2()
        {
            if (Input.GetKeyDown(KeyCode.F))
            {
                spartanKing.wrapMode = WrapMode.Once;
                spartanKing.CrossFade("attack",0.3f);
            }

            if (Input.GetKeyDown(KeyCode.R))
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade("run", 0.3f);
            }

            if (Input.GetKeyDown(KeyCode.I))
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade("idle", 0.3f);
            }


        }
    

    void AnimationPlay_1()
        {
            if(Input.GetKeyDown(KeyCode.F))
            {
                spartanKing.Play("attack");
            }

            if (Input.GetKeyDown(KeyCode.Alpha0))
            {
                spartanKing.Play("idle");
            }

            if (Input.GetKeyDown(KeyCode.Alpha1))
            {
                spartanKing.Play("walk");
            }

            if (Input.GetKeyDown(KeyCode.Alpha2))
            {
                spartanKing.Play("run");
            }

            if (Input.GetKeyDown(KeyCode.Alpha3))
            {
                spartanKing.Play("charge");
            }

        }
    }
}