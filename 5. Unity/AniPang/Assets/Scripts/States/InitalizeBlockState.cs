using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DefineData;

namespace AniPang
{
    public class InitalizeBlockState : IBaseState
    {
        private GameManager gameManager;
        public InitalizeBlockState(StateMachine stateMachine)
        {
            gameManager = stateMachine as GameManager;
            if (gameManager == null) Debug.LogError("gameManager гр╢Г ╬х╣й");
        }
        public void Enter()
        {
            InitalizeBlock();
            gameManager.ChangeState(gameManager.gameState[Game_State.SwitchBlockState]);
        }

        void InitalizeBlock()
        {
            int row = gameManager.blockFrames.GetLength(0);
            int col = gameManager.blockFrames.GetLength(1);

            Vector3 startPos = new Vector3((int)gameManager.gameObject.transform.localPosition.x - (Constant.imageSize / 2) * (row - 1),
                (int)gameManager.gameObject.transform.localPosition.y + (Constant.imageSize / 2) * (col - 1), 0);

            Vector3 pos = startPos;
            for(int i = 0; i < col; i++)
            {
                for(int j = 0; j < row; j++)
                {
                    int randNum = Random.Range(0, (int)Block_Type.TypeCount);
                    GameObject frame = GameObject.Instantiate(gameManager.blockFrame,gameManager.transform);
                    GameObject block = GameObject.Instantiate(gameManager.blockTypes[randNum], gameManager.transform);
                    frame.transform.localPosition = pos;
                    block.transform.localPosition = pos;
                    pos.x += Constant.imageSize;

                    gameManager.blockFrames[j, i] = frame.GetComponent<BlockFrame>();
                    gameManager.blockFrames[j, i].SetPos(new Vector2Int(j, i));
                    gameManager.blockFrames[j, i].SetBlockType((Block_Type)randNum);
                    gameManager.blockFrames[j, i].givePos += gameManager.GetPos;
                }
                pos.x = startPos.x;
                pos.y -= Constant.imageSize;
            }

        }
    }
}