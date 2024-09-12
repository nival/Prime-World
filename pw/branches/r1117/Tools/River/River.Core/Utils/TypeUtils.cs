using System;
using System.Collections.Generic;
using System.Text;
using System.Globalization;
using System.Reflection;

namespace River.Core.Utils
{
	public static class TypeUtils
	{
		public static bool IsSubclassOf( Type type, Type pattern )
		{
			if ( type == null || pattern == null )
				return false;

			if ( type == pattern )
				return true;

			if ( pattern.IsInterface )
			{
				Type[] interfaces = type.GetInterfaces();
				foreach ( Type interfaceType in interfaces )
				{
					if ( interfaceType == pattern || ( interfaceType.IsGenericType && interfaceType.GetGenericTypeDefinition() == pattern ) )
						return true;
				}
			}
			else
			{
				for ( Type baseType = type; baseType != null; baseType = baseType.BaseType )
				{
					if ( pattern == baseType )
						return true;
					if ( baseType.IsGenericType && pattern == baseType.GetGenericTypeDefinition() )
						return true;
				}
			}

			return false;
		}

		#region Attrbutes helpers

		public static bool HasAttribute<T>( ICustomAttributeProvider provider, bool inherit ) where T : Attribute
		{
			return provider.IsDefined( typeof( T ), inherit );
		}

		public static T GetAttribute<T>( ICustomAttributeProvider provider, bool inherit ) where T : Attribute
		{
			T[] attributes = GetAttributes<T>( provider, inherit );
			if ( attributes.Length == 0 )
				return null;
			return attributes[0];
		}

		public static T[] GetAttributes<T>( ICustomAttributeProvider provider, bool inherit ) where T : Attribute
		{
			List<T> result = new List<T>();
			object[] attributes = provider.GetCustomAttributes( typeof( T ), inherit );
			if ( attributes != null )
			{
				foreach ( object attr in attributes )
				{
					if ( attr is T )
						result.Add( attr as T );
				}
			}
			return result.ToArray();
		}

		#endregion

		#region Property and Method retrivers from type

		/// <summary>
		/// Search for property in specified type its base types and its interfaces
		/// </summary>
		/// <param name="type">Type where search for property</param>
		/// <param name="name">Name of property to search</param>
		/// <returns>A PropertyInfo object representing the public property with the specified name, if found; otherwise, null</returns>
		public static System.Reflection.PropertyInfo GetProperty( Type type, string name )
		{
			System.Reflection.BindingFlags flags = System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.FlattenHierarchy;

			//try get property from classes hierarcy
			System.Reflection.PropertyInfo property = type.GetProperty( name, flags );
			if ( property != null )
				return property;

			//search property in implemented interfaces
			Type[] interfaces = type.GetInterfaces();
			foreach ( Type interfaceType in interfaces )
			{
				property = interfaceType.GetProperty( name, flags );
				if ( property != null )
					return property;
			}

			return null;
		}

		/// <summary>
		/// Search for method in specified type its base types and its interfaces
		/// </summary>
		/// <param name="type">Type where search for method</param>
		/// <param name="name">Name of method to search</param>
		/// <param name="types">An array of Type objects representing the number, order, and type of the parameters for the method to get</param>
		/// <returns>A MethodInfo object representing the public property with the specified name, if found; otherwise, null</returns>
		public static System.Reflection.MethodInfo GetMethod( Type type, string name, Type[] types )
		{
			System.Reflection.BindingFlags flags = System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.FlattenHierarchy;

			//try get method from classes hierarcy
			System.Reflection.MethodInfo method = type.GetMethod( name, flags, null, types, null );
			if ( method != null )
				return method;

			//search method in implemented interfaces
			Type[] interfaces = type.GetInterfaces();
			foreach ( Type interfaceType in interfaces )
			{
				method = interfaceType.GetMethod( name, flags, null, types, null );
				if ( method != null )
					return method;
			}

			return null;
		}

		#endregion

		#region Generic helpers

		public static Type GetTypeFromGeneric( Type type )
		{
			return GetTypeFromGeneric( type, 0 );
		}

