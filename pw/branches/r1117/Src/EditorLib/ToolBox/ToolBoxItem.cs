using System.Drawing;

namespace EditorLib.ToolBox
{
	public sealed class ToolBoxItem
	{
		public string category;
		public string name;

    [libdb.DB.StoreTypeWithField]
    public object tag;

    public readonly Image image = null;

	  //public bool IsUserItem { get; set; }

    public ToolBoxItem()
    {
    }

    public ToolBoxItem(string category, string name, object tag)
    {
      this.category = category;
      this.name = name;
      this.tag = tag;
    }

//    public ToolBoxItem(string category, string name, object tag, bool isUserItem)
//    {
//      this.category = category;
//      this.name = name;
//      this.tag = tag;
//      IsUserItem = isUserItem;
//    }

    public ToolBoxItem( string category, string name, Image image, object tag )
    {
      this.category = category;
      this.name = name;
      this.image = image;
      this.tag = tag;
    }
  }
}
