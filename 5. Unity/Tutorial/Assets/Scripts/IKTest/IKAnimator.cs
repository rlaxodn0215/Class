using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IKAnimator : PlayerWithIK
{
    private void OnAnimatorIK(int layerIndex)
    {
        if (animator)
        {

            if (IKs != null)
            {
                ////√÷¿˚»≠
                //for(int i = 0; i < 4; i++)
                //{

                //}

                // Right Hand
                animator.SetIKPositionWeight(AvatarIKGoal.RightHand, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.RightHand, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.RightHand, ik["RightHand"].transform.position);

                Quaternion RightHandRotation = Quaternion.Euler(-60, 0, 0);
                animator.SetIKRotation(AvatarIKGoal.RightHand, RightHandRotation);

                //Left Hand
                animator.SetIKPositionWeight(AvatarIKGoal.LeftHand, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.LeftHand, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.LeftHand, ik["LeftHand"].transform.position);

                Quaternion LeftHandRotation = Quaternion.Euler(-60, 0, 0);
                animator.SetIKRotation(AvatarIKGoal.LeftHand, LeftHandRotation);

                //Right Foot
                animator.SetIKPositionWeight(AvatarIKGoal.RightFoot, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.RightFoot, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.RightFoot, ik["RightFoot"].transform.position);

                Quaternion RightFootRotation = Quaternion.Euler(30, 0, 0);
                animator.SetIKRotation(AvatarIKGoal.RightFoot, RightFootRotation);

                //Left Foot
                animator.SetIKPositionWeight(AvatarIKGoal.LeftFoot, posWeight);
                animator.SetIKRotationWeight(AvatarIKGoal.LeftFoot, rotWeight);

                animator.SetIKPosition(AvatarIKGoal.LeftFoot, ik["LeftFoot"].transform.position);

                Quaternion LeftFootRotation = Quaternion.Euler(30, 0, 0);
                animator.SetIKRotation(AvatarIKGoal.LeftFoot, LeftFootRotation);
            }
        }
    }
}
