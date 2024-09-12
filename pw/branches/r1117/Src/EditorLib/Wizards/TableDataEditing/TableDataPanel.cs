using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib.Panels;
using EditorLib.PropertiesEditor;
using EditorLib.Utils;
using libdb.DB;
using libdb.Diagnostics;							 
using libdb.UndoRedo;

namespace EditorLib.Wizards.TableDataEditing
{
	public partial class TableDataPanel : EditorPanel
	{
		#region Nested Types

		private class PastedCell
		{
			public string Value { get; set; }
			public int RowIndex { get; set; }
			public int ColIndex { get; set; }

			public PastedCell(){}

			public PastedCell(string _value, int _rowIndex, int _colIndex)
			{
				Value = _value;
				RowIndex = _rowIndex;
				ColIndex = _colIndex;
			}
		}

		#endregion

		private const string NONE_VALUE = "###None###";
	  private string filterText = string.Empty;
	  private string filterColumn = string.Empty;
		private bool suspendRefresh = false;
		private TableData data = null;
		private TableDataPreset lastPresset;

    public TableDataPanel( )
    {
      InitializeComponent();
			TabText = "Table Data Editor";
      DataBase.ChangeDBResourceEvent += OnChangeDBResource;

			( (ISupportInitialize)grdData ).BeginInit();
			grdData.ClipboardCopyMode = DataGridViewClipboardCopyMode.Disable;
			grdData.VirtualMode = true;
			grdData.CellValueNeeded += OnCellValueNeeded;
			grdData.CellValuePushed += OnCellValuePushed;
			( (ISupportInitialize)grdData ).EndInit();
    }

    private void OnChangeDBResource( DBID dbid )
    {
    	RefreshGrid();
    }

		protected override bool Initialize(IEditorWinApplication application)
		{
			InitPresets();
			return true;
		}

    public override void Terminate( IEditorWinApplication application )
    {
      base.Terminate( application );
      DataBase.ChangeDBResourceEvent -= OnChangeDBResource;

    }

		#region Grid

		private void InitDataGrid(List<TableDataProperty> headers, int rowsCount)
		{
			if(headers.Count == 0)
			{
				lblNoData.Visible = true;
				grdData.Visible = false;
			}
			else
			{
				lblNoData.Visible = false;
				grdData.Visible = true;

				foreach ( TableDataProperty column in headers )
				{
					grdData.Columns.Add( column.Path, column.Path );
				}

				grdData.RowCount = rowsCount;
			}
		}

		private void OnCellValueNeeded(object sender, DataGridViewCellValueEventArgs e)
		{
      TableData.Cell cell = data[e.RowIndex, e.ColumnIndex];
      DataGridViewCell gridCell = grdData[e.ColumnIndex, e.RowIndex];

      e.Value = ( cell != null ) ? cell.GetValue() : NONE_VALUE;

			gridCell.ReadOnly = (cell == null || cell.isReadonly);
		}

    private void OnCellFormatting( object sender, DataGridViewCellFormattingEventArgs e )
    {
      // The method converts only to string type. Test this using the DesiredType.
      if( e.DesiredType != typeof( string ) )
        return;

      TableData.Cell cell = data[e.RowIndex, e.ColumnIndex];

      DataGridViewCell gridCell = grdData[e.ColumnIndex, e.RowIndex];
      e.Value = TextHelpers.ConvertValueToString( gridCell.Value, application );  
      
      if(cell != null)
      {
        if( cell.defaultValue == null )
					cell.defaultValue = TextHelpers.ConvertValueToString( gridCell.Value, application );

        e.CellStyle.BackColor = !Equals( cell.defaultValue, e.Value ) ? Color.LightGreen : Color.White;
      }

      e.CellStyle.ForeColor = gridCell.ReadOnly ? Color.Gray : Color.Black;
      e.FormattingApplied = true;
    }

	  private void OnCellValuePushed(object sender, DataGridViewCellValueEventArgs e)
		{
      TableData.Cell cell = data[e.RowIndex, e.ColumnIndex];

      if( cell != null && !Equals( e.Value, cell.GetValue() ) )
      {
        cell.SetValue( e.Value );
      }
		}

