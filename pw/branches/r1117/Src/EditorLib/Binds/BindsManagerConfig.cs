using System;
using System.Collections;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Xml;
using EditorLib.Settings;

namespace EditorLib.Binds
{
  [ConfigObject( true )]
  public sealed class BindsManagerConfig : IConfigObject
  {
    private Dictionary<string, Dictionary<string, List<BindConfig>>> sections = new Dictionary<string, Dictionary<string, List<BindConfig>>>();

    private const string SECTION = "section";
    private const string NAME = "name";
    private const string BIND = "bind";
    private const string CONFIG = "config";
    private const string DELTA_SPEED = "deltaSpeed";
    private const string MOUSE_AXIS = "mouseAxis";
    private const string MOUSE_BUTTONS = "mouseButtons";
    private const string INVERT_MOUSE = "invertMouse";
    private const string INVERT_KEY = "invertKey";
    private const string IGNORE_KEYS = "ignoreKeys";
    private const string KEYS = "keys";
    private const string KEY = "key";
    private const string BADKEYS = "badKeys";

    internal Dictionary<string, List<BindConfig>> this[string section]
    {
      get
      {
        if ( !string.IsNullOrEmpty( section ) && sections.ContainsKey( section ) )
        {
          return sections[section];
        }
        else
        {
          return new Dictionary<string, List<BindConfig>>();
        }
      }
      set
      {
        if ( !ReferenceEquals( value, null ) && !string.IsNullOrEmpty( section ) )
        {
          if ( sections.ContainsKey( section ) )
          {
            sections[section] = value;
          }
          else
          {
            sections.Add( section, value );
          }
        }
      }
    }

    #region IConfigObject Members

		public void Serialize( XmlWriter writer, libdb.DB.ConfigFile file )
    {
      XmlDocument doc = new XmlDocument();

      Operation<XmlNode, string, object> appendAttribute =
          ( node, name, value ) => node.Attributes.Append( doc.CreateAttribute( name ) ).Value = value.ToString();

      Function<XmlNode, XmlNode, string> appendChild = ( node, name ) => node.AppendChild( doc.CreateElement( name ) );

      var rootNode = appendChild( doc, GetType().Name );

      foreach ( var sectionName in sections.Keys )
      {
        var sectionNode = appendChild( rootNode, SECTION );
        appendAttribute( sectionNode, NAME, sectionName );
        foreach ( var bindName in sections[sectionName].Keys )
        {
          var bindNode = sectionNode.AppendChild( doc.CreateElement( BIND ) );
          appendAttribute( bindNode, NAME, bindName );
          foreach ( var bindConfig in sections[sectionName][bindName] )
          {
            var configNode = bindNode.AppendChild( doc.CreateElement( CONFIG ) );

            Operation<XmlNode, string, object> appendValueChild = ( node, name, value ) => appendChild( node, name ).InnerText = value.ToString();

            appendValueChild( configNode, DELTA_SPEED, bindConfig.deltaSpeed );
            appendValueChild( configNode, MOUSE_AXIS, bindConfig.mouseAxis );
            appendValueChild( configNode, MOUSE_BUTTONS, bindConfig.mouseButtons );
            appendValueChild( configNode, INVERT_MOUSE, bindConfig.invertMouse );
            appendValueChild( configNode, INVERT_KEY, bindConfig.invertKey );
            appendValueChild( configNode, IGNORE_KEYS, bindConfig.ignoreKeys );

            var keysNode = appendChild( configNode, KEYS );
            foreach ( var key in bindConfig.keys )
            {
              appendValueChild( keysNode, KEY, key );
            }

            var badkeysNode = appendChild( configNode, BADKEYS );
            foreach ( var key in bindConfig.badKeys )
            {
              appendValueChild( badkeysNode, KEY, key );
            }
          }
        }
      }

      doc.Save( writer );
    }

