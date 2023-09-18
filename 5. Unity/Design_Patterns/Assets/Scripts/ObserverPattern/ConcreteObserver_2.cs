using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConcreteObserver_2 : ObserverPattern.Observer
{
    public void UpdateData(int data)
    {
        Debug.Log("ConcreteObserver_2 에서 호출");
    }
}
