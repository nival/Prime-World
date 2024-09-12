using System;
using System.Collections.Generic;
using System.Reflection;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;

namespace EditorPlugins.Scene.Editors
{
  public abstract class EditorControlWidget 
  {
    private EditorControl editorControl = null;
    protected EditorControl EditorControl { get { return editorControl; } }

    public abstract bool IsSelected { get; }

    public EditorControlWidget( EditorControl editor )
    {
      editorControl = editor;
    }

    public abstract bool HasThisWidget( GameSceneObject target );

    public abstract void Create( GameSceneObject target );
    public abstract void Destroy();

    public abstract void Update();
  }


  [AttributeUsage( AttributeTargets.Class, AllowMultiple = false )]
  public sealed class EditorControlWidgetAttribute : Attribute
  {
    private Type targetType = null;
    public Type TargetType { get { return targetType; } }

    public EditorControlWidgetAttribute( Type type )
    {
      targetType = type;
    }
  }


  public class EditorControlWidgetCollection
  {
    private Dictionary<Type, List<Type>> widgets = new Dictionary<Type, List<Type>>();

    public bool HasWidgets( GameSceneObject gso )
    {
      var gameObject = gso.GetGameObject();

      if(gameObject != null)
      {
        return widgets.ContainsKey( gameObject.GetType() );
      }

      return false;
    }

    public List<Type> GetWidgets( GameSceneObject gso )
    {
      if(gso != null && HasWidgets( gso ))
      {
        return widgets[gso.GetGameObject().GetType()];
      }

      return new List<Type>();
    }

    public List<EditorControlWidget> CreateWidgets( EditorControl control, GameSceneObject gso )
    {
      List<EditorControlWidget> result = new List<EditorControlWidget>();

      if ( !HasWidgets( gso ) )
        return result;

      foreach ( Type type in widgets[gso.GetGameObject().GetType()] )
      {
        object obj = TypeUtils.CreateObject<EditorControl>( type, control );
        if ( obj != null && obj is EditorControlWidget )
        {
          if ( ( obj as EditorControlWidget ).HasThisWidget( gso ) )
            result.Add( obj as EditorControlWidget );
        }
      }

      return result;
    }

    public EditorControlWidgetCollection()
    {
      Assembly currentAssembly = Assembly.GetExecutingAssembly();
      Type[] allTypes = currentAssembly.GetTypes();

      foreach ( Type type in allTypes )
      {
        object[] attrs = type.GetCustomAttributes( typeof( EditorControlWidgetAttribute ), true );
        foreach ( object bareAttr in attrs )
        {
          EditorControlWidgetAttribute attr = bareAttr as EditorControlWidgetAttribute;
          if ( null == attr )
            continue;

          if ( !widgets.ContainsKey( attr.TargetType ) )
            widgets[attr.TargetType] = new List<Type>();

          widgets[attr.TargetType].Add( type );
          break;
        }
      }
    }
  }
}
