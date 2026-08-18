namespace Flash
{
  internal struct Margin
  {
    public Margin( int top, int right, int bottom, int left )
    {
      this.right = right;
      this.left = left;
      this.top = top;
      this.bottom = bottom;
    }

    public int right;
    public int left;
    public int top;
    public int bottom;
  }
}