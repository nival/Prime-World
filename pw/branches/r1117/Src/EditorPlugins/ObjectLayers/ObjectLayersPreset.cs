using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Xml.Serialization;
using DBTypes;
using EditorLib.Extensions;
using libdb.DB;

namespace EditorPlugins.ObjectLayers
{
  [Serializable]
  public class ObjectLayersPreset
  {
    public ObjectLayersPreset()
    {
      Enabled = true;
      Selectable = true;
      Types = new List<Type>();
      Paths = new List<ObjectLayersPath>();
    }

    public string Name { get; set; }
    
    [TypesSelector, HideInOutliner] 
    public List<Type> Types { get; set; }
    
    public string ScriptGroupName { get; set; }

    [SupressValueEditor, HideInOutliner]
    public List<ObjectLayersPath> Paths { get; set; }

    [Browsable( false )]
    public bool Enabled { get; set; }

    [Browsable( false )]
    public bool Selectable { get; set; }

    [XmlIgnore, Browsable( false )]
    public bool IsEmpty
    {
      get
      {
        return ( Types == null || Types.Count == 0 ) && 
               string.IsNullOrEmpty( ScriptGroupName ) &&
               ( Paths == null || Paths.Count == 0 );
      }
    }

    public bool IsObjectInPreset( Dictionary<DBID, List<AdvMapObject>> advMapObjects, GameObject gameObject, string scriptGroupName )
    {
      if ( IsEmpty )
        return false;

      if ( !IsValidPath( Paths, gameObject.DBId ) )
        return false;

      if ( !IsValidScriptGroupName( ScriptGroupName, gameObject.DBId, advMapObjects, scriptGroupName ) )
        return false;

      if ( !IsValidType( Types, gameObject ) )
        return false;

      return true;
  }

    private bool IsValidPath( List<ObjectLayersPath> paths, DBID dbId )
    {
      if ( paths == null || paths.Count == 0 )
        return true;//если путь пустой, то мы показываем все объекты

      foreach ( ObjectLayersPath path in paths )
      {
        if ( dbId.FileName.ToLower().Contains( path.Path.ToLower() ) )
          return true;
      }

      return false;
    }

    private bool IsValidScriptGroupName( string scriptGroupName, DBID dbId, Dictionary<DBID, List<AdvMapObject>> advMapObjects, string realScriptGroupName )
    {
      if ( string.IsNullOrEmpty( scriptGroupName ) )
        return true;

      if ( advMapObjects.ContainsKey( dbId ) )
      {
        if ( scriptGroupName == realScriptGroupName )
          return true;
      }
      return false;
    }

    private bool IsValidType( ICollection<Type> types, GameObject go )
    {
      if ( types == null || types.Count == 0 )
        return true;

      foreach ( Type type in types )
      {
        if ( go.GetType() == type )
          return true;
      }

      return false;
    } 
  }

  [FolderSelector]
  public class ObjectLayersPath
  {
    public string Path { get; set; }
  }
}
