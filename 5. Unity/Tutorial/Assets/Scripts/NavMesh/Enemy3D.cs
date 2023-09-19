using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

namespace MazeGame
{
    public class Enemy3D : MonoBehaviour
    {
        public GameObject player;

        public GameObject UnSword;
        public GameObject Sword;

        [Range(0f, 360f)] [SerializeField] float ViewAngle = 0f;
        [SerializeField] float ViewRadius = 1f;
        [SerializeField] LayerMask TargetMask;
        [SerializeField] LayerMask ObstacleMask;

        NavMeshAgent agent;
        Animator animator;

        private bool isSword = false;

        // Start is called before the first frame update
        void Start()
        {
            agent = GetComponent<NavMeshAgent>();
            animator = GetComponent<Animator>();
        }

        // Update is called once per frame
        void Update()
        {
            SearchCoin();
            //SpotPlayer();
        }

        void SearchCoin()
        {
            FollowDest(MazeGameManager.Instance.coinPoint);
        }

        void SpotPlayer()
        {
            Vector3 SightPos = transform.position + Vector3.up * 2.5f;
            float lookingAngle = transform.eulerAngles.y;  //캐릭터가 바라보는 방향의 각도
            Vector3 rightDir = AngleToDir(transform.eulerAngles.y + ViewAngle * 0.5f);
            Vector3 leftDir = AngleToDir(transform.eulerAngles.y - ViewAngle * 0.5f);
            Vector3 lookDir = AngleToDir(lookingAngle);

            Debug.DrawRay(SightPos, rightDir * ViewRadius, Color.blue);
            Debug.DrawRay(SightPos, leftDir * ViewRadius, Color.blue);
            Debug.DrawRay(SightPos, lookDir * ViewRadius, Color.cyan);

            Collider[] Targets = Physics.OverlapSphere(SightPos, ViewRadius, TargetMask);
            //Debug.Log(Targets);

            if (Targets.Length == 0)
            {
                UnLoadSword();
                agent.destination = transform.position;
                animator.SetFloat("Speed", agent.velocity.magnitude);
                return;
            }

            foreach (Collider player in Targets)
            {
                Vector3 targetPos = player.transform.position;
                Vector3 targetDir = (targetPos - SightPos).normalized;
                float targetAngle = Mathf.Acos(Vector3.Dot(lookDir, targetDir)) * Mathf.Rad2Deg;

                if (targetAngle <= ViewAngle * 0.5f && !Physics.Raycast(SightPos, targetDir, ViewRadius, ObstacleMask))
                {
                    LoadSword();
                    FollowDest(targetPos);
                    Debug.DrawLine(SightPos, targetPos, Color.red);
                }

            }

        }

        Vector3 AngleToDir(float angle)
        {
            float radian = angle * Mathf.Deg2Rad;
            return new Vector3(Mathf.Sin(radian), 0f, Mathf.Cos(radian));
        }

        void LoadSword()
        {
            if (!isSword)
            {
                animator.SetTrigger("LoadSword");
                isSword = true;
            }

            if (animator.GetCurrentAnimatorStateInfo(1).IsName("Withdrawing Sword Enemy"))
            {
                if (animator.GetCurrentAnimatorStateInfo(1).normalizedTime >= 0.4f)
                {
                    UnSword.SetActive(false);
                    Sword.SetActive(true);
                }
            }
        }

        void UnLoadSword()
        {
            if (isSword)
            {
                animator.SetTrigger("UnLoadSword");
                isSword = false;
            }

            if (animator.GetCurrentAnimatorStateInfo(1).IsName("Sheathing Sword Enemy"))
            {
                if (animator.GetCurrentAnimatorStateInfo(1).normalizedTime >= 0.8f)
                {
                    UnSword.SetActive(true);
                    Sword.SetActive(false);
                }
            }

        }

        void AttackSword()
        {

        }

        void FollowDest(Vector3 dest)
        {
            agent.destination = dest;
            animator.SetFloat("Speed", agent.velocity.magnitude);
        }

    }
}