using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using EditorLib;
using DBTypes;
using libdb.DB;

namespace EditorPlugins.Wizards
{
  public partial class MayaImportWizardForm : Form
  {
    private List<Type> materialTypes = new List<Type>();
    private MayaSceneImportWizard.MayaFileContents contents = null;
    private TreeNode editedNode = null;
    
    internal MayaImportWizardForm( MayaSceneImportWizard.MayaFileContents _contents )
    {
      InitializeComponent();
      contents = _contents;

      FetchTypeIcons();
      materialTypes.AddRange( contents.materialTypes );
      FillTreeView();

      if ( contents.targetResource != null )
      {
        if ( contents.targetResource is DBTypes.DBSceneObject )
        {
          radioButtonSceneObject.Checked = true;
          radioButtonProxy.Checked = false;
        }
        else
        {
          radioButtonSceneObject.Checked = false;
          radioButtonProxy.Checked = true;
        }
        radioButtonSceneObject.Enabled = false;
        radioButtonProxy.Enabled = false;
        groupBoxCreateTarget.Enabled = false;
      }
    }

    private void FetchTypeIcons()
    {
      if ( EditorCommonApplication.ApplicationSingleton != null )
      {
        ImageList typeImageList = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypesImageList();
        int imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( DBAnimatedSceneComponent ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "skeleton", typeImageList.Images[imgIndex] );

        imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( Material ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "material", typeImageList.Images[imgIndex] );

        imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( Animation ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "animation", typeImageList.Images[imgIndex] );

        imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( Texture ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "texture", typeImageList.Images[imgIndex] );

        imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( DBStaticSceneComponent ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "mesh", typeImageList.Images[imgIndex] );

        imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( DBParticleSceneComponent ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "effect", typeImageList.Images[imgIndex] );

        imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( TimeController ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "time", typeImageList.Images[imgIndex] );

        imgIndex = EditorCommonApplication.ApplicationSingleton.Extensions.GetTypeIconIndex( typeof( CameraShakeSceneComponent ), true );
        if ( imgIndex < 0 )
          imgIndex = 0;   // Empty image
        imageListTypeIcons.Images.Add( "camera", typeImageList.Images[imgIndex] );
      }
    }

    private void FillTreeView()
    {
      treeViewContents.Nodes.Clear();
      foreach ( MayaSceneImportWizard.SkeletonDesc skel in contents.skeletons )
      {
        treeViewContents.Nodes.Add( CreateSkeletonNode( skel ) );
      }

      foreach ( MayaSceneImportWizard.MeshDesc mesh in contents.meshes )
      {
        treeViewContents.Nodes.Add( CreateMeshNode( mesh ) );
      }

      foreach ( MayaSceneImportWizard.EffectDesc eff in contents.effects )
      {
        treeViewContents.Nodes.Add( CreateEffectNode( eff ) );
      }

      foreach ( MayaSceneImportWizard.CameraShakeDesc cam in contents.cameras )
      {
        TreeNode nodeCam = new TreeNode( cam.name + ModifyMark( cam ) );
        nodeCam.SelectedImageKey = "camera";
        nodeCam.ImageKey = "camera";
        nodeCam.Checked = true;
        nodeCam.Tag = cam;

        TreeNode effCycleNode = new TreeNode( "Cycle" );
        effCycleNode.SelectedImageKey = "time";
        effCycleNode.ImageKey = "time";
        effCycleNode.Checked = cam.cycle.isChecked;
        effCycleNode.Tag = cam.cycle;
        nodeCam.Nodes.Add( effCycleNode );

        TryAddAnimTrackNode( cam.translationX, nodeCam );
        TryAddAnimTrackNode( cam.translationY, nodeCam );
        TryAddAnimTrackNode( cam.translationZ, nodeCam );
        TryAddAnimTrackNode( cam.rotationX, nodeCam );
        TryAddAnimTrackNode( cam.rotationY, nodeCam );
        TryAddAnimTrackNode( cam.rotationZ, nodeCam );

        treeViewContents.Nodes.Add( nodeCam );
      }


      treeViewContents.ExpandAll();
      UpdateRunButtonState();
    }

    private TreeNode CreateSkeletonNode( MayaSceneImportWizard.SkeletonDesc skel )
    {
      TreeNode nodeSkel = new TreeNode( skel.name + ModifyMark( skel ) );
      nodeSkel.ImageKey = "skeleton";
      nodeSkel.SelectedImageKey = "skeleton";
      nodeSkel.Checked = true;
      nodeSkel.Tag = skel;

      foreach ( MayaSceneImportWizard.MeshDesc mesh in skel.meshes )
      {
        nodeSkel.Nodes.Add( CreateMeshNode( mesh ) );
      }

      foreach ( MayaSceneImportWizard.AnimDesc anim in skel.anims )
      {
        TreeNode nodeAnim = new TreeNode( anim.name + ModifyMark( anim ) );
        nodeAnim.ImageKey = "animation";
        nodeAnim.SelectedImageKey = "animation";
        nodeAnim.Checked = anim.isChecked;
        nodeAnim.Tag = anim;

        nodeSkel.Nodes.Add( nodeAnim );
      }
      return nodeSkel;
    }

