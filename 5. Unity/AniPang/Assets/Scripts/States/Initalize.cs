using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Initalize : BaseState
{
    private GameManager gameManager;

    public Initalize(StateMachine machine) :base(machine)
    {
        gameManager = machine as GameManager;
    }

    public override void Enter()
    {
        SettingBlocks();
        gameManager.ChangeState(gameManager.States[GameManager.StateName.Evaluate]);
    }

    void SettingBlocks()
    {
        gameManager.blockBoardInfo = new Block[gameManager.width, gameManager.height];
        gameManager.checkBoardInfo = new bool[gameManager.width, gameManager.height];

        // setting block
        for (int i = 0; i < gameManager.width; i++)
        {
            for (int j = 0; j < gameManager.height; j++)
            {
                int randomIndex = Random.Range(0, (int)Block.BlockType.BlockCount);
                RectTransform block = RectTransform.Instantiate(gameManager.block, gameManager.transform);
                gameManager.blockBoardInfo[i, j] = block.GetComponent<Block>();
                gameManager.blockBoardInfo[i, j].Info = new Block.BlockInfo(i, j, (Block.BlockType)randomIndex);
                gameManager.blockBoardInfo[i, j].SetBlockType((Block.BlockType)randomIndex);
                block.localPosition = gameManager.startPos + new Vector3((GameManager.length + GameManager.frameSpace) * i, -(GameManager.length + GameManager.frameSpace) * j, 0);
                gameManager.checkBoardInfo[i, j] = false;
            }
        }
    }
}
