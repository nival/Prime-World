/*
#about Импорт/экспорт амулетов из/в Excel-файл
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/
/*
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.Xml;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using libdb.DB;
using libdb.IO;
using libdb.Diagnostics;
using EditorLib.FieldProcessor;
using EditorLib.Settings;

namespace Scripts
{
  public class UpdateAmulets
  {
    private KeyValuePair<string, EStat>[] primitiveConstants = new KeyValuePair<string, EStat>[]{
      new KeyValuePair<string, EStat>( "Ж", EStat.Life ),
      new KeyValuePair<string, EStat>( "Э", EStat.Energy ),
      new KeyValuePair<string, EStat>( "С", EStat.Power ),
      new KeyValuePair<string, EStat>( "Зэ", EStat.EnergyDefence ),
      new KeyValuePair<string, EStat>( "Зм", EStat.SubstanceDefence ),
      new KeyValuePair<string, EStat>( "Д", EStat.MoveSpeed ),
      new KeyValuePair<string, EStat>( "Скр", EStat. 	AttackSpeed ),
      new KeyValuePair<string, EStat>( "К", EStat.CriticalChance ),
      new KeyValuePair<string, EStat>( "Км", EStat.CriticalMultiplier ),
      new KeyValuePair<string, EStat>( "Вж", EStat.LifeDrain ),
      new KeyValuePair<string, EStat>( "Вэ", EStat.EnergyDrain ),
      new KeyValuePair<string, EStat>( "У", EStat.Evasion ),
      new KeyValuePair<string, EStat>( "Рж%", EStat.LifeRegeneration ),
      new KeyValuePair<string, EStat>( "Рж", EStat.LifeRegenerationAbsolute ),
      new KeyValuePair<string, EStat>( "Рэ%", EStat.EnergyRegeneration ),
      new KeyValuePair<string, EStat>( "Рэ", EStat.EnergyRegenerationAbsolute ),
      new KeyValuePair<string, EStat>( "Б", EStat.Armor )
    };

    private KeyValuePair<string, string>[] defaultNames = new KeyValuePair<string, string>[]
    {
      new KeyValuePair<string, string>( "Урон", "Damage" ),
      new KeyValuePair<string, string>( "Хил", "HealAmount" ),
      new KeyValuePair<string, string>( "КД", "Cooldown" ),
      new KeyValuePair<string, string>( "Длит", "Duration" ),
    };

    private string GetConstant( string expression )
    {
      Match m = Regex.Match( expression, "c([_A-Za-z][_A-Za-z0-9]*)" );
      if ( m.Success && m.Groups.Count == 2 )
        return m.Groups[1].Value;

      return string.Empty;
    }

    private bool IsOne( string expression )
    {
      return expression == "1" || expression == "1." || expression == "1.0" || expression == "1f" || expression == "1.f"  || expression == "1.0f";
    }

    private bool IsTrue( string expression )
    {
      return expression == "1" || string.Compare( expression, "true", StringComparison.InvariantCultureIgnoreCase ) == 0;
    }

    private string GetPrimitiveConstant( PermanentStatModApplicator applicator )
    {
      if ( !IsOne( applicator.modifier.multValue.sString ) || !IsTrue( applicator.enabled.sString ) )
        return string.Empty;

      if ( string.IsNullOrEmpty( GetConstant( applicator.modifier.addValue.sString ) ) )
        return string.Empty;

      foreach ( var value in primitiveConstants )
      {
        if ( value.Value == applicator.modifier.stat )
          return value.Key;
      }

      return string.Empty;
    }

    /// <summary>
    /// Remove last 'f' in case of expresion is just constant
    /// </summary>
    /// <param name="expression"></param>
    /// <returns></returns>
    private string SimplifyFormula( string expression )
    {
      if ( string.IsNullOrEmpty( expression ) )
        return string.Empty;
      if ( char.ToLower( expression[expression.Length - 1] ) == 'f' && Table2.IsNumber( expression.Substring( 0, expression.Length - 1 ) ) )
        return expression.Substring( 0, expression.Length - 1 );

      return expression;
    }

    /// <summary>
    /// Returns list of primitive variables from amulet and theirs "real" names
    /// </summary>
    /// <param name="amulet">Amulet</param>
    /// <returns>List of variables in format default name -> real name </returns>
    private List<KeyValuePair<string, string>> GetPrimitiveConstants( Amulet amulet )
    {
      List<KeyValuePair<string, string>> result = new List<KeyValuePair<string, string>>();

      foreach ( var applicator in amulet.passiveApplicators )
      {
        if ( applicator.Get() == null || !( applicator.Get() is PermanentStatModApplicator ) )
          continue;

        PermanentStatModApplicator peramanent = applicator.Get() as PermanentStatModApplicator;
        string variable = GetPrimitiveConstant( peramanent );
        if ( !string.IsNullOrEmpty( variable ) )
          result.Add( new KeyValuePair<string, string>( variable, GetConstant( peramanent.modifier.addValue.sString ) ) );
      }

      return result;
    }

    private int GetAmuletNumber( Amulet amulet )
    {
      string name = FileUtils.GetFileName( amulet.DBId.FileName );
      int startIndex = 0;
      if ( name[0] == '_' )
        startIndex = 1;

      int index = startIndex;
      while ( index < name.Length && char.IsDigit( name[index] ) )
        ++index;

      if ( index == startIndex )
        return -1;

      return int.Parse( name.Substring( startIndex, index - startIndex ) );
    }

    private string GetRariryString( EAmuletRarity rariry )
    {
      switch ( rariry )
      {
      case EAmuletRarity.ordinary:
        return "О";
      case EAmuletRarity.good:
        return "Х";
      case EAmuletRarity.excellent:
        return "П";
      case EAmuletRarity.magnificent:
        return "В";
      }

      return string.Empty;
    }

    private bool TryGetRarity( string value, out EAmuletRarity rariry )
    {
      rariry = EAmuletRarity.ordinary;
      string lower = value.ToLower();
      if ( lower == "o" || lower == "о" )
        rariry = EAmuletRarity.ordinary;
      else if ( lower == "x" || lower == "х" )
        rariry = EAmuletRarity.good;
      else if ( lower == "п" )
        rariry = EAmuletRarity.excellent;
      else if ( lower == "b" || lower == "в" )
        rariry = EAmuletRarity.magnificent;
      else
        return false;

      return true;
    }

    private string TryGetName( string name, Dictionary<string, string> names )
    {
      string result = string.Empty;
      if ( names.TryGetValue( name, out result ) )
        return result;
      return name;
    }

    private void Store( IEditorWinApplication app, string fileName )
    {
      List<DBID> dbids;
      ObjectsSelector.CollectObjects( app.Application, "/Items/Amulets/", typeof( Amulet ), true, false, out dbids );

      int maxVariables = 0;
      List<Amulet> amulets = new List<Amulet>();
      foreach ( DBID dbid in dbids )
      {
        Amulet amulet = DataBase.Get<Amulet>( dbid ).Get();
        amulets.Add( amulet );
        if ( amulet.constants.Get() != null )
          maxVariables = Math.Max( maxVariables, amulet.constants.Get().vars.Count );
      }

      Table2 table = new Table2( "Amulets", 7 + ( 3 + maxVariables ) * 2, amulets.Count + 1 );
      table[0, 0] = "№";
      table[1, 0] = "Название";
      table[2, 0] = "Описание";
      table[3, 0] = "ТУР";
      table[4, 0] = "devPoints";
      table[5, 0] = "Кч-во";
      table[6, 0] = "Цена";
      table[7, 0] = "Стат1";
      table[8, 0] = "Знач1";
      table[9, 0] = "Стат2";
      table[10, 0] = "Знач2";
      table[11, 0] = "Стат3";
      table[12, 0] = "Знач3";

      amulets.Sort( ( Amulet a, Amulet b ) => { return GetAmuletNumber( a ) - GetAmuletNumber( b ); } );
      Log.TraceMessage( "Store information about {0} amulets", amulets.Count );
      for ( int i = 0; i < amulets.Count; ++i )
      {
        Amulet amulet = amulets[i];
        table[0, i + 1] = GetAmuletNumber( amulet ).ToString();
        table[1, i + 1] = amulet.name.ToString();
        table[2, i + 1] = amulet.description.ToString();
        table[3, i + 1] = ( amulet.minLevel + 1 ).ToString();
        table[4, i + 1] = amulet.devPoints.ToString();
        table[5, i + 1] = GetRariryString( amulet.rarity );
        table[6, i + 1] = amulet.moneyCost.ToString();

        List<KeyValuePair<string, string>> constants = new List<KeyValuePair<string, string>>();
        if ( amulet.constants.Get() != null )
        {
          foreach ( var constant in amulet.constants.Get().vars )
            constants.Add( new KeyValuePair<string, string>( constant.Get().name, constant.Get().var.sString ) );
        }

        List<KeyValuePair<string, string>> primitives = GetPrimitiveConstants( amulet );
        constants.Sort( ( KeyValuePair<string, string> a, KeyValuePair<string, string> b ) => { return string.Compare( a.Key, b.Key ); } );
        Dictionary<string, string> names = new Dictionary<string, string>();
        foreach ( var name in defaultNames )
          names.Add( name.Value, name.Key );
        foreach ( var name in primitives )
        {
          if ( !names.ContainsKey( name.Value ) )
            names.Add( name.Value, name.Key );
        }

        int c = 0;
        foreach ( var constant in constants )
        {
          if ( primitives.FindIndex( ( KeyValuePair<string, string> var ) => { return var.Value == constant.Key; } ) == -1 )
            continue;

          table[7 + c * 2, i + 1] = TryGetName( constant.Key, names );
          table[8 + c * 2, i + 1] = SimplifyFormula( constant.Value );
          ++c;
        }

        c = Math.Max( 3, c );
        foreach ( var constant in constants )
        {
          if ( primitives.FindIndex( ( KeyValuePair<string, string> var ) => { return var.Value == constant.Key; } ) >= 0 )
            continue;

          table[7 + c * 2, i + 1] = TryGetName( constant.Key, names );
          table[8 + c * 2, i + 1] = SimplifyFormula( constant.Value );
          ++c;
        }
      }

      Table2.WriteExcelFile( fileName, new Table2[] { table } );
    }

    private void UpdateConstant( Amulet amulet, string name, string expression, IStringConvertor convertor )
    {
      if ( amulet.constants == null || amulet.constants.Get() == null )
      {
        Log.TraceMessage( "\"{0}\" Create new constants array", amulet.DBId );
        amulet.constants = DataBase.Create<UnitConstantsContainer>( DBID.FromDBID( amulet.DBId, true ), new UnitConstantsContainer() );
      }

      foreach ( var constant in amulet.constants.Get().vars )
      {
        if ( constant == null || constant.Get() == null )
          continue;

        //Log.TraceMessage( "\"{0}\" Found constant \"{1}\" looking for \"{2}\" (equal: {3})", amulet.DBId, constant.Get().name, name, constant.Get().name == name );

        if ( constant.Get().name != name )
          continue;

        if ( constant.Get().var.sString != expression )
        {
          Log.TraceMessage( "\"{0}\" Update constant \"{1}\" from \"{2}\" to \"{3}\"", amulet.DBId, constant.Get().name, constant.Get().var.sString, expression );
          constant.Get().var = convertor.ConvertFromString( null, System.Globalization.CultureInfo.CurrentCulture, expression ) as ExecutableFloatString;
        }
        return;
      }

      Log.TraceMessage( "\"{0}\" Add constant \"{1}\" with value \"{2}\"", amulet.DBId, name, expression );
      amulet.constants.Get().vars.Add( DataBase.Create<UnitConstant>( DBID.FromDBID( amulet.constants.DBId, true ), new UnitConstant() ) );
      amulet.constants.Get().vars[amulet.constants.Get().vars.Count - 1].Get().name = name;
      amulet.constants.Get().vars[amulet.constants.Get().vars.Count - 1].Get().var =
        convertor.ConvertFromString( null, System.Globalization.CultureInfo.CurrentCulture, expression ) as ExecutableFloatString;
    }

    private void Update( IEditorWinApplication app, string fileName )
    {
      List<DBID> dbids;
      ObjectsSelector.CollectObjects( app.Application, "/Items/Amulets/", typeof( Amulet ), true, false, out dbids );

      DataBase.UndoRedoManager.Start( "Update amulets..." );

      Dictionary<int, Amulet> amulets = new Dictionary<int, Amulet>();
      foreach ( DBID dbid in dbids )
      {
        Amulet amulet = DataBase.Get<Amulet>( dbid ).Get();
        int id = GetAmuletNumber( amulet );
        if ( id >= 0 )
        {
          if ( amulets.ContainsKey( id ) )
            Log.TraceWarning( "Two amulets has same id: \"{0}\" and \"{1}\"", amulets[id].DBId, amulet.DBId );
          else
            amulets.Add( id, amulet );
        }
      }

      Table2 table = Table2.ReadExcelFile( fileName )[0];
      for ( int i = 0; i < table.Rows; ++i )
      {
        if ( string.IsNullOrEmpty( table[0, i] ) || table[0, i] == "№" )
          continue;
        int number = 0;
        if ( !int.TryParse( table[0, i], out number ) )
        {
          Log.TraceWarning( "\"{0}\" is not valid amulet id", table[0, i] );
          continue;
        }

        if ( number == -1 )
          continue;

        Amulet amulet = null;
        if ( !amulets.TryGetValue( number, out amulet ) )
        {
          Log.TraceWarning( "Amulet with number {0} not exists in resources", number );
          continue;
        }

        if ( table[1, i] != amulet.name.ToString() )
        {
          Log.TraceMessage( "\"{0}\" Rename to \"{1}\"", amulet.DBId, table[1, i] );
          amulet.name.FromString( table[1, i] );
        }

        //if ( table[2, i] != amulet.description.ToString() )
        //{
        //  Log.TraceMessage( "\"{0}\" Update description from {1} to {2}", amulet.DBId, amulet.description.ToString(), table[2, i] );
        //  amulet.description.FromString( table[2, i] );
        //}

        int n;
        if ( !int.TryParse( table[3, i], out n ) )
          Log.TraceWarning( "\"{0}\" is not valid value for minLevel", table[3, i] );
        else if ( amulet.minLevel != n - 1 )
        {
          Log.TraceMessage( "\"{0}\" Update minLevel from {1} to {2}", amulet.DBId, amulet.minLevel + 1, n );
          amulet.minLevel = n - 1;
        }

        if ( !int.TryParse( table[4, i], out n ) )
          Log.TraceWarning( "\"{0}\" is not valid value for devPoints", table[4, i] );
        else if ( amulet.devPoints != n )
        {
          Log.TraceMessage( "\"{0}\" Update devPoints from {1} to {2}", amulet.DBId, amulet.devPoints, n );
          amulet.devPoints = n;
        }

        EAmuletRarity rarity;
        if ( !TryGetRarity( table[5, i], out rarity ) )
          Log.TraceWarning( "\"{0}\" is not valid value for devPoints", table[5, i] );
        else if ( amulet.rarity != rarity )
        {
          Log.TraceMessage( "\"{0}\" Update rarity from {1} to {2}", amulet.DBId, amulet.rarity, rarity );
          amulet.rarity = rarity;
        }

        if ( !int.TryParse( table[6, i], out n ) )
          Log.TraceWarning( "\"{0}\" is not valid value for devPoints", table[6, i] );
        else if ( amulet.moneyCost != n )
        {
          Log.TraceMessage( "\"{0}\" Update moneyCost from {1} to {2}", amulet.DBId, amulet.moneyCost, n );
          amulet.moneyCost = n;
        }

        Dictionary<EStat, string> primitives = new Dictionary<EStat, string>();
        Dictionary<string, string> constants = new Dictionary<string, string>();
        for ( n = 7; n < table.Columns - 1; n += 2 )
        {
          if ( string.IsNullOrEmpty( table[n, i] ) )
            continue;

          if ( string.IsNullOrEmpty( table[n + 1, i] ) )
          {
            Log.TraceWarning( "Constant \"{0}\" has undefined value", table[n, i] );
            continue;
          }

          bool found = false;
          foreach ( var primitive in primitiveConstants )
          {
            if ( string.Compare( primitive.Key, table[n, i], StringComparison.InvariantCultureIgnoreCase ) == 0 )
            {
              if ( primitives.ContainsKey( primitive.Value ) )
                Log.TraceWarning( "Constant \"{0}\" defined twice for amulet \"{1}\"", table[n, i], table[1, i] );
              else
                primitives.Add( primitive.Value, table[n + 1, i] );
              found = true;
              break;
            }
          }
          if ( found )
            continue;

          foreach( var name in defaultNames )
          {
            if ( string.Compare( name.Key, table[n, i], StringComparison.InvariantCultureIgnoreCase ) == 0 )
            {
              if ( constants.ContainsKey( name.Value ) )
                Log.TraceWarning( "Constant \"{0}\" defined twice for amulet \"{1}\"", table[n, i], table[1, i] );
              else
                constants.Add( name.Value, table[n + 1, i] );
              found = true;
              break;
            }
          }
          if ( found )
            continue;

          if ( constants.ContainsKey( table[n, i] ) )
            Log.TraceWarning( "Constant \"{0}\" defined twice for amulet \"{1}\"", table[n, i], table[1, i] );
          else
            constants.Add( table[n, i], table[n + 1, i] );
        }

        IStringConvertor floatCompiler = app.Application.Extensions.CreateStringConverter( typeof( ExecutableFloatString ), app );
        IStringConvertor boolCompiler = app.Application.Extensions.CreateStringConverter( typeof( ExecutableBoolString ), app );
        List<int> obsolete = new List<int>();
        for ( n = 0; n < amulet.passiveApplicators.Count; ++n )
        {
          DBPtr<BaseApplicator> applicator = amulet.passiveApplicators[n];
          if ( applicator.Get() == null || !( applicator.Get() is PermanentStatModApplicator ) )
            continue;

          PermanentStatModApplicator peramanent = applicator.Get() as PermanentStatModApplicator;
          if ( string.IsNullOrEmpty( GetPrimitiveConstant( peramanent ) ) )
            continue;

          string constant = GetConstant( peramanent.modifier.addValue.sString );

          string expression;
          if ( !primitives.TryGetValue( peramanent.modifier.stat, out expression ) )
            obsolete.Add( n );
          else
          {
            if ( constants.ContainsKey( constant ) )
              Log.TraceWarning( "Constant \"{0}\" defined twice for amulet \"{1}\"", table[n, i], table[1, i] );
            else
            {
              constants.Add( constant, expression );
              primitives.Remove( peramanent.modifier.stat );
            }
          }
        }
        //Log.TraceMessage( "\"{0}\" constants: {1}", amulet.DBId, string.Join( ", ", new List<string>( constants.Keys ).ToArray() ) );

        obsolete.Sort( ( int a, int b ) => { return b - a; } );
        foreach ( int index in obsolete )
        {
          PermanentStatModApplicator applicator = amulet.passiveApplicators[index].Get<PermanentStatModApplicator>();
          Log.TraceMessage( "\"{0}\" Remove applicator \"{1}\"", amulet.DBId, applicator.caption );
          amulet.passiveApplicators.RemoveAt( index );
        }

        foreach ( var primitive in primitives )
        {
          string caption = string.Format( "Add {0}", primitive.Key.ToString() );
          string constant = string.Format( "Add_{0}", primitive.Key.ToString().Replace( "Critical", "Crit" ).Replace( "Regeneration", "Reg" ).Replace( "Absolute", "Abs" ) );
          Log.TraceMessage( "\"{0}\" Add applicator \"{1}\"", amulet.DBId, caption );
          DBPtr<PermanentStatModApplicator> applicator = DataBase.Create<PermanentStatModApplicator>( DBID.FromDBID( amulet.DBId, true ), new PermanentStatModApplicator() );
          amulet.passiveApplicators.Add( applicator.GetPtr<BaseApplicator>() );
          applicator.Get().caption = caption;
          applicator.Get().enabled = boolCompiler.ConvertFromString( null, System.Globalization.CultureInfo.CurrentCulture, "true" ) as ExecutableBoolString;
          applicator.Get().minRank = 0;
          applicator.Get().applyTarget = EApplicatorApplyTarget.ApplicatorTarget;
          applicator.Get().modifier.stat = primitive.Key;
          applicator.Get().modifier.addValue = floatCompiler.ConvertFromString( null, System.Globalization.CultureInfo.CurrentCulture, string.Format( "c{0}", constant ) ) as ExecutableFloatString;
          applicator.Get().modifier.multValue = floatCompiler.ConvertFromString( null, System.Globalization.CultureInfo.CurrentCulture, "1" ) as ExecutableFloatString;
          applicator.Get().modifier.variable = string.Empty;
          if ( constants.ContainsKey( constant ) )
            Log.TraceWarning( "Constant \"{0}\" defined twice for amulet \"{1}\"", table[n, i], table[1, i] );
          else
            constants.Add( constant, primitive.Value );
        }

        foreach ( var constant in constants )
          UpdateConstant( amulet, constant.Key, constant.Value, floatCompiler );
      }

      DataBase.UndoRedoManager.Commit();
    }

    public IEnumerable Main( IEditorWinApplication app )
    {
      ImportExportAmuletsForm form = new ImportExportAmuletsForm();
      if ( form.ShowDialog() == DialogResult.OK )
      {
        if ( form.Import )
          Update( app, form.FileName );
        else
          Store( app, form.FileName );
      }

      yield return true;
    }
  }

  #region public class ImportExportAmuletsForm : Form

  public class ImportExportAmuletsForm : Form
  {
    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.panel1 = new System.Windows.Forms.Panel();
      this.buttonOk = new System.Windows.Forms.Button();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.radioButtonToExcel = new System.Windows.Forms.RadioButton();
      this.radioButtonFromExcel = new System.Windows.Forms.RadioButton();
      this.textBoxFileName = new System.Windows.Forms.TextBox();
      this.buttonBrowse = new System.Windows.Forms.Button();
      this.labelFileName = new System.Windows.Forms.Label();
      this.panel1.SuspendLayout();
      this.SuspendLayout();
      // 
      // panel1
      // 
      this.panel1.BackColor = System.Drawing.SystemColors.Control;
      this.panel1.Controls.Add( this.buttonOk );
      this.panel1.Controls.Add( this.buttonCancel );
      this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.panel1.Location = new System.Drawing.Point( 0, 115 );
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size( 397, 40 );
      this.panel1.TabIndex = 0;
      // 
      // buttonOk
      // 
      this.buttonOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.buttonOk.Location = new System.Drawing.Point( 229, 9 );
      this.buttonOk.Name = "buttonOk";
      this.buttonOk.Size = new System.Drawing.Size( 75, 23 );
      this.buttonOk.TabIndex = 1;
      this.buttonOk.Text = "OK";
      this.buttonOk.UseVisualStyleBackColor = true;
      // 
      // buttonCancel
      // 
      this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 310, 9 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 0;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      // 
      // radioButtonToExcel
      // 
      this.radioButtonToExcel.AutoSize = true;
      this.radioButtonToExcel.Checked = true;
      this.radioButtonToExcel.Location = new System.Drawing.Point( 12, 12 );
      this.radioButtonToExcel.Name = "radioButtonToExcel";
      this.radioButtonToExcel.Size = new System.Drawing.Size( 222, 17 );
      this.radioButtonToExcel.TabIndex = 1;
      this.radioButtonToExcel.TabStop = true;
      this.radioButtonToExcel.Text = "Export data to Excel from resource system";
      this.radioButtonToExcel.UseVisualStyleBackColor = true;
      // 
      // radioButtonFromExcel
      // 
      this.radioButtonFromExcel.AutoSize = true;
      this.radioButtonFromExcel.Location = new System.Drawing.Point( 12, 35 );
      this.radioButtonFromExcel.Name = "radioButtonFromExcel";
      this.radioButtonFromExcel.Size = new System.Drawing.Size( 221, 17 );
      this.radioButtonFromExcel.TabIndex = 2;
      this.radioButtonFromExcel.TabStop = true;
      this.radioButtonFromExcel.Text = "Import data from Excel to resource system";
      this.radioButtonFromExcel.UseVisualStyleBackColor = true;
      // 
      // textBoxFileName
      // 
      this.textBoxFileName.Location = new System.Drawing.Point( 12, 83 );
      this.textBoxFileName.Name = "textBoxFileName";
      this.textBoxFileName.Size = new System.Drawing.Size( 292, 20 );
      this.textBoxFileName.TabIndex = 3;
      // 
      // buttonBrowse
      // 
      this.buttonBrowse.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonBrowse.Location = new System.Drawing.Point( 310, 83 );
      this.buttonBrowse.Name = "buttonBrowse";
      this.buttonBrowse.Size = new System.Drawing.Size( 75, 23 );
      this.buttonBrowse.TabIndex = 4;
      this.buttonBrowse.Text = "Browse...";
      this.buttonBrowse.UseVisualStyleBackColor = true;
      this.buttonBrowse.Click += new System.EventHandler( this.OnButtonBrowseClick );
      // 
      // labelFileName
      // 
      this.labelFileName.AutoSize = true;
      this.labelFileName.Location = new System.Drawing.Point( 12, 67 );
      this.labelFileName.Name = "labelFileName";
      this.labelFileName.Size = new System.Drawing.Size( 57, 13 );
      this.labelFileName.TabIndex = 5;
      this.labelFileName.Text = "File Name:";
      // 
      // ImportExportAmuletsForm
      // 
      this.AcceptButton = this.buttonOk;
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.SystemColors.Window;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 397, 155 );
      this.Controls.Add( this.labelFileName );
      this.Controls.Add( this.buttonBrowse );
      this.Controls.Add( this.textBoxFileName );
      this.Controls.Add( this.radioButtonFromExcel );
      this.Controls.Add( this.radioButtonToExcel );
      this.Controls.Add( this.panel1 );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.Name = "ImportExportAmuletsForm";
      this.Text = "Import and Export Amulets\' Data";
      this.Load += new System.EventHandler( this.OnLoad );
      this.FormClosed += new System.Windows.Forms.FormClosedEventHandler( this.OnClosed );
      this.panel1.ResumeLayout( false );
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.Button buttonOk;
    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.RadioButton radioButtonToExcel;
    private System.Windows.Forms.RadioButton radioButtonFromExcel;
    private System.Windows.Forms.TextBox textBoxFileName;
    private System.Windows.Forms.Button buttonBrowse;
    private System.Windows.Forms.Label labelFileName;

    [ConfigObject( true )]
    private class ImportExportAmuletsSettings : SimpleConfigObject
    {
      public bool import;
      public string file;

      public ImportExportAmuletsSettings()
      {
        import = true;
        file = Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.MyDocuments ), "amulets.xml" );
      }
    }

    public ImportExportAmuletsForm()
    {
      InitializeComponent();
    }

    private void SaveSettings()
    {
      ImportExportAmuletsSettings settings = new ImportExportAmuletsSettings();
      settings.import = radioButtonFromExcel.Checked;
      settings.file = textBoxFileName.Text;

      string fileName = Path.Combine( Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData ), "PF_Editor" ), "ImportExportAmuletsSettings.config" );
      using ( XmlWriter writer = XmlWriter.Create( fileName ) )
      {
        writer.WriteStartElement( "configuration" );
        settings.Serialize( writer, null );
        writer.WriteEndElement();
        writer.Close();
        writer.Flush();
      }
    }

    private void LoadSettings()
    {
      ImportExportAmuletsSettings settings = new ImportExportAmuletsSettings();
      try
      {
        string fileName = Path.Combine( Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData ), "PF_Editor" ), "ImportExportAmuletsSettings.config" );
        using ( XmlReader reader = XmlReader.Create( fileName ) )
        {
          reader.ReadStartElement();
          settings.Deserialize( reader );
          reader.ReadEndElement();
          reader.Close();
        }
      }
      catch
      {
      }
      radioButtonFromExcel.Checked = settings.import;
      radioButtonToExcel.Checked = !settings.import;
      textBoxFileName.Text = settings.file;
    }

    private string ShowSaveFileDialog()
    {
      SaveFileDialog file = new SaveFileDialog();
      file.Filter = "Excel xml files (*.xml)|*.xml";
      file.RestoreDirectory = true;
      file.SupportMultiDottedExtensions = true;
      file.OverwritePrompt = true;
      file.CheckPathExists = true;
      if ( file.ShowDialog() != DialogResult.OK )
        return string.Empty;

      return file.FileName;
    }

    private string ShowOpenFileDialog()
    {
      OpenFileDialog file = new OpenFileDialog();
      file.Filter = "Excel xml files (*.xml)|*.xml";
      file.Multiselect = false;
      file.CheckFileExists = true;
      file.RestoreDirectory = true;
      file.SupportMultiDottedExtensions = true;
      file.CheckPathExists = true;
      if ( file.ShowDialog() != DialogResult.OK )
        return string.Empty;

      return file.FileName;
    }

    private void OnLoad( object sender, EventArgs e )
    {
      LoadSettings();
    }

    private void OnClosed( object sender, FormClosedEventArgs e )
    {
      SaveSettings();
    }

    private void OnButtonBrowseClick( object sender, EventArgs e )
    {
      string fileName = string.Empty;
      if ( radioButtonFromExcel.Checked )
        fileName = ShowOpenFileDialog();
      else if ( radioButtonToExcel.Checked )
        fileName = ShowSaveFileDialog();

      if ( !string.IsNullOrEmpty( fileName ) )
        textBoxFileName.Text = fileName;
    }

    public bool Import { get { return radioButtonFromExcel.Checked; } }

    public string FileName { get { return textBoxFileName.Text; } }
  }

  #endregion

  #region public class Table2

  public class Table2
  {
    private string name;
    private int cols;
    private int rows;
    private int realCols;
    private int realRows;
    private string[,] data;

    public Table2( string name, int reserveCols, int reserveRows )
    {
      this.name = name;
      realCols = reserveCols;
      realRows = reserveRows;
      cols = 0;
      rows = 0;
      data = new string[realCols, realRows];
    }

    public string Name { get { return name; } }
    public int Columns { get { return cols; } }
    public int Rows { get { return rows; } }
    public string this[int col, int row]
    {
      get
      {
        if ( col < 0 || col >= Columns || row < 0 || row >= Rows )
          throw new ArgumentException( String.Format( "Cannot get value for cell {0}x{1}, size of table {2}x{3}", col, row, Columns, Rows ) );
        return data[col, row];
      }
      set
      {
        if ( col < 0 || col >= realCols || row < 0 || row >= realRows )
          throw new ArgumentException( String.Format( "Cannot set value for cell {0}x{1}, size of table {2}x{3}", col, row, realCols, realRows ) );
        data[col, row] = value;
        if ( !string.IsNullOrEmpty( value ) )
        {
          if ( col >= Columns )
            cols = col + 1;
          if ( row >= Rows )
            rows = row + 1;
        }
      }
    }

    public static bool IsNumber( string str )
    {
      Match m = Regex.Match( str, "\\-?[0-9]+(\\.[0-9]*)?" );
      return m.Success && m.Groups[0].Value == str;
    }

    public static Table2[] ReadExcelFile( string fileName )
    {
      List<Table2> tables = new List<Table2>();
      XmlDocument xmlDoc = new XmlDocument();
      using ( FileStream streamFile = new FileStream( fileName, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.ReadWrite ) )
      {
        xmlDoc.Load( streamFile );
        streamFile.Close();
      }
      XmlNode xmlWorkbook = xmlDoc["Workbook"];
      for ( XmlNode xmlNode = xmlWorkbook.FirstChild; xmlNode != null; xmlNode = xmlNode.NextSibling )
      {
        if ( xmlNode.Name == "Worksheet" )
        {
          XmlNode xmlTable = xmlNode["Table"];
          if ( xmlTable != null )
          {
            int nColumns = Convert.ToInt32( xmlTable.Attributes["ss:ExpandedColumnCount"].Value );
            int nRows = Convert.ToInt32( xmlTable.Attributes["ss:ExpandedRowCount"].Value );
            Table2 table = new Table2( xmlNode.Attributes["ss:Name"].Value, nColumns, nRows );
            int nRow = 0;
            for ( XmlNode xmlRow = xmlTable.FirstChild; xmlRow != null; xmlRow = xmlRow.NextSibling )
            {
              if ( xmlRow.Name == "Row" )
              {
                int nCell = 0;
                for ( XmlNode xmlCell = xmlRow.FirstChild; xmlCell != null; xmlCell = xmlCell.NextSibling )
                {
                  if ( xmlCell.Name == "Cell" )
                  {
                    XmlNode xmlIndex = xmlCell.Attributes["ss:Index"];
                    if ( xmlIndex != null )
                      nCell = Convert.ToInt32( xmlIndex.Value ) - 1;
                    XmlNode xmlData = xmlCell["Data"];
                    if ( xmlData != null )
                    {
                      table[nCell, nRow] = xmlData.InnerText;
                    }
                    nCell++;
                  }
                }
                nRow++;
              }
            }
            tables.Add( table );
          }
        }
      }

      return tables.ToArray();
    }

    private static XmlNode CreateWorkbook( XmlDocument xmlDoc, Table2 table )
    {
      XmlNode xmlNodeWorkSheet = xmlDoc.CreateElement( "Worksheet" );
      xmlNodeWorkSheet.Attributes.Append( xmlDoc.CreateAttribute( "ss", "Name", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = table.Name;

      XmlNode xmlTable = xmlDoc.CreateElement( "Table" );
      xmlNodeWorkSheet.AppendChild( xmlTable );
      xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "ss", "ExpandedColumnCount", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = table.Columns.ToString();
      xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "ss", "ExpandedRowCount", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = table.Rows.ToString();
      xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "x", "FullColumns", "urn:schemas-microsoft-com:office:excel" ) ).Value = "1";
      xmlTable.Attributes.Append( xmlDoc.CreateAttribute( "x", "FullRows", "urn:schemas-microsoft-com:office:excel" ) ).Value = "1";

      for ( int nRow = 0; nRow < table.Rows; ++nRow )
      {
        XmlNode xmlRow = xmlDoc.CreateElement( "Row" );
        xmlTable.AppendChild( xmlRow );
        for ( int nCol = 0; nCol < table.Columns; ++nCol )
        {
          XmlNode xmlCell = xmlDoc.CreateElement( "Cell" );
          xmlRow.AppendChild( xmlCell );
          if ( table[nCol, nRow] != null && table[nCol, nRow].Length > 0 )
          {
            XmlNode xmlData = xmlDoc.CreateElement( "Data" );
            xmlCell.AppendChild( xmlData );
            xmlData.Attributes.Append( xmlDoc.CreateAttribute( "ss", "Type", "urn:schemas-microsoft-com:office:spreadsheet" ) ).Value = IsNumber( table[nCol, nRow] ) ? "Number" : "String";
            xmlData.AppendChild( xmlDoc.CreateTextNode( table[nCol, nRow] ) );
          }
        }
      }

      return xmlNodeWorkSheet;
    }

    public static void WriteExcelFile( string fileName, Table2[] tables )
    {
      XmlDocument xmlDoc = new XmlDocument();
      xmlDoc.Prefix = "";

      XmlNode xmlNodeWorkbook = xmlDoc.CreateElement( "Workbook" );
      xmlDoc.AppendChild( xmlNodeWorkbook );
      xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns" ) ).Value = "urn:schemas-microsoft-com:office:spreadsheet";
      xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:o" ) ).Value = "urn:schemas-microsoft-com:office:office";
      xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:x" ) ).Value = "urn:schemas-microsoft-com:office:excel";
      xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:ss" ) ).Value = "urn:schemas-microsoft-com:office:spreadsheet";
      xmlNodeWorkbook.Attributes.Append( xmlDoc.CreateAttribute( "xmlns:html" ) ).Value = "http://www.w3.org/TR/REC-html40";

      foreach ( Table2 table in tables )
      {
        XmlNode xmlNodeWorksheet = CreateWorkbook( xmlDoc, table );
        xmlNodeWorkbook.AppendChild( xmlNodeWorksheet );
      }

      using ( XmlTextWriter xmlWriter = new XmlTextWriter( new FileStream( fileName, FileMode.Create ), System.Text.Encoding.Unicode ) )
      {
        xmlWriter.Indentation = 2;
        xmlWriter.IndentChar = ' ';
        xmlWriter.Formatting = Formatting.Indented;
        xmlDoc.Save( xmlWriter );
        xmlWriter.Flush();
        xmlWriter.Close();
      }
    }
  }

  #endregion
}
*/