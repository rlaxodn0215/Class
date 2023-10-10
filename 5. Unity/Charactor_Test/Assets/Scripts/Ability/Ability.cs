using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public interface Ability
    {
        bool IsPossible { get; set; }
        void Execution();
    }
}