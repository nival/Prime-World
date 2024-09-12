using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Panels;
using EditorLib.PropertiesEditor;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors;
using libdb.DB;

namespace EditorPlugins.ObjectLayers
{
  public partial class ObjectLayersPanel : EditorPanel
  {
    private BindingList<ObjectLayersPreset> presets = new BindingList<ObjectLayersPreset>();
    private EditorControl editorControl;
    private AdvMap advMap;
    private readonly Dictionary<DBID, List<AdvMapObject>> advMapObjects = new Dictionary<DBID, List<AdvMapObject>>();

    public ObjectLayersPanel()
    {
      InitializeComponent();
    }

    public void AttachEditorControl( EditorControl _editorControl, AdvMap _advMap )
    {
      editorControl = _editorControl;
      advMap = _advMap;

      //we need fast way to get AdvMapObject by DbId, it's necessary for filter by scriptGroupName
      if( advMap != null )
      {
        foreach ( AdvMapObject mapObject in advMap.objects )
        {
          if ( !advMapObjects.ContainsKey( mapObject.gameObject.DBId ) )
          {
            advMapObjects[mapObject.gameObject.DBId] = new List<AdvMapObject>();
          }
          advMapObjects[mapObject.gameObject.DBId].Add( mapObject );
        }  
      }

      ApplyPresets();

      if(editorControl != null)
      {
        chkEffects.Checked = editorControl.Scene.IsEnabledEffectsInScene;
        chkTiles.Checked = editorControl.IsShowTileSet;
        EnableSceneButtons( true );
      }     
    }

    public void DetachScene()
    {
      advMapObjects.Clear();
      editorControl = null;
      advMap = null;
      EnableSceneButtons( false );
    }

    protected override bool Initialize( IEditorWinApplication app )
    {
      TabText = "Object Layers";
      return true;
    }

    protected override void OnLoad( EventArgs e )
    {
      base.OnLoad( e );

      ObjectLayersConfig config = application.Application.Settings.Get<ObjectLayersConfig>();

      if ( config != null && config.Presets != null )
        presets = new BindingList<ObjectLayersPreset>(config.Presets);
     
      lstPresets.DataSource = presets;
      lstPresets.DisplayMember = "Name";
      presets.ListChanged += (s, a) => ChackEnabledPresets();//чтобы галочки не сбрасывались при добавлении/удалении пресета

      ChackEnabledPresets();
    }

    #region Event Handlers

    private void OnNewPresetClick( object sender, EventArgs e )
    {
      ObjectLayersPreset preset = new ObjectLayersPreset{ Name = "New preset" };
      presets.Add(preset);
      lstPresets.SelectedItem = preset;
      ShowInPropertiesEditor( preset );
    }

    private void OnDeletePresetClick( object sender, EventArgs e )
    {
      ObjectLayersPreset preset = lstPresets.SelectedValue as ObjectLayersPreset;
      presets.Remove( preset );
    }

    private void OnItemCheck( object sender, ItemCheckEventArgs e )
    {
      if ( e.Index < 0 || e.Index >= lstPresets.Items.Count )
        return;

      ObjectLayersPreset preset = lstPresets.Items[e.Index] as ObjectLayersPreset;
      preset.Enabled = e.NewValue == CheckState.Checked;
      ApplyPresets();

      UpdateCheckAllState( e.CurrentValue, e.NewValue );
    }

    private void OnShowInPEClick( object sender, EventArgs e )
    {
      ObjectLayersPreset preset = lstPresets.SelectedValue as ObjectLayersPreset;
      ShowInPropertiesEditor( preset );
    }

    private void OnCheckAllCheckedChanged( object sender, EventArgs e )
    {
      UpdateCheckedPresets();


      foreach (var preset in presets)
      {
        preset.Enabled = chkCheckAll.Checked;
      }

      ApplyPresets();
    }

