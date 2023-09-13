using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Moving : BaseState
{
    private MovementSM sm;
    private float horizontalInput;

    public Moving(MovementSM stateMachine) : base("Moving", stateMachine) {
        sm = (MovementSM)stateMachine;
    }
    public override void Enter()
    {
        base.Enter();
        horizontalInput = 0f;
        sm.spriteRenderer.color = Color.red;
    }

    public override void UpdateLogic()
    {
        base.UpdateLogic();
        horizontalInput = Input.GetAxis("Horizontal");
        //. transition to "moving" state if input !=0
        if (Mathf.Abs(horizontalInput) < Mathf.Epsilon)
        {
            stateMachine.ChangeState(sm.idleState);
        }
    }

    public override void UpdatePhysics()
    {
        base.UpdatePhysics();
        Vector2 vel = sm.rigidbody.velocity;
        vel.x = horizontalInput * sm.speed;
        sm.rigidbody.velocity = vel;
    }
}