    private TreeNode CreateEffectNode( MayaSceneImportWizard.EffectDesc eff )
    {
      TreeNode nodeEff = new TreeNode( eff.name + ModifyMark( eff ) );
      nodeEff.SelectedImageKey = "effect";
      nodeEff.ImageKey = "effect";
      nodeEff.Checked = true;
      nodeEff.Tag = eff;

      TreeNode effCycleNode = new TreeNode( "Cycle" );
      effCycleNode.SelectedImageKey = "time";
      effCycleNode.ImageKey = "time";
      effCycleNode.Checked = eff.cycle.isChecked;
      effCycleNode.Tag = eff.cycle;
      nodeEff.Nodes.Add( effCycleNode );

      for ( int i = 0; i < eff.fileNames.Length; ++i )
      {
        string nodeName = "[" + i + "]   " + eff.fileNames[i];
        TreeNode effTexNode = new TreeNode( nodeName );
        effTexNode.SelectedImageKey = "texture";
        effTexNode.ImageKey = "texture";
        effTexNode.Checked = true;
        effTexNode.Tag = null;
        nodeEff.Nodes.Add( effTexNode );
      }
      return nodeEff;
    }

    private void UpdateRunButtonState()
    {
      bool hasInvalidSkel = false;
      foreach ( MayaSceneImportWizard.SkeletonDesc skel in contents.skeletons )
      {
        if ( !skel.isChecked )
          continue;

        hasInvalidSkel = true;
        foreach ( MayaSceneImportWizard.AnimDesc anim in skel.anims )
        {
          if ( anim.isChecked )
          {
            hasInvalidSkel = false;
            break;
          }
        }

        if ( hasInvalidSkel )
          break;
      }

      if ( hasInvalidSkel )
      {
        buttonRun.Enabled = false;
      }
      else
      {
        buttonRun.Enabled = true;
      }
    }

    private string ModifyMark( MayaSceneImportWizard.CheckableDesc desc )
    {
      if ( desc.IsUpdated() )
        return " (UPDATE)";
      return string.Empty;
    }

    private TreeNode CreateMeshNode( MayaSceneImportWizard.MeshDesc mesh )
    {
      TreeNode nodeMesh = new TreeNode( mesh.geomName + ModifyMark( mesh ) );
      nodeMesh.ImageKey = "mesh";
      nodeMesh.SelectedImageKey = "mesh";
      nodeMesh.Checked = true;
      nodeMesh.Tag = mesh;

      if ( null != mesh.cycle )
      {
        TreeNode cycleNode = new TreeNode( "Cycle" );
        cycleNode.SelectedImageKey = "time";
        cycleNode.ImageKey = "time";
        cycleNode.Checked = mesh.cycle.isChecked;
        cycleNode.Tag = mesh.cycle;

        nodeMesh.Nodes.Add( cycleNode );
      }

      foreach ( MayaSceneImportWizard.MaterialDesc mat in mesh.materials )
      {
        TreeNode nodeMat = new TreeNode( CreateMaterialText( mat ) + ModifyMark( mat ) );
        nodeMat.ImageKey = "material";
        nodeMat.SelectedImageKey = "material";
        nodeMat.Checked = true;
        nodeMat.Tag = mat;

        TreeNode nodeTex = null;
        if ( mat.fileDiffuse.isChecked )
        {
          nodeTex = new TreeNode( "Diffuse: " + mat.fileDiffuse.Value + ModifyMark( mat.fileDiffuse ) );
          nodeTex.ImageKey = "texture";
          nodeTex.SelectedImageKey = "texture";
          nodeTex.Checked = true;
          nodeTex.Tag = mat.fileDiffuse;
          nodeMat.Nodes.Add( nodeTex );
        }
        if ( mat.fileNormal.isChecked )
        {
          nodeTex = new TreeNode( "Normal: " + mat.fileNormal.Value + ModifyMark( mat.fileNormal ) );
          nodeTex.ImageKey = "texture";
          nodeTex.SelectedImageKey = "texture";
          nodeTex.Checked = true;
          nodeTex.Tag = mat.fileNormal;
          nodeMat.Nodes.Add( nodeTex );
        }
        if ( mat.fileSpecular.isChecked )
        {
          nodeTex = new TreeNode( "Specular: " + mat.fileSpecular.Value + ModifyMark( mat.fileSpecular ) );
          nodeTex.ImageKey = "texture";
          nodeTex.SelectedImageKey = "texture";
          nodeTex.Checked = true;
          nodeTex.Tag = mat.fileSpecular;
          nodeMat.Nodes.Add( nodeTex );
        }
        TryAddAnimTrackNode( mat.offsetU, nodeMat );
        TryAddAnimTrackNode( mat.offsetV, nodeMat );
        TryAddAnimTrackNode( mat.opacity, nodeMat );

        TryAddAnimTrackNode( mat.colourR, nodeMat );
        TryAddAnimTrackNode( mat.colourG, nodeMat );
        TryAddAnimTrackNode( mat.colourB, nodeMat );

        nodeMesh.Nodes.Add( nodeMat );
      }

      TryAddAnimTrackNode( mesh.translationX, nodeMesh );
      TryAddAnimTrackNode( mesh.translationY, nodeMesh );
      TryAddAnimTrackNode( mesh.translationZ, nodeMesh );
      TryAddAnimTrackNode( mesh.rotationX, nodeMesh );
      TryAddAnimTrackNode( mesh.rotationY, nodeMesh );
      TryAddAnimTrackNode( mesh.rotationZ, nodeMesh );
      TryAddAnimTrackNode( mesh.scaleX, nodeMesh );
      TryAddAnimTrackNode( mesh.scaleY, nodeMesh );
      TryAddAnimTrackNode( mesh.scaleZ, nodeMesh );

      return nodeMesh;
    }

