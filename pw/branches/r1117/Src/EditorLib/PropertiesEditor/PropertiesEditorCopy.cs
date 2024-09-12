using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using libdb;
using libdb.Animated;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using libdb.UndoRedo;

namespace EditorLib.PropertiesEditor
{
	internal static class PropertiesEditorCopy
	{
		private class CopyContext
		{
			public bool collecting = true;
			public readonly Dictionary<DBID, DBID> inlineMap = new Dictionary<DBID, DBID>();
		}

		public static bool Copy( object _dst, object _src )
		{
			return Copy( _dst, _src, new Attribute[0] );
		}

		public static bool Copy( object _dst, object _src, IEnumerable<Attribute> _attributes )
		{
			if ( _src == null || _dst == null || ReferenceEquals( _src, _dst ) )
				return false;

			Log.Assert( _src.GetType() == _dst.GetType(), "Can only copy objects of same types" );
			Log.Assert( !TypeUtils.IsSimpleType( _src.GetType() ), "Can only copy reference types" );

			using ( UndoRedoTransaction trans = new UndoRedoTransaction( "DBMetaCopy" ) )
			{
				CopyContext context = new CopyContext();
				
				bool result = CopyObject(_src, _dst, context, _attributes);

				if ( result )
					trans.Commit();

				return result;
			}
		}

		private static bool CopyFields( object _dst, object _src, CopyContext _context )
		{
			if ( _dst == null || _src == null || ReferenceEquals( _dst, _src ) )
				return false;

			Log.Assert( _src.GetType() == _dst.GetType(), "Can only copy objects of same types" );

			DBFieldInfo[] fields = TypeUtils.GetFields( _src.GetType(), true );
			bool isComposite = _src is ICompositeDBValue && !(_src is IAnimated) && ( (ICompositeDBValue)_src ).IsFieldDerivedFromParent( "__parent" );

			foreach ( DBFieldInfo field in fields )
			{
				if ( field.Name == "__parent" )
				{
					if ( isComposite )
					{
						CopySingleField( _dst, _src, field, _context );
						( (ICompositeDBValue)_dst ).SetParent( field.GetValue( _dst ) );
					}
				}
				else
				{
					if ( field.CanRead )
						CopySingleField( _dst, _src, field, _context );
				}
			}

			if ( _src is ICompositeDBValue && _dst is ICompositeDBValue )
				ResetInheritedFields( (ICompositeDBValue)_dst, (ICompositeDBValue)_src, fields );

			return true;
		}

		private static void CopySingleField( object _dest, object _src, DBFieldInfo _field, CopyContext _context )
		{
			object srcValue = _field.GetValue( _src );
			object dstValue = _field.GetValue( _dest );

			if ( TypeUtils.IsSimpleType( _field.FieldType ) )
			{
				CopySimpleType( _field, _dest, srcValue, dstValue );
			}
			else
			{
				CopyObject(srcValue, dstValue, _context, TypeUtils.GetAttributes<Attribute>(_field, true));
			}
		}

		private static bool CopyStates( DBResource _dst, DBResource _src, CopyContext _context )
		{
			if ( _src == null || _dst == null || _src.DBId.IsEmpty || _dst.DBId.IsEmpty )
				return false;

			DBPtr<DBResource> srcPtr = DataBase.Get<DBResource>( _src.DBId );
			DBPtr<DBResource> dstPtr = DataBase.Get<DBResource>( _dst.DBId );

			//удаляем все стейты из dst объекта
			List<string> dstStates = dstPtr.GetStates();
			foreach ( string stateName in dstStates )
			{
				if ( !string.IsNullOrEmpty( stateName ) )
					dstPtr.RemoveState( stateName );
			}

			//копируем стейты из src в dst
			List<string> srcStates = srcPtr.GetStates();
			foreach ( string stateName in srcStates )
			{
				if ( string.IsNullOrEmpty( stateName ) )
					continue;

				dstPtr.AddState( stateName );

				DBResource srcState = srcPtr.Get( stateName );
				DBResource dstState = dstPtr.Get( stateName );

				if ( !CopyFields( dstState, srcState, _context ) )
					return false;

				dstState.SetParent( dstPtr.Get() );
			}

			return true;
		}

