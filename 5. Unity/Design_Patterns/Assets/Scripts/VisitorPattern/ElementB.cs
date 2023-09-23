namespace Chapter.VisitorPattern
{

    public class ElementB : IElement
    {
        int numB = 20;
        public void Accept(IVisitor v)
        {
            v.VisitElementB(this);
        }
    }
}