using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class Ability
    {
        protected string Name;
        protected int Damage;
        public bool IsPossible = true;

        public virtual void Execution() { }


    }
}