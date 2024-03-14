using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace AniPang
{
    public class SwitchBlockState : IBaseState
    {
        private GameManager gameManager;

        public SwitchBlockState(StateMachine stateMachine)
        {
            gameManager = stateMachine as GameManager;
            if (gameManager == null) Debug.LogError("gameManager гр╢Г ╬х╣й");
        }
        public void Enter() { }
        public void Update() 
        {
            if(Input.GetMouseButtonUp(0))
            {
                gameManager.GetDirection(Input.mousePosition);
            }
        }

        public void Exit() { }
    }
}