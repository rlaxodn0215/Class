using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class DimensionOpen : Aeterna, Ability
    {
        GameObject Door;
        public DimensionOpen(GameObject _gameObject)
        {
            Door = _gameObject;
        }

        public void Execution()
        {
            Debug.Log("DimensionOpen");
        }
    }
}