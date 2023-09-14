using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Game_3D
{
    public class Enemy : MonoBehaviour
    {
        public int ID;
        public int Hp = 50;
        public float runSpeed = 10.0f;
        public float SightRange = 30.0f;
        public float AttackRange = 5.5f;
        public GameObject objSword = null;
        public bool Alive = true;

        private Transform colLocation = null;
        private bool ArriveCol = false;
        Animation spartanKing;

        // Start is called before the first frame update
        void Start()
        {
            spartanKing = gameObject.GetComponentInChildren<Animation>();
            objSword.SetActive(false);
        }

        // Update is called once per frame
        void Update()
        {
            if (Alive)
            {
                GoToCollum();
                AttackCollum();
            }

        }

        void GoToCollum()
        {
            if (!ArriveCol)
                transform.Translate(Vector3.forward * runSpeed * Time.deltaTime);

            if (!objSword.activeSelf)
            {
                spartanKing.wrapMode = WrapMode.Loop;
                spartanKing.CrossFade("run", 0.3f);
            }

            Collider[] collums = Physics.OverlapSphere(transform.position, SightRange, 1<<11);

            if (collums.Length != 0)
            {
                colLocation = collums[0].transform;
                for (int i = 1; i < collums.Length; i++)
                {
                    colLocation = Vector3.Distance(colLocation.position, transform.position)
                        < Vector3.Distance(collums[i].transform.position, transform.position)
                        ? colLocation : collums[i].transform;
                }

                Vector3 direction = new Vector3(colLocation.position.x, transform.position.y, colLocation.position.z);
                transform.LookAt(direction);

                if (Vector3.Distance(transform.position, colLocation.position) > AttackRange + 2)
                {
                    spartanKing.wrapMode = WrapMode.Loop;
                    spartanKing.CrossFade("run", 0.3f);
                }

            }
        }

        void AttackCollum()
        {
            if (colLocation)
            {
                if (Vector3.Distance(transform.position, colLocation.position) <= AttackRange)
                {
                    StartCoroutine(EnemyAttack());
                    ArriveCol = true;
                }

                else
                {
                    ArriveCol = false;
                }
            }
        }

        IEnumerator EnemyAttack()
        {
            if (spartanKing["attack"].enabled) yield break;

            objSword.SetActive(true);
            spartanKing.wrapMode = WrapMode.Once;
            spartanKing.CrossFade("attack", 0.3f);
            float delayTime = spartanKing.GetClip("attack").length - 0.3f;
            yield return new WaitForSeconds(delayTime);
        }

        private void OnTriggerEnter(Collider other)
        {
            if(other.tag =="Sword")
            {
                Hp -= GameManager_3D.Instance.PlayerSwordDamage;
                Debug.Log("Enemy Life : " + Hp);

                if (Hp <= 0)
                {
                    Alive = false;
                    spartanKing.wrapMode = WrapMode.Once;
                    spartanKing.CrossFade("diehard", 0.3f);
                    Invoke("EnemyDie", 3.5f);
                    
                }
            }
        }

        void EnemyDie()
        {
            gameObject.SetActive(false);
            GameManager_3D.Instance.EnemyDead(ID);
        }


    }
}
