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

    void ZoomCamera() // FPS 스코프 배율 조정
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

    // Camera Inspector의 ViewPort Rect로 화면 분할 가능
    // Depth : 카메라 그려지는 순서
    // Culling Mask: 해당 레이어만 카메라에 보이게 설정 / 적의 위치만 파악할 때 UI 카메라로 설정, 물건을 숨길 때 
}
