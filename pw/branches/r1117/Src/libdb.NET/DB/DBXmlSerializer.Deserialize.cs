using System;
using System.Collections.Generic;
using System.Threading;
using libdb.Diagnostics;
using System.Globalization;
using System.Reflection;
using System.Xml;

namespace libdb.DB
{
	public static partial class DBXmlSerializer
	{
		private struct DeserializedBackLink
		{
			public readonly DBID dbid;
			public readonly int count;

			public DeserializedBackLink( DBID dbid, int count )
			{
				this.dbid = dbid;
				this.count = count;
			}
		}

		private static bool IsPrimitiveType( Type type )
		{
      return type == typeof(Boolean) || type == typeof(Int32) || type == typeof(long) || type == typeof(UInt32) || type == typeof(Single) || type == typeof(String) || type == typeof(Guid) || (type != null && type.IsEnum);
		}

		#region Primitive types parser helpers

		private static bool TryParseBool( string value, out object obj )
		{
			if ( string.Compare( value, "1" ) == 0 || string.Compare( value, true.ToString(), StringComparison.InvariantCultureIgnoreCase ) == 0 )
				obj = true;
			else if ( string.Compare( value, "0" ) == 0 || string.Compare( value, false.ToString(), StringComparison.InvariantCultureIgnoreCase ) == 0 )
				obj = false;
			else
				obj = null;

			return obj != null;
		}

