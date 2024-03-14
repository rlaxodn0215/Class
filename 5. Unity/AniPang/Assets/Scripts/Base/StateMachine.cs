using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StateMachine : MonoBehaviour
{
    IBaseState currentState;
    void Start()
    {
        currentState = GetInitalState();
        currentState.Enter();
    }

    // Update is called once per frame
    void Update()
    {
        if (currentState != null)
            currentState.Update();
    }

    public void ChangeState(IBaseState newState)
    {
        currentState.Exit();
        currentState = newState;
        currentState.Enter();
    }

    protected virtual IBaseState GetInitalState()
    {
        return null;
    }
}
