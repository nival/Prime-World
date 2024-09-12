using System;
using System.Collections.Generic;
using EditorLib.Settings;
using System.ComponentModel;
using EditorLib.FieldProcessor;

namespace EditorLib.PropertiesEditor.PropertyPresets
{
	[ConfigObject( false, "PropertiesEditorPresets" )]
  public sealed class PropertyPresetConfig : SimpleConfigObject
	{
    public enum OutlinerExpandState
    {
      NA,
      Expand,
      Collapse,
      ListExpand,
    }

    [Serializable]
    public class FieldControlItem
    {
      public string name;
      public bool visible = true;
      public bool canEdit = true;
      public OutlinerExpandState expandInOutliner = OutlinerExpandState.Collapse;

      public FieldControlItem() { }

      public FieldControlItem( FieldControlItem src ) 
      {
        this.name = src.name;
        this.visible = src.visible;
        this.canEdit = src.canEdit;
        this.expandInOutliner = src.expandInOutliner;
      }

      public FieldControlItem( string _name, bool _visible, bool _canEdit )
      {
        name = _name;
        visible = _visible;
        canEdit = _canEdit;
      }
    }

    [Serializable]
    public class PresetConfigItem
    {
      public string name;

      // Field sets
      public Dictionary<string, List<FieldControlItem>> fieldSets = new Dictionary<string, List<FieldControlItem>>();

      // INvisible enum values (it is estimated that is is more efficient to store hidden enum values, not visible)
      public Dictionary<string, List<string>> hiddenEnumValues = new Dictionary<string, List<string>>();

      public PresetConfigItem Clone()
      {
        PresetConfigItem dst = new PresetConfigItem();

        dst.name = this.name;

        foreach (string item in fieldSets.Keys)
        {
          List<FieldControlItem> valueList = new List<FieldControlItem>();
          foreach (FieldControlItem item2 in fieldSets[item])
          {
            valueList.Add(new FieldControlItem(item2));
          }
          dst.fieldSets[item] = valueList;
        }

        foreach (string item in hiddenEnumValues.Keys)
        {
          dst.hiddenEnumValues[item] = new List<string>(hiddenEnumValues[item]);

        }

        return dst;
      }

      public PropertyDescriptorCollection FilterProperties( Type type, PropertyDescriptorCollection orig )
      {
        if ( !fieldSets.ContainsKey( type.Name ) )
          return orig;

        List<PropertyDescriptor> filtered = new List<PropertyDescriptor>();
        List<PropertyDescriptor> remaining = new List<PropertyDescriptor>();
        foreach ( PropertyDescriptor item in orig )
          remaining.Add( item );

        List<FieldControlItem> fieldSet = fieldSets[type.Name];

        for ( int i = 0; i < fieldSet.Count; ++i )
        {
          FieldControlItem item = fieldSet[i];
          string fieldName = item.name;
          PropertyDescriptor desc = orig.Find( fieldName, true );
          if ( null == desc )
            continue;

          remaining.Remove( desc );

          if ( !item.visible )
            continue;

          if ( desc is FieldDescriptor )
          {
            ( desc as FieldDescriptor ).IsForcedReadOnly = !item.canEdit;
          }
          filtered.Add( desc );
        }

        foreach ( PropertyDescriptor item in remaining )
          filtered.Add( item );

        return new PropertyDescriptorCollection( filtered.ToArray() );
      }
    }

    public List<PresetConfigItem> configPresets = new List<PresetConfigItem>();
    [ConfigObjectField( true )]
    public int selectedPreset = -1;
    public bool canEditPresets = true;
	}
}
