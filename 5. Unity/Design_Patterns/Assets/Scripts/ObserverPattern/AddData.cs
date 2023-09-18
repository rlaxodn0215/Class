using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace ObserverPattern
{
    public class AddData : MonoBehaviour, Subject
    {

        private int data = 0;

        private List<Observer> obs = new List<Observer>();

        public void NotifyObservers()
        {
            foreach(Observer ob in obs)
            {
                ob.UpdateData(data);
            }
        }

        public void RemoveObserver(Observer ob)
        {
            obs.Remove(ob);
        }

        public void ResisterObserver(Observer ob)
        {
            obs.Add(ob);
        }

        void Start()
        {
            // MonoBehavior에서 상속을 받을 때는 생성자가 생성이 안된다
            // MonoBehavior는 객체로 클래스만 사용 가능 (GameObject O / gameObject X)

            ConcreteObserver_1 one = new ConcreteObserver_1();
            ConcreteObserver_2 two = new ConcreteObserver_2();

            ResisterObserver(one);
            ResisterObserver(two);
        }

        void Update()
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                data++;
                Debug.Log( gameObject.name + " 에서 data++");
                NotifyObservers();
            }
        }
    }
}