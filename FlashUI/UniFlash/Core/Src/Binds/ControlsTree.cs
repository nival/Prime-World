using System;
using System.Collections.Generic;
using System.Reflection;
using System.Text;
using System.Xml;
using UnityEngine;

namespace Flash
{
	public class ControlsTree
	{
		private ControlNode _root;
		public ControlNode Root
		{
			get { return _root; }
		}
		private bool _writeToXml;

		public ControlsTree(ControlNode root,bool writeToXml)
		{
			_root = root;
		  _root.SetAsRoot();
			_writeToXml = writeToXml;
			CreateFieldControlNode(root.Type, root);
		}
#if UNITY_EDITOR
		public void DampTree()
		{
      if (_writeToXml)
      {
        XmlTextWriter xmlWriter = new XmlTextWriter(FlashEnv.PATH_TO_XML_TREES + _root.Type.Name + ".xml", Encoding.UTF8);
        xmlWriter.Formatting = Formatting.Indented;
        xmlWriter.WriteStartDocument();

        try
        {
          _root.AppendNodeToBuilder(xmlWriter);
        }
        finally
        {
          xmlWriter.Close();
        }
      }
		}
#endif

		private static void CreateFieldControlNode( Type type, ControlNode parent )
		{
            Type tempType = type;
            List<FieldInfo> flattenFields = new List<FieldInfo>();
            BindingFlags flag = BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public;
            while (tempType != typeof(MovieClip))
            {
                FieldInfo[] typeFields = tempType.GetFields(flag);
                foreach (FieldInfo typeField in typeFields)
                {
                    if(!flattenFields.Exists(item => item.Name == typeField.Name))
                    {
                        flattenFields.Add(typeField);
                    }
                }

                // Further only private base fields
                flag = BindingFlags.Instance | BindingFlags.NonPublic;
                tempType = tempType.BaseType;

                if (tempType == null)
                    break;
            }

            foreach (FieldInfo field in flattenFields)
			{
				if ( field.FieldType.IsSubclassOf( typeof( InteractiveObject ) ) )
				{
					BindAttribute[] fieldAttr = field.GetCustomAttributes( typeof( BindAttribute ), false ) as BindAttribute[];

					FramesCountConstraintAttribute[] framesFieldAttr = field.GetCustomAttributes(typeof(FramesCountConstraintAttribute), true) as FramesCountConstraintAttribute[];
					FramesCountConstraintAttribute[] framesClassAttr = field.FieldType.GetCustomAttributes(typeof(FramesCountConstraintAttribute), false) as FramesCountConstraintAttribute[];
					
					if ( fieldAttr != null && fieldAttr.Length > 0 )
					{
						int framesCount = -1;
						if(framesClassAttr!=null && framesClassAttr.Length>0)
						{
							framesCount = framesClassAttr[0].FramesCount;
						}
						if(framesFieldAttr!=null && framesFieldAttr.Length >0)
						{
							framesCount = framesFieldAttr[0].FramesCount;
						}

						ControlNode node = new ControlNode(fieldAttr[0].TargenControl, parent, field.FieldType, field, framesCount);
						try
						{
							parent.AddNode( node );
							CreateFieldControlNode( field.FieldType, node );
						}
                        catch ( Exception e )
                        {
                            Debug.LogError( e.Message );
                        }
					}
				}
			}
		}	
	}
}