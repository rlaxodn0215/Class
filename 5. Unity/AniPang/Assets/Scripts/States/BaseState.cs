
public class BaseState
{
    protected StateMachine stateMachine;

    public BaseState(StateMachine machine)
    {
        stateMachine = machine;
    }

    public virtual void Enter() { }
    public virtual void Update() { }
    public virtual void Exit() { }
}
