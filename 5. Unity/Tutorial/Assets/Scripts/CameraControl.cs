using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControl : MonoBehaviour
{
    Camera mainCamera;

    // Start is called before the first frame update
    void Start()
    {
        mainCamera = GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update()
    {
        MoveCamera();
        RotateCamera();
        ZoomCamera();
    }

    void MoveCamera()
    {
        if(Input.GetMouseButton(0))
        {
            transform.Translate(Input.GetAxis("Mouse X") / 10.0f, Input.GetAxis("Mouse Y") / 10.0f,0.0f);
        }
    }

    void RotateCamera()
    {
        if(Input.GetMouseButton(1))
        {
            transform.Rotate(Input.GetAxis("Mouse Y") * 10.0f, Input.GetAxis("Mouse X") * 10.0f, 0.0f);
            //transform.Rotate(Input.GetAxis("Mouse Y") * 10.0f, 0.0f, 0.0f);
        }
    }

    void ZoomCamera() // FPS ������ ���� ����
    {
        mainCamera.fieldOfView += (20 * Input.GetAxis("Mouse ScrollWheel"));

        if (mainCamera.fieldOfView < 10)
        {
            mainCamera.fieldOfView = 10;
        }

        else if(mainCamera.fieldOfView > 150)
        {
            mainCamera.fieldOfView = 150;
        }
    }

    // Camera Inspector�� ViewPort Rect�� ȭ�� ���� ����
    // Depth : ī�޶� �׷����� ����
    // Culling Mask: �ش� ���̾ ī�޶� ���̰� ���� / ���� ��ġ�� �ľ��� �� UI ī�޶�� ����, ������ ���� �� 
}
