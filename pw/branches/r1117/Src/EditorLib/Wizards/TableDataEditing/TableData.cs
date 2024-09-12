using System;
using System.Collections;
using System.Collections.Generic;
using EditorLib.IO;
using EditorLib.Utils;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorLib.Wizards.TableDataEditing
{
	public class TableData
	{
		#region Nested Classes

		public class Cell
		{
			public readonly object parent;
			public readonly DBFieldInfo field;
			public readonly bool isReadonly = false;
			public string defaultValue = null;

			public Cell( object _parent, DBFieldInfo _field, bool _isReadonly )
			{
				field = _field;
				parent = _parent;
				isReadonly = _isReadonly;
			}		

			public object GetValue()
			{
				return field.GetValue( parent );
			}

			public void SetValue( object _value )
			{
				Log.Assert(!isReadonly, "You can't set readonly Cell");
				
				if(!isReadonly)
					field.SetValue( parent, _value );
			}
		}

		public class Row : IEquatable<Row>
		{
			public readonly List<Cell> Cells = new List<Cell>();

			public Row( IEnumerable<Cell> _cells )
			{
				foreach ( Cell cell in _cells )
				{
					Cells.Add( cell );
				}
			}

			public bool IsEmpty()
			{
				foreach ( var cell in Cells )
				{
					if ( cell != null )
						return false;
				}

				return true;
			}

			public override bool Equals( object _obj )
			{
				return Equals( _obj as Row );
			}

			public bool Equals( Row _other )
			{
				if ( _other == null )
					return false;

				if ( Cells.Count != _other.Cells.Count )
					return false;

				for ( int i = 0; i < Cells.Count; ++i )
				{
					if ( Cells[i] == null )
					{
						if ( _other.Cells[i] != null )
						{
							return false;
						}

						continue;
					}
					else if ( _other.Cells[i] == null )
					{
						return false;
					}

					if ( !Equals( Cells[i].parent, _other.Cells[i].parent ) || Cells[i].field.Name != _other.Cells[i].field.Name )
						return false;
				}

				return true;
			}

			public override int GetHashCode()
			{
				int result = 0;

				foreach ( var cell in Cells )
				{
					result ^= cell.GetHashCode();
				}

				return result;
			}
		}

		#endregion

		private readonly IEditorWinApplication application = null;
		private readonly List<Row> rows = new List<Row>();

		public TableData( IEditorWinApplication _application, TableDataPreset _preset )
		{
			application = _application;

			List<TableDataProperty> properties = _preset.GetAllProperies();

			if(properties.Count == 0)
			{
				Log.TraceWarning( "No properties in preset \"{0}\". Please edit preset and check properties.", _preset.Name );
				return;
			}
				

			ICollection objects;

			if (_preset.BaseType.IsSubclassOf(typeof (DBResource)))
				objects = GetResources(_preset.RootFolder, _preset.BaseType);
			else
				objects = GetStructures(_preset.RootFolder, _preset.BaseType);

			foreach (object obj in objects)
			{
				List<Row> objectTable = new List<Row>();
				objectTable.Add(new Row(new Cell[properties.Count]));

				foreach (TableDataProperty property in _preset.Properties)
				{
					GetRows(obj, property, objectTable);
				}

				foreach (Row row in objectTable)
				{
					if ( FilterRow( row, properties ) )
						continue;

					if(!row.IsEmpty() && !rows.Contains(row))
						rows.Add(row);
				}
			}
		}

		public List<Row> Rows
		{
			get { return rows; }
		}

		public Cell this[int _rowIndex, int _colIndex]
		{
			get { return rows[_rowIndex].Cells[_colIndex]; }
		}

		#region Data Mapping

		private void GetRows( object parent, TableDataProperty property, List<Row> rows )
		{
			if ( parent == null )
				return;

			if ( TypeUtils.IsSubclassOf( parent.GetType(), typeof( DBPtrBase ) ) )
			{
				DBPtrBase ptr = (DBPtrBase)parent;

				if ( !ptr.IsValid )
					return;

				parent = ptr.Get<DBResource>();
			}

			Cell cell = GetCell( parent, property.Name );

			if ( cell == null )
				return;

			if ( property.Properties.Count > 0 )//есть вложенные свойства
			{
				object cellValue = cell.GetValue();

				if ( cellValue != null && TypeUtils.IsList( cellValue.GetType() ) )//что делать если List.Count == 0?
				{
					bool isFirstRow = true;
					List<Row> rowsPattern = CopyRows( rows );

					foreach ( var item in (IEnumerable)cellValue )
					{
						List<Row> tmp = isFirstRow ? rows : CopyRows( rowsPattern );

						foreach ( TableDataProperty p in property.Properties )
						{
							GetRows( item, p, tmp );
						}

						if ( rows != tmp )
						{
							rows.AddRange( tmp );
						}

						isFirstRow = false;
					}
				}
				else
				{
					foreach ( TableDataProperty p in property.Properties )
					{
						GetRows( cellValue, p, rows );
					}
				}
			}

			if ( property.Index >= 0 )//нету вложенных свойств, заполняем строку значениями
			{
				foreach ( Row row in rows )
				{
					row.Cells[property.Index] = cell;
				}
			}
		}

		private static List<Row> CopyRows( List<Row> rows )
		{
			List<Row> result = new List<Row>( rows.Count );

			foreach ( var row in rows )
			{
				result.Add( new Row( row.Cells ) );
			}

			return result;
		}

		private Cell GetCell( object parent, string propertyName )
		{
			if ( parent == null || string.IsNullOrEmpty( propertyName ) )
				return null;

			bool processParent = propertyName != "__parent";

			DBFieldInfo field = TypeUtils.GetField( parent.GetType(), propertyName, processParent );

			if ( field == null )
				return null;

			return new Cell( parent, field, IsReadOnly( field ) );
		}

		private bool IsReadOnly( DBFieldInfo _field )
		{
			if ( !_field.CanWrite )
				return true;

			if ( TypeUtils.IsSubclassOf( _field.FieldType, typeof( DBPtrBase ) ) )
				return true;

			if ( !TextHelpers.CanConvertFromString( _field.FieldType, application ) )
				return true;

			return false;
		}

		#endregion

		private ICollection GetResources(string _rootFolder, Type _baseType)
		{
			List<DBID> objects;
			ObjectsSelector.CollectObjects(application.Application, _rootFolder, _baseType, true, false, out objects);

			List<DBResource> result = new List<DBResource>();

			foreach (DBID dbid in objects)
			{
				DBResource obj = DataBase.Get<DBResource>(dbid).Get();
				
				if(obj != null)
					result.Add(obj);
			}

			return result;
		}

		private ICollection GetStructures(string _rootFolder, Type _baseType)
		{
			List<object> result = new List<object>();

			ObjectsSelector.ProcessStructs(application.Application, _rootFolder, true,
			                               (res, structObj) => 
																		 {
																			if(structObj.GetType() != _baseType)
																				return true;

																			if(!result.Contains(structObj))
																		 		result.Add(structObj);

																			return true;
																		 });

			return result;
		}

		/// <summary>
		/// Фильтрует строку, возвращает true если строку надо скрыть
		/// </summary>
		/// <param name="_row">строка которую надо проверить</param>
		/// <param name="_properties">свойства объекта, отображаемые в данной строке</param>
		/// <returns>true если строку надо отфильтровать (скрыть), false в противном случае</returns>
		private bool FilterRow( Row _row, IEnumerable<TableDataProperty> _properties )
		{
			foreach ( TableDataProperty property in _properties )
			{
				if(string.IsNullOrEmpty(property.Filter))
					continue;

				Cell cell = _row.Cells[property.Index];

				if(cell == null)
					return true;
				
				string cellText = TextHelpers.ConvertValueToString(cell.GetValue(), application).ToLower();
				if(!cellText.Contains(property.Filter.ToLower()))
					return true;
			}

			return false;
		}
	}
}
