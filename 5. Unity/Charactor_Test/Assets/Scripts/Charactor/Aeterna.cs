using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Player
{
    public class Aeterna : Charactor
    {
        public CharactorData AeternaData;
        public GameObject DimensionSword;
        public GameObject DimensionDoor;

        [HideInInspector]
        public int skillButton = -1;
        [HideInInspector]
        public float[] skillTimer;

        protected override void CharactorInitialize()
        {
            Initialize();
        }

        protected override void CharactorUpdate()
        {
            
        }

        void Initialize()
        {
            Skills["Basic_Attack"] = new DimensionSword(this);
            Skills["Skill_1"] = new DimensionOpen(this);
            Skills["Skill_2"] = new DimensionIO(this);

            skillTimer = new float[Skills.Count];

            for(int i = 0; i < Skills.Count; i++)
            {
                skillTimer[i] = -1;
            }

            Hp = AeternaData.Hp;
            moveSpeed = AeternaData.moveSpeed;
            jumpHeight = AeternaData.jumpHeight;
        }

        protected override void PlayerSkillInput()
        {
            // 입력된 스킬 슬롯 에 따라 해당 스킬 사용
            if (Input.GetMouseButtonDown(0))
            {
                if(skillButton==1 && skillTimer[1]<=0.0f)
                {
                    Skills["Skill_1"].Execution();
                    skillTimer[1] = AeternaData.skillTimer[1];
                    StartCoroutine(SkillTimer(1));
                }

                else if(skillButton==2 && skillTimer[2] <= 0.0f)
                {
                    Skills["Skill_2"].Execution();
                    skillTimer[2] = AeternaData.skillTimer[2];
                    StartCoroutine(SkillTimer(2));
                }

                else
                {
                    Skills["Basic_Attack"].Execution();
                }
            }

            if (Input.GetKeyDown(KeyCode.Q) && skillTimer[1] <= 0.0f)
            {
                if (skillButton == 1) skillButton = -1;
                else skillButton = 1;
                Debug.Log("Change to Skill_1");
            }

            else if (Input.GetKeyDown(KeyCode.E) && skillTimer[2] <= 0.0f)
            {
                if (skillButton == 2) skillButton = -1;
                else skillButton = 2;
                Debug.Log("Change to Skill_2");
            }
        }

        IEnumerator SkillTimer(int skillIndex)
        {
            while (skillTimer[skillIndex] > 0.0f)
            {
                skillTimer[skillIndex] -= Time.deltaTime;
                yield return null;
            }
        }

        private void OnGUI()
        {
            GUI.TextField(new Rect(10, 10, 100, 30), skillTimer[1].ToString());
            GUI.TextField(new Rect(10, 30, 100, 50), skillTimer[2].ToString());
        }

    }
}