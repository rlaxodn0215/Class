using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class Aeterna : Charactor
    {
        public CharactorData AeternaData;
        public GameObject DimensionSword;
        public GameObject DimensionDoor;

        [HideInInspector]
        public bool[] skillButton;
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
            skillButton = new bool[Skills.Count];

            Hp = AeternaData.Hp;
            moveSpeed = AeternaData.moveSpeed;
            jumpHeight = AeternaData.jumpHeight;
            skillTimer = AeternaData.skillTimer;
        }

        protected override void PlayerSkillInput()
        {
            // 키 매니저 불러오기

            // 입력된 스킬 슬롯 에 따라 해당 스킬 사용
            if (Input.GetKeyDown(KeyCode.Q))
            {
                Skills["Basic_Attack"].Execution();
            }

            if (Input.GetKeyDown(KeyCode.E))
            {
                Skills["Skill_1"].Execution();
            }
        }
    }
}