using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StateMachine : MonoBehaviour
{
    BaseState currentState;

    // Start is called before the first frame update
    void Start()
    {
        currentState = GetInitalState();
        if (currentState != null)
            currentState.Enter();
    }

    // Update is called once per frame
    void Update()
    {
        if (currentState != null)
            currentState.UpdateLogic();
    }

    private void LateUpdate()
    {
        if (currentState != null)
            currentState.UpdatePhysics();
    }

    public void ChangeState(BaseState newState)
    {
        currentState.Exit();

        currentState = newState;
        currentState.Enter();
    }

    protected virtual BaseState GetInitalState()
    {
        return null;
    }

    private void OnGUI()
    {
        string content = currentState != null ? currentState.name : "(no current state)";
        GUILayout.Label($"<color='black><size=40>{content}</size></color>");
    }

}