		private static void ResetInheritedFields( ICompositeDBValue _dst, ICompositeDBValue _src, IEnumerable<DBFieldInfo> _fields )
		{
			if ( _dst == null || _src == null || ReferenceEquals( _dst, _src ) )
				return;

			foreach ( DBFieldInfo field in _fields )
			{
				if ( field.Name == "__parent" )
					continue;

				if ( field.CanRead && field.CanWrite && _src.IsFieldDerivedFromParent( field.Name ) )
					_dst.ResetField( field.Name );
			}
		}

		private static DBID GetDBIDFromObject( object _obj )
		{
			if ( _obj is DBResource )
				return ( (DBResource)_obj ).DBId;

			if ( _obj is IOwnerable )
			{
				DBResource res = ( (IOwnerable)_obj ).GetOwner();

				if ( res != null )
					return res.DBId;
			}

			return DBID.Empty;
		}

		#region Simple Copy

		private static bool CopyObject( object _src, object _dst, CopyContext context, IEnumerable<Attribute> _attributes )
		{
			bool result;

			if ( _src is DBPtrBase )
			{
				result = CopyDBPtrSimple( (DBPtrBase)_dst, (DBPtrBase)_src, new CopyContext() );
			}
			else if ( _src is IList )
			{
				result = CopyList( (IList)_dst, (IList)_src, null, context );
			}
			else if ( _src is SrcFile )
			{
				SrcFile srcFile = (SrcFile)_src;
				SrcFile dstFile = (SrcFile)_dst;
				object owner = dstFile.GetOwner();

				SrcFileAttribute attr = CollectionUtils.Find( _attributes, a => a is SrcFileAttribute ) as SrcFileAttribute;
				CopySrcFileField( srcFile, dstFile, owner, attr );
				result = true;
			}
			else if ( _src is TextRef )
			{
				CopyTextRef( (TextRef)_src, (TextRef)_dst );
				result = true;
			}
			else if ( _src is IAnimated )
			{
				CopyAnimated( (IAnimated)_src, (IAnimated)_dst );
				result = true;
			}
			else
			{
				result = CopyFields( _dst, _src, context );

				if ( TypeUtils.GetAttribute<HasStatesAttribute>( _src.GetType(), true ) != null )
				{
					context.collecting = false;
					result &= CopyStates( _dst as DBResource, _src as DBResource, context );
				}
			}
			return result;
		}

		private static void CopySimpleType( DBFieldInfo _field, object _dest, object srcValue, object dstValue )
		{
			if ( _field.CanWrite )
			{
				_field.SetValue( _dest, srcValue );
			}

			if ( _field.FieldType == typeof( string ) && TypeUtils.GetAttribute<DstFileAttribute>( _field, true ) != null )
			{
				FileUtils.CopyFile( DataBase.FileSystem, (string)srcValue, (string)dstValue );
			}
		}

		private static void CopyTextRef( TextRef _src, TextRef _dst )
		{
			_dst.Assign( _src );
		}

		private static void CopyAnimated( IAnimated _src, IAnimated _dst )
		{
			MethodInfo assign = TypeUtils.GetMethod( _src.GetType(), "Assign", new[] { _src.GetType() } );

			if ( assign != null )
				assign.Invoke( _dst, new[] { _src } );
		}

