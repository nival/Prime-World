using System;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Panels;
using EditorLib.PropertiesEditor;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Viewers;
using libdb.DB;

namespace EditorPlugins.Editors.AnimGraph
{
  public partial class AnimGraphPanel : EditorPanel
  {
    public event EventHandler<EventArgs> UpdateSceneNeeded;

    private AnimGraphPanelConfig config = null;
    
		public AnimationsSelectionPanel AnimationsPanel { get; private set; }

		private PropertiesEditorPanel PropertiesEditor
		{ 
			get { return application.Panels.GetSingletonPanel<PropertiesEditorPanel>(); }
		}

  	public bool MeasureInFrames
  	{
			get { return config.MeasureInFrames; }
			set
			{
				config.MeasureInFrames = value;

				AnimationsPanel.MeasureInFrames = config.MeasureInFrames;

				PropertiesEditor.RefreshView( false );
				AnimationsPanel.RebuildAnimationsList();
			}
  	}

    /// <summary>
    /// Constructor
    /// </summary>
    public AnimGraphPanel()
    {
      Northwoods.Go.GoView.VersionName = "EditorPlugins?232160";
      InitializeComponent();
    }

    /// <summary>
    /// Вызывается при создании панели
    /// </summary>
    protected override bool Initialize( IEditorWinApplication app )
    {
      config = app.Application.Settings.Get<AnimGraphPanelConfig>();

      toolStripCheckSustain.Checked = config.SustainLooped;
      toolStripEditSustain.Text = config.SustainLength.ToString();
    	btnSmartSelection.Checked = config.SmartSelectionEnabled;

      AnimationsPanel = new AnimationsSelectionPanel()
      {
        Name = "AnimationsPanel",
        Dock = DockStyle.Fill
      };

      tabPageAnimations.Controls.Add( AnimationsPanel );
      splitContainerGraphs.Panel1Collapsed = true;

    	MeasureInFrames = config.MeasureInFrames;

			goView1.SustainLooped = config.SustainLooped;
			goView1.SustainLength = config.SustainLength;

			goView2.SustainLooped = config.SustainLooped;
			goView2.SustainLength = config.SustainLength;

      return true;
    }

    /// <summary>
    /// Вызывается из вьювера, задает новые (либо те же) контроллеры для графа, 
    /// инициирует переинициализацию формы
    /// </summary>
    /// <param name="cont1">Контроллер основного графа</param>
    /// <param name="cont2">Контроллер дополнительного графа</param>
    public void SetControllers( AGController cont1, AGController cont2 )
    {
      goView1.SetController( cont2 );	
      goView2.SetController( cont1 );

			// Сбросим состояние формы в первоначальное
      splitContainerGraphs.Panel1Collapsed = ( goView1.Context == null );

			//выставляем текст
			//DBID animatedDbId = null;
			//if ( cont1 != null )
			//  animatedDbId = cont1.GetAnimatedSceneComponentDBID();
			//else if ( cont2 != null )
			//  animatedDbId = cont2.GetAnimatedSceneComponentDBID();
    	
			//TabText = string.Format( "Animations: {0}", animatedDbId );
    }

    private void toolStripEditSustain_Leave( object sender, EventArgs e )
    {
      float value = 0.0f;
      if ( float.TryParse( toolStripEditSustain.Text, System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture.NumberFormat, out value ) )
      {
        config.SustainLength = value;
        toolStripEditSustain.Text = value.ToString();

      	goView1.SustainLength = config.SustainLength;
				goView2.SustainLength = config.SustainLength;

        goView1.PlayLastSelectedNodes();
        goView2.PlayLastSelectedNodes();
      }
    }

    private void toolStripCheckSustain_CheckStateChanged( object sender, EventArgs e )
    {
      config.SustainLooped = toolStripCheckSustain.Checked;
    	
			goView1.SustainLooped = config.SustainLooped;
			goView2.SustainLooped = config.SustainLooped;
      
			goView1.PlayLastSelectedNodes();
      goView2.PlayLastSelectedNodes();
    }

    private void goView2_SelectedObjectChanged( object sender, EventArgs e )
    {
			PropertiesEditor.SelectedObject = ( (AnimGraphControl)sender ).SelectedObject;
      RaiseUpdateSceneNeeded();
    }

    private void toolStripEditSustain_KeyPress( object sender, KeyPressEventArgs e )
    {
      e.Handled = false;
      if ( e.KeyChar == '\r' )
      {
        float value = 0.0f;
        if ( float.TryParse( toolStripEditSustain.Text, System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture.NumberFormat, out value ) )
        {
          config.SustainLength = value;
          toolStripEditSustain.Text = value.ToString();

					goView1.SustainLength = config.SustainLength;
					goView2.SustainLength = config.SustainLength;

					goView1.PlayLastSelectedNodes();
          goView2.PlayLastSelectedNodes();
        }

        e.Handled = true;
      }
    }

    private void updateTimer_Tick( object sender, EventArgs e )
    {
      bool needUpdate = false;
      if ( goView1.Context != null && goView1.Context.Controller != null )
      {
        needUpdate |= !goView1.Context.IsValid;
        int targetNode = goView1.Context.Controller.GetCurTargetNode();
        if ( targetNode != goView1.lastPlayedIndex )
        {
          goView1.lastPlayedIndex = targetNode;
          Refresh();
        }
      }

      if ( goView2.Context != null && goView2.Context.Controller != null )
      {
        needUpdate |= !goView2.Context.IsValid;
        int targetNode = goView2.Context.Controller.GetCurTargetNode();
        if ( targetNode != goView2.lastPlayedIndex )
        {
          goView2.lastPlayedIndex = targetNode;
          Refresh();
        }
      }

      if(needUpdate)
      {
        RaiseUpdateSceneNeeded();
      }

    }

    private void RaiseUpdateSceneNeeded()
    {
        EventHandler<EventArgs> temp = UpdateSceneNeeded;
        if (temp != null)
            temp(this, EventArgs.Empty);
    }

		private void btnRescaleToFit_Click( object sender, EventArgs e )
		{
			goView1.RescaleToFit();
			goView2.RescaleToFit();
		}

		private void btnSmartSelection_CheckedChanged( object sender, EventArgs e )
		{
			config.SmartSelectionEnabled = btnSmartSelection.Checked;
			goView1.SmartSelectionEnabled = btnSmartSelection.Checked;
			goView2.SmartSelectionEnabled = btnSmartSelection.Checked;
		}
  }
}
