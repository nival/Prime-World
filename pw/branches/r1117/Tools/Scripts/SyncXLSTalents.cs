
/*
#about Talents synchronization between xls file and editor data
#ref {.net}System.Data.dll
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;
using System.Globalization;
using System.IO;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;
using PF_EditorC.Extensions;

public class SyncXLSTalents
{
    private const bool ABORT_ON_ERRORS = 
#if DEBUG
    false;
#else
    true;
#endif

    #region Help Classes / Methods
    #region Classes
    private class Config
    {
      public string ConstColumnPattern = @"const([A-Za-z0-9\-]+)_([A-Za-z0-9\-]+)";
      public int IdSubstringLength = 4;
      public char EditorDecimalSeparator = '.';
      public char EnumValuseSeparator = ',';
      public string DefaultTalentsFolder = "/Items/Talents/Level1";
      public string DefaultRefineScaleFormula = "refineScale( $value, $refinevalue )";

      public Dictionary<Type, PropertyInfo> SimpleTypesNavigation = new Dictionary<Type, PropertyInfo>()
                                                                    {
                                                                      {
                                                                        typeof( BaseExecutableString ),
                                                                        typeof( BaseExecutableString ).GetProperty(
                                                                          "sString" )
                                                                        }
                                                                    };
      public class ExcelType
      {
        public string path = string.Empty;
        public string sheet = string.Empty;
      }

      public class Folder
      {
        public string path = string.Empty;
        public string minLevel = string.Empty;
      }

      public class Column
      {
        public string column = string.Empty;
        public string field = string.Empty;
      }

      public class Value
      {
        public string value = string.Empty;
        public string replace = string.Empty;
      }

      public class StatModConstant
      {
        public string value = string.Empty;
        public EStat stat = 0;
        public string tooltip = string.Empty;
        public List<string> tooltipAnchors = new List<string>();
      }

      public class CopyField
      {
        public Column columnFieldPair = new Column();
        public List<Value> values = new List<Value>();
      }

      public ExcelType Excel = new ExcelType();
      public Column Id = new Column();
      public Column Status = new Column();
      public Column Filename = new Column();
      public Column Minlevel = new Column();
      public string ReportFilename = String.Empty;

      public List<Folder> TalentsFolders = new List<Folder>();
      public List<Value> ValidStatuses = new List<Value>();
      public List<Value> InProgressStatuses = new List<Value>();
      public List<CopyField> CopyFileds = new List<CopyField>();
      public List<Value> ConstantsEnableValues = new List<Value>();
      public List<Value> ConstantsEnableValuesWithoutTooltip = new List<Value>();
      public List<StatModConstant> StatModConstants = new List<StatModConstant>();
      public List<Value> ConstantsRenames = new List<Value>();
      public List<Value> TechConstantPrefixes = new List<Value>();
      public List<Value> RefineFormulas = new List<Value>();
      public Dictionary<int,string> MinLevelFolders = new Dictionary<int, string>();
    }

    public enum ChangeType
    {
      Modified = 0,
      Created,
      Deleted
    }

    private class ModifierChangeEntry
    {
      public ChangeType ChangeType = ChangeType.Modified;
      public EStat Stat;
      public Config.StatModConstant NewValue;
      public string ConstantName = string.Empty;
      public string NewAddValue = string.Empty;
      public PermanentStatModApplicator Psma;
      public string DescriptionFragment;
      public List<string> DescriptionInsertAnchors = new List<string>();
    }

    private class ConstantChangeEntry
    {
      public ChangeType ChangeType = ChangeType.Modified;
      public string Name;
      public UnitConstant Constant;
      public string NewValue;
      public string OldValue;
    }

    private class SyncingTalent
    {
      public List<string> TechicalConstants = new List<string>();
      public SyncingTalent( string id )
      {
        this.ID = id;
      }
      public ChangeType ChangeType = ChangeType.Created;
      public string ID;
      public Talent EditorTalent;
      public string UpdatedPath = string.Empty;
      public int DescriptionChanges = 0;
      public Dictionary<string,UnitConstant> EditorConstants 
        = new Dictionary<string, UnitConstant>();
      public Dictionary<string,TableConstant> TableConstants = 
        new Dictionary<string, TableConstant>();
      //Column Name - Row Value pairs
      public Dictionary<string,string> TableRowValues =
        new Dictionary<string, string>();

      public Dictionary<string,FieldChangeEntry> FieldsChanges =
        new Dictionary<string, FieldChangeEntry>();
      public Dictionary<string, ConstantChangeEntry> ConstantsChanges = 
        new Dictionary<string, ConstantChangeEntry>();

      public Dictionary<EStat, ModifierChangeEntry> ModifiersChanges = 
        new Dictionary<EStat, ModifierChangeEntry>();

      public Dictionary<EStat, PermanentStatModApplicator> EditorModifiers = 
        new Dictionary<EStat, PermanentStatModApplicator>();

      public bool HasChanges()
      {
        return FieldsChanges.Count > 0 ||
          ConstantsChanges.Count > 0 ||
          ModifiersChanges.Count > 0;
      }
    }

    private class TableConstantColumns
    {
      //Parameters names must be equal PARAM_NAME 
      //from 'const%CONST_NAME%_%PARAM_NAME%' (column name from table)
      public string Name;
      public string Enable;
      public string Value;
      public string RefineValue;
      //Values adding when table columns are reading
      private List<string> _requiredFields = new List<string>() { "name", "value", "enable" };
      public List<string> SettedFields = new List<string>();

      public bool IsAllRequireFieldsRead( out string error )
      {
        error = string.Empty;
        foreach ( var fieldName in _requiredFields )
          if ( !SettedFields.Contains( fieldName ) )
            error += string.Format( "'{0}' parameter not setted\n", fieldName );

        return string.IsNullOrEmpty( error );
      }
    }
    private class TableConstant
    {
      public string Name;
      public string Enable;
      public string Value;
      public string RefineValue;
      public bool IsTooltipDisabled;
      public bool IsEnabled( List<Config.Value> allowedEnableValues )
      {
        foreach ( var allowedEnableValue in allowedEnableValues )
          if ( this.Enable == allowedEnableValue.value )
            return true;

        return false;
      }
      /// <summary>
      /// Reads columns names from TableConstant and fills by values of this columns
      /// defined in columnValues. 
      /// <example>Value columnNames.someName will be read, trying to get value from columnValues and
      /// try to write it to this.someName field</example>
      /// Reflection implementation for exclude manually define fields in future.
      /// </summary>
      /// <param name="columnNames"></param>
      /// <param name="columnValues"></param>
      public TableConstant( TableConstantColumns columnNames, Dictionary<string, string> columnValues )
      {
        FieldInfo[] columnsKeeperFields = columnNames.GetType().GetFields();
        FieldInfo[] thisFields = this.GetType().GetFields();
        for ( int i = 0; i < columnsKeeperFields.Length; i++ )
        {
          var field = columnsKeeperFields[i];

          var columnName = field.GetValue( columnNames ) as string;
          if ( string.IsNullOrEmpty( columnName ) )
            continue;

          string value;
          if ( columnValues.TryGetValue( columnName, out value ) )
            for ( int j = 0; j < thisFields.Length; j++ )
              if ( thisFields[j].Name.ToLowerInvariant() == field.Name.ToLowerInvariant() )
              {
                thisFields[j].SetValue( this, value );
                break;
              }
        }
      }
    }

    private class FieldChangeEntry
    {
      public string OriginalFieldPath;
      public object BaseObject;
      public PropertyInfo PropertyInfo;
      public object NewValue;
      public object OldValue;
    }

    private class SyncingFieldInfo
    {
      public string ColumnName;
      //Using for navigating to value fields.
      //e.g. working with 'cooldown' in PvX editor we are working as with textfield
      //but working with 'cooldown' in c# code we are working with object, 
      //which inner field 'sString' contains text
      public string SimpleFieldPath;
      public string OriginalFieldPath;
      public PropertyInfo PropertyInfo;
      public Dictionary<string, string> ReplaceRules = new Dictionary<string, string>();
      /// <summary>
      /// Using for detect fields, that are not copied as is and have custom processing rules
      /// </summary>
      public bool IsPredefined = false;
    }
    #endregion
    #region Methods
    private bool DoesStringContainsCyrrilic( string str )
    {
      return Regex.IsMatch( str, @"\p{IsCyrillic}" );
    }

    private bool TryGetIntFromString( string stringValue, out object result )
    {
      result = null;
      if ( string.IsNullOrEmpty( stringValue ) )
        return false;
      int val;
      if ( int.TryParse( stringValue, out val ) )
      {
        result = val;
        return true;
      }

      return false;
    }

    private bool TryGetFloatFromString( string stringValue, out object result )
    {
      result = null;
      if ( string.IsNullOrEmpty( stringValue ) )
        return false;
      var str = stringValue
        .Replace( ".", CultureInfo.CurrentUICulture.NumberFormat.NumberDecimalSeparator )
        .Replace( ",", CultureInfo.CurrentUICulture.NumberFormat.NumberDecimalSeparator );
      float val;
      if ( float.TryParse( str, out val ) )
      {
        result = val;
        return true;
      }

      return false;
    }

    private bool TryGetEnumValueFromString( string stringValue, Type enumType,
      Dictionary<string, string> replaceRules, out object result, char separator )
    {
      result = null;
      if ( string.IsNullOrEmpty( stringValue ) )
        return false;

      string valuesString = Regex.Replace( stringValue, @"\s", "" );
      string[] values = valuesString.Split( separator );
      string tmp = string.Empty;
      string resultString = string.Empty;
      for ( int i = 0; i < values.Length; i++ )
      {
        if ( !string.IsNullOrEmpty( values[i] ) && replaceRules.TryGetValue( values[i], out tmp ) )
          values[i] = tmp;
        resultString += values[i];
        if ( i < values.Length - 1 )
          resultString += ",";
      }

      try
      {
        result = Enum.Parse( enumType, resultString, true );
      }
      catch ( Exception e )
      {
        Log.TraceWarning( "Skipping enum value, because can't parse to '{0}' string value '{1}'. Error: '{2}'.",
          enumType.Name, resultString, e.Message );
        return false;
      }

      return true;
    }

    private string AdaptNumericValueForEditor( string value, char decimalSeparator )
    {
      return
        value.Replace( ',', decimalSeparator ).Replace( '.', decimalSeparator );
    }

    private bool TryToAdd<T1, T2>( IDictionary<T1, T2> dict, T1 key, T2 value )
    {
      if ( !dict.ContainsKey( key ) )
      {
        dict.Add( key, value );
        return true;
      }
      return false;
    }

    public FieldInfo GetField( Type type, string fieldName )
    {
      var fieldNameL = fieldName.ToLowerInvariant();
      FieldInfo[] fields =  type.GetFields();
      for ( int j = 0; j < fields.Length; j++ )
        if ( fields[j].Name.ToLowerInvariant() == fieldNameL )
          return fields[j];
      return null;
    }

    /// <summary>
    /// Using editor's minLevel values. For using in config directly they must be decreased by 1.
    /// I.e. minLevel in Editor 0 equals minLevel 1 in table
    /// </summary>
    private string GetLocationByMinLevel( int minLevel, Config config )
    {
      string folder = config.DefaultTalentsFolder;
      //In table min levels stored with +1 offset, from 1.
      if ( !config.MinLevelFolders.TryGetValue( minLevel - 1, out folder ) )
      {
        Log.TraceMessage( "Can't get folder for storing by minlevel '{0}'. Using default location '{1}'.",
              minLevel, config.DefaultTalentsFolder );
      }
      return folder;
    }

    private List<UnitConstant> GetInlinedEditorConstants( Talent talent )
    {
      var result = new List<UnitConstant>();
      var con = talent.constants.Get();
      foreach ( var v in con.vars )
        if ( v.DBId.IsInlined )
          result.Add( v.Get() );
      return result;
    }

    private bool IsFragmentExist( string description, string fragment )
    {
      return description.Contains( fragment );
    }

    private string InsertDescriptionFragment( string description, string fragment,
                                            List<string> anchors, string afterFragment, out string usedAnchor )
    {
      usedAnchor = string.Empty;
      string result = description;
      foreach ( var tmp in anchors )
        if ( description.Contains( tmp ) )
          usedAnchor = tmp;

      if ( string.IsNullOrEmpty( usedAnchor ) )
        result = string.Format( "{0}{1}{2}", fragment, afterFragment, description );
      else
      {
        int index = description.LastIndexOf( usedAnchor );
        result = string.Format( "{0}{1}{2}{3}", description.Substring( 0, index + usedAnchor.Length ),
          fragment, afterFragment, description.Substring( index + usedAnchor.Length,
          description.Length - ( index + usedAnchor.Length ) ) );
      }
      return result;
    }
    #endregion
    #endregion

    #region Load Config

    private static T ReadClass<T>( XmlNode node, T result )
    {
      if ( node != null )
      {
        foreach ( XmlAttribute attr in node.Attributes )
        {
          FieldInfo field = typeof( T ).GetField( attr.Name );
          if ( field != null )
          {
            if ( typeof( Enum ).IsAssignableFrom( field.FieldType ) )
              field.SetValue( result, Enum.Parse( field.FieldType, attr.Value ) );
            else
              field.SetValue( result, attr.Value );
          }
        }
      }

      return result;
    }

    private static List<T> ReadList<T>( XmlNodeList nodes, List<T> result ) where T : new()
    {
      if ( nodes != null )
      {
        foreach ( XmlNode node in nodes )
          result.Add( ReadClass( node, new T() ) );
      }
      return result;
    }

    private static Config LoadConfig( string fileName )
    {
      XmlDocument xml = new XmlDocument();
      xml.Load( fileName );

      Config result = new Config();

      ReadClass( xml.SelectSingleNode( @"/Config/Excel" ), result.Excel );
      ReadClass( xml.SelectSingleNode( @"/Config/Id" ), result.Id );
      ReadClass( xml.SelectSingleNode( @"/Config/Filename" ), result.Filename );
      ReadClass( xml.SelectSingleNode( @"/Config/Minlevel" ), result.Minlevel );
      ReadClass( xml.SelectSingleNode( @"/Config/Status" ), result.Status );
      ReadList( xml.SelectNodes( @"/Config/Status/Valid" ), result.ValidStatuses );
      ReadList( xml.SelectNodes( @"/Config/Status/InProgress" ), result.InProgressStatuses );
      ReadList( xml.SelectNodes( @"/Config/TalentsFolders/Folder" ), result.TalentsFolders );
      ReadList( xml.SelectNodes( @"/Config/ConstEnableMark" ), result.ConstantsEnableValues );
      ReadList( xml.SelectNodes( @"/Config/ConstEnableMarkWithoutTooltip" ), result.ConstantsEnableValuesWithoutTooltip );
      ReadList( xml.SelectNodes( @"/Config/ConstRename" ), result.ConstantsRenames );
      ReadList( xml.SelectNodes( @"/Config/TechnicalConstantPrefix" ), result.TechConstantPrefixes );
      ReadList( xml.SelectNodes( @"/Config/RefineFormula" ), result.RefineFormulas );

      foreach ( XmlNode node in xml.SelectNodes( @"/Config/StatModConstants/Constant" ) )
      {
        var statModC = new Config.StatModConstant();
        ReadClass( node, statModC );
        statModC.tooltip = node.SelectSingleNode( "Tooltip" ).InnerText;
        foreach ( XmlNode ta in node.SelectNodes( "TooltipAnchor" ) )
          statModC.tooltipAnchors.Add( ta.InnerText );
        result.StatModConstants.Add( statModC );
      }

      foreach ( XmlNode node in xml.SelectNodes( @"/Config/CopyField" ) )
      {
        var copyField = new Config.CopyField();
        ReadClass( node, copyField.columnFieldPair );
        ReadList( node.SelectNodes( "Value" ), copyField.values );
        result.CopyFileds.Add( copyField );
      }
      var rn = xml.SelectSingleNode( @"/Config/Report" );
      if ( rn != null && rn.Attributes["path"] != null )
        result.ReportFilename = rn.Attributes["path"].Value;

      foreach ( var f in result.TalentsFolders )
      {
        int minLevel = -1;
        if ( !int.TryParse( f.minLevel, out minLevel ) )
        {
          Log.TraceWarning(
            "Can't read '{0}' minLevel attribute as integer. This minLevel folder('{1}') will be ignored.",
            f.minLevel, f.path );
          continue;
        }

        if ( result.MinLevelFolders.ContainsKey( minLevel ) )
          Log.TraceWarning( "Folder for minLevel '{0}' alredy readed as '{1}'. This '{2}' will be ignored.",
            minLevel, result.MinLevelFolders[minLevel], f.path );
        else
          result.MinLevelFolders.Add( minLevel, f.path );
      }

      return result;
    }

    private static bool ValidateConfig( Config config, string rootPath )
    {
      string err = "{0} parameter is required, but not setted.";
      if ( string.IsNullOrEmpty( config.Excel.path ) )
        throw new InvalidDataException( string.Format( err, "Config.Excel.path" ) );
      if ( string.IsNullOrEmpty( config.Excel.sheet ) )
        throw new InvalidDataException( string.Format( err, "Config.Excel.sheet" ) );
      if ( string.IsNullOrEmpty( config.Id.column ) )
        throw new InvalidDataException( string.Format( err, "Config.Id.column" ) );
      if ( string.IsNullOrEmpty( config.Filename.column ) )
        throw new InvalidDataException( string.Format( err, "Config.Filename.column" ) );
      if ( config.TalentsFolders.Count <= 0 )
        throw new InvalidDataException( string.Format( "Config.TalentsFolders contains 0 elements" ) );
      if ( config.ValidStatuses.Count <= 0 )
        throw new InvalidDataException( string.Format( "config.ValidStatuses contains 0 elements" ) );


      foreach ( var folder in config.TalentsFolders )
      {
        var path = rootPath + folder.path;
        if ( !Directory.Exists( path ) )
          throw new InvalidDataException( string.Format( "Directory '{0}' not found", path ) );
      }
      return true;
    }

    #endregion

    #region Load Excel File

    private static string[,] LoadXlslFile( string fileName, string sheetName )
    {
      string fullFileName = Path.GetFullPath( fileName );

      var connString = string.Format(
        "Provider=Microsoft.ACE.OLEDB.12.0;Data Source={0}; Extended Properties=Excel 12.0;",
        fileName );
      var adapter = new OleDbDataAdapter( string.Format( @"SELECT * FROM [{0}$]", sheetName ), connString );
      var dataSet = new DataSet();
      adapter.Fill( dataSet, "data" );
      DataTable dataTable = dataSet.Tables["data"];

      string[,] result = new string[dataTable.Rows.Count + 1, dataTable.Columns.Count];
      int c = 0;
      foreach ( DataColumn col in dataTable.Columns )
        result[0, c++] = col.Caption;

      int r = 1;
      foreach ( DataRow row in dataTable.Rows )
      {
        c = 0;
        foreach ( DataColumn column in dataTable.Columns )
          result[r, c++] = row[column].ToString();
        r++;
      }

      return result;
    }

    private int GetColumnIndexOrException( Dictionary<string, int> columns, string columnName )
    {
      if ( !columns.ContainsKey( columnName ) )
        throw new DataException( string.Format( "'{0}' column not found in table. Aborted.", columnName ) );
      return columns[columnName];
    }
    private bool TryDetectConstantColumn( string stringValue, string pattern,
  out string constName, out string paramName )
    {
      constName = string.Empty;
      paramName = string.Empty;
      var match = Regex.Match( stringValue, pattern );
      if ( match.Success )
      {
        constName = match.Groups[1].Value;
        paramName = match.Groups[2].Value;
        return true;
      }
      return false;
    }

    private void ExcludeInvalidTableConstantsColumns( ref Dictionary<string, TableConstantColumns> constants )
    {
      var invalidConstants = new List<string>();
      foreach ( var constant in constants )
      {
        string error;
        if ( !constant.Value.IsAllRequireFieldsRead( out error ) )
        {
          invalidConstants.Add( constant.Key );
          if ( ABORT_ON_ERRORS )
            throw new InvalidDataException(
              string.Format( "Constant '{0}' is invalid and will be ignored: '{1}'.", constant.Key, error ) );
        }
      }
      foreach ( var invalidConstant in invalidConstants )
        constants.Remove( invalidConstant );
    }

    private void ReadTableColumns(
      string[,] table, string pattern,
      out Dictionary<string, int> columns,
      out Dictionary<string, TableConstantColumns> constantsColumns )
    {
      columns = new Dictionary<string, int>();
      constantsColumns = new Dictionary<string, TableConstantColumns>();
      for ( int i =0; i < table.GetLength( 1 ); i++ )
      {
        var columnName = table[0, i].Trim();
        if ( !TryToAdd( columns, columnName, i ) )
          throw new DataException(
            string.Format( "Column '{0}' defined more than one time (columns: {1}, {2}).",
                         columnName, i, columns[columnName] ) );
        else
        {
          string name;
          string paramName;
          //Constants which filled with columns names, NOT constants values
          //Example: 
          //Columns:    constMyConst_value, constMyConst_name, constMyConst_enable 
          //will be read to
          //Dictionary: Key="MyConst" TableConstant.value ="constMyConst_value" 
          //                          TableConstant.name  ="constMyConst_name" 
          //                          TableConstant.enable="constMyConst_enable"
          if ( TryDetectConstantColumn( columnName, pattern, out name, out paramName ) )
          {
            TableConstantColumns constantColumn;
            if ( !constantsColumns.TryGetValue( name, out constantColumn ) )
            {
              constantColumn = new TableConstantColumns();
              constantsColumns.Add( name, constantColumn );
            }

            FieldInfo field = GetField( typeof( TableConstantColumns ), paramName.ToLowerInvariant() );
            if ( field != null )
            {
              field.SetValue( constantColumn, columnName );
              constantColumn.SettedFields.Add( field.Name.ToLowerInvariant() );
            }
            else
              Log.TraceWarning( "Column '{0}' found and recognized like constant, but param '{1}' not supported. Skipping.",
                columnName, paramName );
          }
        }
      }
    }
    #endregion

    #region Validators
    private bool IsIdValid( string id, int lengthFilter, out string error )
    {
      error = string.Empty;
      if ( string.IsNullOrEmpty( id ) )
      {
        error = "id is empty string.";
        return false;
      }

      if ( id.Length != lengthFilter )
      {
        error = string.Format( @"id '{0}' contains invalid number of characters. 
                                Must be {1}.", id, lengthFilter );
        return false;
      }
      return true;
    }

    private bool IsStatusMatch( string status, List<Config.Value> validStatuses )
    {
      foreach ( var validStatus in validStatuses )
        if ( status == validStatus.value )
          return true;

      return false;
    }
    #endregion

    #region Talents Collection
    private Dictionary<string, SyncingTalent> CollectTalentsFromTable(
      string[,] table, Config config, Dictionary<string, int> columns )
    {
      int ID_INDEX = GetColumnIndexOrException( columns, config.Id.column );
      int STATUS_INDEX = GetColumnIndexOrException( columns, config.Status.column );

      //var tableTalents = 
      //    new Dictionary<string, Dictionary<string, string>>( table.GetLength( 0 ) - 1 );
      var result = new Dictionary<string, SyncingTalent>();
      for ( int i = 1; i < table.GetLength( 0 ); i++ )
      {
        var talentId = table[i, ID_INDEX];
        string error;
        if ( !IsIdValid( talentId, config.IdSubstringLength, out error ) )
        {
          //Log.TraceWarning( @"Skipping talent (row {0}) with invalid id: {1}", i, error );
          continue;
        }

        var talentStatus = table[i, STATUS_INDEX];
        if ( IsStatusMatch( talentStatus, config.InProgressStatuses ) )
        {
          Log.TraceWarning( @"Talent '{0}' (row {1}) marked as 'in progress' by status: {2}",
            talentId, i, talentStatus );
        }
        else
          if ( !IsStatusMatch( talentStatus, config.ValidStatuses ) )
          {
            Log.TraceWarning( @"Skipping talent '{0}' (row {1}) with invalid status: {2}",
              talentId, i, talentStatus );
            continue;
          }

        SyncingTalent sTalent = new SyncingTalent( talentId );
        if ( !TryToAdd( result, talentId, sTalent ) )
        {
          Log.TraceWarning( @"Talent with id '{0}' defined more than one time (row: {1}). 
            First found will be used.", talentId, i );
          continue;
        }

        foreach ( var column in columns )
          sTalent.TableRowValues.Add( column.Key, table[i, column.Value] );
      }
      return result;
    }

    private int CollectTalentsFromEditor(
      Config config,
      IEditorCommonApplication app,
      ref Dictionary<string, SyncingTalent> talents,
      out List<DBID> editorOnlyTalents
      )
    {
      int foundTalents = 0;
      editorOnlyTalents = new List<DBID>();
      foreach ( var folder in config.TalentsFolders )
      {
        Log.TraceMessage( "Collecting talents from '{0}'...", folder.path );

        List<DBID> dbids;
        ObjectsSelector.CollectObjects( app, folder.path,
          typeof( Talent ), true, false, out dbids );
        foreach ( var dbid in dbids )
        {
          string fileName = Path.GetFileName( dbid.Name );
          string name = fileName.Substring( 0,
            fileName.Length > config.IdSubstringLength
            ? config.IdSubstringLength : fileName.Length );

          SyncingTalent st;
          if ( talents.TryGetValue( name, out st ) )
          {
            if ( st.EditorTalent != null )
            {
              Log.TraceWarning( string.Format( @"Editor talent with name '{0}' already found.
                May be this defined more than one time ('{1}', '{2}'). Using first found.",
                  name, dbid.ToString(), st.EditorTalent.DBId.ToString() ) );
              continue;
            }
            st.EditorTalent = DataBase.Get<DBTypes.Talent>( dbid ).Get();
            if ( string.IsNullOrEmpty( st.EditorTalent.persistentId ) )
              Log.TraceWarning( "Talent '{0}' contains empty persistentId", st.EditorTalent.DBId.ToString() );

            st.ChangeType = ChangeType.Modified;
            if ( st.EditorTalent != null )
              foundTalents++;
          }
          else
          {
            editorOnlyTalents.Add( dbid );
            //Log.TraceWarning( "Talent '{0}' defined only in editor.", dbid );
            continue;
          }
        }
      }
      return foundTalents;
    }

    #endregion

    #region Fields Changes
    #region Predefined Fields(custom processing rules)
    private Dictionary<string, Function<string, SyncingTalent, Config>> PredefinedFields = 
      new Dictionary<string, Function<string, SyncingTalent, Config>>() { { "caption", GetCaption } };
    private static string GetCaption( SyncingTalent talent, Config config )
    {
      var result = talent.TableRowValues[config.Id.column];
      string filename = string.Empty;
      if ( talent.TableRowValues.TryGetValue( config.Filename.column, out filename ) )
      {
        if ( !string.IsNullOrEmpty( filename ) )
          result += ": " + filename;
      }
      return result;
    }
    #endregion

    private Dictionary<string, FieldChangeEntry> GetTalentFieldsChangeList(
      SyncingTalent talent,
      List<SyncingFieldInfo> syncingFieldsInfos, Config config
      )
    {
      var tableValues = talent.TableRowValues;
      var editorTalent = talent.EditorTalent;
      var result = new Dictionary<string, FieldChangeEntry>();

      foreach ( var sfi in syncingFieldsInfos )
      {
        var property = sfi.PropertyInfo;
        var replaces = sfi.ReplaceRules;

        string stringValue = string.Empty;
        if ( sfi.IsPredefined )
        {
          Function<string, SyncingTalent, Config> getMethod;
          if ( PredefinedFields.TryGetValue( sfi.OriginalFieldPath, out getMethod ) )
            stringValue = getMethod( talent, config );
        }
        else
          stringValue = tableValues[sfi.ColumnName];

        string error = String.Empty;
        object newValue;
        if ( TryGetNewProperyValue( property, stringValue, replaces,
          config.EnumValuseSeparator, out newValue, ref error ) )
        {
          var keeper = GetPropertyKeeper( typeof( Talent ), sfi.SimpleFieldPath, editorTalent );
          var oldValue = property.GetValue( keeper, null );
          //FIXME: very thick place. 
          //If we are start using objects, then two different will be same as string "[Object]"
          //if ( newValue.ToString() == oldValue.ToString() )
          bool objectCondition = newValue.GetHashCode() != oldValue.GetHashCode();
          bool stringCondition = newValue.ToString() != oldValue.ToString();

          if ( oldValue == null || newValue == null || newValue is string ? stringCondition : objectCondition )
          {
            if ( result.ContainsKey( sfi.OriginalFieldPath ) )
            {
              string err = String.Format( "Trying to collect field '{0}' changes more than 1 time.",
                                          sfi.OriginalFieldPath );
              if ( ABORT_ON_ERRORS )
                throw new InvalidDataException( err );
              else
              {
                Log.TraceError( err );
                continue;
              }
            }
            result.Add( sfi.OriginalFieldPath, new FieldChangeEntry()
            {
              BaseObject = keeper,
              PropertyInfo = property,
              NewValue = newValue,
              OldValue = oldValue,
              OriginalFieldPath = sfi.OriginalFieldPath
            } );
          }
        }
        else
        {
          Log.TraceWarning( "Can't get new value for talent's ('{0}') property '{1}' from string value '{2}': \n'{3}'",
            editorTalent.DBId.ToString(), property.Name, stringValue, error );
          continue;
        }
      }
      return result;
    }


    private bool TryGetNewProperyValue(
      PropertyInfo property, string stringValue,
      Dictionary<string, string> replaceRules, char enumSeparator,
      out object newValue, ref string error )
    {
      newValue = null;
      string parsingStringValue = string.Empty;
      if ( replaceRules != null )
        if ( replaceRules.TryGetValue( stringValue, out parsingStringValue ) )
          error = String.Format( "Note that original string value '{0}' replaced by '{1}' before parsing process.",
            stringValue, parsingStringValue );
        else
          parsingStringValue = stringValue;
      //Empty value
      //if ( string.IsNullOrEmpty( parsingStringValue ) )
      //  return true;

      try
      {
        Type type = property.PropertyType;
        if ( type == typeof( float ) || type == typeof( double ) )
          return TryGetFloatFromString( parsingStringValue, out newValue );
        else if ( type == typeof( int ) || type == typeof( long ) )
          return TryGetIntFromString( parsingStringValue, out newValue );
        else if ( typeof( Enum ).IsAssignableFrom( type ) )
          return TryGetEnumValueFromString( parsingStringValue, type, replaceRules, out newValue, enumSeparator );
        else //if ( type == typeof( string ) )
        {
          newValue = parsingStringValue;
          return true;
        }
      }

      catch ( Exception e )
      {
        error = e.Message;
        return false;
      }
      error = string.Format( "Trying to convert value '{0}' to type '{1}', but string parser not defined.",
        parsingStringValue, property.PropertyType.Name );
      return false;
    }

    /// <summary>
    /// Same as Type.GetProperty excep dot notation support. 
    /// <example>For example you can pass argument "parend.child0.child1" and get 
    /// child2 ProperyInfo as result</example>
    /// </summary>
    private PropertyInfo GetPropertyInfo( Type type, string fieldPath )
    {
      if ( string.IsNullOrEmpty( fieldPath ) )
        return null;

      PropertyInfo result = null;
      TryGetPropertyAndKeeper( type, fieldPath, null, out result );
      return result;
    }

    /// <summary>
    /// Same as PropertyInfo.GetValue, but dot separated fields path using.
    /// </summary>
    private object GetPropertyKeeper( Type type, string fieldPath, object root )
    {
      if ( string.IsNullOrEmpty( fieldPath ) )
        return null;

      PropertyInfo result = null;
      return TryGetPropertyAndKeeper( type, fieldPath, root, out result );
    }

    /// <summary>
    /// Searching for PropertyInfo and its value by dot separated object's fields hierarchy
    /// </summary>    
    private object TryGetPropertyAndKeeper( Type type, string fieldPath, object root,
      out PropertyInfo propInfo )
    {
      propInfo = null;
      if ( string.IsNullOrEmpty( fieldPath ) )
        return false;

      string[] elems = fieldPath.Split( '.' );
      PropertyInfo cprop = null;
      object ckeeper = root;
      Type ctype = type;
      for ( int  i = 0; i < elems.Length; i++ )
      {
        var el = elems[i];
        if ( !string.IsNullOrEmpty( el ) )
        {
          if ( i > 0 && ckeeper != null )
            ckeeper = cprop.GetValue( ckeeper, null );

          cprop = ctype.GetProperty( el );
          if ( cprop == null )
            break;
          ctype = cprop.PropertyType;
        }
      }

      propInfo = cprop;
      return ckeeper;
    }

    private int CollectFieldsChanges(
      ref Dictionary<string, SyncingTalent> talents,
      List<SyncingFieldInfo> syncingFieldsInfos, Config config
      )
    {
      var result = 0;
      foreach ( var p in talents )
      {
        var id = p.Key;
        var talent = p.Value;
        Log.TraceMessage( "Collecting changes for talent's fields '{0}'...", p );
        talent.FieldsChanges = GetTalentFieldsChangeList( talent, syncingFieldsInfos, config );
        result += talent.FieldsChanges.Count;

        Log.TraceMessage( "Collecting changes for talent's fields '{0}'...Ok. {1} collected",
                          id, talent.FieldsChanges.Count );
      }
      return result;
    }
    /// <summary>
    /// Using for navigating to value fields.
    /// Property info will be rewrited to actual if required
    /// <example>e.g. working with 'cooldown' in PvX editor we are working as with textfield
    /// but working with 'cooldown' in c# code we are working with object(ExecutableString), 
    /// which inner field 'sString' contains text.
    /// So will be returned string '.sString', and properyInfo will be rewrited to sString
    /// </example>
    /// </summary>
    /// <param name="info">Current property info</param>
    /// <param name="config">Config, containing simple types navigation rules</param>
    /// <returns></returns>
    private string TryNavigateToSimpleProperty( ref PropertyInfo info, Config config )
    {
      string result = string.Empty;
      //if ( config.SimpleTypesNavigation.ContainsKey( info.PropertyType ) )
      //{
      //  info = config.SimpleTypesNavigation[info.PropertyType];
      //  result = info.Name;
      //}
      //else
      foreach ( var p in config.SimpleTypesNavigation )
        if ( p.Key.IsAssignableFrom( info.PropertyType ) )
        {
          info = p.Value;
          result = "." + info.Name;
        }
      return result;
    }

    private List<SyncingFieldInfo> GetSyncingFiledsInfo(
                                   Config config,
                                   Dictionary<string, int> columns )
    {
      var result = new List<SyncingFieldInfo>();
      //Predefined fields
      foreach ( var p in PredefinedFields )
      {
        var fn = p.Key;
        PropertyInfo cp = GetPropertyInfo( typeof( Talent ), fn );
        if ( cp != null )
        {
          string pathToSimple = fn + TryNavigateToSimpleProperty( ref cp, config );
          result.Add( new SyncingFieldInfo()
          {
            PropertyInfo = cp,
            IsPredefined = true,
            OriginalFieldPath = fn,
            SimpleFieldPath = pathToSimple
          } );
        }
        else
          Log.TraceWarning(
            "Predefined field '{0}' not defined in editor talents. Skipping.",
           fn );
      }
      foreach ( var field in config.CopyFileds )
      {
        //Getting field from editor talent
        PropertyInfo pi = GetPropertyInfo( typeof( Talent ), field.columnFieldPair.field );
        if ( pi != null )
        {
          //Getting column from table
          if ( columns.ContainsKey( field.columnFieldPair.column ) )
          {
            string pathToSimple = field.columnFieldPair.field + TryNavigateToSimpleProperty( ref pi, config );
            var sfi = new SyncingFieldInfo()
            {
              PropertyInfo = pi,
              ColumnName = field.columnFieldPair.column,
              OriginalFieldPath = field.columnFieldPair.field,
              SimpleFieldPath = pathToSimple
            };
            result.Add( sfi );
            //If syncing field found - collecting replace rules
            foreach ( var replaceRule in field.values )
              if ( !string.IsNullOrEmpty( replaceRule.replace )
                && !string.IsNullOrEmpty( replaceRule.value ) )
              {
                if ( sfi.ReplaceRules.ContainsKey( replaceRule.value ) )
                {
                  Log.TraceWarning(
                    @"Replace rule for value '{0}' in config's CopyField for column '{1}' defined more than one times. 
                      First found will be used.",
                    replaceRule.value,
                    field.columnFieldPair.column );
                  continue;
                }
                sfi.ReplaceRules.Add( replaceRule.value, replaceRule.replace );
              }
          }
          else
            Log.TraceWarning( "Table doesn't contains column with name '{0}' but it found in config. Skipping.",
              field.columnFieldPair.column );
        }
        else
        {
          Log.TraceWarning(
            "Field '{0}' not defined in editor talents, but CopyField with column '{1}' found in config. Skipping.",
            field.columnFieldPair.field, field.columnFieldPair.column );
          continue;
        }
      }
      return result;
    }
    #endregion

    #region Location Changes
    private int CollectLocationChanges( ref Dictionary<string, SyncingTalent> talents, Config config )
    {
      int count = 0;
      foreach ( var p in talents )
      {
        var talent = p.Value;
        //Checking move condition
        FieldChangeEntry fce;
        if ( talent.FieldsChanges.TryGetValue( config.Minlevel.field, out fce ) )
        {
          if ( fce.NewValue is int )
          {
            int nMinLevel = (int)fce.NewValue;
            var folder = GetLocationByMinLevel( nMinLevel, config );
            string newPath = folder + "/" + Path.GetFileName( talent.EditorTalent.DBId.Name );
            if ( !string.Equals( talent.EditorTalent.DBId.Name, newPath ) )
              talent.UpdatedPath = newPath;
            count++;
          }
        }
      }
      return count;
    }
    #endregion

    #region Creating New Talents
    private int TryCreateNewTalents( ref Dictionary<string, SyncingTalent> talents, Config config )
    {
      int createdCounter = 0;

      foreach ( var p in talents )
      {
        var talent = p.Value;
        if ( talent.ChangeType == ChangeType.Created )
        {
          int minLevel = -1;
          string tableMinLevel = talent.TableRowValues[config.Minlevel.column];
          if ( !int.TryParse( tableMinLevel, out minLevel ) )
            Log.TraceMessage( "Can't parse to integer min level value '{0}' for talent '{1}'.", tableMinLevel, talent.ID );

          string folder = GetLocationByMinLevel( minLevel, config );
          DBID dbid = new DBID( Path.Combine( folder, p.Key + ".TALENT" ), Guid.Empty );
          talent.EditorTalent = new DBTypes.Talent();
          DataBase.Create( dbid, talent.EditorTalent );
          DBID cdbid = DBID.FromDBID( talent.EditorTalent.DBId, true );
          talent.EditorTalent.constants = DataBase.Create( cdbid, new UnitConstantsContainer() );

          createdCounter++;
        }
      }
      return createdCounter;
    }
    #endregion

    #region Constants Changes
    private bool IsTechnicalConstantName( string name, List<Config.Value> techicalConstants )
    {
      foreach ( var tc in techicalConstants )
      {
        if ( string.IsNullOrEmpty( tc.value ) )
          continue;
        if ( name.ToLowerInvariant().StartsWith( tc.value.ToLowerInvariant() ) )
          return true;
      }
      return false;
    }

    private string GetConstantValueForEditor( TableConstant tableConstant,
      char decimalSeparator, Config config )
    {
      string result = null;
      if ( string.IsNullOrEmpty( tableConstant.Value ) )
        return string.Empty;
      var value = AdaptNumericValueForEditor( tableConstant.Value, decimalSeparator );
      //Refine formula insertion
      if ( !string.IsNullOrEmpty( tableConstant.RefineValue ) )
      {
        var formula = config.DefaultRefineScaleFormula;
        //Searching for refine formula from config
        foreach ( var p in config.RefineFormulas )
        {
          if ( string.Equals( p.value, tableConstant.Enable,
            StringComparison.InvariantCultureIgnoreCase ) )
            formula = p.replace;
        }
        try
        {
          formula = formula.Replace( "$value", tableConstant.Value );
          formula = formula.Replace( "$refinevalue",
                                     AdaptNumericValueForEditor( tableConstant.RefineValue, decimalSeparator ) );
        }
        catch ( Exception e )
        {
          Log.TraceWarning( "Incorrect formula '{0}' defined in config. Can't replace variables with values",
            formula );
        }
        result = formula;
      }
      else
        result = value;
      return result;
    }

    private bool ValidateEditorTalentConstants( Talent talent )
    {
      if ( talent.constants != null
        && talent.constants.Get() != null
        && !talent.constants.DBId.IsInlined )
      {
        string err = string.Format( "Editor talent '{0}' contains not null and not inlined constatns.",
                                    talent.DBId.ToString() );
        if ( ABORT_ON_ERRORS )
          throw new InvalidDataException( err );
        else
          Log.TraceError( err );
        return false;
      }
      return true;
    }

    private void CollectEditorConstants(
      ref Dictionary<string, SyncingTalent> talents, Config config )
    {
      foreach ( var p in talents )
      {
        var talent = p.Value;
        ValidateEditorTalentConstants( talent.EditorTalent );
        if ( talent.EditorTalent.constants != null && !talent.EditorTalent.constants.DBId.IsInlined )
          Log.TraceWarning( "Talent '{0}' contains not inlined and not empty constants block",
            talent.EditorTalent.DBId.ToString() );
        var constants = GetInlinedEditorConstants( talent.EditorTalent );
        if ( constants.Count > 0 )
        {
          var cd = talent.EditorConstants;

          foreach ( var constant in constants )
          {
            if ( cd.ContainsKey( constant.name ) )
            {
              Log.TraceWarning( @"Constant with name '{0}' found more than one times in editor talent '{1}'. 
                                  First found will be used.",
                constant.name, talent.EditorTalent.DBId );
              continue;
            }
            if ( IsTechnicalConstantName( constant.name, config.TechConstantPrefixes ) )
            {
              Log.TraceDebug( "Talent '{0}' contains techincal constant '{1}'", talent.ID, constant.name );
              talent.TechicalConstants.Add( constant.name );
            }
            cd.Add( constant.name, constant );
          }
        }
      }
    }

    private void CollectTableConstants(
      Config config,
      ref Dictionary<string, SyncingTalent> talents,
      Dictionary<string, TableConstantColumns> constantsColumns )
    {
      var result = new Dictionary<string, Dictionary<string, TableConstant>>();
      var constantReplaces = new Dictionary<string, string>();
      Log.TraceMessage( "Prepearing constants replace rules..." );
      foreach ( var cRename in config.ConstantsRenames )
      {
        if ( !constantReplaces.ContainsKey( cRename.value ) )
          constantReplaces.Add( cRename.value, cRename.replace );
        else
          Log.TraceWarning( "Constant replace '{0}'-'{1}' defined more than one time in config. First found will be used.",
            cRename.value, cRename.replace );
      }
      Log.TraceMessage( "Prepearing constants replace rules...Ok." );

      foreach ( var p in talents )
      {
        var id = p.Key;
        var talent = p.Value;
        var rows = p.Value.TableRowValues;
        foreach ( var cc in constantsColumns )
        {
          var constantColumns = cc.Value;
          //Creating talent constant from constantColumnsNames which keeps information about table columns names
          //And rows which keeps row values for all columns for specified talent
          var constant = new TableConstant( constantColumns, rows );
          if ( constant.IsEnabled( config.ConstantsEnableValues ) || constant.IsEnabled( config.ConstantsEnableValuesWithoutTooltip ) )
          {
            if ( string.IsNullOrEmpty( constant.Name ) )
            {
              Log.TraceWarning( "Constant '{0}' marked as enable for talent '{1}' but contains empty name. Skipping.",
                                cc.Key, id );
              continue;
            }
            if ( constantReplaces.ContainsKey( constant.Name ) )
              constant.Name = constantReplaces[constant.Name];

            if ( DoesStringContainsCyrrilic( constant.Name ) )
            {
              string err = string.Format( "Talent '{0}' contains constant with cyrillic symbols name '{1}'. Aborted.",
               id, constant.Name );
              if ( ABORT_ON_ERRORS )
                throw new InvalidDataException( err );
              else
                Log.TraceError( err );
            }

            if ( IsTechnicalConstantName( constant.Name, config.TechConstantPrefixes ) )
            {
              string err = string.Format( "Technical constant '{0}' found in excel data. Aborting.", constant.Name );
              if ( ABORT_ON_ERRORS )
                throw new DataException( err );
              else
                Log.TraceError( err );
            }
            //Disable tooltip substitutions for constants from <ConstEnableMarkWithoutTooltip> group
            constant.IsTooltipDisabled = constant.IsEnabled( config.ConstantsEnableValuesWithoutTooltip );

            if ( !talent.TableConstants.ContainsKey( constant.Name ) )
              talent.TableConstants.Add( constant.Name, constant );
            else
              Log.TraceWarning( @"Constant with name '{0}' defined more than one time in table talent '{1}'. 
            Note, that constant name can be setted by config defined replacement.", constant.Name, id );
          }
        }
      }
    }

    private int CollectConstantsChanges(
     ref Dictionary<string, SyncingTalent> talents, Config config
     )
    {
      var result = 0;

      foreach ( var p in talents )
      {
        var id = p.Key;
        var talent = p.Value;

        var tc = talent.TableConstants;
        var ec = talent.EditorConstants;

        //talent.ConstantsChanges.Add( new ConstantChangeEntry() );
        var editorOnlyConstants = new Dictionary<string, UnitConstant>();
        foreach ( var tmp in ec )
          editorOnlyConstants.Add( tmp.Key, tmp.Value );

        foreach ( var tmp in tc )
        {
          var cid = tmp.Key;
          var tableConstant = tmp.Value;
          editorOnlyConstants.Remove( cid );
          UnitConstant editorConstant;
          ec.TryGetValue( cid, out editorConstant );

          string newValue = GetConstantValueForEditor( tableConstant,
            config.EditorDecimalSeparator, config );
          string oldValue = string.Empty;
          if ( editorConstant != null )
          {
            oldValue = editorConstant.var.sString;
            if ( string.Equals( newValue, oldValue ) )
              continue;
          }

          var change = new ConstantChangeEntry()
          {
            Name = cid,
            NewValue = newValue,
            OldValue = oldValue,
            Constant = editorConstant
          };

          if ( editorConstant == null )
            change.ChangeType = ChangeType.Created;

          //Ignoring technical constants
          if ( editorConstant != null && IsTechnicalConstantName( editorConstant.name, config.TechConstantPrefixes ) )
          {
            Log.TraceDebug( "Constant '{0}' will be ignored, bacause it marked as technical", editorConstant.name );
            continue;
          }
          talent.ConstantsChanges.Add( cid, change );
        }


        foreach ( var tmp in editorOnlyConstants )
        {
          //Ignoring technical constants
          if ( IsTechnicalConstantName( tmp.Value.name, config.TechConstantPrefixes ) )
            continue;

          Log.TraceWarning( "Talent's ('{0}') constant '{1}' not defined in table but found in editor.",
            id, tmp.Key );

          //Removing only editor inlined constants disabled in new design iteration
          //talent.ConstantsChanges.Add( tmp.Key, new ConstantChangeEntry()
          //{
          //  changeType = ChangeType.Deleted,
          //  constant = tmp.Value,
          //  oldValue = tmp.Value.var.sString,
          //  name = tmp.Key
          //} );
        }
        foreach ( var statModConstants in config.StatModConstants )
        {
          UnitConstant c;
          if ( editorOnlyConstants.TryGetValue( statModConstants.value, out c ) )
          {
            //Removing editor only constant which are presented in config StatModConstants section
            talent.ConstantsChanges.Add( statModConstants.value, new ConstantChangeEntry()
            {
              ChangeType = ChangeType.Deleted,
              Constant = c,
              OldValue = c.var.sString,
              Name = c.name
            } );
            editorOnlyConstants.Remove( statModConstants.value );
          }
        }
        result += talent.ConstantsChanges.Count;
      }
      return result;
    }
    #endregion

    #region Modifiers Changes
    private int CollectEditorModifiers(
      ref Dictionary<string, SyncingTalent> talents )
    {
      int result = 0;
      foreach ( var p in talents )
      {
        var id = p.Key;
        var talent = p.Value;
        var mods = talent.EditorModifiers;
        foreach ( var ba in talent.EditorTalent.passiveApplicators )
        {
          if ( ba.DBId.IsInlined )
          {
            var editorMod = ( ba.Get() as PermanentStatModApplicator );
            if ( editorMod != null && editorMod.modifier != null )
            {
              if ( !mods.ContainsKey( editorMod.modifier.stat ) )
                mods.Add( editorMod.modifier.stat, editorMod );
              else
                Log.TraceWarning(
                  "Modifier for stat '{0}' defined in editor talent '{1}' more than one time. Using first found.",
                  editorMod.modifier.stat.ToString(), id );
            }
          }
        }
        result += mods.Count;
      }
      return result;
    }

    private Dictionary<string, Config.StatModConstant> GetConfigModifiers(
      List<Config.StatModConstant> configMods, out Dictionary<EStat, Config.StatModConstant> perStatConfigMods )
    {
      var configStats = new Dictionary<string, Config.StatModConstant>();
      perStatConfigMods = new Dictionary<EStat, Config.StatModConstant>();
      foreach ( var mod in configMods )
      {
        if ( !perStatConfigMods.ContainsKey( mod.stat ) )
          perStatConfigMods.Add( mod.stat, mod );
        else
          Log.TraceWarning( "Stat modifier for stat '{0}' defined in config more than one times. Using first found.",
                            mod.stat );


        if ( !configStats.ContainsKey( mod.value ) )
          configStats.Add( mod.value, mod );
        else
          Log.TraceWarning( "Stat modifier for value '{0}' defined in config more than one times. Using first found.",
                            mod.value );
      }
      return configStats;
    }

    private bool IsPSMAMustBeIgnored( PermanentStatModApplicator psma )
    {
      return ( !String.IsNullOrEmpty( psma.modifier.variable ) || !string.Equals( psma.enabled.sString, "true" ) );
    }

    private int CollectStatModifiersChanges(
      ref Dictionary<string, SyncingTalent> talents,
      Dictionary<string, Config.StatModConstant> modifiers,
      Dictionary<EStat, Config.StatModConstant> perStatModifiers )
    {
      int result = 0;
      foreach ( var p in talents )
      {
        var talent = p.Value;

        var talentMods = talent.EditorModifiers;
        var configMods = new Dictionary<EStat, Config.StatModConstant>();
        ///List of psma which not found in table constants but exist in editor data
        ///Using for deleteing editor only psmas
        var editorOnlyMods = new Dictionary<EStat, PermanentStatModApplicator>();
        foreach ( var tmp in talentMods )
        {
          if ( !IsPSMAMustBeIgnored( tmp.Value ) )
            editorOnlyMods.Add( tmp.Key, tmp.Value );
        }

        //Getting stat modfiers for founded in table constants and storing them by EStat key
        foreach ( var tp in talent.TableConstants )
        {
          var constantName = tp.Key;
          Config.StatModConstant mod;
          if ( modifiers.TryGetValue( constantName, out mod ) )
            configMods.Add( mod.stat, mod );
        }

        foreach ( var pm in configMods )
        {
          var stat = pm.Key;
          var configMod = pm.Value;
          if ( editorOnlyMods.ContainsKey( stat ) )
            editorOnlyMods.Remove( stat );

          var change = new ModifierChangeEntry()
          {
            Stat = stat,
            NewValue = configMod,
            NewAddValue = "c" + configMod.value,
            ConstantName = configMod.value
          };
          var tc = talent.TableConstants[configMod.value];
          if ( !tc.IsTooltipDisabled && talent.EditorTalent.description != null && !string.IsNullOrEmpty( configMod.tooltip ) )
          {
            if ( !IsFragmentExist( talent.EditorTalent.description.GetText(), configMod.tooltip ) )
            {
              foreach ( var anchor in configMod.tooltipAnchors )
                change.DescriptionInsertAnchors.Add( anchor );
              change.DescriptionFragment = configMod.tooltip;
            }
          }

          PermanentStatModApplicator talentMod;
          if ( !talentMods.TryGetValue( stat, out talentMod ) )
          {
            change.ChangeType = ChangeType.Created;
            talent.ModifiersChanges.Add( stat, change );
            continue;
          }

          if ( IsPSMAMustBeIgnored( talentMod ) )
            continue;

          change.Psma = talentMod;
          //Checking for same value
          bool isAddValueSame = String.Equals( change.NewAddValue,
                                change.Psma.modifier.addValue.sString.ToString(),
                                StringComparison.InvariantCultureIgnoreCase );
          if ( !isAddValueSame || !string.IsNullOrEmpty( change.DescriptionFragment ) )
            talent.ModifiersChanges.Add( stat, change );
          if ( !string.IsNullOrEmpty( change.DescriptionFragment ) )
            talent.DescriptionChanges++;
        }

        foreach ( var tmp in editorOnlyMods )
        {
          talent.ModifiersChanges.Add( tmp.Key,
            new ModifierChangeEntry()
            {
              ChangeType = ChangeType.Deleted,
              Psma = tmp.Value,
            } );
          if ( !perStatModifiers.ContainsKey( tmp.Value.modifier.stat ) )
            Log.TraceWarning( "Can't try to remove tooltip fragment for stat '{0}' because it is not found in config.",
              tmp.Value.modifier.stat );
        }
        result += talent.ModifiersChanges.Count;
      }
      return result;
    }
    #endregion

    #region Report
    private class ReportStatuses
    {
      public static string Deleted = "<deleted>";
      public static string Modified = "<modified>";
      public static string Created = "<created>";
      public static string Empty = "<empty>";
    }

    private void SaveChangesReport( string fileName,
      Dictionary<string, SyncingTalent> talents,
      Dictionary<EStat, Config.StatModConstant> perStatConfigMods )
    {
      string nl = "\r\n";
      using ( StreamWriter file = new StreamWriter( fileName, false, Encoding.UTF8 ) )
      {
        List<string> unchangedTalents = new List<string>();
        List<SyncingTalent> talentsWithTechicalConstants = new List<SyncingTalent>();
        foreach ( var p in talents )
        {
          var id = p.Key;
          var talent = p.Value;
          bool hasChanges = talent.HasChanges();
          if ( talent.TechicalConstants.Count > 0 )
            talentsWithTechicalConstants.Add( talent );
          if ( hasChanges )
          {
            file.Write( string.Format( "{0}----{1} [{2}]:{3}", nl, id, talent.ChangeType, nl ) );
            if ( !string.IsNullOrEmpty( talent.UpdatedPath ) )
              file.Write( "#Moved:{2}{0} -> {1}{2}", talent.EditorTalent.DBId.ToString(), talent.UpdatedPath, nl );

            file.Write( "#Fields:" + nl );
            foreach ( var cp in talent.FieldsChanges )
            {
              var change = cp.Value;
              var name = change.OriginalFieldPath;
              string newV = change.NewValue == null ? ReportStatuses.Empty : change.NewValue.ToString();
              string oldV = change.OldValue == null ? ReportStatuses.Empty : change.OldValue.ToString();
              file.Write( string.Format( "'{0}': {1} -> {2}{3}",
                name, oldV, newV, nl ) );
            }
            file.Write( "#Constants:" + nl );
            foreach ( var cp in talent.ConstantsChanges )
            {
              var name = cp.Key;
              var change = cp.Value;
              string oldV = string.Empty;
              string newV = string.Empty;
              if ( change.ChangeType == ChangeType.Modified )
              {
                oldV = change.OldValue;
                newV = change.NewValue;
              }
              else if ( change.ChangeType == ChangeType.Created )
              {
                oldV = ReportStatuses.Created;
                newV = change.NewValue;
              }
              else if ( change.ChangeType == ChangeType.Deleted )
              {
                oldV = change.OldValue;
                newV = ReportStatuses.Deleted;
              }

              file.Write( string.Format( "{0} '{1}': {2} -> {3}{4}",
                change.ChangeType, name, oldV, newV, nl ) );
            }
            file.Write( "#Stat Modifiers:" + nl );
            string newDescription = talent.EditorTalent.description.GetText();
            bool isTooltipWasChanged = false;
            int descrittionInsertertionCounter = 0;
            foreach ( var cp in talent.ModifiersChanges )
            {
              var name = cp.Key;
              var change = cp.Value;
              string oldV = string.Empty;
              string newV = string.Empty;
              if ( change.ChangeType == ChangeType.Modified )
              {
                oldV = change.Psma.modifier.addValue.sString;
                newV = change.NewAddValue;
              }
              else if ( change.ChangeType == ChangeType.Created )
              {
                oldV = ReportStatuses.Created;
                newV = change.NewAddValue;
              }
              else if ( change.ChangeType == ChangeType.Deleted )
              {
                oldV = change.Psma.modifier.addValue.sString;
                newV = ReportStatuses.Deleted;
              }
              if ( !string.Equals( oldV, newV ) )
              {
                file.Write( string.Format( "{0} '{1}': {2} -> {3}{4}",
                                           change.ChangeType, name, oldV, newV, nl ) );

                if ( change.ChangeType == ChangeType.Deleted && perStatConfigMods.ContainsKey( change.Psma.modifier.stat ) )
                {
                  var tooltipFragment = perStatConfigMods[change.Psma.modifier.stat].tooltip;
                  if ( newDescription.Contains( tooltipFragment ) )
                  {
                    isTooltipWasChanged = true;
                    newDescription = newDescription.Replace( tooltipFragment, string.Empty );
                    file.Write( string.Format( "removed from description: '{0}'{1}", tooltipFragment, nl ) );
                  }
                }
              }

              if ( !string.IsNullOrEmpty( change.DescriptionFragment )
                && !newDescription.Contains( change.DescriptionFragment ) )
              {
                isTooltipWasChanged = true;
                string afterFragment = string.Empty;
                if ( descrittionInsertertionCounter > 0 )
                  afterFragment = "<br>";
                string anchor = string.Empty;
                //InsertDescriptionFragment( talent.EditorTalent.description.GetText(), change.DescriptionFragment,
                //                           change.DescriptionInsertAnchors, beforeFragment, out anchor );

                newDescription = InsertDescriptionFragment( newDescription, change.DescriptionFragment,
                                                            change.DescriptionInsertAnchors, afterFragment, out anchor );
                descrittionInsertertionCounter++;
                string tip = "tooltip (start)";
                if ( !string.IsNullOrEmpty( anchor ) )
                  tip = string.Format( "tooltip (after '{0}')", anchor );

                file.Write( string.Format( "{0}:{2}{1}{2}",
                                           tip, change.DescriptionFragment, nl ) );
              }
            }

            //Writing whole new tooltip to report
            if ( isTooltipWasChanged )
            {
              file.Write( string.Format( "{0}[+description]:{0}", nl ) );
              file.Write( string.Format( "{0}{1}", newDescription, nl ) );
              file.Write( string.Format( "[-description]{0}", nl ) );
            }
          }
          else
          {
            //Unchanged talents
            unchangedTalents.Add( talent.ID );
          }
        }

        if ( unchangedTalents.Count > 0 )
          file.Write( string.Format( "{0}unchanged talents:", nl ) );
        foreach ( var unchangedTalent in unchangedTalents )
          file.Write( nl + unchangedTalent );

        if ( talentsWithTechicalConstants.Count > 0 )
          file.Write( string.Format( "{0}{0}talents with techincal constants:", nl ) );
        foreach ( var t in talentsWithTechicalConstants )
        {
          file.Write( nl + t.ID + ":" + nl );
          foreach ( var tc in t.TechicalConstants )
            file.Write( tc + ", " );
          file.Write( nl );
        }
      }
    }
    #endregion

    #region Applying Changes
    private void ApplyChanges( Dictionary<string, SyncingTalent> talents, Dictionary<EStat, Config.StatModConstant> perStatConfigMods )
    {
      foreach ( var p in talents )
      {
        var talent = p.Value;
        bool hasChanges = talent.HasChanges();
        if ( hasChanges )
        {
          foreach ( var cp in talent.FieldsChanges )
          {
            var change = cp.Value;
            if ( typeof( TextRef ).IsAssignableFrom( change.PropertyInfo.PropertyType ) )
            {
              var textref = change.PropertyInfo.GetValue( change.BaseObject, null );
              ( textref as TextRef ).FromString( change.NewValue.ToString() );
            }
            else
            {
              change.PropertyInfo.SetValue( change.BaseObject, change.NewValue, null );
              TryApplyHook( ref change.BaseObject );
            }
          }

          foreach ( var cp in talent.ConstantsChanges )
          {
            var change = cp.Value;

            if ( change.ChangeType == ChangeType.Created )
            {
              DBID cdbid = DBID.FromDBID( talent.EditorTalent.DBId, true );
              DBPtr<UnitConstant> cPntr = DataBase.Create( cdbid, new UnitConstant() );
              change.Constant = cPntr.Get();
              change.Constant.var.sString = change.NewValue;
              change.Constant.name = change.Name;
              talent.EditorTalent.constants.Get().vars.Add( cPntr );
            }
            else if ( change.ChangeType == ChangeType.Modified )
              change.Constant.var.sString = change.NewValue;
            else if ( change.ChangeType == ChangeType.Deleted )
            {
              talent.EditorTalent.constants.Get().vars.Remove( new DBPtr<UnitConstant>( change.Constant.DBId,
                                                                                        change.Constant ) );
              DataBase.Delete( change.Constant.DBId );
            }
            if ( change.ChangeType != ChangeType.Deleted )
            {
              var execString = (object)change.Constant.var;
              TryApplyHook( ref execString );
            }
          }

          string newDescription = talent.EditorTalent.description.GetText();
          bool isTooltipWasChanged = false;
          int descrittionInsertertionCounter = 0;
          foreach ( var cp in talent.ModifiersChanges )
          {
            var stat = cp.Key;
            var change = cp.Value;
            if ( change.ChangeType == ChangeType.Created )
            {
              DBID cdbid = DBID.FromDBID( talent.EditorTalent.DBId, true );
              DBPtr<PermanentStatModApplicator> cPntr = DataBase.Create( cdbid, new PermanentStatModApplicator() );
              change.Psma = cPntr.Get();
              var ptrBaseApplicator = cPntr.GetPtr<BaseApplicator>();
              talent.EditorTalent.passiveApplicators.Add( ptrBaseApplicator );

              change.Psma.modifier.stat = change.Stat;
              change.Psma.modifier.addValue.sString = change.NewAddValue;
              change.Psma.caption = change.ConstantName;
            }
            else if ( change.ChangeType == ChangeType.Modified )
            {
              change.Psma.modifier.addValue.sString = change.NewAddValue;
            }
            else if ( change.ChangeType == ChangeType.Deleted )
            {
              if ( perStatConfigMods.ContainsKey( change.Psma.modifier.stat ) )
              {
                var tooltipFragment = perStatConfigMods[change.Psma.modifier.stat].tooltip;
                if ( newDescription.Contains( tooltipFragment ) )
                {
                  isTooltipWasChanged = true;
                  newDescription = newDescription.Replace( tooltipFragment, string.Empty );
                }
              }

              DBPtr<BaseApplicator> ptr = new DBPtr<BaseApplicator>( change.Psma.DBId, change.Psma );
              talent.EditorTalent.passiveApplicators.Remove( ptr );
              DataBase.Delete( change.Psma.DBId );
            }

            if ( change.ChangeType != ChangeType.Deleted )
            {
              var execString = (object)change.Psma.modifier.addValue;
              TryApplyHook( ref execString );
            }

            if ( !string.IsNullOrEmpty( change.DescriptionFragment )
              && !newDescription.Contains( change.DescriptionFragment ) )
            {
              isTooltipWasChanged = true;
              string afterFragment = string.Empty;
              if ( descrittionInsertertionCounter > 0 )
                afterFragment = "<br>";
              string anchor = string.Empty;
              newDescription = InsertDescriptionFragment( newDescription,
                                                          change.DescriptionFragment,
                                                          change.DescriptionInsertAnchors, afterFragment,
                                                          out anchor );
              descrittionInsertertionCounter++;
            }
          }
          if ( isTooltipWasChanged )
            talent.EditorTalent.description.FromString( newDescription );

        }
      }
    }
    #endregion

    #region Post Apply Hooks
    delegate T1 RefFunction<T1, T2>( ref T2 obj );
    private Dictionary<Type, RefFunction<bool,object>> _hooks = 
      new Dictionary<Type, RefFunction<bool, object>>()
      {
        {typeof(BaseExecutableString), CompileExecutableString}
  };

    private bool TryApplyHook( ref Object o )
    {
      if ( o != null )
        foreach ( var p in _hooks )
          if ( p.Key.IsAssignableFrom( o.GetType() ) )
            return p.Value( ref o );

      return false;
    }

    #region Executable Strings Compilation
    private static FormulaGatherer<ExecutableFloatString> floatImport = new FormulaGatherer<ExecutableFloatString>();
    private static FormulaGatherer<ExecutableBoolString> boolImport = new FormulaGatherer<ExecutableBoolString>();
    private static FormulaGatherer<ExecutableIntString> intImport = new FormulaGatherer<ExecutableIntString>();
    private static bool CompileExecutableString( ref object es )
    {
      if ( es == null )
        return false;

      if ( es is ExecutableFloatString )
      {
        var p = es as ExecutableFloatString;
        return floatImport.Functor( ref p, false );
      }

      if ( es is ExecutableBoolString )
      {
        var p = es as ExecutableBoolString;
        return boolImport.Functor( ref p, false );
      }

      if ( es is ExecutableIntString )
      {
        var p = es as ExecutableIntString;
        return intImport.Functor( ref p, false );
      }
      return false;
    }
    #endregion
    #endregion

    #region Executing

    public IEnumerable Main( IEditorCommonApplication app, string[] args )
    {
      try
      {
        if ( args.Length == 0 )
        {
          Log.TraceError( "Config path argument required. Usage: <script %config_path%>" );
          yield break;
        }
        var configPath = args[0];

        #region Reading Files
        Log.TraceMessage( "Loading config from '{0}'...", configPath );
        var config = LoadConfig( configPath );
        ValidateConfig( config, app.FileSystem.RootPath );
        var configDir = Path.GetDirectoryName( Path.GetFullPath( configPath ) );
        string xlsPath = Path.Combine( configDir, config.Excel.path );
        Log.TraceMessage( "Loading XLS from '{0}'...", xlsPath );
        var table = LoadXlslFile( xlsPath, config.Excel.sheet );
        #endregion

        #region Columns and Constants Detection
        Log.TraceMessage( "Reading columns and detecting constants columns..." );
        var columns = new Dictionary<string, int>( table.GetLength( 1 ) );
        var constantsColumns = new Dictionary<string, TableConstantColumns>();
        ReadTableColumns( table, config.ConstColumnPattern, out columns, out constantsColumns );
        Log.TraceMessage( "Reading columns and detecting constants columns...Ok. {0} columns, {1} constants found.",
          columns.Count, constantsColumns.Count );

        Log.TraceMessage( "Validating constants columns..." );
        ExcludeInvalidTableConstantsColumns( ref constantsColumns );
        Log.TraceMessage( "Validating constants columns...Ok. {0} valid constants found.", constantsColumns.Count );
        #endregion

        #region Loading talents from table
        Log.TraceMessage( "Collecting talents from table..." );
        var talents = CollectTalentsFromTable( table, config, columns );
        Log.TraceMessage( "{0} talents collected from table", talents.Count );
        #endregion

        #region Loading talents from editor
        Log.TraceMessage( "Collecting talents from editor..." );
        List<DBID> editorOnlyTalents;
        int foundTalentsCount = CollectTalentsFromEditor( config, app, ref talents, out editorOnlyTalents );
        Log.TraceMessage( "Collecting talents from editor...Ok." );
        Log.TraceMessage( "{0} talents defined in editor but missed in table.",
                          editorOnlyTalents.Count );
        if ( editorOnlyTalents.Count > 0 )
        {
          Log.TraceError( "Talents missed in table:" );
          foreach ( var dbid in editorOnlyTalents )
            Log.TraceError( dbid.ToString() );
          string err = "Talents, not defined, in table found in editor";
          if ( ABORT_ON_ERRORS )
            throw new InvalidDataException( err );
          else
            Log.TraceError( err );
        }

        Log.TraceMessage( "{0} talents ready for modifying, {1} talents ready for creation",
          foundTalentsCount, Math.Max( talents.Count - foundTalentsCount, 0 ) );


        #region Creating New Talents
        if ( talents.Count - foundTalentsCount > 0 )
        {
          Log.TraceMessage( "Creating new talents(without saving)..." );
          //Checking that minlevel column defined in table
          int MINLEVEL_INDEX = GetColumnIndexOrException( columns, config.Minlevel.column );
          var createdTalentsCounter = TryCreateNewTalents( ref talents, config );
          Log.TraceMessage( "Creating new talents(without saving)...Ok. {0} created", createdTalentsCounter );
        }
        #endregion
        #endregion

        #region Collecting Changes
        #region Fields Changes
        Log.TraceMessage( "Prepearing syncing fields..." );
        var syncingFieldInfos = GetSyncingFiledsInfo( config, columns );
        Log.TraceMessage( "Prepearing syncing fields...Ok. {0} found", syncingFieldInfos.Count );

        Log.TraceMessage( "Searching for talent's fields changes..." );
        var fieldsChanges = CollectFieldsChanges( ref talents, syncingFieldInfos, config );
        Log.TraceMessage( "Searching for talent's fields changes...Ok. '{0}' found", fieldsChanges );
        #endregion
        #region Location Changes
        Log.TraceMessage( "Searching for location changes(move talents)..." );
        int relocatedTalentsCount = CollectLocationChanges( ref talents, config );
        Log.TraceMessage( "Searching for location changes(move talents)...Ok {0} relocated", relocatedTalentsCount );
        #endregion
        #region Constants Changes
        Log.TraceMessage( "Filtering table constants..." );
        CollectTableConstants( config, ref talents, constantsColumns );
        Log.TraceMessage( "Filtering table constants...Ok" );

        Log.TraceMessage( "Collecting editor talent's constants..." );
        CollectEditorConstants( ref talents, config );
        Log.TraceMessage( "Collecting editor talent's constants...Ok" );

        Log.TraceMessage( "Searching for talent's constants changes..." );
        int constantsChanges = CollectConstantsChanges( ref talents, config );
        Log.TraceMessage( "Searching for talent's constants changes...Ok. '{0}' found", constantsChanges );
        #endregion

        #region Modifiers Changes
        Log.TraceMessage( "Collecting stat modifiers..." );
        int editorModifiers = CollectEditorModifiers( ref talents );
        Dictionary<EStat, Config.StatModConstant> perStatConfigMods;
        var configModifiers = GetConfigModifiers( config.StatModConstants, out perStatConfigMods );
        Log.TraceMessage( "Collecting stat modifiers... Ok. {0} collected from editor and {1} collected from config.",
          editorModifiers, configModifiers.Count );

        Log.TraceMessage( "Collecting stat modifier changes..." );
        int modifiersChanges = CollectStatModifiersChanges( ref talents, configModifiers, perStatConfigMods );
        Log.TraceMessage( "Collecting stat modifier changes...Ok. {0} found", modifiersChanges );
        #endregion
        #endregion

        #region Report Generation
        if ( !string.IsNullOrEmpty( config.ReportFilename ) )
        {
          var path = Path.Combine( configDir, config.ReportFilename );
          Log.TraceMessage( "Saving report to '{0}'...", path );
          SaveChangesReport( Path.Combine( configDir, config.ReportFilename ), talents, perStatConfigMods );
          Log.TraceMessage( "Saving report to '{0}'...Ok", path );
        }
        else
          Log.TraceMessage( "Ignoring report generation step, report filename not setted in config." );
        #endregion

        #region Applying Changes & Saving
        Console.WriteLine( "Would you like to save changes? (type 'yes' for confirmation)" );
        string userEntered = Console.ReadLine();
        if ( userEntered == "yes" )
        {
          Log.TraceMessage( "Applying changes..." );
          ApplyChanges( talents, perStatConfigMods );
          Log.TraceMessage( "Applying changes...Ok" );
          Log.TraceMessage( "Saving..." );
          DataBase.Store();
          Log.TraceMessage( "Saving...Ok" );
        }
        else
          Log.TraceMessage( "Applying changes discarded" );
        #endregion
      }
      catch ( Exception e )
      {
        Log.TraceError( "Exception {0}. {1}\n{2}", e.GetType().Name, e.Message, e.StackTrace );
      }
      yield break;
    }
    #endregion
}

