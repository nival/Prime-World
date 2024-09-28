using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace libdb.DB
{
	public sealed class FieldPath : IEnumerable<FieldPath.FieldPathItem>
	{
		public sealed class FieldPathItem
		{
			private readonly object owner = null;
			private readonly DBFieldInfo field = null;
			private readonly int index = 0;
			private readonly System.Reflection.PropertyInfo item = null;

			internal FieldPathItem( object owner, DBFieldInfo field, int index )
			{
				this.owner = owner;
				this.field = field;
				this.index = index;
				if ( Index > 0 )
				{
					item = TypeUtils.GetProperty( field.FieldType, "Item" );
					if ( item == null )
						this.index = -1;
				}
			}

			public object Owner { get { return owner; } }
			public DBFieldInfo Field { get { return field; } }
			public int Index { get { return index; } }
			public object Value
			{
				get
				{
					return ( Index < 0 ) ? Field.GetValue( Owner ) : item.GetValue( Field.GetValue( Owner ), new object[] { index } );
				}
			}
		}

		private readonly List<FieldPathItem> path = new List<FieldPathItem>();

		public FieldPath() { }
		private FieldPath( FieldPath path, FieldPathItem item ) { this.path.Add( item ); this.path.AddRange( path.path ); }

		public FieldPath Push( object owner, DBFieldInfo field )
		{
			return new FieldPath( this, new FieldPathItem( owner, field, -1 ) );
		}

		public FieldPath Push( int index )
		{
			FieldPathItem item = path[0];
			return new FieldPath( this, new FieldPathItem( item.Owner, item.Field, index ) );
		}

		public IEnumerator<FieldPath.FieldPathItem> GetEnumerator() { return path.GetEnumerator(); }
		System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() { return path.GetEnumerator(); }
	}
}
