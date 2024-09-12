using System;
using System.Collections.Generic;
using System.ComponentModel;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public sealed class AnimationSCEventStandardValuesProvider : TwoTypedStandardValuesProvider<string, AnimationScEventSelectorAttribute>
  {
    public AnimationSCEventStandardValuesProvider( IEditorWinApplication application, Attribute attribute ) : base( application, attribute ) { }

    public override bool HasStandardValuesConvertor( ITypeDescriptorContext context )
    {
      return false;
    }

    protected override string ConvertFromStandardValueInternal( ITypeDescriptorContext context, object instance, object value )
    {
      return value as string;
    }

    public override bool IsStandardValuesExclusive( ITypeDescriptorContext context )
    {
      return false;
    }

    public override Type GetStandardValuesType( ITypeDescriptorContext context )
    {
      return typeof( string );
    }

    public override TypeConverter.StandardValuesCollection GetStandardValues( ITypeDescriptorContext context )
    {
      AnimationSCEvent animationScEvent = FullTypePropertyDescriptor.GetInstanceFromContext( context ) as AnimationSCEvent;

      List<string> result = CreateEventsList( animationScEvent );

      return new TypeConverter.StandardValuesCollection( result );
    }

    #region List Creating

    //все ноды/маркеры для всех графов, на которые есть беклинки
    private Dictionary<string, int> itemsDictionary = new Dictionary<string, int>(); //имя, счетчик
    private int componentsWithGraph = 0;//количество компонент с анимграфом

    private List<string> CreateEventsList( AnimationSCEvent animationScEvent )
    {
      List<string> result = new List<string>();

      if( animationScEvent == null || !animationScEvent.DBId.IsInlined )
        return result;

      itemsDictionary.Clear();
      componentsWithGraph = 0;

      DBPtr<DBResource> resourcePtr = DataBase.Get<DBResource>( DBID.FromDBID( animationScEvent.DBId, false ) );
      DBResource resource = resourcePtr.Get();

      if( resource is EnableDisableSCEvents )
      {
        Dictionary<DBID, int> backlinks = resourcePtr.GetBackLinks();
        Log.Assert( backlinks != null );

        foreach( DBID dbId in backlinks.Keys )
        {
          DBResource sceneObject = DataBase.Get<DBResource>( dbId );

          if( sceneObject is DBSceneObject )
            ProcessSceneObject( animationScEvent.type, ( sceneObject as DBSceneObject ).attached );
        }
      }
      else if( resource is DBSceneObject )
      {
        ProcessSceneObject( animationScEvent.type, ( resource as DBSceneObject ).attached );
      }

      foreach( KeyValuePair<string, int> item in itemsDictionary )
      {
        if( item.Value == componentsWithGraph )
          result.Add( item.Key );
      }

      result.Sort();

      return result;
    }

    private void ProcessSceneObject( EAnimEventType eventType, IEnumerable<AttachedSceneComponent> attaches )
    {
      foreach( AttachedSceneComponent attach in attaches )
      {
        DBAnimatedSceneComponent component = attach.component.Get() as DBAnimatedSceneComponent;
        if( component == null )
          continue;

        if( AnalizeComponent( eventType, component ) )
        {
          componentsWithGraph++;
        }
      }
    }

    private bool AnalizeComponent( EAnimEventType eventType, DBAnimatedSceneComponent component )
    {
      AnimGraphCreator anGr1 = component.additionalGraph.Get();
      AnimGraphCreator anGr2 = component.animGraph.Get();

      if(anGr1 == null && anGr2 == null)
        return false; //у компонента нету ни одного аним графа

      ProcessGraph(eventType, new[] { anGr1, anGr2 } );

      return true;
    }

    private void ProcessGraph(EAnimEventType type, AnimGraphCreator[] animGraphList )
    {
      List<string> nameList = new List<string>();

      foreach( AnimGraphCreator animGraph in animGraphList )
      {
        if(animGraph == null) continue;

        foreach( AnGrMacronode node in animGraph.macroNodes )
        {
          if(type == EAnimEventType.Marker)
            AddMarkerName( node, ref nameList );
          else
            AddNodeName( node, ref nameList );
        } 
      }

      foreach( string item in nameList )
      {
        if( !itemsDictionary.ContainsKey( item ) )
          itemsDictionary.Add( item, 1 );
        else
          itemsDictionary[item] += 1;
      }
    }

    private void AddNodeName(AnGrMacronode node, ref List<string> result)
    {
      if( !result.Contains( node.nodeName ) )
        result.Add( node.nodeName );
    }

    private void AddMarkerName( AnGrMacronode node, ref List<string> result )
    {
      foreach( AnGrMarker marker in node.markers )
      {
        if( !result.Contains( marker.name ) )
          result.Add( marker.name );
      }
    }

    #endregion
  }
}