    private void OnUpClick( object sender, EventArgs e )
    {
      int index = lstPresets.SelectedIndex;

      if ( index <= 0 ) return;

      ObjectLayersPreset tmp = (ObjectLayersPreset)lstPresets.Items[index];
      presets.RemoveAt( index );
      presets.Insert( index - 1, tmp );

      lstPresets.SelectedIndex = index - 1;

      ApplyPresets();
    }

    private void OnDownClick( object sender, EventArgs e )
    {
      int index = lstPresets.SelectedIndex;

      if ((index < 0) || (index >= presets.Count - 1))
        return;

      ObjectLayersPreset tmp = (ObjectLayersPreset)lstPresets.Items[index];
      presets.RemoveAt( index );
      presets.Insert( index + 1, tmp );

      lstPresets.SelectedIndex = index + 1;

      ApplyPresets();
    }

    private void OnSceneButtonClick( object sender, EventArgs e )
    {
      if ( editorControl == null || editorControl.Scene == null || !editorControl.Scene.IsMapLoaded )
        return;

      if ( sender == chkEffects ) //Effects
      {
        chkEffects.Checked = !chkEffects.Checked;
        editorControl.EnableEffects( chkEffects.Checked );                                                  
      }
      else if( sender == chkTiles ) //Tiles
      {
        editorControl.IsShowTileSet = !editorControl.IsShowTileSet;
        chkTiles.Checked = editorControl.IsShowTileSet;
      }
      else if ( sender == chkAttackSpace ) //Attack Space
      {
        editorControl.SceneControl.IsShowAttackSpace = !editorControl.SceneControl.IsShowAttackSpace;
        chkAttackSpace.Checked = editorControl.SceneControl.IsShowAttackSpace;
      }
      else if ( sender == chkRenderSH ) //Render SH
      {
        editorControl.Scene.ToggleDebugRenderSH();
        chkRenderSH.Checked = !chkRenderSH.Checked;
      }
    }

    #endregion

    private void ChackEnabledPresets()
    {
      foreach ( ObjectLayersPreset preset in presets )
      {
        int index = lstPresets.Items.IndexOf( preset );

        if ( index != -1 )
          lstPresets.SetItemChecked( index, preset.Enabled );
      }
    }

    private void ShowInPropertiesEditor( ObjectLayersPreset preset )
    {
      PropertiesEditorPanel propertiesEditor = application.Panels.GetSingletonPanel<PropertiesEditorPanel>();
      propertiesEditor.SelectedObject = preset;
      //propertiesEditor.Focus();
    }

    public void ApplyPresets()
    {
      if( editorControl == null )
        return;

      // Если выключили пресет, поменяли его и включили, то не все объекты будут отображены, 
      // т.к. они были скрыты пресетом до изменения. 
      // Из-за этого сначала отображаем все объекты, а потом применяем все пресеты. 

      ShowAll();

      foreach (ObjectLayersPreset preset in presets)
      {
          ApplyPreset(preset);        
      }
    }

    private void ShowAll()
    {
      if ( editorControl == null )
        return;

      foreach ( SceneElement element in editorControl.Scene.GetSceneElements() )
      {
        GameSceneObject gso = element as GameSceneObject;

        if (gso == null)
          continue;

        gso.Show();
        gso.IsSelectable = true;
      }
    }

    private void ApplyPreset(ObjectLayersPreset preset)
    {
      if ( editorControl == null )
        return;

      foreach ( SceneElement element in editorControl.Scene.GetSceneElements() )
      {
        if( preset.IsEmpty )
          continue;

        GameSceneObject gso = element as GameSceneObject;
                                   
        if ( gso == null )
          continue;

        //filter by path
        if ( !IsValidPath( preset.Paths, gso.DbId ) )
          continue;
        
        GameObject go = gso.GetGameObject();

        if ( go != null )
        {
          if ( !advMapObjects.ContainsKey(go.DBId) || !preset.IsObjectInPreset( advMapObjects, go, gso.GetScriptGroupName() ) )
            continue;
        }

        if ( preset.Enabled )
          gso.Show();
        else
          gso.Hide();

        if ( preset.Enabled )
          gso.IsSelectable = preset.Selectable;
        else
          gso.IsSelectable = false;
      }
    }

