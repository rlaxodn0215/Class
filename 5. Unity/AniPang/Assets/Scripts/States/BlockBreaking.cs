using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockBreaking : BaseState
{
    private GameManager gameManager;

    public BlockBreaking(StateMachine machine) : base(machine)
    {
        gameManager = machine as GameManager;
    }

    public override void Enter()
    {
        
    }

    public override void Update()
    {

    }
}
