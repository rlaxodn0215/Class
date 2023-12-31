using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Mechanic
{
    public class MechanicControl : MonoBehaviour
    {
        public float runSpeed = 10.0f;
        public float rotationSpeed = 360.0f;

        CharacterController pcController;
        Vector3 direction;
        Animator animator;

        // Start is called before the first frame update
        void Start()
        {
            pcController = GetComponent<CharacterController>();
            animator = GetComponent<Animator>();
        }

        // Update is called once per frame
        void Update()
        {
            CharactorControll_Slerp();

            if(Input.GetKeyDown(KeyCode.Space))
            {
                animator.SetTrigger("Pose1");
            }

            //else if (Input.GetKeyUp(KeyCode.Space))
            //{
            //    animator.SetTrigger("Pose1");
            //}
        }

        void Input_Animation()
        { 
            if(Input.GetMouseButtonDown(0))
            {
                //animator.SetBool()
                animator.GetCurrentAnimatorStateInfo(1).IsName("UpperBody.Attack");
                if (animator.GetCurrentAnimatorStateInfo(1).normalizedTime >= 0.9f) ;
            }


        }

        void CharactorControll_Slerp()
        {
            direction = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
            if(direction.sqrMagnitude > 0.01f)
            {
                Vector3 forward = Vector3.Slerp(transform.forward,
                                                direction,
                                                rotationSpeed * Time.deltaTime / Vector3.Angle(transform.forward, direction));

                transform.LookAt(transform.position + forward);
            }

            else
            {

            }

            animator.SetFloat("Speed", pcController.velocity.magnitude);
            pcController.Move(direction * runSpeed * Time.deltaTime + Physics.gravity*Time.deltaTime);
        }
    }
}