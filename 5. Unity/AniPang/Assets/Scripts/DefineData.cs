using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace DefineData
{
    public class Constant
    {
        public static int imageSize = 50;
    }

    public enum Block_Type
    {
        Red,
        Green,
        Blue,
        TypeCount
    }

    public enum Switch_Way
    {
        None,
        Up,
        Down,
        Left,
        Right
    }

    public enum Game_State
    {
        InitalizeBlockState,
        SwitchBlockState,
        BreakBlockState,
        GameStateCount
    }
}
