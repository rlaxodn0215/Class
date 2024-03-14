using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using DefineData;
using UnityEngine.EventSystems;

namespace AniPang
{
    public class BlockFrame : MonoBehaviour, IPointerDownHandler
    {
        public delegate void GivePos(Vector2Int start, Vector3 mouse);
        public GivePos givePos;

        //[HideInInspector]
        public Block_Type type;
        //[HideInInspector]
        public Vector2Int pos = new Vector2Int();

        public void SetBlockType(Block_Type type)
        {
            this.type = type;
        }

        public void SetPos(Vector2Int pos)
        {
            this.pos = pos;
        }

        public void OnPointerDown(PointerEventData eventData)
        {
            givePos(pos, Input.mousePosition);
        }

    }
}