using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace AniPang
{
    public class BreakBlockState : IBaseState
    {
        private GameManager gameManager;
        public BreakBlockState(StateMachine stateMachine)
        {
            gameManager = stateMachine as GameManager;
            if (gameManager == null) Debug.LogError("gameManager гр╢Г ╬х╣й");
        }
        public void Enter() { }
        public void Update() { }
        public void Exit() { }
    }
}