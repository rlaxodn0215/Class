using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class PlayerNav : MonoBehaviour
{
    public float runSpeed = 10.0f;
    public float rotationSpeed = 360.0f;

    CharacterController pcController;
    Vector3 direction;
    Animator animator;
    NavMeshAgent agent = null;

    // Start is called before the first frame update
    void Start()
    {
        pcController = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
        agent = GetComponent<NavMeshAgent>();
    }

    // Update is called once per frame
    void Update()
    {
        //CharactorControll_Slerp();
        NavMesh_Control();
    }

    void NavMesh_Control()
    {
        if(Input.GetMouseButton(1))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;

            if(Physics.Raycast(ray,out hit))
            {
                agent.SetDestination(hit.point);
            }
        }
    }

    private void FixedUpdate()
    {
        animator.SetFloat("Speed", agent.velocity.magnitude);
    }

    void CharactorControll_Slerp()
    {
        direction = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        if (direction.sqrMagnitude > 0.01f)
        {
            Vector3 forward = Vector3.Slerp(transform.forward,
                                            direction,
                                            rotationSpeed * Time.deltaTime / Vector3.Angle(transform.forward, direction));

            transform.LookAt(transform.position + forward);
        }

        else
        {

        }

        animator.SetFloat("Speed", pcController.velocity.magnitude);
        pcController.Move(direction * runSpeed * Time.deltaTime + Physics.gravity * Time.deltaTime);
    }

    private void OnDrawGizmos()
    {
        if (agent == null) return;
        NavMeshPath path = agent.path;

        Gizmos.color = Color.blue;
        foreach (Vector3 corner in path.corners)
        {
            Gizmos.DrawSphere(corner, 0.4f);
        }

        Gizmos.color = Color.red;
        Vector3 pos = transform.position;
        foreach (Vector3 corner in path.corners)
        {
            Gizmos.DrawLine(pos, corner);
            pos = corner;
        }
    }
}