    private void OnCellParsing( object sender, DataGridViewCellParsingEventArgs e )
    {
      TableData.Cell cell = data[e.RowIndex, e.ColumnIndex];

      if( cell != null )
      {
        object value;
				if ( TextHelpers.TryGetValueFromString( e.Value as string, cell.field.FieldType, cell.GetValue(), application, out value ) )
        {
          e.Value = value;
        }
        else
        {
          e.Value = cell.GetValue();
          MessageBox.Show( "You must set correct value", "Cell Format Error", MessageBoxButtons.OK, MessageBoxIcon.Error );
        }
        
        e.ParsingApplied = true;
      }
    }

	  private void mnuCopy_Click(object sender, EventArgs e)
		{
			Copy();
		}

		private void mnuPaste_Click(object sender, EventArgs e)
		{
			Paste();
		}

		private void mnuPasteForSelection_Click( object sender, EventArgs e )
		{
			PasteForSelected();
		}

		private void grdData_KeyUp(object sender, KeyEventArgs e)
		{
		  if ((e.Control && e.KeyCode == Keys.C) || (e.Control && e.KeyCode == Keys.Delete) || (e.Shift && e.KeyCode == Keys.Delete))
			{
				Copy();
			}

			if ((e.Control && e.KeyCode == Keys.V) || (e.Control && e.KeyCode == Keys.Insert) || (e.Shift && e.KeyCode == Keys.Insert))
			{
				Paste();
			}

      if(e.Control && e.KeyCode == Keys.E)
      {
        GoToPropertiesEditor();
      }
		}

		private void mnuReset_Click(object sender, EventArgs e)
		{
      Reset();
		}

	  private void OnFilterTextChanged( object sender, EventArgs e )
	  {
	    filterColumn = Convert.ToString( cboColumns.SelectedValue );
	    filterText = txtFilter.Text;

      Filter( filterColumn, filterText );
	  }

    private void Filter( string _columnName, string _filterText )
	  {
      if( !grdData.Columns.Contains( _columnName ) )
        return;

      if( string.IsNullOrEmpty( _filterText ) )
	    {
	      foreach( DataGridViewRow row in grdData.Rows )
	      {
	        row.Visible = true;
	      }
	    }
	    else
	    {
        _filterText = _filterText.ToLower();

	      foreach( DataGridViewRow row in grdData.Rows )
	      {
	        string cellText = Convert.ToString(row.Cells[_columnName].FormattedValue).ToLower();
          row.Visible = cellText.Contains( _filterText );	        
	      }
	    }
	  }

	  private void OnLoadClick( object sender, EventArgs e )
    {
      TableDataPreset preset = cboPreset.SelectedItem as TableDataPreset;

      if( preset != null )
        LoadData( preset );
    }

    private void OnColumnHeaderClick( object sender, DataGridViewCellMouseEventArgs e )
    {
      foreach( DataGridViewColumn column in grdData.Columns )
      {
        if( column.Index != e.ColumnIndex )
          column.HeaderCell.SortGlyphDirection = SortOrder.None;
      }

      if( grdData.Columns[e.ColumnIndex].HeaderCell.SortGlyphDirection != SortOrder.Ascending )
      {
        grdData.Columns[e.ColumnIndex].HeaderCell.SortGlyphDirection = SortOrder.Ascending;
        SortRows( e.ColumnIndex, SortOrder.Ascending );
      }
      else
      {
        grdData.Columns[e.ColumnIndex].HeaderCell.SortGlyphDirection = SortOrder.Descending;
        SortRows( e.ColumnIndex, SortOrder.Descending );
      }

			RefreshGrid();
    }

		private void RefreshGrid()
		{
			if ( !suspendRefresh )
				grdData.Refresh();
		}

		#endregion

    #region Helper Methods

		private void Copy()
		{
			List<List<string>> table = GetStringsTable();
			var dataObject = new DataObject();
			
			//Text
			string textTable = TextHelpers.CreateTextTable( table );
			dataObject.SetData( DataFormats.Text, textTable );

			//Html
			string html = TextHelpers.CreatHtmlTable( table );
			string htmlText = Encoding.Default.GetString( Encoding.UTF8.GetBytes( html ) );
			string htmlTable = HtmlFragment.GetFragment( htmlText );
			dataObject.SetData( DataFormats.Html, htmlTable );

			Clipboard.Clear();
			Clipboard.SetDataObject( dataObject );			
		}

		private void Paste()
		{
			//в таблицу еще не загружены данные
			if ( grdData.Columns.Count == 0 )
				return;

			try
			{
				suspendRefresh = true;

				//List<List<string>> pastedRows = GetPastedRows();

				//if ( pastedRows.Count == 0 )
				//  return;

				////данные должны вставляться именно в dataGrid, т.к. порядок столбцов и вообще их наличие в dataGrid и rows может отличаться
				//PasteRows(pastedRows, GetPastePosition());

				List<PastedCell> pastedCells = GetPastedCells();

				if(pastedCells.Count == 0)
					return;

				PasteCells( pastedCells, GetPastePosition() );

			}
			finally
			{
				suspendRefresh = false;
				RefreshGrid();	
			}		
		}

