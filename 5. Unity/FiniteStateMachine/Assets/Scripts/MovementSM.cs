using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementSM : StateMachine
{
    [HideInInspector]
    public Idle idleState;
    [HideInInspector]
    public Moving movingState;

    public Rigidbody2D rigidbody;

    public float speed = 4.0f;
    public SpriteRenderer spriteRenderer;

    private void Awake()
    {
        idleState = new Idle(this);
        movingState = new Moving(this);
    }

    protected override BaseState GetInitalState()
    {
        return idleState;
    }
}
