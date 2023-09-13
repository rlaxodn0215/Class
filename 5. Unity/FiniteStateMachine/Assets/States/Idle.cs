using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Idle : BaseState
{
    private float horizontalInput;

    public Idle(MovementSM stateMachine) : base("Idle", stateMachine) { }
    public override void Enter()
    {
        base.Enter();
        horizontalInput = 0f;
        ((MovementSM)stateMachine).spriteRenderer.color = Color.black;
    }

    public override void UpdateLogic()
    {
        base.UpdateLogic();
        horizontalInput = Input.GetAxis("Horizontal");
        //. transition to "moving" state if input !=0
        if(Mathf.Abs(horizontalInput) > Mathf.Epsilon)
        {
            stateMachine.ChangeState(((MovementSM)stateMachine).movingState);
        }
    }
}
