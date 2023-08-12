using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour
{
    private int itemNum;
    public int ItemNum { get { return itemNum; } set { itemNum = value; } }
    public string ItemMenu(int num)
    {
        if (num == 0)
        {
            return "ARROW";
        }

        else if (num == 1)
        {
            return "HP Potion";
        }

        else
            return null;
    }
}
