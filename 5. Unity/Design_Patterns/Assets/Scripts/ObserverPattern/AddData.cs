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
            // MonoBehavior���� ����� ���� ���� �����ڰ� ������ �ȵȴ�
            // MonoBehavior�� ��ü�� Ŭ������ ��� ���� (GameObject O / gameObject X)

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
                Debug.Log( gameObject.name + " ���� data++");
                NotifyObservers();
            }
        }
    }
}