namespace Chapter.VisitorPattern
{
    public interface IElement
    {
        void Accept(IVisitor v);
    }
}