using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using libdb;
using System.IO;
using libdb.Diagnostics;
namespace libdb.DB
{
	public static class TypeHelper
	{
		private static System.Globalization.NumberFormatInfo numberFormat = new System.Globalization.NumberFormatInfo();
		private static Dictionary<string, Type> typeCache = new Dictionary<string, Type>();

		static TypeHelper()
		{
			numberFormat.NumberDecimalSeparator = ".";
			numberFormat.NumberGroupSeparator = "";
		}

		public static int Compare( Type type1, Type type2 )
		{
			return string.Compare( type1.Name, type2.Name );
		}

		public static MemberInfo[] GetFields( Type type )
		{
			List<MemberInfo> fields = new List<MemberInfo>();
				foreach ( FieldInfo field in type.GetFields( BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly ) )
					fields.Add( field );

				foreach ( PropertyInfo property in type.GetProperties( BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly ) )
					fields.Add( property );
			return fields.ToArray();
		}
		public static Type GetTypeFromPtr( Type type )
		{
			if ( !type.IsGenericType || type.GetGenericTypeDefinition() != typeof( DBPtr<DBResource> ).GetGenericTypeDefinition() || type.GetGenericArguments().Length != 1 )
				return null;

			return type.GetGenericArguments()[0];
		}
		public static object GetFieldValue( MemberInfo field, object instance )
		{
			DBPtrBase dbPtr = instance as DBPtrBase;
			if ( dbPtr == null )
			{
				FieldInfo fieldInfo = field as FieldInfo;
				if ( fieldInfo != null )
				{
					object obj = fieldInfo.GetValue( instance );
					if ( obj is DBPtrBase )
					{
						//DBID DBid = ( obj as DBPtrBase ).GetDBResource().DBId;
						if ( ( obj as DBPtrBase ).GetDBResource() == null || ( obj as DBPtrBase ).GetDBResource().DBId == null || ( obj as DBPtrBase ).GetDBResource().DBId.FileName == string.Empty )
						return null;
					}
					return obj;
				}

				PropertyInfo propertyInfo = field as PropertyInfo;
				if ( propertyInfo != null )
				{
					return propertyInfo.GetValue( instance, null );
				}
				//ListInfo 
			}
			else
			{
				DBResource resource = dbPtr.GetDBResource();
				if ( resource != null )
				{
					PropertyInfo propertyInfo = field as PropertyInfo;
					if ( propertyInfo != null )
						return propertyInfo.GetValue( resource, null );
					FieldInfo fieldInfo = field as FieldInfo;
					if ( fieldInfo != null )
						return fieldInfo.GetValue( resource );
				}
			}
			return null;
		}

		public static void SetFieldValue( MemberInfo field, object instance, object value )
		{
			DBPtrBase dbPtr = instance as DBPtrBase;
			if ( dbPtr == null )
			{
				FieldInfo fieldInfo = field as FieldInfo;
				if ( fieldInfo != null )
				{
					fieldInfo.SetValue( instance, value );
					return;
				}

				PropertyInfo propertyInfo = field as PropertyInfo;
				if ( propertyInfo != null )
					propertyInfo.SetValue( instance, value, null );
			}
			else
			{
				DBResource resource = dbPtr.GetDBResource();
				if ( resource != null )
				{
					PropertyInfo propertyInfo = field as PropertyInfo;
					if ( propertyInfo != null )
					{
						propertyInfo.SetValue( resource, value, null );
						return;
					}
					FieldInfo fieldInfo = field as FieldInfo;
					if ( fieldInfo != null )
					{
						object ttt = fieldInfo.GetValue( resource );
						fieldInfo.SetValue( resource, value );
						ttt = fieldInfo.GetValue( resource );
				
					}
					
				}
			}
		}

		public static Type GetFieldType( MemberInfo field )
		{
			FieldInfo fieldInfo = field as FieldInfo;
			if ( fieldInfo != null )
				return fieldInfo.FieldType;

			PropertyInfo propertyInfo = field as PropertyInfo;
			if ( propertyInfo != null )
				return propertyInfo.PropertyType;

			return null;
		}

		public static bool CanCreate( Type type )
		{
			if (!type.IsSubclassOf(typeof(DBResource)))
				return false;

			object[] attributes = type.GetCustomAttributes( typeof( NonTerminalAttribute ), false );
			return (attributes == null) || (attributes.Length == 0);
		}

		public static Object CreateInstance( Type type )
		{
			if ( type == typeof( string ) )
				return string.Empty;
			else
				return type.GetConstructor( new Type[0] ).Invoke( new Object[0] );
		}

		public static bool IsPrimitive( Type type )
		{
			return GetFields( type ).Length == 0 || type.IsPrimitive || type == typeof( string );
		}

		public static System.Globalization.NumberFormatInfo NumberFormat { get { return numberFormat; } }
	}
}
