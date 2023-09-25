using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Loading
{
    public class GameManager : SingletonTemplate<GameManager>
    {
        //로딩할 씬 이름
        public string nextSceneName;
    }
}