    private bool IsValidPath( List<ObjectLayersPath> paths, DBID dbId )
    {
      if(paths == null || paths.Count == 0)
        return true;//если путь пустой, то мы показываем все объекты

      foreach (ObjectLayersPath path in paths)
      {
        if( dbId.FileName.ToLower().Contains( path.Path.ToLower() ))
          return true;
      }

      return false;
    }

    private void UpdateCheckAllState( CheckState currentValue, CheckState newValue )
    {
      chkCheckAll.CheckedChanged -= OnCheckAllCheckedChanged;

      if ( currentValue != CheckState.Checked && newValue == CheckState.Checked )
      {
        //поставили галочку
        chkCheckAll.Checked = lstPresets.CheckedItems.Count + 1 == lstPresets.Items.Count;// будут установлены все галочки	      
      }
      else
      {
        //убрали галочку
        chkCheckAll.Checked = false;
      }

      chkCheckAll.CheckedChanged += OnCheckAllCheckedChanged;
    }

    private void UpdateCheckedPresets()
    {
      lstPresets.ItemCheck -= OnItemCheck;

      for ( int i = 0; i < lstPresets.Items.Count; i++ )
      {
        lstPresets.SetItemChecked( i, chkCheckAll.Checked );
      }

      lstPresets.ItemCheck += OnItemCheck;
    }

    private void EnableSceneButtons( bool enable )
    {
      chkEffects.Enabled = enable;
      chkTiles.Enabled = enable;
      chkAttackSpace.Enabled = enable;
      chkRenderSH.Enabled = enable;
    }

    private void OnSelection( object sender, EventArgs e )
    {
      int index = lstPresets.SelectedIndex;

      if ( ( index < 0 ) || ( index >= presets.Count - 1 ) )
        return;

      ObjectLayersPreset preset = lstPresets.Items[index] as ObjectLayersPreset;
      if ( preset != null )
      {
        preset.Selectable = !preset.Selectable;
      }

      ApplyPresets();
      lstPresets.SelectedIndex = -1;
      lstPresets.Refresh();
    }

    private void OnSelectionAll( object sender, EventArgs e )
    {
      bool needSelectable = false;
      foreach ( ObjectLayersPreset preset in presets )
      {
        if ( !preset.Selectable )
          needSelectable = true;
      }

      foreach ( ObjectLayersPreset preset in presets )
      {
        preset.Selectable = needSelectable;
      }

      ApplyPresets();
      lstPresets.SelectedIndex = -1;
      lstPresets.Refresh();
    }

    private void OnSelectElements( object sender, EventArgs e )
    {
      int index = lstPresets.SelectedIndex;

      if ( ( index < 0 ) || ( index >= presets.Count - 1 ) )
        return;

      ObjectLayersPreset preset = lstPresets.Items[index] as ObjectLayersPreset;
      if ( preset != null )
      {
        if ( editorControl == null )
          return;

        foreach ( SceneElement element in editorControl.Scene.GetSceneElements() )
        {
          if ( preset.IsEmpty )
            continue;

          GameSceneObject gso = element as GameSceneObject;

          if ( gso == null )
            continue;

          gso.IsSelected = false;

          //filter by path
          if ( !IsValidPath( preset.Paths, gso.DbId ) )
            continue;

          GameObject go = gso.GetGameObject();

          if ( go != null )
          {
            if ( !advMapObjects.ContainsKey( go.DBId ) || !preset.IsObjectInPreset( advMapObjects, go, gso.GetScriptGroupName() ) )
              continue;
          }

          gso.IsSelected = true;
        }
      }
    }
  }
}