		private static bool TryParseInt( string value, out object obj )
		{
			int outObj = 0;
			if ( int.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

    private static bool TryParseLong( string value, out object obj )
    {
      long outObj = 0;
      if ( long.TryParse( value, out outObj ) )
        obj = outObj;
      else
        obj = null;

      return obj != null;
    }

		private static bool TryParseUint( string value, out object obj )
		{
			uint outObj = 0;
			if ( uint.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private static bool TryParseFloat( string value, out object obj )
		{
			float outObj;

      string sep = Thread.CurrentThread.CurrentCulture.NumberFormat.NumberDecimalSeparator;

      if( float.TryParse( value.Replace( ".", sep ).Replace( ",", sep ), out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private static bool TryParseEnum( string value, Type type, out object obj )
		{
			int intValue = 0;
			if ( int.TryParse( value, out intValue ) )
			{
				obj = intValue;
				return true;
			}

			try
			{
				obj = Enum.Parse( type, value, true );
				return true;
			}
			catch ( ArgumentException )
			{
				obj = null;
				return false;
			}
		}

		private static bool TryParseGuid( string value, out object obj )
		{
			if ( string.IsNullOrEmpty( value ) )
			{
				obj = Guid.Empty;
				return true;
			}

			char[] guidValue = new char[32];
			int guidIndex = 0;
			foreach ( char c in value )
			{
				if ( c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f' )
				{
					if ( guidIndex >= guidValue.Length )
					{
						obj = null;
						return false;
					}
					guidValue[guidIndex++] = c;
				}
				else if ( c == '-' || c == '{' || c == '}' || c == '(' || c == ')' )
					continue;
				else
				{
					obj = null;
					return false;
				}
			}

			obj = new Guid( new string( guidValue ) );
			return true;
		}

		private static bool TryParsePrimitive( string value, Type type, out object result )
		{
			if ( type == typeof( bool ) )
				return TryParseBool( value, out result );
			else if ( type == typeof( int ) )
				return TryParseInt( value, out result );
      else if ( type == typeof( long ) )
        return TryParseLong( value, out result );
			else if ( type == typeof( UInt32 ) )
				return TryParseUint( value, out result );
      else if (type == typeof(uint))
        return TryParseUint(value, out result);
      else if (type == typeof(float))
				return TryParseFloat( value, out result );
			else if ( type == typeof( Guid ) )
				return TryParseGuid( value, out result );
			else if ( type.IsEnum )
				return TryParseEnum( value, type, out result );
			else if ( type == typeof( string ) )
			{
				result = value;
				return true;
			}

			result = null;
			return false;
		}

		private static bool TryDeserializePrimitive( XmlContextReader reader, Type type, out object result )
		{
			return TryParsePrimitive( reader.IsEmptyElement ? string.Empty : reader.ReadContentAsString(), type, out result );
		}

		#endregion

		private static bool TryDeserializeList( XmlContextReader reader, Type type, ref object result, DBTypesCache cache, DBResource owner, DBID ownerDBID )
		{
			if ( result == null )
				result = CreateObject( type, owner );

			Type internalType = TypeUtils.GetTypeFromList( type );

			//@Ivn@TODO: Remove usage of SetOrAdd method use Item, Count, Clear etc instead
      MethodInfo setOrAddMethos = TypeUtils.GetMethod( result.GetType(), "SetOrAdd", new Type[2] { typeof( int ), internalType } );
      MethodInfo removeAtMethod = TypeUtils.GetMethod( result.GetType(), "RemoveAt", new Type[1] { typeof( int ) } );

			if ( Log.Assert( setOrAddMethos != null && removeAtMethod != null, "Serializing list that is not UndoRedoList" ) )
				return false;

      IRichList list = result as IRichList;

      int counter = 0;
      while ( reader.IsStartElement() )
      {
        object value = null;

        if ( reader.Name != "Item" )
        {
          reader.Skip();
          continue;
        }

        if ( reader.GetAttribute( SkipItemFieldName ) != null )
        {
          ++counter;
          reader.Skip();
        }
        else if ( reader.GetAttribute( DeleteItemFieldName ) != null )
        {
          if ( counter < list.Count )
            removeAtMethod.Invoke( result, new object[1] { counter } );
          reader.Skip();
        }
        else
        {
          if ( counter < list.Count )
          {
            foreach ( PropertyInfo pi in result.GetType().GetProperties() )
            {
              if ( pi.GetIndexParameters().Length == 1 )
              {
                value = pi.GetValue( result, new object[1] { counter } );
                break;
              }
            }          
          }

          if ( TryDeserializeField( reader, internalType, ref value, cache, owner, ownerDBID ) )
          {
            if ( null == list || list.MaxCount <= 0 || counter < list.MaxCount )
              setOrAddMethos.Invoke( result, new object[2] { counter++, value } );
          }
        }
			}

			return true;
		}

		private static bool IsPtrType( Type type )
		{
			return TypeUtils.GetTypeFromPtr( type ) != null;
		}

		private static bool TryDeserializePtr( XmlContextReader reader, Type type, ref object result, DBTypesCache cache, DBResource owner, DBID ownerDBID )
		{
			Type internalType = TypeUtils.GetTypeFromPtr( type );
			ConstructorInfo ownerConstructor = type.GetConstructor( new Type[] { typeof( DBID ), internalType, typeof( DBResource ) } );

			if ( ownerConstructor == null )
			{
				Log.TraceWarning( "Cannot find constructor for DBPtr<{0}> in context {1}", internalType.Name, reader.Context.Name );
				return false;
			}

			bool emptyElement = reader.IsEmptyElement;

			string fileName = string.Empty;
			Guid id = Guid.Empty;
      bool valid = false;
			if ( reader.MoveToAttribute( "id" ) )
				id = new Guid( reader.Value );
      if ( reader.MoveToAttribute( "href" ) )
      {
        fileName = reader.Value;
        valid = true;
      }

      DBID dbid = DBID.FromFileName(id == Guid.Empty ? fileName : ownerDBID.FileName, id);
      if ( dbid.IsEmpty )
      {
        if ( valid )
          result = ownerConstructor.Invoke(new object[] { dbid, null, owner });
        else
          result = null;
        reader.Skip();
        return valid;
      }
      
      if (!emptyElement)
				reader.ReadStartElement();

			if ( !dbid.IsInlined )
			{
				result = ownerConstructor.Invoke( new object[] { dbid, null, owner } );
				reader.Skip();
			}
			else if ( emptyElement )
			{
				result = ownerConstructor.Invoke( new object[] { DBID.Empty, null, owner } );
				reader.Skip();
			}
			else 
			{
				object resource = null;
        Dictionary<string, DBResource> states = new Dictionary<string, DBResource>();
				if ( !TryDeserializeClass( reader, internalType, ref resource, null, states, cache, null, dbid ) || resource == null )
				{
					reader.Skip();
					reader.ReadEndElement();
					result = null;
					return false;
				}
				result = ownerConstructor.Invoke( new object[3] { dbid, resource, owner } );
        if ( states.Count > 0 )
        {
          DBPtrBase resultPtr = result as DBPtrBase;
          resultPtr.LoadStates( states );
        }

				reader.ReadEndElement();
			}

			return true;
		}

		private static bool IsDBSerializable( Type type )
		{
			return TypeUtils.IsSubclassOf( type, typeof( IDBSerializable ) );
		}

		private static bool TryDeserializeDBSerializable( XmlContextReader reader, Type type, ref object result, DBTypesCache cache, DBResource owner, DBID ownerDBID )
		{
			if ( result == null )
			{
				result = TypeUtils.CreateInstance( type );
				if ( result == null )
					return false;
			}

			IDBSerializable serializable = result as IDBSerializable;
			object attributes = TypeUtils.CreateInstance( serializable.GetAttributesType() );
			if ( attributes == null )
        return false;

      Dictionary<string, DBFieldInfo> fields = CollectFields( attributes );
      if ( reader.MoveToFirstAttribute() )
      {
        do
        {
          DBFieldInfo field = null;
          object fieldValue = null;
          if ( fields.TryGetValue( reader.Name, out field ) && TryParsePrimitive( reader.Value, field.FieldType, out fieldValue ) )
            field.SetValue( attributes, fieldValue );
        } while ( reader.MoveToNextAttribute() );
      }

			Type nestedObjectType = null;
			if ( !serializable.DeserializeAttributes( attributes, out nestedObjectType ) )
				return false;

			if ( nestedObjectType == null )
			{
				reader.Skip();
				return true;
			}

			object nestedObject = null;
			reader.MoveToElement();
      if ( !TryDeserializeField( reader, nestedObjectType, ref nestedObject, cache, owner, ownerDBID ) )
				return false;

			return serializable.DeserializeNestedObject( attributes, nestedObject );
		}

		private static bool IsTextRefType( Type type ) 
		{
			return type == typeof( TextRef );
		}

		private static Dictionary<string, DBFieldInfo> CollectFields( object result )
		{
			Dictionary<string, DBFieldInfo> fields = new Dictionary<string, DBFieldInfo>();
			foreach ( DBFieldInfo field in TypeUtils.GetFields( result.GetType(), true ) )
			{
				if ( field.CanWrite )
				{
					fields.Add( field.Name, field );
				}
			}
			return fields;
		}

    private static bool TryDeserializeStruct( XmlContextReader reader, Type type, ref object result, Dictionary<DBID, int> backLinks, Dictionary<string, DBResource> states, DBTypesCache cache, DBResource owner, DBID ownerDBID )
		{
			if ( !reader.IsStartElement() )
				return false;

			if ( result == null )
			{
				result = TypeUtils.CreateInstance( type );
				if ( result == null )
				{
					Log.TraceWarning( "Cannot create object of type \"{0}\" in context \"{1}\"", type.Name, reader.Context.Name );
					return false;
				}
			}

			Dictionary<string, DBFieldInfo> fields = CollectFields( result );

			while ( reader.IsStartElement() )
			{
				DBFieldInfo field = null;
        if ( reader.Name == BackLinkFieldName )
				{
					if ( backLinks != null )
					{
						DBID dbid = DBID.Empty;
						int count = 0;

						if ( reader.MoveToAttribute( "DBID" ) )
							dbid = DBID.FromFileName( reader.Value, false );

						if ( reader.MoveToAttribute( "Count" ) )
							int.TryParse( reader.Value, out count );

            int oldCount = 0;
            if ( !backLinks.TryGetValue( dbid, out oldCount ) )
              oldCount = 0;
            backLinks[ dbid ] = count + oldCount;
					}

					reader.Skip();
				}
        else if ( reader.Name == StatesListFieldName )
        {
          if ( states != null )
          {
            if ( reader.IsEmptyElement )
            {
              reader.Skip();
              continue;
            }
            reader.ReadStartElement();

            while ( reader.IsStartElement() )
            {
              if ( reader.Name != StateElementFieldName )
              {
                reader.Skip();
                continue;
              }

              if ( !reader.MoveToAttribute( StateNameAttributeName ) )
              {
                reader.Skip();
                continue;
              }

              string stateName = reader.Value;
              object stateObj = TypeUtils.CreateObject( result.GetType() );

              if ( stateObj is DBResource )
              {
                ( stateObj as DBResource ).SetParent( result );
                reader.MoveToElement();
                TryReadClassContents( reader, type, ref stateObj, null, null, cache, owner, ownerDBID );
                states[stateName] = (DBResource)stateObj;
              }

            }
            reader.ReadEndElement();
          }
        }
        else if ( fields.TryGetValue( reader.Name, out field ) )
        {
          object value = field.GetValue( result );

          if ( TryDeserializeField( reader, field.FieldType, ref value, cache, owner, ownerDBID ) )
            field.SetValue( result, value );
        }
        else
          reader.Skip();
			}

			return true;
		}

		private static object CreateObject( Type type, DBResource owner )
		{
			ConstructorInfo ownedConstructor = type.GetConstructor( new Type[1] { typeof( DBResource ) } );
			if ( ownedConstructor != null )
				return ownedConstructor.Invoke( new object[1] { owner } );

			ConstructorInfo defaultConstructor = type.GetConstructor( Type.EmptyTypes );
			if ( defaultConstructor == null )
			{
				Log.TraceWarning( "Default constructor not found for type \"{0}\"", type.Name );
				return null;
			}

			return defaultConstructor.Invoke( new object[0] );
		}

    private static bool TryDeserializeClass( XmlContextReader reader, Type type, ref object result, Dictionary<DBID, int> backLinks, Dictionary<string, DBResource> states, DBTypesCache cache, DBResource owner, DBID ownerDBID )
		{
			if ( !reader.IsStartElement() || !TypeUtils.IsResourceType( type ) )
				return false;

			Type objectType = null;
			if ( !cache.TryGetType( reader.Name, out objectType ) )
			{
				Log.TraceWarning( "Found unknown type \"{0}\" in context \"{1}\"", reader.Name, reader.Context.Name );
				return false;
			}

			if ( type != objectType && !TypeUtils.IsSubclassOf( objectType, type ) )
			{
				Log.TraceWarning( "Cannot cast type \"{0}\" to type \"{1}\" in context \"{2}\"", objectType.Name, type.Name, reader.Context.Name );
				return false;
			}

      result = CreateObject( objectType, owner );

      if ( result == null )
      {
        Log.TraceWarning( "Cannot create object of type \"{0}\" in context \"{1}\"", objectType.Name, reader.Context.Name );
        return false;
      }

      TryReadClassContents( reader, type, ref result, backLinks, states, cache, owner, ownerDBID );
			return true;
		}

    private static void TryReadClassContents( XmlContextReader reader, Type type, ref object result, Dictionary<DBID, int> backLinks, Dictionary<string, DBResource> states, DBTypesCache cache, DBResource owner, DBID ownerDBID )
    {
      TryReadParentAttribute( reader, result, owner );
      if ( reader.IsEmptyElement )
        reader.Skip();
      else
      {
        reader.ReadStartElement();

        TryDeserializeStruct( reader, type, ref result, backLinks, states, cache, result as DBResource, ownerDBID );

        if ( reader.NodeType == System.Xml.XmlNodeType.EndElement )
          reader.ReadEndElement();
      }
    }

    private static void TryReadParentAttribute( XmlContextReader reader, object result, DBResource owner )
    {
      string parentName = reader.GetAttribute( ParentResourceAttributeName );
      if ( parentName != null && parentName != string.Empty )
      {
        ICompositeDBValue resValue = result as ICompositeDBValue;
        if ( resValue != null )
        {
          DBID dbid = DBID.FromString( parentName );
          DBPtr<DBResource> ptr = new DBPtr<DBResource>( dbid, null );
          resValue.SetParent( ptr );
        }
      }
    }

    private static bool TryDeserializeField( XmlContextReader reader, Type type, ref object result, DBTypesCache cache, DBResource owner, DBID ownerDBID )
    {
      if ( IsPtrType( type ) )
        return TryDeserializePtr( reader, type, ref result, cache, owner, ownerDBID );
      else if ( IsDBSerializable( type ) )
        return TryDeserializeDBSerializable( reader, type, ref result, cache, owner, ownerDBID );
      else
      {
        bool isEmptyElement = reader.IsEmptyElement;
        if ( !isEmptyElement )
          reader.ReadStartElement();

        bool resultValue = false;
        if ( IsPrimitiveType( type ) )
          resultValue = TryParsePrimitive( isEmptyElement ? string.Empty : reader.ReadContentAsString(), type, out result );
        else if ( TypeUtils.IsList( type ) )
        {
          if ( !isEmptyElement )
            resultValue = TryDeserializeList( reader, type, ref result, cache, owner, ownerDBID );
        }
        else if ( !isEmptyElement )
          resultValue = TryDeserializeStruct( reader, type, ref result, null, null, cache, owner, ownerDBID );

        if ( isEmptyElement )
          reader.Skip();
        else
        {
          if ( reader.NodeType == XmlNodeType.Element )
            reader.ReadStartElement();
          while ( reader.NodeType != XmlNodeType.EndElement )
            reader.Skip();
          reader.ReadEndElement();
        }

        return resultValue;
      }
    }

	  internal static DBResource Deserialize( XmlContextReader reader, DBTypesCache cache, Dictionary<DBID, int> backLinks, Dictionary<string, DBResource> states )
		{
			object result = null;
      try
      {
        DataBase.UndoRedoManager.SerializeSuspend();
        if ( !TryDeserializeClass( reader, typeof( DBResource ), ref result, backLinks, states, cache, null, reader.Context ) )
          result = null;
      }
      finally
      {
        DataBase.UndoRedoManager.SerializeResume();
      }

			return result as DBResource;
		}

    //public static T Deserialize<T>( string xml, DBID context ) where T : DBResource
    //{
    //  DBReference.Reset();
    //  DataBase.UndoRedoManager = new libdb.UndoRedo.UndoRedoManager();
    //  DBTypesCache cache = new DBTypesCache();
    //  cache.RegisterTypeTest( typeof( T ) );
    //  return Deserialize( XmlContextReader.Create( xml, context ), cache, null, null ) as T ;
    //}
	}
}
