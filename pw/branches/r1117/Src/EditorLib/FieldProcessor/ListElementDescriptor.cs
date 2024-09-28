using System;
using System.Reflection;
using EditorLib.Extensions;
using libdb.DB;
using System.Collections;
using libdb.Diagnostics;
using System.Collections.Generic;
using libdb;

namespace EditorLib.FieldProcessor
{
  public class ListElementDescriptor : FullTypePropertyDescriptor
  {
    private readonly int index = 0;
    private readonly Type componentType = null;
		private readonly bool hasIndexField = false;
    private string displayName = string.Empty;

    # region attributes getting

    public static Attribute[] GetCombinedAttributes( Type type, Attribute[] attributes )
    {
      List<Attribute> result = new List<Attribute>( TypeUtils.GetAttributes<Attribute>( type, true ) );
      if ( null != attributes )
        result.AddRange( attributes );
      return result.ToArray();
    }

    # endregion

    # region Initialization

    public ListElementDescriptor( int index, Type itemType, Type componentType, Attribute[] attributes, IEditorWinApplication application, string fieldSignature )
      : base( FullTypeDescriptor.Create( itemType, application, attributes, fieldSignature ), index.ToString(), GetCombinedAttributes( itemType, attributes ) )
    {
      this.index = index;
      this.componentType = componentType;
      this.hasIndexField = HasIndexField( itemType );
      this.displayName = index.ToString();
    }

    public ListElementDescriptor( int index, string forceName, Type itemType, Type componentType, Attribute[] attributes, IEditorWinApplication application, string fieldSignature )
      : base(FullTypeDescriptor.Create(itemType, application, attributes, fieldSignature ), forceName, GetCombinedAttributes(itemType, attributes))
    {
      this.index = index;
      this.componentType = componentType;
      hasIndexField = false;
      displayName = forceName;
    }

    # endregion

    # region PropertyDescriptor overiding

    public override Type ComponentType { get { return componentType; } }
    public override string DisplayName { get { return displayName; } }

    protected override object GetValueInternal( object component )
    {
      PropertyInfo itemProperty = TypeUtils.GetProperty( component.GetType(), "Item" );
      if ( null == itemProperty )
      {
        Log.TraceWarning( "Cannot find \"Item\" property in component with type \"{0}\"", component.GetType() );
        return null;
      }

      //TODO: Do not throw exception when index outside of array's bounds
      object value = itemProperty.GetValue( component, new object[1] { index } );
      
      // change display name if IndexField attribute set
      if ( hasIndexField )
        UpdateDisplayName( value );
      
      return value;
    }

    protected override void SetValueInternal( object component, object value )
    {
      PropertyInfo itemProperty = TypeUtils.GetProperty( component.GetType(), "Item" );
      if ( null == itemProperty )
      {
        Log.TraceWarning( "Cannot find \"Item\" property in component with type \"{0}\"", component.GetType() );
        return;
      }

      //TODO: Do not throw exception when index outside of array's bounds
      itemProperty.SetValue( component, value, new object[1] { index } );
    }

    # endregion

    #region general access to list implementation

    public int Index { get { return index; } }
 
    #endregion

    # region evaluating element name

    private bool HasIndexField( Type itemType )
    {
      Type typeToCheck = itemType.IsSubclassOf( typeof( DBPtrBase ) ) ? TypeUtils.GetTypeFromPtr( itemType ) : itemType;

      return TypeUtils.HasAttribute<IndexFieldAttribute>( typeToCheck, true );
    }

		private string GetDefaultName()
		{
			if ( !hasIndexField )
			{
				string result = index.ToString();
				if ( result.Length > 5 )
					return result;

				return new string( ' ', 5 - result.Length ) + result;
			}
			else
				return "(" + index.ToString() + ")";
		}

    private void UpdateDisplayName( object value )
    {
			if ( value == null )
				return;

      object nameValue = value;
      
      bool attributePresent = false;
      bool hideIndex = false;
      while ( nameValue != null )
      {
        Type nameValueType = nameValue.GetType();
        
        DBPtrBase ptrNameValue = nameValue as DBPtrBase;
        if ( ptrNameValue != null )
        {
          nameValue = ptrNameValue.Get<DBResource>();
          if ( nameValue == null )
            break;
          nameValueType = nameValue.GetType();
        }

        IndexFieldAttribute indexFieldAttr = TypeUtils.GetAttribute<IndexFieldAttribute>( nameValueType, true );
        if ( null == indexFieldAttr )
          break;
        
        attributePresent = true;

        DBFieldInfo field = TypeUtils.GetField( nameValueType, indexFieldAttr.FieldName, true );
        if ( field == null )
          break;

        nameValue = field.GetValue( nameValue );
        hideIndex = indexFieldAttr.HideItemIndex;
      }

			if ( nameValue == null || !attributePresent )
			{
        displayName = GetDefaultName();
			}
			else
			{
				displayName = nameValue.ToString();
				if ( string.IsNullOrEmpty( displayName ) )
				{
          displayName = GetDefaultName();
				}
        else if( !hideIndex )
				{
          displayName = displayName + " " + GetDefaultName();
				}
			}
    }

    # endregion

    public override bool ShouldSerializeValue( object component )
    {
      if ( !( component is IRichList ) )
        return false;

      IRichList list = component as IRichList;
      if ( list.IsElementDerivedFromParent( index ) )
        return false;
      else
        return true;
    }

    public override bool CanResetValue( object component )
    {
      return ShouldSerializeValue( component );
    }

    public override void ResetValue( object component )
    {
      if ( !( component is IRichList ) )
        return;

      IRichList list = component as IRichList;
      list.ResetElement( index );
    }

  }
}
