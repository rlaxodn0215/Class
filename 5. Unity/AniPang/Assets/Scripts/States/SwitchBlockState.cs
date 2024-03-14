using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DefineData;

namespace AniPang
{
    public class SwitchBlockState : IBaseState
    {
        private GameManager gameManager;
        private int[] dx = { -1, 0, 1, 0 };
        private int[] dy = { 0, -1, 0, 1 };
        [HideInInspector]
        public bool[,] blockFramesVisited;
        public SwitchBlockState(StateMachine stateMachine)
        {
            gameManager = stateMachine as GameManager;
            if (gameManager == null) Debug.LogError("gameManager гр╢Г ╬х╣й");
        }
        public void Enter()
        {
            blockFramesVisited = new bool[gameManager.row, gameManager.col];
            ResetVisited();
        }
        public void Update() 
        {
            if(Input.GetMouseButtonUp(0))
            {
                gameManager.GetDirection(Input.mousePosition);
                Debug.Log(gameManager.way);
                ExChangeBlock();
                gameManager.startSwitchPos = new Vector2Int(-1,-1);
            }
        }

        void ExChangeBlock()
        {
            switch (gameManager.way)
            {
                case Switch_Way.Up:
                    if (CheckChangeable())
                    {
                        gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector2Int(0, -1));
                        CheckBlockBreakAll();
                    }
                    break;
                case Switch_Way.Down:
                    if (CheckChangeable())
                    {
                        gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector2Int(0, 1));
                        CheckBlockBreakAll();
                    }
                    break;
                case Switch_Way.Left:
                    if (CheckChangeable())
                    {
                        gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector2Int(-1, 0));
                        CheckBlockBreakAll();
                    }
                    break;
                case Switch_Way.Right:
                    if (CheckChangeable())
                    {
                        gameManager.SwapBlock(gameManager.startSwitchPos, gameManager.startSwitchPos + new Vector2Int(1, 0));
                        CheckBlockBreakAll();
                    }
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

        void CheckBlockBreakAll()
        {
            List<BlockFrame> blocks = new List<BlockFrame>();
            for (int i = 0; i < gameManager.row; i++)
            {
                for (int j = 0; j < gameManager.col; j++)
                {
                    List<BlockFrame> temp = BreakBlockList(i, j);
                    if (temp.Count >= gameManager.breakNumber)
                    {
                        blocks.AddRange(temp);
                    }
                }
            }

            //if (blocks.Count > 0)
            //{
            //    gameManager.ChangeState(gameManager.States[GameManager.StateName.BlockBreaking]);
            //}
        }

        List<BlockFrame> BreakBlockList(int posX, int posY)
        {
            List<BlockFrame> ans = new List<BlockFrame>();

            Queue<BlockFrame> q = new Queue<BlockFrame>();
            q.Enqueue(gameManager.blockFrames[posX, posY]);
            ans.Add(gameManager.blockFrames[posX, posY]);
            blockFramesVisited[posX, posY] = true;

            while (q.Count > 0)
            {
                BlockFrame temp = q.Peek(); q.Dequeue();

                for (int i = 0; i < 4; i++)
                {
                    int x = temp.pos.x + dx[i];
                    int y = temp.pos.y + dy[i];

                    if (x < 0 || y < 0 || x >= gameManager.row || y >= gameManager.col) continue;
                    if (blockFramesVisited[x, y]) continue;
                    if (gameManager.blockFrames[x, y].type == temp.type)
                    {
                        blockFramesVisited[x, y] = true;
                        q.Enqueue(gameManager.blockFrames[x, y]);
                        ans.Add(gameManager.blockFrames[x, y]);
                    }
                }
            }

            return ans;
        }


        public void Exit() 
        {
            ResetVisited();
        }

        void ResetVisited()
        {
            for (int i = 0; i < gameManager.row; i++)
            {
                for (int j = 0; j < gameManager.col; j++)
                {
                    blockFramesVisited[i, j] = false;
                }
            }
        }
    }
}