    public bool Deserialize( XmlReader reader )
    {
      XmlDocument doc = new XmlDocument();
      doc.Load( reader );

      Function<XmlNode, IEnumerable, string> findNode =
          ( enumerable, name ) =>
          {
            foreach ( XmlNode node in enumerable )
            {
              if ( node.Name == name )
              {
                return node;
              }
            }
            return null;
          };

      Function<XmlAttribute, XmlNode, string> findAttribute = ( node, name ) => findNode( node.Attributes, name ) as XmlAttribute;

      foreach ( XmlNode sectionNode in doc.DocumentElement.ChildNodes )
      {
        if ( sectionNode.Name == SECTION )
        {
          Predicate<object> notNull = obj => !ReferenceEquals( obj, null );

          var sectionNameAttribute = findAttribute( sectionNode, NAME );
          if ( notNull( sectionNameAttribute ) )
          {
            var sectionName = sectionNameAttribute.Value;
            var section = new Dictionary<string, List<BindConfig>>();
            foreach ( XmlNode bindNode in sectionNode.ChildNodes )
            {
              if ( bindNode.Name == BIND )
              {
                var bindNameAttribute = findAttribute( bindNode, NAME );
                if ( notNull( bindNameAttribute ) )
                {
                  var bindName = bindNameAttribute.Value;
                  var configs = new List<BindConfig>();
                  foreach ( XmlNode configNode in bindNode.ChildNodes )
                  {
                    if ( configNode.Name == CONFIG )
                    {
                      Function<XmlNode, XmlNode, string> findChild = ( node, childName ) => findNode( node.ChildNodes, childName );

                      Operation<string, Operation<string>> tryPerform =
                          ( name, operation ) =>
                          {
                            var child = findChild( configNode, name );
                            if ( notNull( child ) )
                            {
                              try
                              {
                                operation( child.InnerText );
                              }
                              catch ( Exception )
                              {
                                // Ignore.
                              }
                            }
                          };

                      var config = new BindConfig();

                      tryPerform( DELTA_SPEED, text => config.deltaSpeed = Convert.ToSingle( text ) );
                      tryPerform( MOUSE_AXIS, text => config.mouseAxis = (MouseAxis)Enum.Parse( typeof( MouseAxis ), text ) );
                      tryPerform( MOUSE_BUTTONS, text => config.mouseButtons = (MouseButtons)Enum.Parse( typeof( MouseButtons ), text ) );
                      tryPerform( INVERT_MOUSE, text => config.invertMouse = Convert.ToBoolean( text ) );
                      tryPerform( INVERT_KEY, text => config.invertKey = Convert.ToBoolean( text ) );
                      tryPerform( IGNORE_KEYS, text => config.ignoreKeys = Convert.ToBoolean( text ) );

                      var keysNode = findChild( configNode, KEYS );
                      if ( notNull( keysNode ) )
                      {
                        foreach ( XmlNode keyNode in keysNode.ChildNodes )
                        {
                          if ( keyNode.Name == KEY )
                          {
                            try
                            {
                              config.keys.Add( (Keys)Enum.Parse( typeof( Keys ), keyNode.InnerText ) );
                            }
                            catch
                            {
                              // Ignore.
                            }
                          }
                        }
                      }

                      var badkeysNode = findChild( configNode, BADKEYS );
                      if ( notNull( badkeysNode ) )
                      {
                        foreach ( XmlNode keyNode in badkeysNode.ChildNodes )
                        {
                          if ( keyNode.Name == KEY )
                          {
                            try
                            {
                              config.badKeys.Add( (Keys)Enum.Parse( typeof( Keys ), keyNode.InnerText ) );
                            }
                            catch
                            {
                              // Ignore.
                            }
                          }
                        }
                      }

                      configs.Add( config );
                    }
                  }

                  if ( configs.Count > 0 )
                  {
                    section.Add( bindName, configs );
                  }
                }
              }
            }

            if ( section.Count > 0 )
            {
              sections.Add( sectionName, section );
            }
          }
        }
      }

      return true;
    }

    #endregion





	}
}
