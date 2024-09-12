using DBTypes;
using EditorNative;
using System;

namespace EditorPlugins.Scene.Editors
{
	internal sealed class EditorLightEnvironmentSettingsController : LightEnvironmentSettingsController
	{
		private readonly EditorScene scene;
		private readonly AdvMap map;
    private LightEnvironment lightEnvironment;

		internal EditorLightEnvironmentSettingsController( EditorScene scene, EditorLightEnvironmentSettingsConfig config, AdvMap map )
			: base( scene, config )
		{
			this.scene = scene;
			this.map = map;
      lightEnvironment = map.lightEnvironment.Get();
      
      map.Changed += OnAdvMapChanged;
      if ( lightEnvironment != null )
        lightEnvironment.Changed += OnlightEnvironmentChanged;

			config.defaultIndex = AdditionalNonRemovableLightEnvironmentsBaseIndex;
		}

    private void OnAdvMapChanged( object sender, EventArgs e )
    {
      if( map.lightEnvironment.Get() != lightEnvironment )
      {
        if( lightEnvironment != null )
          lightEnvironment.Changed -= OnlightEnvironmentChanged;

        lightEnvironment = map.lightEnvironment.Get();
        scene.SceneLightEnvironment = new EditorLightEnvironment( map.lightEnvironment.DBId );

        if ( lightEnvironment != null )
          lightEnvironment.Changed += OnlightEnvironmentChanged;
      }
    }
    private void OnlightEnvironmentChanged( object sender, EventArgs e )
    {
      scene.CalculateLighting();
    }

		protected override string[] AdditionalNonRemovableLightEnvironments
		{
			get { return new string[]{ "Map Light Environment" }; }
		}

		protected override void OnAdditionalNonRemovableLightEnvironmentSelected( int index )
		{
			if ( index == 0 && map.lightEnvironment.IsValid )
			{
				scene.SceneLightEnvironment = new EditorLightEnvironment( map.lightEnvironment.DBId );
			}
		}
	}
}
