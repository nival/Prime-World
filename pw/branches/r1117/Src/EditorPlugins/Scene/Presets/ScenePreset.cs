using System;
using System.Collections.Generic;
using System.Xml;
using EditorLib.Extensions;
using EditorLib.Settings;
using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Scene.Presets
{
	[ConfigObject( false, "ScenePreset" )]
	public abstract class ScenePreset : IConfigObject
	{
		public delegate void ScenePresetUpdatedHandle( ScenePreset preset );
		public event ScenePresetUpdatedHandle ScenePresetUpdated = null;

		private Dictionary<string, ScenePreset> presets = new Dictionary<string, ScenePreset>();
		private string name = string.Empty;

		public virtual List<string> GetLocators()
		{
			return null;
		}

		public virtual void AfterRebuild() { }
		public virtual void AddNoneObject( EditorSceneObject eso ) { }
		public abstract void Init( SimpleEditorScene _scene );
		public abstract void Release();
		public abstract void Rebuild();
		public abstract bool TestForCompatible( DBID _dbid );
		public abstract void SetMainObject( DBID resource, EditorSceneObject so );
		public abstract EditorSceneObject GetMainObject();
		public virtual void OnTimerTick( float time, float delta ) { }

		public virtual void SetControllers( AGController _agc1, AGController _agc2 ) {}
    
		public string GetName()
		{
			return name;
		}

		public void Updated()
		{
			if ( ScenePresetUpdated != null )
				ScenePresetUpdated( this );
		}

		public override string ToString()
		{
			if (string.IsNullOrEmpty(name))
			{
				return GetType().Name;
			}
			else
			{
				return name;
			}
		}

		public void Serialize( XmlWriter writer, libdb.DB.ConfigFile file )
		{
			writer.WriteStartElement( GetType().Name );
			XmlSerializer serialize = new SimpleRegisteringXmlSerializer( GetType() );
			serialize.Serialize( this, writer );
			serialize.Serialize( presets, writer );
			writer.WriteEndElement();
		}

		public bool Deserialize( XmlReader reader )
		{
			if ( reader.IsEmptyElement )
				reader.Skip();
			else
			{
				reader.ReadStartElement();
				if ( reader.NodeType != XmlNodeType.None )
				{
					XmlSerializer serialize = new SimpleRegisteringXmlSerializer( GetType() );
					serialize.Deserialize( this, reader );
					serialize.Deserialize( presets, reader );
					reader.ReadEndElement();
				}
			}

			foreach ( var preset in presets )
				preset.Value.name = preset.Key;

			return true;
		}

		public IEnumerable<ScenePreset> GetStoredPresets()
		{
			return presets.Values;
		}

		public ScenePreset Copy( SettingsManager settings, string name, bool isRewrite )
		{
			ScenePreset parent = settings.Get( GetType() ) as ScenePreset;
			if ( parent.presets.ContainsKey( name ) )
			{
				if (isRewrite)
				{
					parent.presets.Remove(name);
				}
				else
				{
					return null;
				}
			}
			ScenePreset preset = TypeUtils.CreateInstance( GetType() ) as ScenePreset;

			DBFieldInfo[] fields = TypeUtils.GetFields( GetType(), true );
			foreach ( DBFieldInfo field in fields )
			{
				if ( !field.CanRead || !field.CanWrite )
				{
					continue;
				}
				field.SetValue( preset, field.GetValue( this ) );
			}
			preset.name = name;

			parent.presets.Add( name, preset );
			return preset;
		}

		public bool Delete( SettingsManager settings )
		{
			if ( string.IsNullOrEmpty( name ) )
			{
				Log.TraceWarning( "Cannot delete default preset \"{0}\"", GetType().Name );
				return false;
			}
			ScenePreset parent = settings.Get( GetType() ) as ScenePreset;
			parent.presets.Remove( name );

			return true;
		}

	
	}

	public class ScenePresets : TypesCollector<ScenePreset>
	{
		public List<ScenePreset> GetPresets( DBID resourceId, SettingsManager settings )
		{
			List<ScenePreset> presets = new List<ScenePreset>();

			foreach ( Type presetType in GetTypes() )
			{
				ScenePreset presetPattern = settings.Get( presetType ) as ScenePreset;
				if ( !presetPattern.TestForCompatible( resourceId ) )
					continue;

				presets.Add( presetPattern );
				presets.AddRange( presetPattern.GetStoredPresets() );
			}

			presets.Sort((x, y) => string.Compare(x.GetName(), y.GetName()));

			return presets;
		}
	}
}