		private static bool CopyList( IList dest, IList src, SrcFileAttribute scrFileAttribute, CopyContext context )
		{
			if ( dest == null || src == null )
				return false;

			Type srcItemType = TypeUtils.GetTypeFromList( src.GetType() );
			Type dstItemType = TypeUtils.GetTypeFromList( dest.GetType() );

			if ( srcItemType == null || dstItemType == null )
				return false;

			dest.Clear();

			bool useInheritance = ( src is IRichList && dest is IRichList );

            int index = 0;

			foreach ( object srcItem in src )
			{
				if ( TypeUtils.IsSimpleType( srcItemType ) && srcItemType == dstItemType )
				{
					dest.Add( srcItem );
				}
				else if ( TypeUtils.IsSubclassOf( srcItemType, typeof( SrcFile ) ) && TypeUtils.IsSubclassOf( dstItemType, typeof( SrcFile ) ) )
				{
					SrcFile destItem = new SrcFile();
					CopySrcFileField( srcItem as SrcFile, destItem, dest, scrFileAttribute );
					dest.Add( destItem );
				}
				else if ( TypeUtils.IsStruct( srcItemType ) )
				{
					dest.Add( TypeUtils.CreateInstance( dstItemType ) );
                    object destItem = dest[index];
					CopyFields( destItem, srcItem, context );
				}
				else if ( TypeUtils.IsList( srcItemType ) )
				{
					dest.Add( TypeUtils.CreateInstance( dstItemType ) );
                    IList destItem = dest[index] as IList;
					CopyList( destItem, srcItem as IList, scrFileAttribute, context );
				}
				else if ( TypeUtils.GetTypeFromPtr( srcItemType ) != null && TypeUtils.GetTypeFromPtr( dstItemType ) != null )
				{
					dest.Add( TypeUtils.CreateInstance( dstItemType ) );
                    DBPtrBase destItem = dest[index] as DBPtrBase;
					CopyDBPtrSimple( destItem, srcItem as DBPtrBase, context );
				}

                if (useInheritance && index >= 0 && ((IRichList)src).IsElementDerivedFromParent(index))
                    ((IRichList)dest).ResetElement(index);

                index++;
			}

			return true;
		}

		private static bool CopyDBPtrSimple( DBPtrBase dst, DBPtrBase src, CopyContext context )
		{
			if ( src == null || dst == null )
				return false;

			DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, DBID.Empty ) );

			if ( src.DBId.IsEmpty )
				return true;

			Type srcType = TypeUtils.GetTypeFromPtr( src.GetType() );
			Type dstType = TypeUtils.GetTypeFromPtr( dst.GetType() );

			if ( TypeUtils.IsSubclassOf( srcType, dstType ) )
			{
				if ( src.DBId.IsInlined )
					CopyDBPtrProcessInline( dst, src, src.Get<DBResource>().GetType(), context );
				else
					DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, src.DBId ) );
			}
			else
			{
				if ( src.DBId.IsInlined && !TypeUtils.HasAttribute<NonTerminalAttribute>( dstType, false ) )
					CopyDBPtrProcessInline( dst, src, dstType, context );
			}

			return true;
		}

		private static void CopyDBPtrProcessInline( DBPtrBase dst, DBPtrBase src, Type objType, CopyContext context )
		{
			if ( !context.collecting && context.inlineMap.ContainsKey( src.DBId ) )
			{
				DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, context.inlineMap[src.DBId] ) );
				return;
			}

			DBID destDbid = DBID.FromDBID( dst.GetOwner().DBId, true );
			DBResource resource = TypeUtils.CreateInstance( objType ) as DBResource;
			DataBase.Create<DBResource>( destDbid, resource );
			DataBase.AddOperation( new DBPtrBaseChangeOperation( dst, destDbid ) );

			if ( context.collecting )
				context.inlineMap[src.DBId] = destDbid;

			CopyFields( resource, src.Get<DBResource>(), context );
		}

		private static void CopySrcFileField( SrcFile _srcSrcFile, SrcFile _destSrcFile, object _owner, SrcFileAttribute _srcFileAttr )
		{
			string destFolder;

			if ( _srcFileAttr == null || string.IsNullOrEmpty( _srcFileAttr.SourceFolder ) )
				destFolder = FileUtils.GetParentFolderPath( GetDBIDFromObject( _owner ).FileName );
			else
				destFolder = _srcFileAttr.SourceFolder;

			destFolder = FileUtils.PathSeparatorString + destFolder;

			_destSrcFile.SetFileName( FileUtils.Combine( FileUtils.FixFolderName( destFolder ), FileUtils.GetFileName( _srcSrcFile.FileName ) ) );
			_destSrcFile.SetChecksum( 0 );
		}

		#endregion
	}
}
