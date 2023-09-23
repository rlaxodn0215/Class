using UnityEngine;

namespace Chapter.VisitorPattern
{

    public class AddNum : IVisitor //ScriptableObject 사용하여 모듈화
    {
        public void VisitElementA(ElementA A)
        {
            Debug.Log("AddNum ccess Element A");
        }

        public void VisitElementB(ElementB B)
        {
            Debug.Log("AddNum access Element B");
        }
    }
}