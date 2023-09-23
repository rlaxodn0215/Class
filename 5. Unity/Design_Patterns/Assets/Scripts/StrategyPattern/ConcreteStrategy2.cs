using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Chapter.Strategy
{
    public class ConcreteStrategy2 : MonoBehaviour, Strategy
    {
        public void Execute()
        {
            Debug.Log("Strayegy2 execute!");
        }

    }
}