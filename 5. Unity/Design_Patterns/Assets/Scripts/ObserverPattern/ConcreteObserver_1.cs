using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConcreteObserver_1 : ObserverPattern.Observer 
{
    public void UpdateData(int data)
    {
        Debug.Log("ConcreteObserver_1 에서 호출");
    }
}