		private void PasteForSelected()
		{
			//в таблицу еще не загружены данные
			if ( grdData.SelectedCells.Count == 0 )
				return;

			//вставка данных возможно только если все поселекченные ячейки находятся в одном столбце
			int columnIndex = grdData.SelectedCells[0].ColumnIndex;

			for(int index = 1; index < grdData.SelectedCells.Count; ++index)
			{
				DataGridViewCell cell = grdData.SelectedCells[index];
				
				//все поселекченные ячейки должны находиться в одном столбце
				if(columnIndex != cell.ColumnIndex)
				{
					MessageBox.Show( "Incorrect selection", "Paste Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
					return;
				}
			}

			try
			{
				suspendRefresh = true;

				List<PastedCell> pastedRows = GetPastedCells();

				//должна быть скопирована только одна ячейка
				if ( pastedRows.Count != 1 )
				{
					MessageBox.Show( "You can't paste many cells for selection", "Paste Error",
													 MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
					return;
				}


				List<PastedCell> forPaste = new List<PastedCell>();

				//добавляем в pastedRows нужное количество ячеек, чтобы воспользоваться обычной процедурой вставки
				//нам известо что у нас скопирована только одна ячейка, все ячейки находятся в одном столбце
				for ( int i = 0; i < grdData.SelectedCells.Count; ++i )
				{
					forPaste.Add( new PastedCell( pastedRows[0].Value, grdData.SelectedCells[i].RowIndex, grdData.SelectedCells[i].ColumnIndex ) );
				}

				//данные должны вставляться именно в dataGrid, т.к. порядок столбцов и вообще их наличие в dataGrid и rows может отличаться
				PasteCells( forPaste );
			}
			finally
			{
				suspendRefresh = false;
				RefreshGrid();
			}
		}

		private void PasteCells( IEnumerable<PastedCell> _cells )
		{
			PasteCells(_cells, Point.Empty);
		}

		private void PasteCells( IEnumerable<PastedCell> _cells, Point _offset )
		{
			try
			{
				bool isDataTruncated = false;

				using ( var trans = new UndoRedoTransaction( "Paste Cells" ) )
				{
					foreach ( PastedCell pastedCell in _cells )
					{
						int rowIndex = pastedCell.RowIndex + _offset.X;
						int colIndex = pastedCell.ColIndex + _offset.Y;

						//если вставляются данные с заголовками столбцов, игнорируем заголовки
						if ( pastedCell.Value == grdData.Columns[colIndex].HeaderText )
						{
							continue;
						}

						//игнорируем ячейки не влезающие в таблицу
						if ( rowIndex >= grdData.RowCount || colIndex >= grdData.ColumnCount)
						{
							isDataTruncated = true;
							continue;
						}
							

						DataGridViewCell gridCell = grdData[colIndex, rowIndex];					
						TableData.Cell dataCell = data[gridCell.RowIndex, gridCell.ColumnIndex];

						if ( dataCell != null && !dataCell.isReadonly )
						{
							if ( Convert.ToString( gridCell.FormattedValue ) != pastedCell.Value )
							{
								object value;
								if ( TextHelpers.TryGetValueFromString( pastedCell.Value, dataCell.field.FieldType, 
																												dataCell.GetValue(), application, out value ) )
								{
									gridCell.Value = value;
								}
							}
						}
					}

					trans.Commit();
				}

				if(isDataTruncated)
					Log.TraceWarning( "Part of the data is not got in the table and was truncated" );
			}
			catch ( FormatException err )
			{
				string message = string.Format( "The data you pasted is in the wrong format for the cell.{0}{1}",
																			 Environment.NewLine, err.Message );

				MessageBox.Show( message, "Paste Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				Log.TraceWarning( message );
				return;
			}
		}

		private List<PastedCell> GetPastedCells()
		{
			List<PastedCell> result = new List<PastedCell>();

			IDataObject dataObject = Clipboard.GetDataObject();

			if ( dataObject != null && dataObject.GetDataPresent( DataFormats.Html, false ) )
			{
				HtmlFragment html = HtmlFragment.FromClipboard();
				
				string htmlTable = Encoding.UTF8.GetString( Encoding.Default.GetBytes( html.Context ) );
				
				List<List<string>> table = TextHelpers.ParseHtmlTable( htmlTable );

				if ( table.Count == 0 )
					return result;

				bool ignoreFirstRow = true; //игнорируем первую строку, если она содержит заголовки столбцов

				//если вставляются данные с заголовками столбцов, игнорируем заголовки
				for(int i = 0; i < table[0].Count; i++)
				{
					if(table[0][i] != grdData.Columns[i].HeaderText)
					{
						ignoreFirstRow = false;
						break;
					}
				}

				for(int rowIndex = 0; rowIndex < table.Count; ++rowIndex)
				{
					if(ignoreFirstRow && rowIndex == 0)
						continue;

					for ( int colIndex = 0; colIndex < table[rowIndex].Count; ++colIndex )
					{
						result.Add( new PastedCell( table[rowIndex][colIndex], ignoreFirstRow ? rowIndex - 1 : rowIndex, colIndex ) );	
					}
				}
			}
			else
			{
				Log.TraceWarning( "Can't paste data. Incorrect data format in clipboard." );
			}

			return result;
		}

		private List<List<string>> GetStringsTable()
		{
			var table = new List<List<string>>();
			var lastRow = new List<string>();

			//если выделены все строки, то копируем названия столбцов
			if(grdData.SelectedRows.Count == grdData.Rows.Count)
			{
				foreach (DataGridViewColumn column in grdData.Columns)
				{
					lastRow.Add(column.HeaderText);
				}

				table.Add( lastRow );
				lastRow = new List<string>();
			}

			for ( int rowIndex = 0; rowIndex < grdData.Rows.Count; ++rowIndex )
			{
				//не копируем скрытые строки
				if ( !grdData.Rows[rowIndex].Visible )
					continue;

				bool appendRow = false;

				for ( int colIndex = 0; colIndex < grdData.Columns.Count; ++colIndex )
				{
					DataGridViewCell cell = grdData[colIndex, rowIndex];

					if ( cell.Selected )
					{
						string text = cell.FormattedValue as string;

						lastRow.Add( text ?? string.Empty );
						appendRow = true;
					}
				}

				if ( appendRow )
				{
					table.Add( lastRow );
					lastRow = new List<string>();
				}
			}
			return table;
		}

		private Point GetPastePosition()
		{
			for ( int rowIndex = 0; rowIndex < grdData.Rows.Count; ++rowIndex )
			{
				for ( int colIndex = 0; colIndex < grdData.Columns.Count; ++colIndex )
				{
					if ( grdData[colIndex, rowIndex].Selected )
						return new Point( rowIndex, colIndex );
				}
			}

			return new Point( 0, 0 );
		}

    private void Reset()
    {
    	try
    	{
				suspendRefresh = true;

				using ( var trans = new UndoRedoTransaction( "Reset Table Data" ) )
				{
					foreach ( DataGridViewCell gridCell in grdData.SelectedCells )
					{
						TableData.Cell cell = data[gridCell.RowIndex, gridCell.ColumnIndex];

						if ( cell != null && !cell.isReadonly )
						{
							object value;
							if ( TextHelpers.TryGetValueFromString( cell.defaultValue, cell.field.FieldType, cell.GetValue(), 
								application, out value ) )
							{
								if ( !Equals( value, cell.GetValue() ) )
									cell.SetValue( value );
							}
						}
					}

					trans.Commit();
				}
    	}
			finally
    	{
				suspendRefresh = false;
				RefreshGrid();
    	}
    }

		private void InitPresets()
		{
			TableDataPresetConfig config = application.Application.Settings.Get<TableDataPresetConfig>();
			
			cboPreset.Items.Clear();
			cboPreset.DisplayMember = "Name";
			cboPreset.Items.AddRange(config.Presets.ToArray());
		}

		private void LoadData(TableDataPreset _preset)
		{
			SaveSettingsToConfig(lastPresset);

			grdData.Rows.Clear();
			grdData.Columns.Clear();

			List<TableDataProperty> properties = _preset.GetAllProperies();
			cboColumns.DataSource = properties;
			cboColumns.DisplayMember = "Path";
			cboColumns.ValueMember = "Path";

			data = new TableData(application, _preset);

			InitDataGrid( properties, data.Rows.Count );

			GetSettingsFromConfig( _preset );

			lastPresset = _preset;
		}

		protected override void OnClosing( CancelEventArgs e )
		{
			SaveSettingsToConfig(lastPresset);
			CleanupSettingsConfig();
		}
		
		private void GetSettingsFromConfig( TableDataPreset _preset )
		{
			if ( _preset == null )
				return;

			TableDataConfig config = application.Application.Settings.Get<TableDataConfig>();

			foreach ( ConfigEntry entry in config.entries )
			{
				if ( _preset.Name == entry.presetName && entry.columns.Count == grdData.ColumnCount )
				{			
					foreach(ColumnConfig conf in entry.columns)
					{
						foreach(DataGridViewColumn column in grdData.Columns)
						{
							if(conf.name == column.Name)
							{
								if(conf.index >= 0 && conf.index < grdData.ColumnCount)
									column.DisplayIndex = conf.index;
							}
						}
					}

					break;
				}
			}
		}
		
		private void SaveSettingsToConfig( TableDataPreset _preset )
		{
			if ( _preset == null )
				return;

			TableDataConfig config = application.Application.Settings.Get<TableDataConfig>();

			//Remove presset
			ConfigEntry currentEntry = null;
			foreach(ConfigEntry entry in config.entries)
			{
				if ( entry.presetName == _preset.Name )
				{
					config.entries.Remove(entry);
					break;
				}
			}

			// Create presset
			currentEntry = new ConfigEntry();
			currentEntry.presetName = _preset.Name;

			//Add columns
			foreach ( DataGridViewColumn column in grdData.Columns )
			{
				ColumnConfig confEntry = new ColumnConfig();
				confEntry.index = column.DisplayIndex;
				confEntry.name = column.Name;
				currentEntry.columns.Add( confEntry );
			}

			config.entries.Add(currentEntry);
		}
		
		private void CleanupSettingsConfig()
		{
			TableDataConfig config = application.Application.Settings.Get<TableDataConfig>();
			TableDataPresetConfig configOfPressets = application.Application.Settings.Get<TableDataPresetConfig>();

			for ( int i = config.entries.Count-1; i > -1; --i)
			{
				bool exist = false;
				foreach ( TableDataPreset preset in configOfPressets.Presets )
				{
					if ( config.entries[i].presetName == preset.Name )
					{
						exist = true;
						break;
					}
				}

				if ( !exist )
					config.entries.RemoveAt(i);
			}
		}

    private void SortRows( int _columnIndex, SortOrder _direction )
    {
      data.Rows.Sort(( x, y ) =>
        {
          TableData.Cell cell1 = x.Cells[_columnIndex];
          TableData.Cell cell2 = y.Cells[_columnIndex];

					string str1 = ( cell1 == null ) ? NONE_VALUE : TextHelpers.ConvertValueToString( cell1.GetValue(), application );
					string str2 = ( cell2 == null ) ? NONE_VALUE : TextHelpers.ConvertValueToString( cell2.GetValue(), application );
          
          if( _direction == SortOrder.Ascending )
            return str1.CompareTo( str2 );
          else
            return str2.CompareTo( str1 );
        } );

      Filter( filterColumn, filterText );
    }

    private void GoToPropertiesEditor()
    {
      PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();

      if( grdData.SelectedCells.Count > 0 )
      {
        DataGridViewCell gridCell = grdData.SelectedCells[0];
        TableData.Cell cell = data[gridCell.RowIndex, gridCell.ColumnIndex];

        if( cell != null )
        {
          propertiesEditor.SelectedObject = cell.parent;
          propertiesEditor.SelectProperty( cell.field.Name );
          propertiesEditor.Focus();
        }
      }
    }

		#endregion

    private void mnuShowPE_Click( object sender, EventArgs e )
    {
      GoToPropertiesEditor();
    }

	  private void mnuSelectAll_Click( object sender, EventArgs e )
    {
      grdData.SelectAll();
    }

    private void OnPresetSelected( object sender, EventArgs e )
    {
      btnLoad.Enabled = cboPreset.SelectedIndex >= 0 && cboPreset.SelectedIndex < cboPreset.Items.Count;
    }

		private void btnManagePreset_Click( object sender, EventArgs e )
		{
			TableDataPreset selectedPreset = cboPreset.SelectedItem as TableDataPreset;
			TableDataPresetsForm presetsManager = new TableDataPresetsForm( application, selectedPreset );

			if(presetsManager.ShowDialog() == DialogResult.OK)
			{
				InitPresets();
				cboPreset.SelectedItem = presetsManager.SelectedPreset;
			}		
			
		}
	}
}

