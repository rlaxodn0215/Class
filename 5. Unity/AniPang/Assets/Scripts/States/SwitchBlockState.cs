using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DefineData;

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
                ExChangeBlock();
            }
        }

        void ExChangeBlock()
        {
            switch (gameManager.way)
            {
                case Switch_Way.Up:
                    if(CheckChangeable()) gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector3(0, -1, 0));
                    break;
                case Switch_Way.Down:
                    if (CheckChangeable()) gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector3(0, 1, 0));
                    break;
                case Switch_Way.Left:
                    if (CheckChangeable()) gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector3(-1, 0, 0));
                    break;
                case Switch_Way.Right:
                    if (CheckChangeable()) gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector3(1, 0, 0));
                    break;

            }
        }

        bool CheckChangeable()
        {
            switch (gameManager.way)
            {
                case Switch_Way.Up:     return gameManager.startSwitchPos.y > 0;
                case Switch_Way.Down:   return gameManager.startSwitchPos.y < gameManager.row - 1;
                case Switch_Way.Left:   return gameManager.startSwitchPos.x > 0;
                case Switch_Way.Right:  return gameManager.startSwitchPos.x < gameManager.col - 1;
            }
            return false;
        }

        public void Exit() { }
    }
}