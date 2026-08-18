namespace Flash
{
  // Класс агрегатор подпорок для FlashFramework
  public static class FlashProp
  {
    public static int DjvuTopMarginBias
    {
      get { return 4; }
    }
    public static int DjvuSideMarginBias
    {
      get { return 2; }
    }

    public static int ViewTextFieldAutoWidth()
    {
      return 1;
    }
    public static int ViewTextFieldNoCharsY(int fontSize)
    {
      return (int)(3 + fontSize / 12.0F);
    }
  
  }
}

