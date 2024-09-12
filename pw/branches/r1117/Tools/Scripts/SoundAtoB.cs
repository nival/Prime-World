/*
#about Move sounds from one object to another
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using libdb.DB;
using EditorLib.ObjectSelector;
using System.Collections;
using libdb.Diagnostics;
using EditorLib;
using EditorLib.Extensions;
using WeifenLuo.WinFormsUI.Docking;

public class HierarchyComponent
{
	public readonly DBTypes.DBSceneComponent owner;
	public readonly DBTypes.AttachedSceneComponent sound = new DBTypes.AttachedSceneComponent();

	public HierarchyComponent( DBTypes.DBSceneComponent owner, DBTypes.AttachedSceneComponent sound )
	{
		this.owner = owner;
		this.sound = sound;
	}
}

public class SoundsMover
{
	private List<HierarchyComponent> componentsA = new List<HierarchyComponent>();

	private void ProcessHierarcy( DBTypes.DBSceneComponent owner, libdb.IChangeableList<DBTypes.AttachedSceneComponent> sceneComponents, bool isA )
	{
		for ( int i = 0; i < sceneComponents.Count; i++ )
		{
			DBTypes.AttachedSceneComponent sceneComponent = sceneComponents[i];

			if ( sceneComponent.component == null || sceneComponent.component.Get() == null )
				continue;

			if ( sceneComponent.component.Get() is DBTypes.DBSoundSceneComponent )
			{
				if ( owner != null )
				{
					if ( isA )
						componentsA.Add( new HierarchyComponent( owner, sceneComponent ) );
					else
					{
						sceneComponents.RemoveAt( i );
						i--;
					}

				}
			}
			else
			{
				if ( sceneComponent.component.DBId.IsInlined )
				{
					ProcessHierarcy( sceneComponent.component.Get(), sceneComponent.component.Get().attached, isA );
				}
			}
		}
	}

	private bool TestForOneOwner()
	{
		if ( componentsA.Count == 0 )
			return false;

		DBTypes.DBSceneComponent mainowner = componentsA[0].owner;

		for ( int i = 1; i < componentsA.Count; i++ )
		{
			if ( mainowner != componentsA[i].owner )
				return false;
		}

		return true;
	}

	public bool Move( libdb.IChangeableList<DBTypes.AttachedSceneComponent> sceneComponents )
	{
		if ( sceneComponents.Count != 1 )
			return false;

		for ( int i = 0; i < componentsA.Count; i++ )
		{
			sceneComponents[0].component.Get().attached.Add( new DBTypes.AttachedSceneComponent() );
			DBTypes.AttachedSceneComponent attached = sceneComponents[0].component.Get().attached[sceneComponents[0].component.Get().attached.Count - 1];
			attached.Assign( componentsA[i].sound );
			if ( componentsA[i].sound.events.IsValid )
			{
				attached.events = DataBase.Create<DBTypes.EnableDisableSCEvents>( DBID.FromDBID( sceneComponents[0].component.DBId, true ), new DBTypes.EnableDisableSCEvents() );
				for ( int eventIdx = 0; eventIdx < componentsA[i].sound.events.Get().enableEvents.Count; eventIdx++ )
				{
					attached.events.Get().enableEvents.Add( DataBase.Create<DBTypes.SCEvent>( DBID.FromDBID( sceneComponents[0].component.DBId, true ), new DBTypes.AnimationSCEvent() ) );
					DBTypes.AnimationSCEvent animationEvent = attached.events.Get().enableEvents[attached.events.Get().enableEvents.Count - 1].Get<DBTypes.AnimationSCEvent>();
					animationEvent.type = ( componentsA[i].sound.events.Get().enableEvents[eventIdx].Get() as DBTypes.AnimationSCEvent ).type;
					animationEvent.name = ( componentsA[i].sound.events.Get().enableEvents[eventIdx].Get() as DBTypes.AnimationSCEvent ).name;
					animationEvent.animParam = ( componentsA[i].sound.events.Get().enableEvents[eventIdx].Get() as DBTypes.AnimationSCEvent ).animParam;
					animationEvent.probability = ( componentsA[i].sound.events.Get().enableEvents[eventIdx].Get() as DBTypes.AnimationSCEvent ).probability;
				}
			}
			if ( componentsA[i].sound.component.IsValid )
			{
				attached.component = DataBase.Create<DBTypes.DBSceneComponent>( DBID.FromDBID( sceneComponents[0].component.DBId, true ), new DBTypes.DBSoundSceneComponent() );
				DBTypes.DBSoundSceneComponent sound = attached.component.Get<DBTypes.DBSoundSceneComponent>();
				sound.desc.projectName = ( componentsA[i].sound.component.Get() as DBTypes.DBSoundSceneComponent ).desc.projectName;
				sound.desc.groupName = ( componentsA[i].sound.component.Get() as DBTypes.DBSoundSceneComponent ).desc.groupName;
				sound.desc.eventName = ( componentsA[i].sound.component.Get() as DBTypes.DBSoundSceneComponent ).desc.eventName;
				sound.caption = ( componentsA[i].sound.component.Get() as DBTypes.DBSoundSceneComponent ).caption;
			}
		}

		return true;
	}

	public SoundsMover( DBTypes.DBSceneObject sceneObjectFrom, DBTypes.DBSceneObject sceneObjectTo )
	{
		ProcessHierarcy( null, sceneObjectFrom.attached, true );
		if ( TestForOneOwner() )
		{
			ProcessHierarcy( null, sceneObjectTo.attached, false );
			if ( !Move( sceneObjectTo.attached ) )
			{
				Log.TraceWarning( "Error move sound components" );
			}
		}
		else
		{
			Log.TraceWarning( "Bad sound components hierarchy" );
		}
	}
}

public class SoundAtoB
{
	public IEnumerable Main( IEditorWinApplication app )
	{
		ObjectSelectorForm fromA = new ObjectSelectorForm();
		if ( fromA.ShowDialog() == DialogResult.OK )
		{
			ObjectSelectorForm toB = new ObjectSelectorForm();
			if ( toB.ShowDialog() == DialogResult.OK )
			{
				DBPtr<DBResource> fromAresource = DataBase.Get<DBResource>( fromA.SelectedObject );
				DBPtr<DBResource> toBresource = DataBase.Get<DBResource>( toB.SelectedObject );
				Log.TraceWarning( "From {0} to {1}", fromAresource.Get().DBId.GetFullFileName(), toBresource.Get().DBId.GetFullFileName() );
				if ( TypeUtils.IsSubclassOf( fromAresource.Get().GetType(), typeof( DBTypes.DBSceneObject ) )
					&& TypeUtils.IsSubclassOf( toBresource.Get().GetType(), typeof( DBTypes.DBSceneObject ) ) )
				{
					DataBase.UndoRedoManager.Start( "Moving from A to B" );
					SoundsMover objectA = new SoundsMover( fromAresource.Get() as DBTypes.DBSceneObject, toBresource.Get() as DBTypes.DBSceneObject );
					DataBase.UndoRedoManager.Commit();
					DataBase.Store();
				}
				else
				{
					Log.TraceWarning( "Invalid type (\"{0}\") of selected object", fromAresource.Get().GetType() );
					Log.TraceWarning( "Invalid type (\"{0}\") of selected object", toBresource.Get().GetType() );
				}

			}
		}

		yield return true;
	}
}
