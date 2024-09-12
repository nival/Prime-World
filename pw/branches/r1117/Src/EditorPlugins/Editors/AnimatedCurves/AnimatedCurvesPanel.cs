using System.Collections.Generic;
using System.Reflection;
using DBTypes;
using EditorLib;
using EditorLib.Panels;
using libdb.Animated;
using libdb.DB;

namespace EditorPlugins.Editors.AnimatedCurves
{
	public partial class AnimatedCurvesPanel : EditorPanel
	{
		#region Nested Types

		private class DepthController
		{
			public bool Functor( object obj, ref int depth )
			{
				return ( obj != null ) && !( obj is AttachedSceneComponent ) && !( obj is IAnimated );
			}
		}

		private class AnimatedCollector
		{
			public class Info
			{
				public readonly IAnimated animated = null;
				public readonly DBFieldInfo field = null;

				public Info( IAnimated _animated, DBFieldInfo _field )
				{
					animated = _animated;
					field = _field;
				}
			}

			public Dictionary<string, List<Info>> targets = new Dictionary<string, List<Info>>();

			private object owner = null;
			private string caption = string.Empty;
			private int counter = 0;

			public bool Functor( ref object animated, DBFieldInfo field )
			{
				if ( animated == null )
					return true;

				if ( animated is IAnimated )
				{
					object curOwner = GetOwner( animated );

					if ( curOwner != owner )
					{
						caption = string.Format( "{0} ({1})", GetCaption( curOwner ), counter );
						targets.Add( caption, new List<Info>() );
						owner = curOwner;
						counter++;
					}

					targets[caption].Add( new Info( animated as IAnimated, field ) );
				}

				return true;
			}

			private static object GetOwner( object animated )
			{
				object result = null;

				if ( animated != null )
				{
					MethodInfo method = animated.GetType().GetMethod( "GetOwner" );

					if ( method != null )
						result = method.Invoke( animated, null );
				}

				return result;
			}

			private static string GetCaption( object owner )
			{
				if ( owner != null )
				{
					PropertyInfo pi = owner.GetType().GetProperty( "caption" );

					if ( pi != null )
						return pi.GetValue( owner, null ).ToString();
				}

				return string.Empty;
			}
		}

		#endregion

		private int trackCount = -1;

		public AnimatedCurvesPanel()
		{
			InitializeComponent();
		}

		protected override bool Initialize( IEditorWinApplication _application )
		{
			return animatedCurvesControl.Initialize( _application );
		}

    public override void Terminate( IEditorWinApplication application )
    {
      base.Terminate( application );
      animatedCurvesControl.Deinitialize();
    }

		private object selectedObject = null;
		public object SelectedObject
		{
			get { return selectedObject; }
			set
			{
				if ( selectedObject == value )
					return;

				selectedObject = value;

				AnimatedCurvesItem root = BuildTrackList( selectedObject );
				animatedCurvesControl.SetRoot( root );
			}
		}

		private AnimatedCurvesItem BuildTrackList( object _selectedObject )
		{
			if ( _selectedObject == null )
				return null;

			object target = _selectedObject;
			trackCount = -1;

			AnimatedCurvesItem root = new AnimatedCurvesItem( target.GetType().Name );

			if ( target is AttachedSceneComponent )
			{
				AttachedSceneComponent asc = (AttachedSceneComponent)target;

				DBSceneComponent sceneComponent = asc.component.Get();

				string caption = sceneComponent.caption;

				if ( !string.IsNullOrEmpty( caption ) )
					root.Text = caption;

				root.AddChild( GetTrsListItem( asc.placement ) );

				target = sceneComponent;
			}
			else if ( target is SceneObjectTrack )
			{
				SceneObjectTrack objectTrack = (SceneObjectTrack)target;

				string caption = objectTrack.name;

				if ( !string.IsNullOrEmpty( caption ) )
					root.Text = caption;

				root.AddChild( GetTrsListItem( objectTrack.placement ) );
				root.AddChild( new AnimatedCurvesItem( "opacity", objectTrack.opacity, 0, ++trackCount ) );

				target = null;
			}

			var depthController = new DepthController();
			var collector = new AnimatedCollector();
			FieldsWalker.VisitFields( target, collector.Functor, depthController.Functor );

			foreach ( var key in collector.targets )
			{
				string materialName = key.Key;

				AnimatedCurvesItem animatedCurvesItem1 = new AnimatedCurvesItem( materialName );
				root.AddChild( animatedCurvesItem1 );

				foreach ( var item in collector.targets[key.Key] )
				{
					string animatedName = item.field.Name;

					if ( item.animated.TracksCount == 1 )
					{
						AnimatedCurvesItem animatedCurvesItem = new AnimatedCurvesItem( animatedName, item.animated, 0, ++trackCount );
						animatedCurvesItem1.AddChild( animatedCurvesItem );
					}
					else
					{
						AnimatedCurvesItem animatedCurvesItem = new AnimatedCurvesItem( animatedName );
						animatedCurvesItem1.AddChild( animatedCurvesItem );

						AnimatedComplexConverterAttribute complexConverter = TypeUtils.GetAttribute<AnimatedComplexConverterAttribute>( item.animated.GetType(), true );

						for ( int i = 0; i < item.animated.TracksCount; ++i )
						{
							AnimatedCurvesItem leaf = new AnimatedCurvesItem( complexConverter.Args[i], item.animated, i, ++trackCount );
							animatedCurvesItem.AddChild( leaf );
						}
					}
				}
			}

			return root;
		}

		private AnimatedCurvesItem GetTrsListItem( AnimatedPlacement _placement )
		{
			return new AnimatedCurvesItem( "TRS", new List<AnimatedCurvesItem>
      {
        new AnimatedCurvesItem( "translateX", _placement.pos, 0, ++trackCount ),
        new AnimatedCurvesItem( "translateY", _placement.pos, 1, ++trackCount ),
        new AnimatedCurvesItem( "translateZ", _placement.pos, 2, ++trackCount ),
        new AnimatedCurvesItem( "rotateX", _placement.rot, 0, ++trackCount ),
        new AnimatedCurvesItem( "rotateY", _placement.rot, 1, ++trackCount ),
        new AnimatedCurvesItem( "rotateZ", _placement.rot, 2, ++trackCount ),
        new AnimatedCurvesItem( "scaleX", _placement.scale, 0, ++trackCount ),
        new AnimatedCurvesItem( "scaleY", _placement.scale, 1, ++trackCount ),
        new AnimatedCurvesItem( "scaleZ", _placement.scale, 2, ++trackCount )
      } );
		}
	}
}