using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class Aeterna : Charactor
    {
        //public ScriptableObject AternaData;
        public GameObject DimensionSword;
        public GameObject DimensionDoor;

        void Initialize()
        {
            //charactor = PlayerCharactor.Aeterna;
            Skills["Basic_Attack"] = new DimensionSword(DimensionSword);
            Skills["Skill_1"] = new DimensionOpen(DimensionDoor);
            Skills["Skill_2"] = new DimensionIO();
        }

        protected override void CharactorInitialize()
        {
            Initialize();
        }

        protected override void PlayerSkillInput()
        {
            // �Էµ� ��ų ���� �� ���� �ش� ��ų ���
        }
    }
}