using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player.Aeterna
{
    public class DimensionIO : Player.Aeterna.Aeterna, Player.Ability
    {
        public bool IsPossible { get; set; }

        public void Execution()
        {
            Debug.Log("DimensionIO");
        }
    }
}