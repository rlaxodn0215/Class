using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Block : MonoBehaviour
{
    public enum BlockType
    {
        RedBlock,
        GreenBlock,
        BlueBlock,
        BlockCount,
        EmptyBlock
    }

    public struct BlockInfo
    {
        public int posX;
        public int posY;
        public BlockType blockType;
        public BlockInfo(int x, int y, BlockType type)
        {
            posX = x;
            posY = y;
            blockType = type;
        }
    }

    [HideInInspector]
    public BlockInfo Info;
    private RawImage image;

    public float dropSpeed = 5.0f;

    private void Awake()
    {
        image = GetComponent<RawImage>();
    }

    public void SetBlockType(BlockType type)
    {
        switch(type)
        {
            case BlockType.RedBlock:
                image.color = Color.red;
                break;
            case BlockType.GreenBlock:
                image.color = Color.green;
                break;
            case BlockType.BlueBlock:
                image.color = Color.blue;
                break;
        }
    }

    public void MoveDown()
    {
        transform.Translate(Vector3.down * dropSpeed * Time.deltaTime,Space.Self);
    }

    public void PlayerMoveBlock()
    {

    }



}
