using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Evaluate : BaseState
{
    private GameManager gameManager;

    private int[] dx = { -1, 0, 1, 0 };
    private int[] dy = { 0, -1, 0, 1 };

    public Evaluate(StateMachine machine) : base(machine)
    {
        gameManager = machine as GameManager;
    }

    public override void Enter()
    {
        CheckBlockBreakAll();
    }

    public override void Update()
    {
        //PlayerMouseMove();
    }

    void CheckBlockBreakAll()
    {
        List<Block> blocks = new List<Block>();
        for (int i = 0; i < gameManager.width; i++)
        {
            for (int j = 0; j < gameManager.height; j++)
            {
                List<Block> temp = BreakBlockList(i, j);
                if (temp.Count >= gameManager.breakNumber)
                {
                    blocks.AddRange(temp);
                }
            }
        }

        if(blocks.Count > 0)
        {
            MoveBlockToTop(blocks);
            gameManager.ChangeState(gameManager.States[GameManager.StateName.BlockBreaking]);
        }
    }

    void MoveBlockToTop(List<Block> blocks)
    {
        for(int i = 0; i < blocks.Count; i++)
        {
            blocks[i].SetBlockType((Block.BlockType)Random.Range(0, (int)Block.BlockType.BlockCount));
            gameManager.widthIndex[blocks[i].Info.posX]++;
            Vector3 moveLot = gameManager.blockBoardInfo[blocks[i].Info.posX, blocks[i].Info.posY].transform.localPosition;
            gameManager.blockBoardInfo[blocks[i].Info.posX, blocks[i].Info.posY].transform.localPosition 
                = new Vector3(moveLot.x, gameManager.startPos.y + (GameManager.length + GameManager.frameSpace) * gameManager.widthIndex[blocks[i].Info.posX], moveLot.z);
        }
    }

    List<Block> BreakBlockList(int posX, int posY)
    {
        List<Block> ans = new List<Block>();

        Queue<Block> q = new Queue<Block>();
        q.Enqueue(gameManager.blockBoardInfo[posX, posY]);
        ans.Add(gameManager.blockBoardInfo[posX, posY]);
        gameManager.checkBoardInfo[posX, posY] = true;

        while (q.Count > 0)
        {
            Block temp = q.Peek(); q.Dequeue();

            for (int i = 0; i < 4; i++)
            {
                int x = temp.Info.posX + dx[i];
                int y = temp.Info.posY + dy[i];

                if (x < 0 || y < 0 || x >= gameManager.width || y >= gameManager.height) continue;
                if (gameManager.checkBoardInfo[x, y]) continue;
                if (gameManager.blockBoardInfo[x, y].Info.blockType == temp.Info.blockType)
                {
                    gameManager.checkBoardInfo[x, y] = true;
                    q.Enqueue(gameManager.blockBoardInfo[x, y]);
                    ans.Add(gameManager.blockBoardInfo[x, y]);
                }
            }
        }

        return ans;
    }

    public override void Exit()
    {
        ResetVisited();
    }

    void ResetVisited()
    {
        for (int i = 0; i < gameManager.width; i++)
        {
            for (int j = 0; j < gameManager.height; j++)
            {
                gameManager.checkBoardInfo[i, j] = false;
            }
        }
    }


}
