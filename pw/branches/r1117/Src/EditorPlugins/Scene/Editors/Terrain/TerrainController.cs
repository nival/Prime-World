using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorNative.Terrain;
using libdb;

namespace EditorPlugins.Scene.Editors.Terrain
{
	public sealed class TerrainController : IController<DBTypes.Terrain>
	{
		#region Private members.

		private readonly EditorTerrain terrain;
		private readonly DBTypes.Terrain resource;

    private readonly Dictionary<TerrainElementInstance,ControlableTerrainElement> terrainElements = new Dictionary<TerrainElementInstance, ControlableTerrainElement>();
		private readonly List<ControlableTerrainGlobalLayer> terrainLayers = new List<ControlableTerrainGlobalLayer>();
		private readonly List<ControlableTcvMarker> tcvMarkers = new List<ControlableTcvMarker>();

		private bool markersVisible;
		private bool terrainElementsCanBeSelected;
		private bool terrainElementsSelectable;

		#endregion

		#region Initialization.

		public TerrainController( DBTypes.Terrain resource )
		{
			this.resource = resource;

			terrain = new EditorTerrain( resource );

			AddMarkers( terrain );

      foreach (TerrainElementInstance instance in resource.geometry.terrainElements )
      {
        AddTerrainElement(instance);
      }

      foreach (var layer in resource.layers.terrainLayers )
      {
        AddTerrainGlobalLayer(layer);
      }

			OnTerrainElementsSelectableChanged();
			OnChangeMarkersState();

			resource.layers.terrainLayers.ListItemAdded += OnGlobalLayerAdded;
			resource.layers.terrainLayers.ListItemBeforeChanged += OnGlobalLayerBeforeChanged;
			resource.layers.terrainLayers.ListItemChanged += OnGlobalLayerChanged;
			resource.layers.terrainLayers.ListItemBeforeRemoved += OnGlobalLayerBeforeRemoved;

			resource.geometry.terrainElements.ListItemAdded += OnTerrainElementAdded;
			resource.geometry.terrainElements.ListItemBeforeChanged += OnTerrainElementBeforeChanged;
			resource.geometry.terrainElements.ListItemChanged += OnTerrainElementChanged;
			resource.geometry.terrainElements.ListItemBeforeRemoved += OnTerrainElementBeforeRemoved;
		}

		public void Unsubscribe()
		{
			resource.layers.terrainLayers.ListItemAdded -= OnGlobalLayerAdded;
			resource.layers.terrainLayers.ListItemBeforeChanged -= OnGlobalLayerBeforeChanged;
			resource.layers.terrainLayers.ListItemChanged -= OnGlobalLayerChanged;
			resource.layers.terrainLayers.ListItemBeforeRemoved -= OnGlobalLayerBeforeRemoved;

			resource.geometry.terrainElements.ListItemAdded -= OnTerrainElementAdded;
			resource.geometry.terrainElements.ListItemBeforeChanged -= OnTerrainElementBeforeChanged;
			resource.geometry.terrainElements.ListItemChanged -= OnTerrainElementChanged;
			resource.geometry.terrainElements.ListItemBeforeRemoved -= OnTerrainElementBeforeRemoved;

			terrainLayers.ForEach( RemoveTerrainGlobalLayer );

      List<TerrainElementInstance> elements = new List<TerrainElementInstance>( terrainElements.Keys );
      foreach ( TerrainElementInstance key in elements )
		  {
		    RemoveTerrainElement( key );
		  }
		}

		#endregion

		#region Event handlers.

		private void OnGlobalLayerAdded( object sender, ListItemAddedEventArgs<DBTypes.TerrainLayer> e )
		{
			AddTerrainGlobalLayer( e.Item );
			FireLayersCountChangedEvent();
		}

		private void OnGlobalLayerBeforeChanged( object sender, ListItemBeforeChangedEventArgs<DBTypes.TerrainLayer> e )
		{
			RemoveTerrainGlobalLayer( FindLayerByResourcePart( e.PrevValue ) );
			FireLayersCountChangedEvent();
		}

		private void OnGlobalLayerChanged( object sender, ListItemChangedEventArgs<DBTypes.TerrainLayer> e )
		{
			AddTerrainGlobalLayer( e.NewValue );
			FireLayersCountChangedEvent();
		}

		private void OnGlobalLayerBeforeRemoved( object sender, ListItemBeforeRemovedEventArgs<DBTypes.TerrainLayer> e )
		{
			RemoveTerrainGlobalLayer( FindLayerByResourcePart( e.Item ) );
			FireLayersCountChangedEvent();
		}

		private void OnTerrainElementAdded( object sender, ListItemAddedEventArgs<DBTypes.TerrainElementInstance> e )
		{
			AddTerrainElement( e.Item );
		}

		private void OnTerrainElementBeforeChanged( object sender, ListItemBeforeChangedEventArgs<DBTypes.TerrainElementInstance> e )
		{
			RemoveTerrainElement( e.PrevValue );
		}

