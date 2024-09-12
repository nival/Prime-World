/*
#about Cкрипт для проставления маркеров workTime в абилках
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;

namespace Scripts
{
	public class SetWorkTimeMarkers
	{
		private const string ROOT_DIR = @"/Heroes/";

		private IEditorCommonApplication application = null;

		public IEnumerable Main( IEditorCommonApplication app )
		{
			application = app;

			List<DBID> types;
			ObjectsSelector.CollectObjects( application, ROOT_DIR, typeof( Hero ), true, true, out types );

			foreach ( DBID dbid in types )
			{
				Hero hero = DataBase.Get<Hero>( dbid ).Get();

				if ( hero != null )
					FixHeroTalents( hero );
			}

			DataBase.Store();

			yield return true;
		}

		private void FixHeroTalents( Hero hero )
		{
			AnimGraphCreator animGraphCreator = GetAnimGraph( hero );
			if ( animGraphCreator == null )
				return;

			IEnumerable<Animation> animations = GetAnimations( hero );

			foreach ( var _talentsSet in hero.defaultTalentsSets )
			{
				TalentsSet talentsSet = _talentsSet.Get();
				if ( talentsSet == null )
					return;

				foreach ( TalentsLevel level in talentsSet.levels )
				{
					foreach ( TalentSlot talentSlot in level.talents )
					{
						Talent talent = talentSlot.talent.Get();

						if ( talent == null )
							continue;

						SetMarker( animGraphCreator, talent.node, talent.workTime, animations );
					}
				}
			}
		}

		private AnimGraphCreator GetAnimGraph( Hero _hero )
		{
			if ( _hero == null )
				return null;

			DBAnimatedSceneComponent component = _hero.heroSceneObjects[0].Get().attached[0].component.Get() as DBAnimatedSceneComponent;

			AnimGraphCreator animGraphCreator = component.animGraph.Get();

			return animGraphCreator;
		}

		private IEnumerable<Animation> GetAnimations( Hero _hero )
		{
			if ( _hero == null )
				return new List<Animation>();

			DBAnimatedSceneComponent component = _hero.heroSceneObjects[0].Get().attached[0].component.Get() as DBAnimatedSceneComponent;

			if ( component == null )
				return new List<Animation>();

			return component.animations;
		}

		private void SetMarker( AnimGraphCreator _animGraphCreator, string _nodeName, float _workTime, IEnumerable<Animation> _animations )
		{
			if ( string.IsNullOrEmpty( _nodeName ) )
				return;

			if ( _workTime == 0.0f )
				return;

			//Find node
			for ( int i = 0; i < _animGraphCreator.macroNodes.Count; i++ )
			{
				AnGrMacronode node = _animGraphCreator.macroNodes[i];
				if ( node.nodeName == _nodeName )
				{
					float animTime = GetAnimTime( node.sequenceName, _animations );

					if ( animTime == 0 )
						continue;

					float virtPar = _workTime/animTime*node.speed.value;
					virtPar = Math.Max( 0.0f, virtPar );
					virtPar = Math.Min( 1.0f, virtPar );

					bool isFind = false;
					AnGrMarker findMarker = null;
					foreach( AnGrMarker marker in node.markers )
					{
						if ( marker.name.IndexOf( "workTime" ) != -1 )
						{
							isFind = true;
							findMarker = marker;
							break;
						}
					}
					if ( isFind )
					{
						findMarker.virtPar = virtPar;
					}
					else
					{
						AnGrMarker marker = new AnGrMarker();
						marker.name = "workTime" + GetNumber( node.nodeName );
						marker.virtPar = virtPar;
						node.markers.Add( marker );
					}
				}
			}
		}

		private string GetNumber( string _in )
		{
			string res = "";
			foreach ( char c in _in )
				if ( Char.IsDigit(c) )
					res += c;
			return res;
		}
		
		private float GetAnimTime( string sequenceName, IEnumerable<Animation> _animations )
		{
			float animTime = 0;

			//Find animation
			foreach ( Animation animation in _animations )
			{
				if ( animation.name == sequenceName )
				{
					if ( !TryGetAnimTime( application.FileSystem.GetRealFileName( animation.animationFileName ), out animTime ) )
						return animTime;
					else
						break;
				}
			}

			return animTime;
		}

		private bool TryGetAnimTime( string filename, out float result )
		{
			result = 0;

			if ( !File.Exists( filename ) )
				return false;

			if ( Path.GetExtension( filename ).ToLower() != ".anim" )
			{
				Log.AlwaysAssert( "Invalid file extension" );
				return false;
			}

			using ( FileStream stream = new FileStream( filename, FileMode.Open ) )
			{
				using ( BinaryReader reader = new BinaryReader( stream ) )
				{
					byte[] bytes = reader.ReadBytes( 4 );

					if ( Encoding.ASCII.GetString( bytes ) != "ANIM" )
					{
						Log.AlwaysAssert( "It's not anim file format" );
						return false;
					}

					float minTime = reader.ReadSingle();

					if ( minTime != 0 )
					{
						Log.AlwaysAssert( "minTime is not 0" );
						return false;
					}

					float maxTime = reader.ReadSingle();

					result = maxTime - minTime;

					Log.Assert( result != 0, "Animation time = 0" );
				}
			}

			return true;
		}
	}
}
