using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Reflection;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Serialization;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace libdb.DB
{
  public static partial class DBXmlSerializer
  {
    private static string ParentResourceFieldName = "__parent";
    private static string ParentResourceAttributeName = "parent";
    private static string SkipItemFieldName = "skip";
    private static string DeleteItemFieldName = "delete";
    private static string BackLinkFieldName = "BackLink";

    private static string StatesListFieldName = "__states";
    private static string StateElementFieldName = "state";
    private static string StateNameAttributeName = "name";

    //поля помеченные одним из этих атрибутов будут игнорироваться при сериализации
    private static Type[] ignoredAttributes = new Type[0];
    private static bool skipParents = false;
    private static bool skipInlined = false;
    private static bool storeBacklinks = true;

    public delegate object TypeReplacementFunc( object obj );

    private static bool SerializeObject( XmlWriter writer, object realobj, object parent, FieldPath path, bool root, Dictionary<Type, TypeReplacementFunc> replacementDelegates )
    {
      bool result = true;
      object obj = realobj;

      if ( replacementDelegates != null && replacementDelegates.ContainsKey( realobj.GetType()) && replacementDelegates[ realobj.GetType() ] != null )
        obj = replacementDelegates[obj.GetType()]( realobj );

      if ( obj.GetType() == typeof( Boolean ) )
        writer.WriteValue( (Boolean)obj );
      else if ( obj.GetType() == typeof( Int32 ) )
        writer.WriteValue( (Int32)obj );
      else if ( obj.GetType() == typeof( long ) )
        writer.WriteValue( (long)obj );
      else if ( obj.GetType() == typeof( UInt32 ) )
        writer.WriteValue( obj.ToString() );
      else if ( obj.GetType() == typeof( Single ) )
      {
        if ( ( (Single)( obj ) ).ToString( NumberFormatInfo.InvariantInfo ) == "NaN" )
        {
          string pathstr = "";
          foreach ( libdb.DB.FieldPath.FieldPathItem p in path )
          {
            pathstr += p.Field.Name + " ";
          }
          Log.TraceError( "NaN: " + pathstr );
        }
        writer.WriteString( ( (Single)( obj ) ).ToString( NumberFormatInfo.InvariantInfo ) );
      }
      else if ( obj.GetType() == typeof( String ) )
        writer.WriteString( ( obj as String ) );
      else if ( obj.GetType() == typeof( Guid ) )
        writer.WriteString( ( (Guid)( obj ) ).ToString().ToUpper() );
      else if ( obj.GetType().IsEnum )
        WriteEnumValue( writer, obj );
      else if ( TypeUtils.IsList( obj.GetType() ) )
      {
        MethodInfo method = obj.GetType().GetMethod( "MayBeBroken" );
        if ( method != null )
        {
          bool maybeBroken = (bool)method.Invoke( obj, null );
          if ( maybeBroken )
          {
            method = obj.GetType().GetMethod( "GetOwner" );
            if ( method != null )
            {
              DBResource res = (DBResource)method.Invoke( obj, null );
              if ( res != null )
              {
                var rootObj = DataBase.Get<DBResource>( res.DBId );
                if ( rootObj != null )
                {
                  if( rootObj.GetBackLinks().Keys.Count > 0 )
                  {
                    List<DBID> badDBIDs = new List<DBID>();

                    foreach ( var bl in rootObj.GetBackLinks().Keys )
                    {
                      var childObj = DataBase.Get<DBResource>( bl );
                      if ( childObj != null )
                      {
                        var resParent = GetResourceParent( childObj.Get() );
                        if ( resParent != null && resParent.DBId == res.DBId )
                        {
                          badDBIDs.Add( bl );
                        }
                      }
                    }
                    if ( badDBIDs.Count > 0 )
                    {
                      Log.TraceError( "May be broken children: " );
                      foreach( var badId in badDBIDs )
                      {
                        Log.TraceError( badId.NameFormatted );
                      }
                      Log.TraceError( " due to parent change: " );
                      Log.TraceError( res.DBId.NameFormatted );
                    }
                  }
                }
              }
            }
          }
        }

        method = obj.GetType().GetMethod( "FixBroken" );
        if ( method != null )
        {
          method.Invoke( obj, null );
        }

        result = WriteListValue( writer, obj, parent, path, replacementDelegates );

      }
      else if ( TypeUtils.GetTypeFromPtr( obj.GetType() ) != null )
        result = WriteDBPtrValue( writer, obj, parent, path, root, replacementDelegates );
      else if ( TypeUtils.IsSubclassOf( obj.GetType(), typeof( IDBSerializable ) ) )
        WriteDBSerializable( writer, obj, parent, path, replacementDelegates );
      else
        result = WriteClass( writer, obj, parent, path, replacementDelegates );

      return result;
    }

    public delegate bool FieldCheckFunction( DBFieldInfo dbFieldInfo );

    private static bool WriteClass( XmlWriter writer, object obj, object parent, FieldPath path, Dictionary<Type, TypeReplacementFunc> replacementDelegates )
    {
      return WriteClass( writer, obj, parent, path, replacementDelegates, null );
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="writer"></param>
    /// <param name="obj"></param>
    /// <param name="parent"></param>
    /// <param name="path"></param>
    /// <param name="replacementDelegates"></param>
    /// <param name="fieldCheckFunction">Is checked field will be serialized</param>
    /// <returns></returns>
    private static bool WriteClass( XmlWriter writer, object obj, object parent, FieldPath path, Dictionary<Type, TypeReplacementFunc> replacementDelegates, FieldCheckFunction isFieldMaySerializedCheckFunction )
    {
      List<DBFieldInfo> fields = new List<DBFieldInfo>();
      fields.AddRange( TypeUtils.GetFields( obj.GetType(), true ) );
      fields.Sort( ( x, y ) => { return string.Compare( x.Name, y.Name ); } );

      if ( fields.Count == 0 )
        return true;

      bool result = true;

      foreach ( DBFieldInfo field in fields )
      {
        if ( !field.CanRead || TypeUtils.HasAttribute<XmlIgnoreAttribute>( field, false ) )
          continue;

        if ( IsFieldIgnored( field ) )
          continue;

        if ( field.Name == ParentResourceFieldName )
          continue;

        if ( isFieldMaySerializedCheckFunction != null )
          if ( !isFieldMaySerializedCheckFunction( field ) )
            continue;

        object parentField = parent != null ? field.GetValue( parent ) : null;
        object childField = field.GetValue( obj );

        if ( parent != null && IsDerivedFromParent( field, childField, obj ) )
          continue;

        if (replacementDelegates != null && replacementDelegates.ContainsKey(childField.GetType()) && replacementDelegates[childField.GetType()] == null)
          continue;

        writer.WriteStartElement( field.Name );
        result = SerializeObject( writer, childField, parentField, path.Push( obj, field ), false, replacementDelegates );
        writer.WriteEndElement();
      }

      return result;
    }

    private static bool IsFieldIgnored( DBFieldInfo field )
    {
      foreach ( Type attribute in ignoredAttributes )
      {
        object[] attr = field.GetCustomAttributes( attribute, true );

        if ( attr != null && attr.Length > 0 )
        {
          return true;
        }
      }

      return false;
    }

    private static bool IsDerivedFromParent( DBFieldInfo fieldType, object childField, object childObject )
    {
      bool isDerived = true;
      if ( childField is libdb.IBasicDBValue )
      {
        isDerived = ( childField as libdb.IBasicDBValue ).IsDerivedFromParent();
      }
      else if ( childObject != null && childObject is libdb.ICompositeDBValue )
      {
        isDerived = ( childObject as libdb.ICompositeDBValue ).IsFieldDerivedFromParent( fieldType.Name );
      }
      return isDerived;
    }

    private static void WriteResourceParentAttribute( XmlWriter writer, DBResource obj )
    {
      libdb.Diagnostics.Log.Assert( writer.WriteState == System.Xml.WriteState.Element || writer.WriteState == System.Xml.WriteState.Attribute, "Invalid xml writer state" );
      DBPtrBase parentPtr = GetResourceParent( obj );
      if ( parentPtr != null && !parentPtr.DBId.IsEmpty )
        writer.WriteAttributeString( ParentResourceAttributeName, parentPtr.DBId.ToString() );
    }

    private static void WriteDBSerializable( XmlWriter writer, object obj, object parent, FieldPath path, Dictionary<Type, TypeReplacementFunc> replacementDelegates )
    {
      IDBSerializable serializable = obj as IDBSerializable;

      object nestedObject = null;
      object attributes = null;
      serializable.Serialize( path, out nestedObject, out attributes );

      if ( attributes != null )
      {
        List<DBFieldInfo> fieldList = new List<DBFieldInfo>();
        fieldList.AddRange( TypeUtils.GetFields( attributes.GetType(), true ) );
        fieldList.Sort( ( x, y ) => { return string.Compare( x.Name, y.Name ); } );
        foreach ( DBFieldInfo field in fieldList )
          writer.WriteAttributeString( field.Name, field.GetValue( attributes ).ToString() );
      }

      if ( nestedObject != null )
        SerializeObject( writer, nestedObject, null, path, false, replacementDelegates );
    }

    private static bool WriteDBPtrValue( XmlWriter writer, object obj, object _parent, FieldPath path, bool root, Dictionary<Type, TypeReplacementFunc> replacementDelegates )
    {
      bool result = true;
      DBPtrBase ptr = obj as DBPtrBase;
      DBPtrBase parentPtr = ptr.Get<DBResource>() == null ? null : GetResourceParent( ptr.Get<DBResource>() );
      DBResource parent = parentPtr == null ? null : parentPtr.Get<DBResource>();

      if ( root )
      {
        string typeName = ResolveContentTypeName( ptr );
        writer.WriteStartElement( typeName );
        WriteResourceParentAttribute( writer, ptr.Get<DBResource>() );

        if ( storeBacklinks )
        {
          Dictionary<DBID, int> backLinks = ptr.GetBackLinks();
          if ( backLinks != null )
          {
            foreach ( KeyValuePair<DBID, int> backLink in backLinks )
            {
              writer.WriteStartElement( BackLinkFieldName );
              writer.WriteStartAttribute( "DBID" );
              writer.WriteValue( backLink.Key.Name );
              writer.WriteEndAttribute();
              writer.WriteStartAttribute( "Count" );
              writer.WriteValue( backLink.Value );
              writer.WriteEndAttribute();
              writer.WriteEndElement();
            }
          }
        }

        result = SerializeObject( writer, ptr.Get<DBResource>(), parent, path, true, replacementDelegates );

        if ( TypeUtils.HasAttribute<HasStatesAttribute>( ptr.Get<DBResource>().GetType(), true ) )
          WriteDataStates( writer, ptr, path, replacementDelegates );

        writer.WriteEndElement();
      }
      else
      {
        writer.WriteStartAttribute( "href" );
        writer.WriteValue( ptr.DBId.FileName );
        writer.WriteEndAttribute();

        if ( ptr.DBId.IsInlined )
        {
          writer.WriteStartAttribute( "id" );
          writer.WriteValue( ptr.DBId.Id );
          writer.WriteEndAttribute();

          if ( !skipInlined )
          {
            string typeName = ResolveContentTypeName( ptr );
            writer.WriteStartElement( typeName );
            WriteResourceParentAttribute( writer, ptr.Get<DBResource>() );

            result = SerializeObject( writer, ptr.Get<DBResource>(), parent, path, false, replacementDelegates );

            if ( TypeUtils.HasAttribute<HasStatesAttribute>( ptr.Get<DBResource>().GetType(), true ) )
              WriteDataStates( writer, ptr, path, replacementDelegates );

            writer.WriteEndElement();
          }
        }
      }
      return result;
    }

    private static void WriteDataStates( XmlWriter writer, DBPtrBase ptr, FieldPath path, Dictionary<Type, TypeReplacementFunc> replacementDelegates )
    {
      List<string> stateNames = ptr.GetStates();

      if ( stateNames == null || stateNames.Count <= 1 )
        return;

      writer.WriteStartElement( StatesListFieldName );

      foreach ( var stateName in stateNames )
      {
        if ( stateName == String.Empty )
          continue;

        writer.WriteStartElement( StateElementFieldName );
        writer.WriteAttributeString( StateNameAttributeName, stateName );
        DBResource res = ptr.Get<DBResource>( stateName );
        DBPtrBase parentPtr = GetResourceParent( res );
        //WriteResourceParentAttribute( writer, res );

        //TODO SE> update FieldPath ( used by TextRef )
        SerializeObject( writer, res, parentPtr == null ? null : parentPtr.Get<DBResource>(), path, false, replacementDelegates );

        writer.WriteEndElement();
      }
      writer.WriteEndElement();
    }

    private static string ResolveContentTypeName( DBPtrBase ptr )
    {
      if ( ptr.Get<DBResource>() == null )
      {
        libdb.Diagnostics.Log.AlwaysAssert( "Error: inlined or root resource is null" );
        return string.Empty;
      }

      Type type = ptr.Get<DBResource>().GetType();
      CrapTypeNameAttribute crapAttribute = TypeUtils.GetAttribute<CrapTypeNameAttribute>( type, false );
      string typeName = crapAttribute == null ? type.Name : crapAttribute.Name;
      return typeName;
    }

    private static bool WriteListValue( XmlWriter writer, object obj, object parent, FieldPath path, Dictionary<Type, TypeReplacementFunc> replacementDelegates )
    {
      bool result = true;
      if ( parent == null )
      {
        int index = 0;
        foreach ( object item in obj as IEnumerable )
        {
          writer.WriteStartElement( "Item" );
          result &= SerializeObject( writer, item, null, path.Push( index ), false, replacementDelegates );
          writer.WriteEndElement();
          ++index;
        }
      }
      else
      {
        int index = 0;
        IEnumerator objEnum = ( obj as IEnumerable ).GetEnumerator();
        IEnumerator parentEnum = ( parent as IEnumerable ).GetEnumerator();
        Type elemType = TypeUtils.GetTypeFromList( obj.GetType() );

        IRichList listCasted = obj as IRichList;
        while ( true )
        {
          bool hasObjElem = objEnum.MoveNext();
          bool hasParentElem = parentEnum.MoveNext();
          if ( !hasObjElem && !hasParentElem )
            break;

          writer.WriteStartElement( "Item" );
          if ( hasObjElem && hasParentElem )
          {
            if ( listCasted.IsElementDerivedFromParent( index ) )
            {
              writer.WriteAttributeString( SkipItemFieldName, "1" );
            }
            else
            {
              result &= SerializeObject( writer, objEnum.Current, parentEnum.Current, path.Push( index ), false, replacementDelegates );
            }
          }
          else if ( !hasObjElem )
          {
            writer.WriteAttributeString( DeleteItemFieldName, "1" );
          }
          else
          {
            result &= SerializeObject( writer, objEnum.Current, null, path.Push( index ), false, replacementDelegates );
          }
          writer.WriteEndElement();
          ++index;
        }
      }
      return result;
    }

    private static void WriteEnumValue( XmlWriter writer, object obj )
    {
      if ( TypeUtils.HasAttribute<FlagsAttribute>( obj.GetType(), true ) )
        writer.WriteString( Enum.Format( obj.GetType(), obj, "D" ) );
      else
        writer.WriteString( obj.ToString() );
    }

    private static DBPtrBase GetResourceParent( DBResource resource )
    {
      if ( skipParents )
        return null;

      DBFieldInfo parentField = TypeUtils.GetField( resource.GetType(), ParentResourceFieldName, false );
      if ( parentField == null )
      {
        Log.AlwaysAssert( "Cannot find field \'parent\' in type {0}", resource.GetType().Name );
        return null;
      }

      if ( parentField != null )
        return parentField.GetValue( resource ) as DBPtrBase;
      return null;
    }

    internal static bool Serialize( XmlWriter writer, DBPtrBase resource )
    {
      return Serialize( writer, resource, new Type[0], true );
    }

    internal static bool Serialize( XmlWriter writer, DBPtrBase resource, Type[] attributesToIgnore, bool _storeBacklinks )
    {
      if ( writer == null || resource == null || resource.Get<DBResource>() == null )
        return false;
      DBPtrBase parent = GetResourceParent( resource.Get<DBResource>() );

      bool result = false;
      try
      {
        DataBase.UndoRedoManager.SerializeSuspend();
        ignoredAttributes = attributesToIgnore ?? new Type[0];
        storeBacklinks = _storeBacklinks;
        skipParents = false;
        skipInlined = false;
        result = SerializeObject( writer, resource, parent, new FieldPath(), true, null );
      }
      finally
      {
        DataBase.UndoRedoManager.SerializeResume();
        ignoredAttributes = new Type[0];
        storeBacklinks = true;
      }

      return result;
    }

    public static bool Serialize( XmlWriter writer, object resource, Dictionary<Type, TypeReplacementFunc> replacementDelegates )
    {
      return Serialize( writer, resource, replacementDelegates, null );
    }

    public static bool Serialize( XmlWriter writer, object resource, Dictionary<Type, TypeReplacementFunc> replacementDelegates, FieldCheckFunction isFieldMaySerializedCheckFunction )
    {
      skipParents = true;
      skipInlined = true;
      return WriteClass( writer, resource, null, new FieldPath(), replacementDelegates, isFieldMaySerializedCheckFunction );
    }
  }
}
