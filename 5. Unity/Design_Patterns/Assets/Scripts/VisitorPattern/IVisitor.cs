namespace Chapter.VisitorPattern
{
    public interface IVisitor
    {
        void VisitElementA(ElementA A);

        void VisitElementB(ElementB B);
    }
}
