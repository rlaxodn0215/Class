using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Chapter.Strategy
{
    public class ConcreteStrategy3 : MonoBehaviour, Strategy
    {
        public void Execute()
        {
            Debug.Log("Strayegy3 execute!");
        }

    }
}