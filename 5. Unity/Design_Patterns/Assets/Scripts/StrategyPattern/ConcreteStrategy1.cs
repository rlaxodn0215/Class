using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Chapter.Strategy
{
    public class ConcreteStrategy1 : MonoBehaviour, Strategy
    {
        public void Execute()
        {
            Debug.Log("Strayegy1 execute!");
        }

    }
}