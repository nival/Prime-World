/*
#about Cкрипт, который сделает анимации талантов прерываемыми с момента Х
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
	public class FixTalentsAnimation
	{
		private const string ROOT_DIR = @"/Heroes/";
		private const float NEW_WORK_TIME = 0.5f; //сек
		private const float DURATION = 0.1f; //сек
		private const float DURATION_FOR_CHANNELING = 0.3f; //сек
		private const float MIN_FROM = 0.5f; //сек

		#region Talents to Ignore

		private readonly List<string> ignore = new List<string>
		{
			"/Items/Talents/Class/FireFox/Ability3.TALENT",
			"/Items/Talents/Class/FireFox/Ability3_Upg1.TALENT",
			"/Items/Talents/Class/FireFox/Ability4.TALENT",
			"/Items/Talents/Class/FireFox/Ability4_Upg1.TALENT",
      "/Items/Talents/Class/Healer/Ability4.TALENT",
			"/Items/Talents/Class/Healer/Ability4_Upg1.TALENT",
			"/Items/Talents/Class/Highlander/Ability1.TALENT",
			"/Items/Talents/Class/Highlander/Ability1_Upg1.TALENT",
			"/Items/Talents/Class/Highlander/Ability4.TALENT",
			"/Items/Talents/Class/ManaWyrm/Ability2.TALENT",
			"/Items/Talents/Class/ManaWyrm/Ability2Upg.TALENT",
			"/Items/Talents/Class/ManaWyrm/Ability3.TALENT",
			"/Items/Talents/Class/ManaWyrm/Ability3Upg.TALENT",
			"/Items/Talents/Class/ManaWyrm/Ability4.TALENT",
			"/Items/Talents/Class/ManaWyrm/Ability4Upg.TALENT",
			"/Items/Talents/Class/Mowgli/Ability1.TALENT",
			"/Items/Talents/Class/Mowgli/Ability1Upg1.TALENT",
			"/Items/Talents/Class/Mowgli/Ability1Upg2.TALENT",
			"/Items/Talents/Class/Mowgli/Ability4.TALENT",
			"/Items/Talents/Class/Mowgli/Ability4Upg.TALENT",
			"/Items/Talents/Class/Night/Ability4.TALENT",
			"/Items/Talents/Class/Night/Ability4_Upg.TALENT",
			"/Items/Talents/Class/Ratcatcher/Ability1.TALENT",
			"/Items/Talents/Class/Ratcatcher/Ability1_3_Upg.TALENT",
			"/Items/Talents/Class/Ratcatcher/Ability4.TALENT",
			"/Items/Talents/Class/Ratcatcher/Ability4_Upg.TALENT",
			"/Items/Talents/Class/Rockman/Ability1.TALENT",
			"/Items/Talents/Class/Rockman/Ability1Upg.TALENT",
			"/Items/Talents/Class/Rockman/Ability4.TALENT",
			"/Items/Talents/Class/Rockman/Ability4Upg.TALENT",
			"/Items/Talents/Class/ThunderGod/Ability4.TALENT",
			"/Items/Talents/Class/ThunderGod/Ability4Upg.TALENT",
			"/Items/Talents/Class/Unicorn/Ability4.TALENT",
			"/Items/Talents/Class/Unicorn/Ability4Upg.TALENT",
			"/Items/Talents/Class/Faceless/Ability4_Upg1.TALENT",
			"/Items/Talents/Class/Faceless/Ability3.TALENT",
			"/Items/Talents/Class/Faceless/Ability3_Upg1.TALENT",
			"/Items/Talents/Class/Faceless/Ability3_Upg2.TALENT",
			"/Items/Talents/Class/Faceless/Ability4.TALENT"
		};

		#endregion

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
			AnimGraphCreator animGraphCreator = GetAnimGraph(hero);
			if(animGraphCreator == null) return;

			IEnumerable<Animation> animations = GetAnimations(hero);

      foreach ( var _talentsSet in hero.defaultTalentsSets )
      {
        TalentsSet talentsSet = _talentsSet.Get();
        if ( talentsSet == null ) 
          continue;

        foreach ( TalentsLevel level in talentsSet.levels )
        {
          foreach ( TalentSlot talentSlot in level.talents )
          {
            Talent talent = talentSlot.talent.Get();

            if ( talent == null )
              continue;

            if ( IgnoreTalent( talent ) )
            {
              //Log.TraceMessage( "Talent Ignored: {0}", talent.DBId );
              continue;
            }

            FixAGNode( animGraphCreator, animations, talent.node );

            talent.attackTimeOffset = ( talent.attackTimeOffset * talent.workTime ) / NEW_WORK_TIME;
            talent.workTime = NEW_WORK_TIME;
          }
        }
      }
		}

		private AnimGraphCreator GetAnimGraph(Hero _hero)
		{
			if ( _hero == null ) return null;

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

		private bool IgnoreTalent(Talent talent)
		{
			if ( !talent.DBId.FileName.ToLower().Contains( @"\items\talents\class" ) &&
					 !talent.DBId.FileName.ToLower().Contains( @"/items/talents/class" ) )
			{
				return true;
			}

			if(string.IsNullOrEmpty(talent.node))
				return true;

			if(ignore.Exists(x => x.ToLower() == talent.DBId.FileName.ToLower()))
				return true;

			return false;
		}

		private void FixAGNode( AnimGraphCreator _animGraphCreator, IEnumerable<Animation> _animations, string _nodeName )
		{
			if ( string.IsNullOrEmpty( _nodeName ) )
			{
				Log.TraceError( "NodeName cant't be empty" );
				return;
			}

			//Find node
			foreach ( AnGrMacronode node in _animGraphCreator.macroNodes )
			{
				float animTime = GetAnimTime(node.sequenceName, _animations);

				if(animTime == 0)
					continue;

				if ( node.nodeName == _nodeName )
				{
					foreach ( AnGrFlMultiTransaction link in node.simpleTransactions )
					{
						if ( string.Equals( link.targetNode, "move", StringComparison.InvariantCultureIgnoreCase ) ||
							   string.Equals( link.targetNode, "attack", StringComparison.InvariantCultureIgnoreCase ) ||
							   link.targetNode.StartsWith( "ability", StringComparison.InvariantCultureIgnoreCase ) )
						{
							link.parameters.duration = DURATION;
							FixMinFrom( link, node, animTime );
						}
						else if ( string.Equals( link.targetNode, "channeling", StringComparison.InvariantCultureIgnoreCase ) )
						{
							link.parameters.duration = DURATION_FOR_CHANNELING;
							FixMinFrom(link, node, animTime);
						}
					}
				}
			}
		}

		private void FixMinFrom( AnGrFlMultiTransaction link, AnGrMacronode node, float animTime )
		{
			if ( node.startPar.value > link.parameters.fromMin.value )
				link.parameters.fromMin.value = node.startPar.value;
			else
				link.parameters.fromMin.value = MIN_FROM / animTime;
		}

		private float GetAnimTime(string sequenceName, IEnumerable<Animation> _animations)
		{
			float animTime = 0;

			//Find animation
			foreach ( Animation animation in _animations )
			{
				if ( animation.name == sequenceName )
				{
					if ( !TryGetAnimTime( application.FileSystem.GetRealFileName(animation.animationFileName), out animTime ) )
						return animTime;
					else
						break;
				}
			}

			return animTime;
		}

		private bool TryGetAnimTime(string filename, out float result)
		{
			result = 0;

			if ( !File.Exists( filename ) )
				return false;

			if ( Path.GetExtension(filename).ToLower() != ".anim" )
			{
				Log.AlwaysAssert("Invalid file extension");
				return false;
			}

			using ( FileStream stream = new FileStream( filename, FileMode.Open ) )
			{
				using ( BinaryReader reader = new BinaryReader( stream ) )
				{
					byte[] bytes = reader.ReadBytes( 4 );

					if(Encoding.ASCII.GetString(bytes) != "ANIM")
					{
						Log.AlwaysAssert( "It's not anim file format" );
						return false;
					}

					float minTime = reader.ReadSingle();

					if(minTime != 0)
					{
						Log.AlwaysAssert( "minTime is not 0" );
						return false;
					}

					float maxTime = reader.ReadSingle();

					result = maxTime - minTime;

					Log.Assert( result != 0, "Animation time = 0");
				}
			}

			return true;
		}
	}
}
