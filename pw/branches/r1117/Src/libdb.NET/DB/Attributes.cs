using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text.RegularExpressions;

namespace libdb.DB
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class DBAttribute : Attribute
  {
    public virtual string ConstructorParameters { get { return string.Empty; } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class FieldCategoryAttribute : DBAttribute
  {
    public readonly string category = string.Empty;
    public FieldCategoryAttribute( string category ) { this.category = category; }
    public override string ConstructorParameters { get { return String.Format( "\"{0}\"", category ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class FileRefAttribute : DBAttribute
  {
    public readonly string filenameExtension = string.Empty;
    public FileRefAttribute( string _filenameExtension )
    {
      filenameExtension = _filenameExtension;
    }
    public override string ConstructorParameters { get { return String.Format( "\"{0}\"", filenameExtension ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class SwfFileRefAttribute : DBAttribute
  {
    public readonly string filenameExtension = string.Empty;
    public SwfFileRefAttribute( string _filenameExtension )
    {
      filenameExtension = _filenameExtension;
    }
    public override string ConstructorParameters { get { return String.Format( "\"{0}\"", filenameExtension ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class ToolBoxItemAttribute : DBAttribute
  {
    public readonly string category = string.Empty;
    public readonly string name = string.Empty;
    public readonly string image = null;
    public ToolBoxItemAttribute( string _category, string _name, string _image )
    { category = _category; name = _name; image = _image; }
    public override string ConstructorParameters { get { return String.Format( "\"{0}\", \"{1}\", \"{2}\"", category, name, image ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class NoCodeAttribute : DBAttribute
  {
    public string IncludeFile { get; private set; }
    public NoCodeAttribute() : this( string.Empty ) { }
    public NoCodeAttribute( string fileName ) { IncludeFile = fileName; }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class NoCSCodeAttribute : DBAttribute
  {
    public NoCSCodeAttribute() { }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Using for NameMapValue attributed code generation for social client. 
  /// Synced attribute code with NivalCLI.NameMaps
  /// </summary>
  [AttributeUsageAttribute( AttributeTargets.Field | AttributeTargets.Property | AttributeTargets.Class, Inherited = true, AllowMultiple = false )]
  public sealed class NameMapValueAttribute : DBAttribute
  {
    private string _name = string.Empty;
    private string _description = string.Empty;

    public NameMapValueAttribute() { }
    public NameMapValueAttribute( string name ) : this( name, null ) { }
    public NameMapValueAttribute( string name, string description )
    {
      _name = name;
      _description = description;
    }

    public string Name { get { return _name; } set { _name = value; } }
    public string Description { get { return _description; } set { _description = value; } }

    public override string ConstructorParameters
    {
      get
      {
        //[NameMapValue("Name","Desc")]
        if ( !string.IsNullOrEmpty( Description ) )
          return String.Format( "\"{0}\", \"{1}\"", Name, Description );

        //[NameMapValue("Name")]
        if ( !string.IsNullOrEmpty( Name ) )
          return String.Format( "\"{0}\"", Name );
        //[NameMapValue()]
        return string.Empty;
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class LuaPropertyAttribute : DBAttribute
  {
    public LuaPropertyAttribute() { }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class RenameTypeAttribute : DBAttribute
  {
    private readonly string newName = string.Empty;

    public RenameTypeAttribute( string newName ) { this.newName = newName; }
    public string NewName { get { return newName; } }

    public override string ConstructorParameters { get { return '\"' + newName + '\"'; } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class SimpleTypeAttribute : DBAttribute
  {
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class NonTerminalAttribute : DBAttribute
  {
    public NonTerminalAttribute() { }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class TraceArray2Attribute : DBAttribute
  {
    //public TraceArray2Attribute() { }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class EnumArrayAttribute : DBAttribute
  {
    public readonly Type enumType = null;
    public int MaxCount
    {
      get
      {
        return ( enumType == null && ( !( enumType.IsEnum ) ) ) ? 0 : Enum.GetValues( enumType ).Length;
      }
    }

    public EnumArrayAttribute( Type enumType ) { this.enumType = enumType; }

    public override string ConstructorParameters { get { return "typeof(" + enumType.Name + ")"; } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class MinMaxSizeAttribute : DBAttribute
  {
    public readonly int min = 0;
    public readonly int max = 0;

    public MinMaxSizeAttribute( int min, int max ) { this.min = min; this.max = max; }

    public override string ConstructorParameters { get { return String.Format( "{0}, {1}", min, max ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class FloatMinMaxAttribute : DBAttribute
  {
    public readonly float min = float.MinValue;
    public readonly float max = float.MaxValue;

    public FloatMinMaxAttribute( float min, float max ) { this.min = min; this.max = max; }

    public static void Check( float value, float min, float max )
    {
      if ( value < min && value > max )
        throw new InvalidProgramException( String.Format( "Value should be between {0} and {1}", min, max ) );
    }

    public override string ConstructorParameters { get { return String.Format( "{0}f, {1}f", min, max ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class IntMinMaxAttribute : DBAttribute
  {
    public readonly int min = Int32.MinValue;
    public readonly int max = Int32.MaxValue;

    public IntMinMaxAttribute( int min, int max ) { this.min = min; this.max = max; }

    public static void Check( int value, int min, int max )
    {
      if ( value < min && value > max )
        throw new InvalidProgramException( String.Format( "Value should be between {0} and {1}", min, max ) );
    }

    public override string ConstructorParameters { get { return String.Format( "{0}, {1}", min, max ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class IntMinAttribute : DBAttribute
  {
    public readonly int min = Int32.MinValue;

    public IntMinAttribute( int min ) { this.min = min; }

    public static void Check( int value, int min )
    {
      if ( value < min )
        throw new InvalidProgramException( String.Format( "Value should be greater than {0}", min ) );
    }

    public override string ConstructorParameters { get { return String.Format( "{0}", min ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class IntMaxAttribute : DBAttribute
  {
    public readonly int max = Int32.MaxValue;

    public IntMaxAttribute( int max ) { this.max = max; }

    public static void Check( int value, int max )
    {
      if ( value > max )
        throw new InvalidProgramException( String.Format( "Value should be less than {0}", max ) );
    }

    public override string ConstructorParameters { get { return String.Format( "{0}", max ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class FloatMinAttribute : DBAttribute
  {
    public readonly float min = float.MinValue;

    public FloatMinAttribute( float min ) { this.min = min; }

    public static void Check( float value, float min )
    {
      if ( value < min )
        throw new InvalidProgramException( String.Format( "Value should be greater than {0}", min ) );
    }

    public override string ConstructorParameters { get { return String.Format( "{0}f", min ); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class CommentAttribute : DBAttribute
  {
    private readonly string text = string.Empty;

    public CommentAttribute( string text ) { this.text = text; }

    public override string ConstructorParameters { get { return '\"' + text + '\"'; } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class IncludeAttribute : DBAttribute
  {
    public readonly string fileName = string.Empty;

    public IncludeAttribute( string fileName ) { this.fileName = fileName; }

    public override string ConstructorParameters { get { return '\"' + fileName + '\"'; } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class AbstractAttribute : DBAttribute
  {
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class NeedEqualOperatorAttribute : DBAttribute
  {
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class NeedAssignOperatorAttribute : DBAttribute
  {
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class SrcFileAttribute : DBAttribute
  {
    private readonly string description;
    private readonly string extensions;
    private readonly string sourceFolder = string.Empty;

    public SrcFileAttribute() { }

    public SrcFileAttribute( string _description, string _extensions )
    {
      if ( !new Regex( @"^\s*\*\.[\w\d]+\s*(?:\s*;\s*\*\.[\w\d]+)*$" ).IsMatch( _extensions ?? string.Empty ) )
      {
        throw new InvalidProgramException( "Extensions should be in valid format." );
      }
      description = _description ?? string.Empty;
      extensions = _extensions;
    }

    public SrcFileAttribute( string _description, string _extensions, string _sourceFolder )
    {
      if ( !new Regex( @"^\s*\*\.[\w\d]+\s*(?:\s*;\s*\*\.[\w\d]+)*$" ).IsMatch( _extensions ?? string.Empty ) )
      {
        throw new InvalidProgramException( "Extensions should be in valid format." );
      }
      description = _description ?? string.Empty;
      extensions = _extensions;
      sourceFolder = _sourceFolder ?? string.Empty;
    }

    public string Description
    {
      get { return description; }
    }

    public string Extensions
    {
      get { return extensions; }
    }

    public string SourceFolder
    {
      get { return sourceFolder; }
    }

    public override string ConstructorParameters
    {
      get
      {
        if ( sourceFolder != string.Empty )
        {
          return string.Format( "\"{0}\", \"{1}\", \"{2}\"", description, extensions, sourceFolder );
        }
        else
        {
          return string.Format( "\"{0}\", \"{1}\"", description, extensions );
        }
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class DstFileAttribute : DBAttribute
  {
    private readonly string extension;

    public DstFileAttribute( string _extension )
    {
      if ( !new Regex( @"^\s*[\w\d]+\s*$" ).IsMatch( _extension ) )
      {
        throw new InvalidProgramException( "Extension should be in valid format." );
      }
      extension = _extension;
    }

    public string Extension
    {
      get { return extension; }
    }

    public override string ConstructorParameters
    {
      get { return string.Format( "\"{0}\"", extension ); }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class DstFileArgAttribute : DBAttribute
  {
    private readonly int position;

    public DstFileArgAttribute( int _position )
    {
      if ( _position < 0 )
      {
        throw new InvalidProgramException( "Position should be greater of equal to 0." );
      }
      position = _position;
    }

    public int Position
    {
      get { return position; }
    }

    public override string ConstructorParameters
    {
      get { return position.ToString(); }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class CrapTypeNameAttribute : DBAttribute
  {
    private readonly string name;

    public CrapTypeNameAttribute( string _name )
    {
      name = _name;
    }

    public string Name
    {
      get { return name; }
    }

    public override string ConstructorParameters
    {
      get { return string.Format( "\"{0}\"", name ); }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class TypeIdAttribute : DBAttribute
  {
    private readonly uint id = 0xFFFFFFFF;

    public TypeIdAttribute() { }
    public TypeIdAttribute( uint id ) { this.id = id; }

    public uint ID { get { return id; } }
    public bool HasID { get { return id != 0xFFFFFFFF; } }

    public override string ConstructorParameters { get { return HasID ? string.Format( "0x{0:X8}", id ) : base.ConstructorParameters; } }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class UseTypeNameAttribute : DBAttribute
  {
    public readonly string alias = string.Empty;

    public UseTypeNameAttribute() { }
    public UseTypeNameAttribute( string alias ) { this.alias = alias; }

    public override string ConstructorParameters { get { return string.IsNullOrEmpty( alias ) ? base.ConstructorParameters : "\"" + alias + "\""; } }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class GenerateChangedEventAttribute : DBAttribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class )]
  public sealed class BaseMaterialTypeAttribute : DBAttribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class )]
  public sealed class StateTypeAttribute : DBAttribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public enum Pin2
  {
    Runtime,
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class Pin2Attribute : DBAttribute
  {
    public const bool Runtime = true;

    private readonly string exposeName = string.Empty;
    private readonly bool isRuntime = false;

    public Pin2Attribute() { }
    public Pin2Attribute( string exposeName ) { this.exposeName = exposeName; }
    public Pin2Attribute( Pin2 pin ) { this.isRuntime = true; }

    public bool IsRuntime { get { return isRuntime; } }
    public string ExposeName { get { return exposeName; } }

    public override string ConstructorParameters { get { return IsRuntime ? typeof( Pin2 ).Name + Pin2.Runtime.ToString() : string.IsNullOrEmpty( ExposeName ) ? string.Empty : "\"" + ExposeName + "\""; } }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class SamplerAttribute : DBAttribute
  {
    private readonly int samplerIndex = 0;
    private readonly string exposeName = string.Empty;
    private readonly bool canBeVisualDegrade = false;

    public SamplerAttribute( int samplerIndex ) { this.samplerIndex = samplerIndex; }
    public SamplerAttribute( int samplerIndex, string exposeName ) { this.samplerIndex = samplerIndex; this.exposeName = exposeName; }
    public SamplerAttribute( int samplerIndex, string exposeName, bool canBeVisualDegrade ) : this( samplerIndex, exposeName ) { this.canBeVisualDegrade = canBeVisualDegrade; }
    public SamplerAttribute( int samplerIndex, bool canBeVisualDegrade ) { this.samplerIndex = samplerIndex; this.canBeVisualDegrade = canBeVisualDegrade; }

    public int SamplerIndex { get { return samplerIndex; } }
    public string ExposeName { get { return exposeName; } }
    public bool CanBeVisualDegrade { get { return canBeVisualDegrade; } }

    public override string ConstructorParameters
    {
      get
      {
        return SamplerIndex.ToString() +
        ( string.IsNullOrEmpty( ExposeName ) ? string.Empty : ", \"" + ExposeName + "\"" ) +
        ( CanBeVisualDegrade ? ", " + CanBeVisualDegrade.ToString().ToLower() : string.Empty );
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class, AllowMultiple = true )]
  public sealed class MaterialGroupAttribute : DBAttribute
  {
    private readonly string groupName = string.Empty;
    private readonly string baseGroupName = string.Empty;

    public MaterialGroupAttribute( string groupName )
    {
      this.groupName = groupName;
    }

    public MaterialGroupAttribute( string groupName, string baseGroupName )
    {
      this.groupName = groupName;
      this.baseGroupName = baseGroupName;
    }

    public string GroupName { get { return groupName; } }
    public string BaseGroupName { get { return baseGroupName; } }

    public override string ConstructorParameters
    {
      get
      {
        if ( string.IsNullOrEmpty( BaseGroupName ) )
          return "\"" + GroupName + "\"";
        else
          return "\"" + GroupName + "\", " + "\"" + BaseGroupName + "\"";
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class, AllowMultiple = true )]
  public sealed class MaterialFuncAttribute : DBAttribute
  {
    private readonly string includeFileName = string.Empty;
    private readonly string[] functions = null;

    public MaterialFuncAttribute( string includeFileName, params string[] functions )
    {
      this.includeFileName = includeFileName;
      this.functions = functions;
    }

    public string IncludeFileName { get { return includeFileName; } }
    public IEnumerable<string> Functions { get { return functions; } }

    public override string ConstructorParameters
    {
      get
      {
        if ( ( functions == null || functions.Length == 0 ) )
          return "\"" + IncludeFileName + "\"";
        else
        {
          List<string> formattedFunctions = new List<string>();
          foreach ( string function in Functions )
            formattedFunctions.Add( "\"" + function + "\"" );
          return "\"" + IncludeFileName + "\", " + string.Join( ", ", formattedFunctions.ToArray() );
        }
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class )]
  public sealed class IndexFieldAttribute : DBAttribute
  {
    private readonly string fieldName = string.Empty;
    private readonly bool hideItemIndex = false;
    private readonly string constructorParams = string.Empty;

    public IndexFieldAttribute( string fieldName )
    {
      this.fieldName = fieldName;
      constructorParams = string.Format( "\"{0}\"", fieldName );
    }

    public IndexFieldAttribute( string fieldName, bool hideItemIndex )
    {
      this.fieldName = fieldName;
      this.hideItemIndex = hideItemIndex;
      constructorParams = string.Format( "\"{0}\", {1}", fieldName, hideItemIndex ? "true" : "false" );
    }

    public string FieldName { get { return fieldName; } }
    public bool HideItemIndex { get { return hideItemIndex; } }

    public override string ConstructorParameters
    {
      get { return constructorParams; }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Field | AttributeTargets.Property )]
  public sealed class NonSignificantFieldAttribute : DBAttribute
  {

  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class, AllowMultiple = true )]
  public sealed class FactoryBaseAttribute : DBAttribute
  {
    private readonly string factoryFunctionName = string.Empty;
    private readonly string baseClassName = string.Empty;
    private readonly string[] args = null;

    public string ReturnType = string.Empty;
    public string Define = string.Empty;

    public FactoryBaseAttribute( string factoryFunctionName, string baseClassName, params string[] args )
    {
      this.factoryFunctionName = factoryFunctionName;
      this.baseClassName = baseClassName;
      this.args = args;
    }

    public string FactoryFunctionName { get { return factoryFunctionName; } }
    public string BaseClassName { get { return baseClassName; } }
    public string[] Args { get { return args; } }

    public string GetReturnType()
    {
      if ( string.IsNullOrEmpty( ReturnType ) )
        return BaseClassName + "*";
      else
        return ReturnType;
    }

    public override string ConstructorParameters
    {
      get
      {
        string result = "\"" + FactoryFunctionName + "\", \"" + BaseClassName + "\"";
        if ( Args != null && Args.Length > 0 )
          foreach ( string arg in Args )
            result += ", \"" + arg + "\"";

        if ( !string.IsNullOrEmpty( ReturnType ) )
          result += ", ReturnType = \"" + ReturnType + "\"";

        if ( !string.IsNullOrEmpty( Define ) )
          result += ", Define = \"" + Define + "\"";

        return result;
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class, AllowMultiple = true )]
  public sealed class FactoryImplAttribute : DBAttribute
  {
    private readonly string factoryFunctionName = string.Empty;
    private readonly string className = string.Empty;
    private readonly string[] includes = null;

    public string CreateFunction = string.Empty;

    public FactoryImplAttribute( string factoryFunctionName, string className, params string[] includes )
    {
      this.factoryFunctionName = factoryFunctionName;
      this.className = className;
      this.includes = includes;
    }

    public string FactoryFunctionName { get { return factoryFunctionName; } }
    public string ClassName { get { return className; } }
    public string[] Includes { get { return includes; } }

    public override string ConstructorParameters
    {
      get
      {
        string result = "\"" + FactoryFunctionName + "\", \"" + ClassName + "\"";
        if ( Includes != null && Includes.Length > 0 )
          foreach ( string include in Includes )
            result += ", \"" + include + "\"";

        if ( !string.IsNullOrEmpty( CreateFunction ) )
          result += ", CreateFunction = \"" + CreateFunction + "\"";

        return result;
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class )]
  public class PostInitializeAttribute : DBAttribute
  {
    public PostInitializeAttribute() { }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class HideInOutlinerAttribute : DBAttribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class )]
  public class HasStatesAttribute : DBAttribute
  {
    public HasStatesAttribute() { }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class )]
  public class DBVersionAttribute : DBAttribute
  {
    private readonly int version = 0;
    public DBVersionAttribute( int version ) { this.version = version; }

    public int Version { get { return version; } }
    public override string ConstructorParameters { get { return Version.ToString(); } }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class StoreTypeWithFieldAttribute : DBAttribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Class )]
  public sealed class DbRootAttribute : DBAttribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class DefaultValuesAttribute : DBAttribute
  {
    private readonly Type enumType = null;
    private readonly string[] values = null;

    public DefaultValuesAttribute( Type enumType )
    {
      this.enumType = enumType;
      FieldInfo[] fields = enumType.GetFields( BindingFlags.Public | BindingFlags.Static );
      values = new string[fields.Length];
      for ( int i = 0; i < fields.Length; ++i )
        values[i] = fields[i].Name;
    }

    public DefaultValuesAttribute( params string[] values )
    {
      this.values = values;
    }

    public string[] Values { get { return values; } }
    public override string ConstructorParameters
    {
      get
      {
        if ( enumType != null )
          return string.Format( "typeof( {0} )", enumType.Name );
        else if ( values != null && values.Length > 0 )
        {
          string result = "\"" + values[0] + "\"";
          for ( int i =1; i < values.Length; ++i )
            result += ", \"" + values[i] + "\"";
          return result;
        }

        return string.Empty;
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class HideEnumValuesAttribute : DBAttribute
  {
    private readonly string[] values;

    public HideEnumValuesAttribute( params string[] values )
    {
      this.values = values;
    }

    public override string ConstructorParameters
    {
      get
      {
        if ( values == null || values.Length == 0 )
          return "string.Empty";

        string result = "\"" + values[0] + "\"";
        for ( int i = 1; i < values.Length; ++i )
          result += ", \"" + values[i] + "\"";
        return result;
      }
    }

    public bool Contains( Enum value )
    {
      return Contains( value.ToString() );
    }

    public bool Contains( string _value )
    {
      foreach ( var value in values )
        if ( string.Compare( value, _value, true ) == 0 )
          return true;
      return false;
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class CustomAttribute : DBAttribute
  {
    private readonly string[] _names;

    public CustomAttribute( params string[] names ) { _names = names; }

    public bool IsMatch( string name )
    {
      foreach ( var _name in _names )
      {
        if ( _name == name )
          return true;
      }

      return false;
    }

    public override string ConstructorParameters
    {
      get
      {
        return string.Join( ", ", new List<string>( _names ).ConvertAll<string>( name => { return "\"" + name + "\""; } ).ToArray() );
      }
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class LocatorNameSelectorAttribute : Attribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public class AnimationScEventSelectorAttribute : Attribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class TypesSelectorAttribute : Attribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  public sealed class FolderSelectorAttribute : Attribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  public sealed class JointNamesSelectorAttribute : Attribute
  {
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// <summary>
  /// Список помеченный таким атрибутом нельзя модифицировать из PE или Outliner.
  /// Можно изменять сами элементы списка, но нельзя менять размер списка, т.е. удалять или добавлять в него элементы.
  /// </summary>
  public sealed class FixedList : Attribute
  {
  }

  [AttributeUsage( AttributeTargets.Property | AttributeTargets.Field )]
  public sealed class MultilineAttribute : Attribute
  {
  }

  /// <summary>
  /// Атрибут для Main ф-ций в исполняемых скриптах. При его наличие ScriptMachine
  /// позволяет вызов Main только в том же вызываемом файле, что указан в атрибуте
  /// </summary>
  [AttributeUsage( AttributeTargets.Method )]
  public sealed class ScriptAttribute : Attribute
  {
    private readonly string[] _names;

    public ScriptAttribute( params string[] names ) { _names = names; }

    public bool Contains( string name )
    {
      foreach ( var n in _names )
        if ( string.Compare( name, n, true ) == 0 )
          return true;
      return false;
    }
  }
}
