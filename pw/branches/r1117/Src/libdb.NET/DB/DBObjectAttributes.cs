using System;
using System.Collections.Generic;
using System.Text;

namespace libdb.DB
{
	public sealed class DBObjectAttributes
	{
		private string value = string.Empty;
		private Dictionary<string, string> attributes = new Dictionary<string, string>();

		private string GetAttribute( string name )
		{
			string result = string.Empty;
			if ( !attributes.TryGetValue( name.ToLower(), out result ) )
				return string.Empty;
			
			return result;
		}

		private void SetAttribute( string name, string value )
		{
			attributes[name.ToLower()] = value;
		}

		public string Value
		{
			get { return value; }
			set { this.value = value; }
		}

		public string this[string name]
		{
			get { return GetAttribute( name ); }
			set { SetAttribute( name, value ); }
		}

		public IEnumerable<string> Attributes { get { return attributes.Keys; } }
	}
}
