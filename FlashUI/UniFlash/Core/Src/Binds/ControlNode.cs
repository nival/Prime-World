using System;
using System.Collections.Generic;
using System.Reflection;
using System.Xml;
using UnityEngine;

#if UNITY_EDITOR

#endif

namespace Flash
{
  public class ControlNode
  {
    private readonly string _controlName;
    public string ControlName
    {
      get { return _controlName; }
    }
    private readonly FieldInfo _field;
    public FieldInfo Field
    {
      get { return _field; }
    }
    private readonly ControlNode _parent;
    public ControlNode Parent
    {
      get { return _parent; }
    }
    private readonly Type _type;
    public Type Type
    {
      get { return _type; }
    }
    //Average nodes count per object is 15
    private List<ControlNode> _children = null; //new List<ControlNode>(15);
    private InteractiveObject _bind;
    public InteractiveObject Bind
    {
      get { return _bind; }
      set
      {
        if ( _bind == null )
          _bind = value;
      }
    }
    private readonly int _framesCount = -1;
    private string _linkError;
    private bool _isRoot;

    public ControlNode( string name, ControlNode parent, Type type, FieldInfo fieldInfo, int framesCount )
    {
      _controlName = name;
      _parent = parent;
      _type = type;
      _field = fieldInfo;
      _framesCount = framesCount;
    }
    public void AddNode( ControlNode node )
    {
      if ( !CheckRecursivedLink( node ) )
      {
        _linkError = "RECURSIVED LINK ERROR : " + "[" + node.ControlName + "] " + node.Field.FieldType + " " + node.Field.Name;
        Debug.LogError( "CONTROLS TREE ASSERT : Recursived link in controls tree founded , see " + FlashEnv.PATH_TO_XML_TREES );
        return;
      }
      if ( _children == null )
        _children = new List<ControlNode>();
      _children.Add( node );
    }
#if UNITY_EDITOR
    public void AppendNodeToBuilder( XmlWriter xmlWriter )
    {
      xmlWriter.WriteStartElement( "node" );

      xmlWriter.WriteAttributeString( "name", _isRoot ? _type.Name : _controlName );
      if ( _field == null )
      {
        xmlWriter.WriteAttributeString( "type", _type.Name );
      }
      else
      {
        xmlWriter.WriteAttributeString( "type", _field.FieldType.Name );
        xmlWriter.WriteAttributeString( "field", _field.Name );
      }
      if ( _framesCount != -1 )
      {
        xmlWriter.WriteAttributeString( "framesCount", _framesCount.ToString() );
      }

      if ( !string.IsNullOrEmpty( _linkError ) )
        xmlWriter.WriteComment( _linkError );

      if ( _children != null )
      {
        for ( int i = 0; i < _children.Count; i++ )
          _children[i].AppendNodeToBuilder( xmlWriter );
      }

      xmlWriter.WriteEndElement();
    }
#endif
    public ControlNode FindNode( string name )
    {
      if ( _children == null )
        return null;

      for ( int i = 0; i < _children.Count; i++ )
      {
        if ( _children[i].ControlName == name )
          return _children[i];
      }

      return null;
    }
    public bool IsBinded()
    {
      return _bind != null;
    }
    public void ValidateBind()
    {
      if ( !IsBinded() )
      {
        String path = GetPath();
        Debug.LogError( "BIND WARNING: Node " + path + " is not binded!" );
      }
      else
      {
        if ( _framesCount != -1 && Bind is MovieClip && _framesCount > ( (MovieClip)Bind ).TotalFrames )
        {
          String path = GetPath();
          Debug.LogError( "BIND WARNING: Node " + path + " has less frames count " + ( (MovieClip)Bind ).TotalFrames + " declared " + _framesCount + " !" );
        }
      }
    }
    public void ValidateBindChildren()
    {
      ValidateBind();
      if ( _children != null )
      {
        for ( int i = 0; i < _children.Count; i++ )
          _children[i].ValidateBindChildren();
      }
    }
    public ControlNode Instantiate()
    {
      ControlNode instance = InstantiateInternal( _parent );
      return instance;
    }
    public void ReleaseBind()
    {
      _bind = null;
    }
    public void ReleaseBindChildren()
    {
      ReleaseBind();
      if ( _children != null )
      {
        for ( int i = 0; i < _children.Count; i++ )
          _children[i].ValidateBindChildren();
      }
    }
    public string GetPath()
    {
      ControlNode current = this;
      string path = "";
      while ( current != null )
      {
        path = "/" + ( !string.IsNullOrEmpty( current._controlName ) ? current._controlName : "__ROOT" ) + path;
        current = current.Parent;
      }
      path = path.Remove( 0, 1 );
      return path;
    }
    public void SetAsRoot()
    {
      _isRoot = true;
    }

    private ControlNode InstantiateInternal( ControlNode parent )
    {
      ControlNode instance = new ControlNode( _controlName, parent, _type, _field, _framesCount );
      if ( _children != null )
      {
        instance._children = new List<ControlNode>( _children.Count );

        for ( int i = 0; i < _children.Count; i++ )
        {
          ControlNode newChild = _children[i].InstantiateInternal( instance );
          instance._children.Add( newChild );
        }
      }

      return instance;
    }
    private bool CheckRecursivedLink( ControlNode node )
    {
      if ( _type == node.Type )
        return false;

      if ( _parent != null )
      {
        if ( !_parent.CheckRecursivedLink( node ) )
          return false;
      }

      return true;
    }
  }
}
