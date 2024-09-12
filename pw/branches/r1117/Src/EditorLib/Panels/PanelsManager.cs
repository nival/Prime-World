using System;
using System.Collections.Generic;
using System.Text;
using libdb.Diagnostics;
using System.Reflection;
using WeifenLuo.WinFormsUI.Docking;
using System.Drawing;

namespace EditorLib.Panels
{
	public sealed class PanelsManager
	{
		private readonly IEditorWinApplication application = null;
		private Dictionary<Type, EditorPanel> singletonPanels = new Dictionary<Type, EditorPanel>();
		private DockPanel dockPanel = null;

		public PanelsManager( IEditorWinApplication application )
		{
			this.application = application;
		}

		public void RegisterSingletonPanel( Type panelType )
		{
			try
			{
				if ( !panelType.IsSubclassOf( typeof( EditorPanel ) ) )
				{
					Log.TraceWarning( "Cannot register panel of type \"{0}\". Its not a subclass of \"{1}\"", panelType.Name, typeof( EditorPanel ).Name );
					return;
				}

				if ( singletonPanels.ContainsKey( panelType ) )
				{
					Log.TraceWarning( "Cannot register panel of type \"{0}\". Panel with such type already registred", panelType.Name );
					return;
				}

				ConstructorInfo constructor = panelType.GetConstructor( Type.EmptyTypes );
				if ( constructor == null )
				{
					Log.TraceWarning( "Cannot register panel of type \"{0}\". Default constructor not found", panelType.Name );
					return;
				}

				EditorPanel panel = constructor.Invoke( new Object[0] ) as EditorPanel;
				if ( panel == null )
				{
					Log.TraceWarning( "Cannot register panel of type \"{0}\". Default constructor failed", panelType.Name );
					return;
				}

				panel.HideOnClose = true;
				panel.DockStateChanged += new EventHandler( OnSingletonPanelDockStateChanged );
				singletonPanels.Add( panelType, panel );
			}
			catch ( Exception e )
			{
				Log.TraceWarning( "Cannot register panel of type \"{0}\". Exception {1}: {2}", panelType.Name, e.ToString(), e.Message );
			}
		}

		private void OnSingletonPanelDockStateChanged( object sender, EventArgs e )
		{
			EditorPanel panel = sender as EditorPanel;
			if ( UpdateSingletonPanelEvent != null && panel != null )
				UpdateSingletonPanelEvent( panel, panel.DockState != DockState.Unknown & panel.DockState != DockState.Hidden );
		}

		public T GetSingletonPanel<T>() where T: EditorPanel
		{
			EditorPanel panel = null;
			if ( !singletonPanels.TryGetValue( typeof( T ), out panel ) )
				return null;

			return panel as T;
		}

		public EditorPanel GetSingletonPanel( Type type )
		{
			EditorPanel panel = null;
			if ( !singletonPanels.TryGetValue( type, out panel ) )
				return null;

			return panel;
		}

		public void ShowSingletonPanel<T>() where T: EditorPanel
		{
			ShowSingletonPanel( GetSingletonPanel<T>() );
		}

		public void ShowSingletonPanel( EditorPanel panel )
		{
			if ( panel == null || !singletonPanels.ContainsKey( panel.GetType() ) )
				return;
			if ( dockPanel != null && ( panel.DockState == DockState.Hidden || panel.DockState == DockState.Unknown ) )
			{
				panel.Show( dockPanel );
				if ( UpdateSingletonPanelEvent != null )
					UpdateSingletonPanelEvent( panel, true );
			}
		}

		public void ShowSingletonPanel<T>( DockState dockState ) where T: EditorPanel
		{
			ShowSingletonPanel( GetSingletonPanel<T>(), dockState );
		}

		public void ShowSingletonPanel( EditorPanel panel, DockState dockState )
		{
			if ( panel == null || !singletonPanels.ContainsKey( panel.GetType() ) )
				return;
			if ( dockPanel != null && ( panel.DockState == DockState.Hidden || panel.DockState == DockState.Unknown ) )
			{
				panel.Show( dockPanel, dockState );
				if ( UpdateSingletonPanelEvent != null )
					UpdateSingletonPanelEvent( panel, true );
			}
		}

		public void HideSingletonPanel<T>() where T: EditorPanel
		{
			HideSingletonPanel( GetSingletonPanel<T>() );
		}

		public void HideSingletonPanel( EditorPanel panel )
		{
			if ( panel == null || !singletonPanels.ContainsKey( panel.GetType() ) )
				return;
			if ( dockPanel != null && panel.DockState != DockState.Hidden )
			{
				panel.Hide();
				if ( UpdateSingletonPanelEvent != null )
					UpdateSingletonPanelEvent( panel, false );
			}
		}

		public IEnumerable<EditorPanel> SingletonPanels { get { return singletonPanels.Values; } }

		public delegate void UpdateSingletonPanelEventHandler( EditorPanel panel, bool show );
		public event UpdateSingletonPanelEventHandler UpdateSingletonPanelEvent = null;

    public void Add( DockContent panel )
    {
      panel.Show( dockPanel );
    }

    public void Add( DockContent panel, DockState state )
    {
      panel.Show( dockPanel, state );
    }

    public void Add( DockContent panel, Rectangle bounds )
    {
      panel.Show( dockPanel, bounds );
    }

		public bool Initialize( EditorLib.Operations.IOperationContext context )
		{
			context.Start( true, true );
			context.Progress( "Prepare editor panels ...", 0 );
			
			List<EditorPanel> panelsToInitialize = new List<EditorPanel>();
			panelsToInitialize.AddRange( singletonPanels.Values );
			
			while ( panelsToInitialize.Count > 0 )
			{
				bool panelInitialized = false;
				foreach ( EditorPanel panel in panelsToInitialize )
				{
					if ( panel.InitializeInternal( application ) )
					{
						panelsToInitialize.Remove( panel );
						panelInitialized = true;
						context.Progress( "Prepare editor panels ...", (singletonPanels.Count - panelsToInitialize.Count) * 100 / singletonPanels.Count );
						break;
					}
				}

				if ( !panelInitialized )
				{
					string panelTypes = string.Empty;
					foreach( EditorPanel panel in panelsToInitialize )
					{
						if ( !string.IsNullOrEmpty( panelTypes ) )
							panelTypes += ", ";
						panelTypes += panel.GetType().Name;
					}
					Log.TraceError( "Cannot initialize some panels: {0}", panelTypes );
					break;
				}
			}

			return true;
		}

		public void Terminate()
		{
			foreach ( EditorPanel panel in singletonPanels.Values )
				panel.Terminate( application );
		}

    public DockPanel GetDP()
    {
      return dockPanel;
    }

		public void SetDockPanel( DockPanel dockPanel )
		{
			this.dockPanel = dockPanel;
		}

		public void Invoke( Delegate method )
		{
			if ( dockPanel != null )
				dockPanel.Invoke( method );
		}

		public void Invoke( Delegate method, params object[] args )
		{
			if ( dockPanel != null )
				dockPanel.Invoke( method, args );
		}
	}
}