		private void OnTerrainElementChanged( object sender, ListItemChangedEventArgs<DBTypes.TerrainElementInstance> e )
		{
			AddTerrainElement( e.NewValue );
		}

		private void OnTerrainElementBeforeRemoved( object sender, ListItemBeforeRemovedEventArgs<DBTypes.TerrainElementInstance> e )
		{
			RemoveTerrainElement( e.Item );
		}

		#endregion

		#region Internal properties.

		internal ControlableTcvMarker[] Markers
		{
			get { return tcvMarkers.ToArray(); }
		}

		internal IList<TerrainElement> ElementsOrder
		{
			get
			{
        var elementsOrder = new List<TerrainElement>();
        foreach ( TerrainElementInstance instance in resource.geometry.terrainElements )
        {
          ControlableTerrainElement value;
          if ( terrainElements.TryGetValue( instance, out value ) )
          {
            if ( ReferenceEquals( instance, value.Resource ) )
            {
              elementsOrder.Add( value );
            }
          }
        }
        return elementsOrder;
			}
		}

		internal bool TerrainElementsSelectable
		{
			get { return terrainElementsSelectable; }
			set
			{
				terrainElementsSelectable = value;
				OnTerrainElementsSelectableChanged();
			}
		}

		internal bool TerrainElementsCanBeSelected
		{
			get { return terrainElementsCanBeSelected; }
			set
			{
				terrainElementsCanBeSelected = value;
				OnChangeMarkersState();
			}
		}

		internal bool MarkersVisible
		{
			get { return markersVisible; }
			set
			{
				markersVisible = value;
				OnChangeMarkersState();
			}
		}

		#endregion

		#region Public properties.

		public DBTypes.Terrain Resource
		{
			get { return resource; }
		}

		public EditorTerrain Terrain
		{
			get { return terrain; }
		}

		#endregion

		#region Internal methods.

		internal void Remove(TerrainElementInstance terrainElementInstance)
		{
			resource.geometry.terrainElements.Remove(terrainElementInstance);
		}

		internal void UpdateTcvMarkers()
		{
			tcvMarkers.ForEach(marker => marker.Update());
		}

		#endregion

		#region Public events.

		public event Operation LayersCountChanged;

		#endregion

		#region Private helper methods.

		private ControlableTerrainGlobalLayer FindLayerByResourcePart( TerrainLayer resourcePart )
		{
			return terrainLayers.Find( layerView => ReferenceEquals( layerView.Resource, resourcePart ) );
		}

	  private void FireLayersCountChangedEvent()
		{
			if ( LayersCountChanged != null )
			{
				LayersCountChanged();
			}
		}

		private void OnTerrainElementsSelectableChanged()
		{
		  foreach (ControlableTerrainElement element in terrainElements.Values)
		  {
		    element.IsSelectable = terrainElementsSelectable;
		  }
		}

		private void OnChangeMarkersState()
		{
			bool state = markersVisible && !terrainElementsCanBeSelected;
			tcvMarkers.ForEach( marker => marker.IsSelected = false );
			tcvMarkers.ForEach( marker => marker.IsVisible = state );
			tcvMarkers.ForEach( marker => marker.IsSelectable = state );
			if ( !markersVisible )
			{
					terrain.UpdateHeightsController();
			}
		}

		private void AddMarkers( EditorTerrain terrain )
		{
			int countX = terrain.SizeX + 1;
			int countY = terrain.SizeY + 1;

			ControlableTcvMarker[,] markers = new ControlableTcvMarker[countX, countY];

			for ( int markerX = 0; markerX < countX; ++markerX )
			{
				for ( int markerY = 0; markerY < countY; ++markerY )
				{
					markers[markerX, markerY] = new ControlableTcvMarker( this, markerX, markerY );
				}
			}

			foreach ( ControlableTcvMarker marker in markers )
			{
				tcvMarkers.Add( marker );
				terrain.Add( marker );
			}
		}

		private void AddTerrainGlobalLayer( TerrainLayer resLayer )
		{
			var terrainLayer = new ControlableTerrainGlobalLayer( resLayer );
			terrainLayer.TerrainTypeChanged += FireLayersCountChangedEvent;
			terrainLayers.Add( terrainLayer );
			terrain.Add( terrainLayer );
		}

		private void RemoveTerrainGlobalLayer( ControlableTerrainGlobalLayer layer )
		{
			terrainLayers.Remove( layer );
			terrain.Remove( layer );
			layer.Unsubscribe();
		}

    private void AddTerrainElement( TerrainElementInstance instance )
    {
      var terrainElement = new ControlableTerrainElement( instance );
      terrain.Add( terrainElement );
      terrainElements.Add( instance, terrainElement );
    }

    private void RemoveTerrainElement( TerrainElementInstance instance )
    {
      ControlableTerrainElement element;
      if( terrainElements.TryGetValue( instance, out element ) )
      {
        terrain.Remove( element );
        element.Unsubscribe();
        terrainElements.Remove(instance);
      }
		}

		#endregion
	}
}
