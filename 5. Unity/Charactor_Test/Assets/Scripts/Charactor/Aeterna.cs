using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player.Aeterna
{
    public class Aeterna : Player.Charactor
    {

        void Start()
        {
            Initialize();
        }

        void Initialize()
        {
            animator.GetComponent<Animator>();
            rigidbody.GetComponent<Rigidbody>();
            SkillInput();
        }

        void SkillInput()
        {
            Skills["Basic_Attack"] = new DimensionSword();
            Skills["Skill_1"] = new DimensionOpen();
            Skills["Skill_2"] = new DimensionIO();
        }
    }
}