using System;
using System.Collections.Generic;
using EditorLib.Settings;
using EditorLib.ToolBox;

namespace EditorLib.Extensions
{
  [ConfigObject( true )]
  public class AbstractEditorConfig : SimpleConfigObject
	{
    public Dictionary<Type, List<ToolBoxItem>> userToolBoxItems = new Dictionary<Type, List<ToolBoxItem>>();
    public Dictionary<Type, List<string>> recentToolBoxItems = new Dictionary<Type, List<string>>();


    public void StoreUserToolBoxItems( Type editorType, List<ToolBoxItem> items )
    {
      userToolBoxItems[editorType] = items;
    }

    public List<ToolBoxItem> GetUserToolBoxItems( Type editorType )
    {
      List<ToolBoxItem> items = null;
      if ( !userToolBoxItems.TryGetValue( editorType, out items ) || items == null )
        return new List<ToolBoxItem>();

      return items;
    }

    public List<string> GetRecentlyUsedToolBoxItems(Type editorType)
    {
      List<string> result;

      if (!recentToolBoxItems.TryGetValue(editorType, out result))
        return new List<string>();

      return result;
    }

    public void StoreRecentlyUsedToolBoxItems(Type editorType, List<string> items)
    {
      recentToolBoxItems[editorType] = items;
    }
	}
}
