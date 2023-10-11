using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Player
{
    public class DimensionSword : Aeterna, Ability
    {
        public GameObject Sword;

        public DimensionSword(GameObject _gameObject)
        {
            Sword = _gameObject;
        }

        public void Execution()
        {
            //공격 애니매이션 사용, 칼 활성화
            //만일 타격이 없다면 원거리 공격
            //animator.SetBool("")
            Debug.Log("DimensionSword!");
        }
    }
}