using System;
using System.Collections.Generic;
using System.ComponentModel;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using EditorNative.SceneElements.SceneObjects;

namespace EditorPlugins.Editors.AnimGraph
{
  #region AnimStandardValuesProvider

  public class AnimationSelectedAttribute : Attribute
  {
  }

  [ApplicableForDeriver]
  public sealed class AnimStandardValuesProvider : TwoTypedStandardValuesProvider<string, AnimationSelectedAttribute>
  {

    public AnimStandardValuesProvider( IEditorWinApplication application, Attribute attribute ) : base( application, attribute ) { }

    public override TypeConverter.StandardValuesCollection GetStandardValues( System.ComponentModel.ITypeDescriptorContext context )
    {
      List<string> newvalues = new List<string>();
      Node owner = context.Instance as Node;
      if ( null == owner && context.Instance is ICustomTypeDescriptor )
      {
        owner = (context.Instance as ICustomTypeDescriptor).GetPropertyOwner(context.PropertyDescriptor) as Node;
      }
      if ( owner != null )
      {
        AnimGraphContext agc = owner.Context;
        foreach( AnimInfo item in agc.animInfos )
        {
          newvalues.Add( item.animName );
        }
        newvalues.Sort();
      }
      return new TypeConverter.StandardValuesCollection( newvalues );
    }

    public override bool HasStandardValuesConvertor( System.ComponentModel.ITypeDescriptorContext context ) { return false; }
    protected override string ConvertFromStandardValueInternal( System.ComponentModel.ITypeDescriptorContext context, object instance, object value ) { return value as string; }
    public override bool IsStandardValuesExclusive( System.ComponentModel.ITypeDescriptorContext context ) { return true; }
    public override Type GetStandardValuesType( System.ComponentModel.ITypeDescriptorContext context ) { return typeof( string ); }
  }

  #endregion

  #region NextNodeSelectedAttribute
  
  public class NextNodeSelectedAttribute : Attribute
  {
  }

  [ApplicableForDeriver]
  public sealed class NodeSelectStandardValuesProvider : TwoTypedStandardValuesProvider<string, NextNodeSelectedAttribute>
  {
    public NodeSelectStandardValuesProvider( IEditorWinApplication application, Attribute attribute ) : base( application, attribute ) { }

    public override TypeConverter.StandardValuesCollection GetStandardValues( System.ComponentModel.ITypeDescriptorContext context )
    {
      List<string> newvalues = new List<string>();
      Node owner = context.Instance as Node;
      if ( null == owner && context.Instance is ICustomTypeDescriptor )
      {
        owner = (context.Instance as ICustomTypeDescriptor).GetPropertyOwner(context.PropertyDescriptor) as Node;
      }
      if ( owner != null )
      {
        AnimGraphContext agc = owner.Context;
        foreach ( Link link in owner.Links )
        {
          newvalues.Add( link.ToNode.Name );
        }
        newvalues.Sort();
      }
      return new TypeConverter.StandardValuesCollection( newvalues );
    }

    public override bool HasStandardValuesConvertor( System.ComponentModel.ITypeDescriptorContext context ) { return false; }
    protected override string ConvertFromStandardValueInternal( System.ComponentModel.ITypeDescriptorContext context, object instance, object value ) { return value as string; }
    public override bool IsStandardValuesExclusive( System.ComponentModel.ITypeDescriptorContext context ) { return true; }
    public override Type GetStandardValuesType( System.ComponentModel.ITypeDescriptorContext context ) { return typeof( string ); }
  }

  #endregion
}
