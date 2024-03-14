using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DefineData;

namespace AniPang
{
    public class GameManager : StateMachine
    {
        public int row = 5;
        public int col = 3;
        public GameObject blockFrame;

        [HideInInspector]
        public BlockFrame[,] blockFrames;
        [HideInInspector]
        public Vector3 startSwitchPos = new Vector3();
        [HideInInspector]
        public Vector3 switchStartDirection = new Vector3();
        [HideInInspector]
        public Switch_Way way = Switch_Way.None;


        public List<GameObject> blockTypes;
        public Dictionary<Game_State, IBaseState> gameState = new Dictionary<Game_State, IBaseState>();


        private void Awake()
        {
            InitalizeBlockNums();
            MakeGameState();
        }

        void InitalizeBlockNums()
        {
            blockFrames = new BlockFrame[row, col];
        }

        void MakeGameState()
        {
            for (int i = 0; i < (int)Game_State.GameStateCount; i++)
            {
                switch ((Game_State)i)
                {
                    case Game_State.InitalizeBlockState: gameState[Game_State.InitalizeBlockState] = new InitalizeBlockState(this); break;
                    case Game_State.SwitchBlockState: gameState[Game_State.SwitchBlockState] = new SwitchBlockState(this); break;
                    case Game_State.CheckBlockState: gameState[Game_State.CheckBlockState] = new CheckBlockState(this); break;
                    case Game_State.BreakBlockState: gameState[Game_State.BreakBlockState] = new BreakBlockState(this); break;
                }
            }          
        }

        protected override IBaseState GetInitalState()
        {
            return gameState[Game_State.InitalizeBlockState];
        }

        public void GetPos(Vector3 start, Vector3 mouse)
        {
            startSwitchPos = start;
            switchStartDirection = mouse;
        }

        public void GetDirection(Vector3 pos)
        {
            Vector3 dir = (pos - switchStartDirection).normalized;

            if (dir.x >= 0.95f) way = Switch_Way.Right;
            else if (dir.x <= -0.95f) way = Switch_Way.Left;
            else if (dir.y >= 0.95f) way = Switch_Way.Up;
            else if (dir.y <= -0.95f) way = Switch_Way.Down;
            else way = Switch_Way.None;
        }

        public void SwapBlock(Vector3 from, Vector3 to)
        {
            BlockFrame temp = blockFrames[(int)from.y, (int)from.x];
            blockFrames[(int)from.y, (int)from.x] = blockFrames[(int)to.y, (int)to.x];
            blockFrames[(int)to.y, (int)to.x] = temp;
        }

    }
}