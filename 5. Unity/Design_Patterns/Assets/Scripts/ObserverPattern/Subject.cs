using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace ObserverPattern
{ 
    public interface Subject
    {
        public void ResisterObserver(Observer ob);
        public void RemoveObserver(Observer ob);
        void NotifyObservers();

    }
}