		public static Type GetTypeFromGeneric( Type type, int index )
		{
			if ( type == null )
				return null;
			else if ( type.IsGenericType )
			{
				if ( type.GetGenericArguments().Length > index )
					return type.GetGenericArguments()[index];
				else
					return null;
			}
			else
				return GetTypeFromGeneric( type.BaseType, index );
		}

		#endregion

		#region string to object converters

		private static bool TryParseBoolean( string value, out object obj )
		{
			obj = false;
			if ( string.Compare( value, "1" ) == 0 || string.Compare( value, Boolean.TrueString, StringComparison.InvariantCultureIgnoreCase ) == 0 )
				obj = true;
			else if ( string.Compare( value, "0" ) != 0 && string.Compare( value, Boolean.FalseString, StringComparison.InvariantCultureIgnoreCase ) != 0 )
				obj = false;

			return obj != null;
		}

		private static bool TryParseInt32( string value, out object obj )
		{
			Int32 outObj = 0;
			if ( Int32.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private static bool TryParseUInt32( string value, out object obj )
		{
			UInt32 outObj = 0;
			if ( UInt32.TryParse( value, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private static bool TryParseSingle( string value, out object obj )
		{
			Single outObj = 0.0f;
			if ( Single.TryParse( value, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private static bool TryParseDouble( string value, out object obj )
		{
			Double outObj = 0.0;
			if ( Double.TryParse( value, NumberStyles.Any, NumberFormatInfo.InvariantInfo, out outObj ) )
				obj = outObj;
			else
				obj = null;

			return obj != null;
		}

		private static bool TryParseEnum( string value, Type type, out object obj )
		{
			Dictionary<string, int> enumValues = new Dictionary<string, int>();
			foreach ( string name in Enum.GetNames( type ) )
				enumValues.Add( name, (int)Enum.Parse( type, name ) );

			Object[] flagsAttributes = type.GetCustomAttributes( typeof( FlagsAttribute ), true );
			bool isFlag = TypeUtils.HasAttribute<FlagsAttribute>( type, true );
			string[] values = isFlag ? value.Split( ',' ) : new string[1] { value };
			int result = 0;
			foreach ( string strValue in values )
			{
				int intValue = 0;
				if ( !enumValues.TryGetValue( strValue.Trim(), out intValue ) )
				{
					obj = null;
					return false;
				}

				result |= intValue;
			}

			obj = Enum.ToObject( type, result );
			return true;
		}

		private static bool TryParseGuid( string value, out object obj )
		{
			if ( string.IsNullOrEmpty( value ) )
			{
				obj = Guid.Empty;
				return true;
			}

			obj = null;
			char[] guidValue = new char[32];
			int guidIndex = 0;
			foreach ( char c in value )
			{
				if ( c >= '0' && c <= '9' || c >= 'A' && c <= 'F' || c >= 'a' && c <= 'f' )
				{
					if ( guidIndex >= guidValue.Length )
						return false;
					guidValue[guidIndex++] = c;
				}
				else if ( c == '-' || c == '{' || c == '}' || c == '(' || c == ')' )
					continue;
				else
					return false;
			}

			if ( guidIndex < 32 )
				return false;

			obj = new Guid( new string( guidValue ) );
			return true;
		}

		public static bool TryParsePrimitive( string value, Type type, out object obj )
		{
			if ( type == typeof( Boolean ) )
				return TryParseBoolean( value, out obj );
			else if ( type == typeof( int ) )
				return TryParseInt32( value, out obj );
			else if ( type == typeof( uint ) )
				return TryParseUInt32( value, out obj );
			else if ( type == typeof( Single ) )
				return TryParseSingle( value, out obj );
			else if ( type == typeof( Double ) )
				return TryParseDouble( value, out obj );
			else if ( type == typeof( Guid ) )
				return TryParseGuid( value, out obj );
			else if ( type.IsEnum )
				return TryParseEnum( value, type, out obj );
			else if ( type == typeof( string ) )
			{
				obj = value;
				return true;
			}

			obj = null;
			return false;
		}

		public static int TryParse( string s, int defaultValue )
		{
			int result = defaultValue;
			if ( !int.TryParse( s, out result ) )
				return defaultValue;

			return result;
		}

		#endregion
	}
}
