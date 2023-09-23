using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Chapter.Strategy
{
    public class ClientStrategy : MonoBehaviour
    {
        private List<Strategy> strategies = new List<Strategy>();

        // Start is called before the first frame update
        void Start()
        {
            InitStrategies();
        }

        void InitStrategies()
        {
            strategies.Add(new ConcreteStrategy1());
            strategies.Add(new ConcreteStrategy2());
            strategies.Add(new ConcreteStrategy3());
        }

        // Update is called once per frame
        void Update()
        {
            if(Input.GetKeyDown(KeyCode.Space))
            {
                int index = Random.Range(0, strategies.Count);

                strategies[index].Execute();

            }
        }
    }
}