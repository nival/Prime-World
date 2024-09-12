using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public sealed class JointNamesValueProvider : TwoTypedStandardValuesProvider<string, JointNamesSelectorAttribute>
  {
    private const uint SKEL_SIGN = 0x4C454B53;

    private TypeConverter.StandardValuesCollection emptyResult = new TypeConverter.StandardValuesCollection( new List<string>{string.Empty} );

    public JointNamesValueProvider( IEditorWinApplication _application, Attribute _attribute )
      : base( _application, _attribute ) { }

    private List<string> GetAllJointsFromFile( string mayaFileName )
    {
      List<string> res = new List<string>();

      using ( FileStream file = new FileStream( DataBase.FileSystem.GetRealFileName( mayaFileName ), FileMode.Open ) )
      {
        using(BinaryReader readBinary = new BinaryReader( file ))
        {
          uint sign = readBinary.ReadUInt32();
          if( sign != SKEL_SIGN )
            return res;

          uint jointsCount = readBinary.ReadUInt32();
          for( uint i = 0; i < jointsCount; i++ )
          {
            string jointName = "";
            Char c = readBinary.ReadChar();
            do
            {
              jointName += c;
              c = readBinary.ReadChar();
            } while( c != 0 );

            res.Add( jointName );

            uint tempuint = readBinary.ReadUInt32();
            for( uint nJ = 0; nJ < 3; ++nJ )
            {
              for( uint nK = 0; nK < 4; ++nK )
              {
                float temp = readBinary.ReadSingle();
              }
            }
          }
        }
      }

      return res;
    }

    public override TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext _context )
    {
      List<string> result = new List<string>();

      Locator locator = FullTypePropertyDescriptor.GetInstanceFromContext( _context ) as Locator;

      if( locator == null )
        return emptyResult;

      LocatorList locatorList = locator.GetOwner() as LocatorList;

      if( locatorList == null )
        return emptyResult;

      if( !locatorList.DBId.IsInlined )
      {
        DBPtr<LocatorList> ptr = DataBase.Get<LocatorList>( locatorList.DBId );
        Dictionary<DBID, int> backlinks = ptr.GetBackLinks();

        Log.Assert( backlinks != null );

        foreach( DBID key in backlinks.Keys )
        {
          GetResult( locatorList.DBId, key, ref result );
        }
      }
      else
      {
        GetResult( locatorList.DBId, DBID.FromDBID( locatorList.DBId, false ), ref result );
      }

      result.Sort();
      result.Insert( 0, "" );
      return new TypeConverter.StandardValuesCollection( result );
    }

    private void GetResult( DBID locatorListId, DBID resourceId, ref List<string> result )
    {
      DBResource resource = DataBase.Get<DBResource>( resourceId );

      List<string> temp = new List<string>();

      if( resource is DBAnimatedSceneComponent )
      {
        temp = GetAllJointsFromFile( ( resource as DBAnimatedSceneComponent ).mayaFileName );
      }
      else if( resource is DBSceneResource )
      {
        temp = GetJointsFromSceneResource( locatorListId, resource as DBSceneResource );
      }
      
      result = ( result.Count == 0 ) ? temp : CollectionUtils.Intersection( result, temp );
    }

    private List<string> GetJointsFromSceneResource( DBID locatorListId, DBSceneResource sceneResource )
    {
      List<string> result = new List<string>();

      foreach( AttachedSceneComponent attach in sceneResource.attached )
      {
        DBAnimatedSceneComponent component = attach.component.Get() as DBAnimatedSceneComponent;

        if( component != null && component.locatorList.DBId == locatorListId )
        {
          result = GetAllJointsFromFile( component.mayaFileName );
          break;
        }
      }

      return result;
    }

    public override bool HasStandardValuesConvertor( ITypeDescriptorContext _context ) { return false; }

    protected override string ConvertFromStandardValueInternal( ITypeDescriptorContext _context, object _instance, object _value )
    {
      return _value as string;
    }

    public override bool IsStandardValuesExclusive( ITypeDescriptorContext _context ) { return true; }

    public override Type GetStandardValuesType( ITypeDescriptorContext _context ) { return typeof( string ); }
  }

  [ApplicableForDeriver]
  public sealed class JointNamesStringConvertor : TwoTypedStringConvertor<string, JointNamesSelectorAttribute>
  {
    public JointNamesStringConvertor( IEditorWinApplication _application, Attribute _attribute )
      : base( _application, _attribute ) { }

    public override bool SuppressProperties { get { return true; } }

    protected override string ConvertFromStringInternal( ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, string value )
    {
      if( value == "None" )
        return string.Empty;

      return value;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, System.Globalization.CultureInfo culture, string value )
    {
      if( string.IsNullOrEmpty( value ) )
        return "None";

      return value;
    }
  }
}