    void TryAddAnimTrackNode( MayaSceneImportWizard.AnimTrackDesc track, TreeNode parent )
    {
      if ( null == track )
        return;

      TreeNode node = new TreeNode( "Animated: " + track.name + " (" + track.times.Length.ToString() + " keys)" + ModifyMark( track ) );
      node.ImageKey = "animation";
      node.SelectedImageKey = "animation";
      node.Checked = true;
      node.Tag = track;

      parent.Nodes.Add( node );
    }

    private void ForceCheckedState( TreeNode fromNode, bool state )
    {
      if ( null == fromNode.Tag 
        && null != fromNode.Parent )
      {
        fromNode.Checked = fromNode.Parent.Checked;
        return;
      }

      fromNode.Checked = state;
      if ( fromNode.Tag != null )     // Not a texture
      {
        MayaSceneImportWizard.CheckableDesc checkable = fromNode.Tag as MayaSceneImportWizard.CheckableDesc;
        if ( checkable != null )
          checkable.isChecked = state;
      }
      else
      {
      }
      foreach ( TreeNode item in fromNode.Nodes )
        ForceCheckedState( item, state );
    }

    private void treeViewContents_AfterCheck( object sender, TreeViewEventArgs e )
    {
      if ( e.Action != TreeViewAction.Unknown )
      {
        ForceCheckedState( e.Node, e.Node.Checked );
        UpdateRunButtonState();
      }
    }

    private void treeViewContents_NodeMouseClick( object sender, TreeNodeMouseClickEventArgs e )
    {
      if ( e.Button != MouseButtons.Right || e.Node == null )
        return;

      MayaSceneImportWizard.MaterialDesc mat = e.Node.Tag as MayaSceneImportWizard.MaterialDesc;
      if ( mat == null )
        return;

      editedNode = e.Node;

      System.Windows.Forms.ContextMenu menu = new ContextMenu();
      foreach ( Type type in materialTypes )
      {
        MenuItem result = menu.MenuItems.Add( type.Name, SwitchMaterialTarget );
        result.Tag = type;
      }
      menu.Show( this, new Point( e.X, e.Y ) );
    }

    private void SwitchMaterialTarget( object sender, EventArgs e )
    {
      MenuItem item = sender as MenuItem;
      if ( item == null || editedNode == null )
        return;

      Type type = item.Tag as Type;
      MayaSceneImportWizard.MaterialDesc mat = editedNode.Tag as MayaSceneImportWizard.MaterialDesc;
      if ( type == null || mat == null )
        return;

      mat.result = type;
      editedNode.Text = CreateMaterialText( mat );
    }

    private string CreateMaterialText( MayaSceneImportWizard.MaterialDesc mat )
    {
      string result = mat.name + "   (" + mat.result.Name + ")";

      return result;
    }

    private void buttonRun_Click( object sender, EventArgs e )
    {
      if ( radioButtonSceneObject.Checked )
        contents.target = MayaSceneImportWizard.WizardTarget.SceneObject;
      else if ( radioButtonProxy.Checked )
        contents.target = MayaSceneImportWizard.WizardTarget.Proxy;

      contents.autoImport = checkBoxAutoImport.Checked;

      DialogResult = DialogResult.OK;
      Close();
    }
    
  }
}
