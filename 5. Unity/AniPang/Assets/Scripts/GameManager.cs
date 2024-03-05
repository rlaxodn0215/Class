using System.Collections.Generic;
using UnityEngine;

public class GameManager : StateMachine
{
    public enum StateName
    {
        Initalize,
        Evaluate,
        BlockBreaking
    }

    [HideInInspector]
    public const int length = 50;
    [HideInInspector]
    public const int frameSpace = 5;

    public int width = 6;
    public int height = 5;
    public int breakNumber = 3;
    public RectTransform block;

    [HideInInspector]
    public Block[,] blockBoardInfo;
    [HideInInspector]
    public bool[,] checkBoardInfo;
    [HideInInspector]
    public int[] widthIndex;

    [HideInInspector]
    public Dictionary<StateName, BaseState> States = new Dictionary<StateName, BaseState>();
    [HideInInspector]
    public Vector3 startPos;

    void Awake()
    {
        InitStates();
        startPos = new Vector3(-(width - 1) * length / 2, (height - 1) * length / 2, 0);
        widthIndex = new int[width];
    }

    void InitStates()
    {
        States[StateName.Initalize] = new Initalize(this);
        States[StateName.Evaluate] = new Evaluate(this);
        States[StateName.BlockBreaking] = new BlockBreaking(this);
    }

    protected override BaseState GetInitalState()
    {
        return States[StateName.Initalize];
    }

    //void ShowBlockInfo()
    //{
    //    string temp = "";
    //    for (int i = 0; i < width; i++)
    //    {
    //        for (int j = 0; j < height; j++)
    //        {
    //            temp +=(blockBoardInfo[i,j].Info.typeNumber + " ");
    //        }
    //        temp += "\n";
    //    }
    //    Debug.Log(temp);
    //}
}
