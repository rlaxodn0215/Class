namespace Chapter.VisitorPattern
{
    public class ElementA : IElement
    {
        int numA = 10;
        public void Accept(IVisitor v)
        {
            v.VisitElementA(this);
        }
    }
}
