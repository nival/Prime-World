using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Globalization;
using System.IO;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.ObjectsBrowser;
using EditorLib.Operations;
using EditorLib.Wizards;
using EditorPlugins.Importer.Texture;
using libdb.Animated;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using libdb.UndoRedo;
using Tools.MayaExeInteraction;

namespace EditorPlugins.Wizards
{
  [ImportWizard( ".mb" )]
  public class MayaSceneImportWizard : IImportWizard
  {
    #region Exceptions
    private class WizardException : Exception
    {
      public WizardException() { }
      public WizardException( string reason ) : base( reason ) { }
    }
    #endregion

    #region Contents Desc data structures

    internal class CheckableDesc
    {
      public bool isChecked = true;
      public virtual bool IsUpdated() { return false; }
    }

    internal class CheckableFloatDesc : CheckableDesc
    {
      public float Value = 0.0f;
      public CheckableFloatDesc() { isChecked = false; }
    }

    internal class CheckableIntDesc : CheckableDesc
    {
      public int Value = 0;
      public CheckableIntDesc() { isChecked = false; }
    }

    internal class CheckableStringDesc : CheckableDesc
    {
      public string Value = string.Empty;
      public CheckableStringDesc() { isChecked = false; }
    }

    internal class AnimTrackDesc : CheckableDesc
    {
      public string name = string.Empty;
      public float[] times = null;
      public float[] values = null;
    }

    internal class MaterialDesc : CheckableDesc
    {
      public Material materialOrig = null;
      public override bool IsUpdated() { return ( null != materialOrig ); }

      public string name = string.Empty;
      public CheckableStringDesc fileDiffuse = new CheckableStringDesc();
      public CheckableStringDesc fileNormal = new CheckableStringDesc();
      public CheckableStringDesc fileSpecular = new CheckableStringDesc();

      public Type result = typeof( BasicMaterial );

      public AnimTrackDesc offsetU = null;
      public AnimTrackDesc offsetV = null;
      public AnimTrackDesc opacity = null;

      public AnimTrackDesc colourR = null;
      public AnimTrackDesc colourG = null;
      public AnimTrackDesc colourB = null;
    }

    internal class MeshDesc : CheckableDesc
    {
      public enum MaterialHint
      {
        None,
        FXMaterial,
        DecalMaterial,
      }

      public SkinPart skinPartOrig = null;
      public AttachedSceneComponent componentOrig = null;
      public override bool IsUpdated() { return ( null != skinPartOrig || null != componentOrig ); }

      public string geomName = string.Empty;
      public bool vertexColour = false;
      public MaterialHint matHint = MaterialHint.None;
      public float param = 0.0f;
      public CheckableIntDesc cycle = null;
      public List<MaterialDesc> materials = new List<MaterialDesc>();

      public AnimTrackDesc translationX = null;
      public AnimTrackDesc translationY = null;
      public AnimTrackDesc translationZ = null;
      public AnimTrackDesc rotationX = null;
      public AnimTrackDesc rotationY = null;
      public AnimTrackDesc rotationZ = null;
      public AnimTrackDesc scaleX = null;
      public AnimTrackDesc scaleY = null;
      public AnimTrackDesc scaleZ = null;
    }

    internal class AnimDesc : CheckableDesc
    {
      public Animation animOrig = null;
      public override bool IsUpdated() { return ( null != animOrig ); }

      public string name = string.Empty;
    }

    internal class SkeletonDesc : CheckableDesc
    {
      public AttachedSceneComponent componentOrig = null;
      public override bool IsUpdated() { return ( null != componentOrig ); }

      public string name = string.Empty;
      public List<MeshDesc> meshes = new List<MeshDesc>();
      public List<AnimDesc> anims = new List<AnimDesc>();
    }

    internal class EffectDesc : CheckableDesc
    {
      public AttachedSceneComponent componentOrig = null;
      public override bool IsUpdated() { return ( null != componentOrig ); }

      public string name = string.Empty;
      public int[] indices;
      public string[] fileNames;
      public CheckableFloatDesc cycle = new CheckableFloatDesc();
      public bool planeOrient = false;
    }

    internal class CameraShakeDesc : CheckableDesc
    {
      public AttachedSceneComponent componentOrig = null;
      public override bool IsUpdated() { return ( null != componentOrig ); }

      public string name = string.Empty;
      public CheckableFloatDesc cycle = new CheckableFloatDesc();

      public AnimTrackDesc translationX = null;
      public AnimTrackDesc translationY = null;
      public AnimTrackDesc translationZ = null;
      public AnimTrackDesc rotationX = null;
      public AnimTrackDesc rotationY = null;
      public AnimTrackDesc rotationZ = null;
    }

    internal enum WizardTarget
    {
      SceneObject,
      Proxy,
    }

    internal class MayaFileContents
    {
      public string fileName = string.Empty;
      public WizardTarget target = WizardTarget.SceneObject;
      public List<Type> materialTypes = new List<Type>();
      public bool autoImport = true;
      public string resourceFolder = string.Empty;

      public List<SkeletonDesc> skeletons = new List<SkeletonDesc>();
      public List<MeshDesc> meshes = new List<MeshDesc>();
      public List<EffectDesc> effects = new List<EffectDesc>();
      public List<CameraShakeDesc> cameras = new List<CameraShakeDesc>();

      public DBResource targetResource = null;
    }

    #endregion

    public string FileExtension { get { return "*.mb"; } }
    public string FileDescription { get { return "Maya Scenes"; } }

    MayaFileContents contents = null;
    private DBSceneObject targetSceneObject = null;
    private DBSceneComponent targetProxy = null;

    private List<DBResource> objectsToImport = null;

    private IEditorWinApplication application = null;

    public bool Run( IEditorWinApplication _application, string fileName )
    {
      contents = new MayaFileContents();
      targetProxy = null;
      targetSceneObject = null;
      objectsToImport = new List<DBResource>();
      application = _application;

      if ( !ValidateTarget( application, fileName ) )
        return false;
      // Run script
      if ( !MayaOperationsUtility.LaunchSceneContentsScript( FileUtils.FixFileName( fileName ) ) )
      {
        Log.TraceError( "Failed to execute scene contents script" );
        return false;
      }

      string contentsFileName = fileName + ".desc";
      contents.fileName = contents.resourceFolder + "/" + FileUtils.GetFileName( fileName );
      contents.materialTypes.Add( typeof( BasicMaterial ) );
      contents.materialTypes.Add( typeof( BasicFXMaterial ) );
      contents.materialTypes.Add( typeof( DecalMaterial ) );

      if ( CheckTargetExistence() )
      {
        MayaImportFileExists formOverwrite = new MayaImportFileExists( targetSceneObject, targetProxy );
        DialogResult answer = formOverwrite.ShowDialog();
        if ( answer != DialogResult.OK )
          return false;

        contents.targetResource = formOverwrite.Target;
      }

      // Parse
      try
      {
        ParseContents( contentsFileName );
      }
      catch ( WizardException e )
      {
        Log.TraceError( "Failed to parse scene contents. Big Red Button .desc parse failed: {0}", e.Message );
        return false;
      }
      catch ( Exception e )
      {
        Log.TraceError( "Failed to parse scene contents. Big Red Button misc. parsing error: {0}", e );
        return false;
      }

      // Open form
      MayaImportWizardForm form = new MayaImportWizardForm( contents );
      if ( form.ShowDialog() == DialogResult.Cancel )
        return false;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Maya Import Wizard Activities" ) )
      {
        try
        {
          if( null == contents.targetResource )
            CreateNewResouce();
          else
            UpdateResource();
        }
        catch( WizardException e )
        {
          Log.TraceError( "Failed to create/update objects. Big Red Button failed: {0}", e.Message );
          return false;
        }

        objectsToImport.Add( contents.targetResource );

        trans.Commit();
      }

      // Run importers
      if ( contents.autoImport )
      {
        List<Executor.OperationHandler> ops = new List<Executor.OperationHandler>();
        foreach ( DBResource res in objectsToImport )
        {
          if ( !application.Application.Extensions.HasImporter( res.GetType() ) )
            continue;
          IImporter importer = application.Application.Extensions.CreateImporter( res.DBId, application.Application, false );
          ops.Add( importer.Import );
        }
        application.Application.OperationExecutor.Start( ops.ToArray() );
      }

      application.Panels.GetSingletonPanel<ObjectsBrowserPanel>().CurrentFolder = contents.resourceFolder;
      return true;
    }

    private bool CheckTargetExistence()
    {
      DBID dbid = null;
      string shortFileName = Path.GetFileNameWithoutExtension( contents.fileName );

      // Check Proxy
      if ( !DBID.TryCreateDBID( contents.resourceFolder, shortFileName, typeof( DBSceneComponent ), out dbid ) )
      {
        targetProxy = DataBase.Get<DBSceneComponent>( dbid );
        contents.targetResource = targetProxy;
      }

      // Check SceneObject
      if ( !DBID.TryCreateDBID( contents.resourceFolder, shortFileName, typeof( DBSceneObject ), out dbid ) )
      {
        targetSceneObject = DataBase.Get<DBSceneObject>( dbid );
        contents.targetResource = targetSceneObject;
      }

      return ( targetProxy != null && targetSceneObject != null );
    }

    private bool ValidateTarget( IEditorWinApplication application, string fileName )
    {
      string srcRoot = FileUtils.FixFolderName( application.Application.SourceFileSystem.RootPath ).ToLower();
      string fileFixed = FileUtils.FixFileName( fileName ).ToLower();
      if ( !fileFixed.Contains( srcRoot ) )
      {
        Log.TraceWarning( string.Format( "Source file must be selected from source tree (\"{0}\")", srcRoot ) );
        return false;
      }
      fileFixed = FileUtils.GetFolderName( FileUtils.FixFileName( fileName ) );

      contents.resourceFolder = fileFixed.Substring( srcRoot.Length - 1 );
      
      return true;
    }

    #region Parse the file

    private class ParseNode
    {
      public List<ParseNode> nodes = new List<ParseNode>();
      public string[] parts;

      public ParseNode( string[] _parts ) { parts = _parts; }
    }

    private void ParseContents( string fileName )
    {
      List<ParseNode> roots = new List<ParseNode>();
      List<ParseNode> parseStack = new List<ParseNode>();
      int lineNo = 0;
      using ( StreamReader sr = new StreamReader( fileName ) )
      {
        string line = sr.ReadLine();
        ++lineNo;
        int level = 0;

        do
        {
          level = GetLevel( line );
          line = line.Trim();
          if ( line.Length == 0 || line == "\0" )
            break;
          string[] parts = line.Split( ' ' );
          if ( parts.Length < 2 )
          {
            throw new WizardException( string.Format( "Line {0}: Too short, need 2 tokens", lineNo ) );
          }

          ParseNode curNode = new ParseNode( parts );
          if ( level == 0 )
          {
            roots.Add( curNode );
            parseStack.Clear();
            parseStack.Add( curNode );
          }
          else
          {
            if ( level > parseStack.Count )
            {
              throw new WizardException( string.Format( "Line {0}: Tab depth grows by more than 1 step", lineNo ) );
            }
            else if ( level < parseStack.Count )
              parseStack.RemoveRange( level, parseStack.Count - level );

            ParseNode parentNode = parseStack[level - 1];
            parentNode.nodes.Add( curNode );
            parseStack.Add( curNode );
          }

          line = sr.ReadLine();
        } while ( line != null );
      }

      ConvertToContents( roots );

      foreach ( EffectDesc eff in contents.effects )
        ResortEffectTextures( eff );
    }

    private void ConvertToContents( List<ParseNode> roots )
    {
      foreach ( ParseNode root in roots )
      {
        if ( root.parts[0] == "skeleton" )
        {
          contents.skeletons.Add( ParseSkeletonNode( root ) );
        }
        else if ( root.parts[0] == "mesh" )
        {
          contents.meshes.Add( ParseMeshNode( root, true, null ) );
        }
        else if ( root.parts[0] == "particle" )
        {
          contents.effects.Add( ParseParticleNode( root ) );
        }
        else if ( root.parts[0] == "camera" )
        {
          contents.cameras.Add( ParseCameraShakeNode( root ) );
        }
        else
        {
          Log.TraceWarning( "Contents parse: Unknown root: {0}", root.parts[0] );
        }
      }
    }

    private CameraShakeDesc ParseCameraShakeNode( ParseNode node )
    {
      CameraShakeDesc camera = new CameraShakeDesc();
      camera.name = node.parts[1];

      bool updating = CheckCameraShakePresent( camera );

      if ( updating && camera.componentOrig.timeController.Get() != null )
      {
        TimeController tc = camera.componentOrig.timeController.Get();
        camera.cycle.isChecked = ( tc.cycleCount == 0 );
        camera.cycle.Value = tc.cycleLength;
      }

      foreach ( ParseNode item in node.nodes )
      {
        if ( item.parts[0] == "animChannel" )
        {
          if ( item.parts[1] == "translateX" )
            camera.translationX = ParseAnimChannel( item );
          else if ( item.parts[1] == "translateY" )
            camera.translationY = ParseAnimChannel( item );
          else if ( item.parts[1] == "translateZ" )
            camera.translationZ = ParseAnimChannel( item );
          else if ( item.parts[1] == "rotateX" )
            camera.rotationX = ParseAnimChannel( item );
          else if ( item.parts[1] == "rotateY" )
            camera.rotationY = ParseAnimChannel( item );
          else if ( item.parts[1] == "rotateZ" )
            camera.rotationZ = ParseAnimChannel( item );
        }
        else
          Log.TraceWarning( "Contents parse: Unknown CameraShakeComponent part: {0}", item.parts[0] );
      }

      return camera;
    }

    private bool CheckCameraShakePresent( CameraShakeDesc camera )
    {
      if ( null == contents.targetResource )
        return false;

      IList<AttachedSceneComponent> components = null;
      if ( contents.targetResource is DBSceneObject )
        components = targetSceneObject.attached;
      else
        components = targetProxy.attached;

      foreach ( AttachedSceneComponent item in components )
      {
        if ( !( item.component.Get() is CameraShakeSceneComponent ) )
          continue;

        CameraShakeSceneComponent sc = item.component.Get() as CameraShakeSceneComponent;
        if ( sc.caption == ( ( camera.name == "_" ) ? "" : camera.name ) )
        {
          camera.componentOrig = item;
          return true;
        }
      }

      return false;
    }

    private SkeletonDesc ParseSkeletonNode( ParseNode root )
    {
      SkeletonDesc skel = new SkeletonDesc();
      skel.name = root.parts[1];

      DBAnimatedSceneComponent animSCOrig = CheckSkeletonPresent( skel );
      bool updating = ( null != animSCOrig );

      foreach ( ParseNode item in root.nodes )
      {
        if ( item.parts[0] == "mesh" )
        {
          if ( updating )
          {
            skel.meshes.Add( ParseMeshNode( item, true, animSCOrig ) );
          }
          else
            skel.meshes.Add( ParseMeshNode( item, false, null ) );
        }
        else if ( item.parts[0] == "anim" )
        {
          AnimDesc anim = new AnimDesc();
          anim.name = item.parts[1];
          skel.anims.Add( anim );

          if ( updating )
          {
            foreach ( Animation itemAnim in animSCOrig.animations )
            {
              if ( itemAnim.name == anim.name )
              {
                anim.animOrig = itemAnim;
                break;
              }
            }
          }

          if ( item.parts.Length > 2 && item.parts[2] == "off" )
            anim.isChecked = false;
        }
        else
        {
          throw new WizardException( string.Format( "Unknown skeleton part: {0}", item.parts[0] ) );
        }
      }
      return skel;
    }

    private DBAnimatedSceneComponent CheckSkeletonPresent( SkeletonDesc skel )
    {
      if ( null == contents.targetResource )
        return null;

      IList<AttachedSceneComponent> components = null;
      if ( contents.targetResource is DBSceneObject )
        components = targetSceneObject.attached;
      else
        components = targetProxy.attached;

      foreach ( AttachedSceneComponent item in components )
      {
        if ( !( item.component.Get() is DBAnimatedSceneComponent ) )
          continue;

        DBAnimatedSceneComponent sc = item.component.Get() as DBAnimatedSceneComponent;
        if ( sc.selection == ( ( skel.name == "_" ) ? "" : skel.name ) )
        {
          skel.componentOrig = item;
          return sc;
        }
      }

      return null;
    }

    private EffectDesc ParseParticleNode( ParseNode node )
    {
      EffectDesc eff = new EffectDesc();
      eff.name = node.parts[1];

      if ( node.parts.Length > 2 )
      {
        eff.cycle.Value = float.Parse( node.parts[2], CultureInfo.InvariantCulture );
        if ( node.parts.Length > 3  && HasPin( node.parts, "Cycled" ) )
        {
          eff.cycle.isChecked = true;
        }
        if ( node.parts.Length > 3 && HasPin( node.parts, "Plane" ) )
        {
          eff.planeOrient = true;
        }
      }

      bool updating = CheckEffectPresent( eff );

      List<int> indices = new List<int>();
      List<string> names = new List<string>();
      foreach ( ParseNode item in node.nodes )
      {
        {
          indices.Add( int.Parse( item.parts[0] ) );
          names.Add( item.parts[1] );
        }
      }
      eff.indices = indices.ToArray();
      eff.fileNames = names.ToArray();

      return eff;
    }

    private bool HasPin( string[] parts, string pinName )
    {
      foreach ( string item in parts )
      {
        if ( item == pinName )
          return true;
      }
      return false;
    }

    private bool CheckEffectPresent( EffectDesc eff )
    {
      if ( null == contents.targetResource )
        return false;

      IList<AttachedSceneComponent> components = null;
      if ( contents.targetResource is DBSceneObject )
        components = targetSceneObject.attached;
      else
        components = targetProxy.attached;

      foreach ( AttachedSceneComponent item in components )
      {
        if ( !( item.component.Get() is DBParticleSceneComponent ) )
          continue;

        DBParticleSceneComponent sc = item.component.Get() as DBParticleSceneComponent;
        if ( sc.selection == ( ( eff.name == "_" ) ? "" : eff.name ) )
        {
          eff.componentOrig = item;
          if ( item.timeController.IsValid && item.timeController.Get().cycleCount == 0 )
          {
            eff.cycle.isChecked = true;
            eff.cycle.Value = item.timeController.Get().cycleLength;
          }
          return true;
        }
      }

      return false;
    }

    private MeshDesc ParseMeshNode( ParseNode item, bool checkOrig, DBAnimatedSceneComponent skeletonToCheck )
    {
      MeshDesc mesh = new MeshDesc();
      mesh.geomName = item.parts[1];

      bool updating = false;
      if ( checkOrig )
      {
        if ( null == skeletonToCheck )
          updating = CheckMeshPresent( mesh );
        else
          updating = CheckSkinPartPresent( skeletonToCheck, mesh );
      }

      if ( item.parts.Length > 2 )
      {
        if ( item.parts[2] == "vertexColor" )
        {
          mesh.vertexColour = true;
          mesh.matHint = MeshDesc.MaterialHint.FXMaterial;
        }
        else if ( item.parts.Length > 3 && item.parts[2] == "decal" )
        {
          mesh.matHint = MeshDesc.MaterialHint.DecalMaterial;
          mesh.param = float.Parse( item.parts[3], CultureInfo.InvariantCulture ); 
        }
      }

      int matIndex = 0;
      foreach ( ParseNode itemMat in item.nodes )
      {
        if ( itemMat.parts[0] == "material" )
        {
          MaterialDesc mat = ParseMaterialNode( mesh, itemMat );
          CheckMaterialPresent( mesh, mat, matIndex );
          if ( ( null != mat.opacity || null != mat.offsetU || null != mat.offsetV ) && null == mesh.cycle )
          {
            mesh.cycle = new CheckableIntDesc();
            mesh.cycle.isChecked = false;
            mesh.cycle.Value = 1;
          }
        }
        else if ( itemMat.parts[0] == "animChannel" )
        {
          if ( null == mesh.cycle )
          {
            mesh.cycle = new CheckableIntDesc();
            mesh.cycle.isChecked = false;
            mesh.cycle.Value = 1;
          }

          if ( itemMat.parts[1] == "translateX" )
            mesh.translationX = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "translateY" )
            mesh.translationY = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "translateZ" )
            mesh.translationZ = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "rotateX" )
            mesh.rotationX = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "rotateY" )
            mesh.rotationY = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "rotateZ" )
            mesh.rotationZ = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "scaleX" )
            mesh.scaleX = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "scaleY" )
            mesh.scaleY = ParseAnimChannel( itemMat );
          else if ( itemMat.parts[1] == "scaleZ" )
            mesh.scaleZ = ParseAnimChannel( itemMat );
        }
        else
        {
          throw new WizardException( string.Format( "Unknown mesh part: {0}", itemMat.parts[0] ) );
        }
        ++matIndex;
      }
      return mesh;
    }

    private void CheckMaterialPresent( MeshDesc mesh, MaterialDesc mat, int matIndex )
    {
      if ( null != mesh.componentOrig )
      {
        DBStaticSceneComponent sc = mesh.componentOrig.component.Get() as DBStaticSceneComponent;
        if ( null == sc )
          return;

        if ( matIndex < sc.materialsReferences.Count )
        {
          mat.materialOrig = sc.materialsReferences[matIndex].Get();
          mat.result = mat.materialOrig.GetType();
        }
      }
      else if ( null != mesh.skinPartOrig )
      {
        if ( matIndex < mesh.skinPartOrig.materialsReferences.Count )
        {
          mat.materialOrig = mesh.skinPartOrig.materialsReferences[matIndex].Get();
          mat.result = mat.materialOrig.GetType();
        }
      }
    }

    private bool CheckSkinPartPresent( DBAnimatedSceneComponent skeletonToCheck, MeshDesc mesh )
    {
      foreach ( SkinPart item in skeletonToCheck.skins )
      {
        if ( item.skinPartName == ( ( mesh.geomName == "_" ) ? "" : mesh.geomName ) )
        {
          mesh.skinPartOrig = item;
          return true;
        }
      }

      return false;
    }

    private bool CheckMeshPresent( MeshDesc mesh )
    {
      if ( null == contents.targetResource )
        return false;

      IList<AttachedSceneComponent> components = null;
      if ( contents.targetResource is DBSceneObject )
        components = targetSceneObject.attached;
      else
        components = targetProxy.attached;

      foreach ( AttachedSceneComponent item in components )
      {
        if ( !( item.component.Get() is DBStaticSceneComponent ) )
          continue;

        DBStaticSceneComponent sc = item.component.Get() as DBStaticSceneComponent;
        if ( sc.caption == ( ( mesh.geomName == "_" ) ? "" : mesh.geomName ) )
        {
          mesh.componentOrig = item;
          if ( !item.timeController.DBId.IsEmpty )
          {
            TimeController tc = item.timeController.Get();
            mesh.cycle = new CheckableIntDesc();
            mesh.cycle.isChecked = ( tc.cycleCount == 0 );
            mesh.cycle.Value = ( tc.cycleCount == 0 ) ? 1 : tc.cycleCount;
          }
          return true;
        }
      }

      return false;
    }

    private MaterialDesc ParseMaterialNode( MeshDesc mesh, ParseNode itemMat )
    {
      MaterialDesc mat = new MaterialDesc();
      mat.name = itemMat.parts[1];

      if ( mesh.matHint == MeshDesc.MaterialHint.FXMaterial )
        mat.result = typeof( BasicFXMaterial );
      else if ( mesh.matHint == MeshDesc.MaterialHint.DecalMaterial )
        mat.result = typeof( DecalMaterial );

      foreach ( ParseNode itemTex in itemMat.nodes )
      {
        if ( itemTex.parts[0] == "diffuse" )
        {
          mat.fileDiffuse.Value = itemTex.parts[1];
          mat.fileDiffuse.isChecked = true;

          if ( mat.fileDiffuse.Value.Contains( "GFX_Textures" ) && mat.result != typeof( DecalMaterial ) )
            mat.result = typeof( BasicFXMaterial );
        }
        else if ( itemTex.parts[0] == "normal" )
        {
          mat.fileNormal.Value = itemTex.parts[1];
          mat.fileNormal.isChecked = true;
        }
        else if ( itemTex.parts[0] == "specular" )
        {
          mat.fileSpecular.Value = itemTex.parts[1];
          mat.fileSpecular.isChecked = true;
        }
        else if ( itemTex.parts[0] == "animChannel" )
        {
          if ( itemTex.parts[1] == "opacity" )
          {
            mat.opacity = ParseAnimChannel( itemTex );
            if ( mat.result != typeof( DecalMaterial ) )
              mat.result = typeof( BasicFXMaterial );
          }
          else
          {
						if ( mat.result != typeof( DecalMaterial ) )
							mat.result = typeof( BasicFXMaterial );

            if ( itemTex.parts[1] == "offsetU" )
              mat.offsetU = ParseAnimChannel( itemTex );
            else if ( itemTex.parts[1] == "offsetV" )
              mat.offsetV = ParseAnimChannel( itemTex );
            else if ( itemTex.parts[1] == "multR" )
              mat.colourR = ParseAnimChannel( itemTex );
            else if ( itemTex.parts[1] == "multG" )
              mat.colourG = ParseAnimChannel( itemTex );
            else if ( itemTex.parts[1] == "multB" )
              mat.colourB = ParseAnimChannel( itemTex );
          }
        }
        else
        {
          throw new WizardException( string.Format( "Unknown material part: {0}", itemTex.parts[0] ) );
        }
      }

      mesh.materials.Add( mat );
      return mat;
    }

    private AnimTrackDesc ParseAnimChannel( ParseNode item )
    {
      List<float> times = new List<float>();
      List<float> values = new List<float>();

      if ( item.nodes.Count != 2 )
        throw new WizardException( string.Format( "AnimChannel {0}: 2 children expected", item.parts[1] ) );

      if ( item.nodes[0].parts.Length < 2 
        || item.nodes[1].parts.Length < 2
        || item.nodes[1].parts.Length != item.nodes[0].parts.Length
        || item.nodes[0].parts[0] != "time"
        || item.nodes[1].parts[0] != "value" )
        throw new WizardException( string.Format( "AnimChannel {0}: expected children 'time' and 'value'", item.parts[1] ) );

      string[] strTimes = item.nodes[0].parts;
      string[] strValues = item.nodes[1].parts;

      for ( int i = 1; i < strTimes.Length; ++i )
      {
        times.Add( float.Parse( strTimes[i], CultureInfo.InvariantCulture ) );
        values.Add( float.Parse( strValues[i], CultureInfo.InvariantCulture ) );
      }

      AnimTrackDesc desc = new AnimTrackDesc();
      desc.name = item.parts[1];
      desc.times = times.ToArray();
      desc.values = values.ToArray();

      return desc;
    }

    int GetLevel( string s )
    {
      for ( int i = 0; i < s.Length; ++i )
      {
        if ( s[i] != '\t' )
          return i;
      }

      return s.Length;
    }

    private void ResortEffectTextures( EffectDesc eff )
    {
      int maxIndex = -1;
      foreach ( int value in eff.indices )
      {
        if ( value > maxIndex )
          maxIndex = value;
      }

      if ( maxIndex < 0 || maxIndex > 100 )
        return;

      string[] fileNames = new string[maxIndex + 1];
      for ( int i = 0; i < eff.indices.Length; ++i )
      {
        fileNames[eff.indices[i]] = eff.fileNames[i];
      }

      eff.indices = null;
      eff.fileNames = fileNames;
    }

    #endregion

    #region Object creation

    private void UpdateResource()
    {
      IList<AttachedSceneComponent> components = null;
      if ( contents.targetResource is DBSceneObject )
        components = targetSceneObject.attached;
      else
        components = targetProxy.attached;

      if ( components.Count > 0 )
        components[0].attachFlags = components[0].attachFlags;

      List<AttachedSceneComponent> remainingComponents = new List<AttachedSceneComponent>( components );

      foreach ( SkeletonDesc skel in contents.skeletons )
      {
        if ( !skel.isChecked )
          continue;

        if ( null == skel.componentOrig )
        {
          AttachedSceneComponent component = new AttachedSceneComponent();
          CreateSkeletonResource( contents.targetResource.DBId, component, skel );
          components.Add( component );
        }
        else
        {
          CreateSkeletonResource( contents.targetResource.DBId, skel.componentOrig, skel );
          remainingComponents.Remove( skel.componentOrig );
        }
      }

      foreach ( MeshDesc mesh in contents.meshes )
      {
        if ( !mesh.isChecked )
          continue;

        if ( null == mesh.componentOrig )
        {
          var component = new AttachedSceneComponent();
          CreateMeshResource( contents.targetResource.DBId, component, mesh );
          components.Add( component );
        }
        else
        {
          CreateMeshResource( contents.targetResource.DBId, mesh.componentOrig, mesh );
          remainingComponents.Remove( mesh.componentOrig );
        }
      }

      foreach ( EffectDesc eff in contents.effects )
      {
        if ( !eff.isChecked )
          continue;

        if ( null == eff.componentOrig )
        {
          AttachedSceneComponent component = new AttachedSceneComponent();
          CreateEffectResource( contents.targetResource.DBId, component, eff );
          components.Add( component );
        }
        else
        {
          CreateEffectResource( contents.targetResource.DBId, eff.componentOrig, eff );
          remainingComponents.Remove( eff.componentOrig );
        }
      }

      foreach ( CameraShakeDesc cam in contents.cameras )
      {
        if ( !cam.isChecked )
          continue;

        if ( null == cam.componentOrig )
        {
          AttachedSceneComponent component = new AttachedSceneComponent();
          CreateCameraShakeResource( contents.targetResource.DBId, component, cam );
          components.Add( component );
        }
        else
        {
          CreateCameraShakeResource( contents.targetResource.DBId, cam.componentOrig, cam );
          remainingComponents.Remove( cam.componentOrig );
        }
      }


      foreach ( AttachedSceneComponent item in remainingComponents )
      {
      	DBSceneComponent component = item.component.Get();

				if ( component is DBSoundSceneComponent || component is DBTraceSceneComponent )
          continue;

        components.Remove( item );
      }
    }

    private void CreateNewResouce()
    {
      Type createdType;
      if ( contents.target == WizardTarget.SceneObject )
      {
        createdType = typeof( DBSceneObject );
        targetSceneObject = new DBSceneObject();
        contents.targetResource = targetSceneObject;
      }
      else
      {
        createdType = typeof( DBSceneComponent );
        targetProxy = new DBSceneComponent();
        contents.targetResource = targetProxy;
      }

      DBID dbid = null;
      string shortFileName = Path.GetFileNameWithoutExtension( contents.fileName );

      if ( !DBID.TryCreateDBID( contents.resourceFolder, Path.GetFileNameWithoutExtension( contents.fileName ), createdType, out dbid ) )
        throw new WizardException( "Failed to create DBID" );

      DataBase.Create<DBResource>( dbid, contents.targetResource );
      CreateDBObjects( dbid );
    }

    private void CreateDBObjects( DBID dbid )
    {
      foreach ( SkeletonDesc skel in contents.skeletons )
      {
        if ( !skel.isChecked )
          continue;

        AttachedSceneComponent component = new AttachedSceneComponent();
        CreateSkeletonResource( dbid, component, skel );

        if ( contents.target == WizardTarget.SceneObject )
          targetSceneObject.attached.Add( component );
        else
          targetProxy.attached.Add( component );
      }

      foreach ( MeshDesc mesh in contents.meshes )
      {
        if ( !mesh.isChecked )
          continue;

        AttachedSceneComponent component = new AttachedSceneComponent();
        CreateMeshResource( dbid, component, mesh );

        if ( contents.target == WizardTarget.SceneObject )
          targetSceneObject.attached.Add( component );
        else
          targetProxy.attached.Add( component );
      }

      foreach ( EffectDesc eff in contents.effects )
      {
        if ( !eff.isChecked )
          continue;

        AttachedSceneComponent component = new AttachedSceneComponent();
        CreateEffectResource( dbid, component, eff );

        if ( contents.target == WizardTarget.SceneObject )
          targetSceneObject.attached.Add( component );
        else
          targetProxy.attached.Add( component );
      }

      foreach ( CameraShakeDesc cam in contents.cameras )
      {
        if ( !cam.isChecked )
          continue;

        AttachedSceneComponent component = new AttachedSceneComponent();
        CreateCameraShakeResource( dbid, component, cam );

        if ( contents.target == WizardTarget.SceneObject )
          targetSceneObject.attached.Add( component );
        else
          targetProxy.attached.Add( component );
      }
    }

    private void CreateSkeletonResource( DBID parent, AttachedSceneComponent component, SkeletonDesc skel )
    {
      DBAnimatedSceneComponent animSC = null;
      if ( null == skel.componentOrig )
      {
        animSC = new DBAnimatedSceneComponent();
        animSC.srcFileName = new SrcFile( contents.fileName );
        animSC.selection = ( skel.name == "_" ) ? "" : skel.name;
        component.component = DataBase.Create<DBSceneComponent>( DBID.FromDBID( parent, true ), animSC );
      }
      else
      {
        animSC = component.component.Get() as DBAnimatedSceneComponent;
      }
      bool captionAssigned = false;
      List<SkinPart> skinsRemaining = new List<SkinPart>( animSC.skins );
      foreach ( MeshDesc mesh in skel.meshes )
      {
        if ( !mesh.isChecked )
          continue;

        SkinPart skin = null;
        if ( null == mesh.skinPartOrig )
        {
          skin = new SkinPart();
          skin.srcFileName = new SrcFile( contents.fileName );
          skin.selection = ( mesh.geomName == "_" ) ? "" : mesh.geomName;
          skin.skinPartName = skin.selection;
        }
        else
          skin = mesh.skinPartOrig;

        if ( !captionAssigned )
        {
          captionAssigned = true;
          animSC.caption = skin.selection;
        }

        List<DBPtr<Material>> materialsRemaining = new List<DBPtr<Material>>( skin.materialsReferences );
        foreach ( MaterialDesc mat in mesh.materials )
        {
          if ( !mat.isChecked )
            continue;

          if ( null == mat.materialOrig )
          {
            Material matRes = CreateMaterialFromType( parent, mat, true, mesh );

            if ( matRes != null )
              skin.materialsReferences.Add( DataBase.Create( DBID.FromDBID( parent, true ), matRes ) );
          }
          else
          {
            Material matRes = CreateMaterialFromType( parent, mat, true, mesh );
            foreach ( DBPtr<Material> item in materialsRemaining )
            {
              if ( item.Get() == mat.materialOrig )
              {
                materialsRemaining.Remove( item );
                break;
              }
            }

            if ( matRes != mat.materialOrig )
            {
              foreach ( DBPtr<Material> item in skin.materialsReferences )
              {
                if ( item.Get() == mat.materialOrig )
                {
                  item.Set( DataBase.Create<Material>( DBID.FromDBID( parent, true ), matRes ) );
                  break;
                }
              }
            }

          }
        }

        foreach ( DBPtr<Material> item in materialsRemaining )
          skin.materialsReferences.Remove( item );

        animSC.skins.Add( skin );
      }

      foreach ( SkinPart item in skinsRemaining )
        animSC.skins.Remove( item );

      if ( !captionAssigned )
        animSC.caption = animSC.selection;

      List<Animation> animsRemaining = new List<Animation>( animSC.animations );
      foreach ( AnimDesc anim in skel.anims )
      {
        if ( !anim.isChecked )
          continue;

        Animation animRes = null;
        if ( null == anim.animOrig )
        {
          animRes = new Animation();
          animRes.name = anim.name;
          animRes.srcFileName = new SrcFile( contents.resourceFolder + "/" + anim.name + ".ma" );
          animRes.compression = 0;

          animSC.animations.Add( animRes );
        }
        else
        {
          animsRemaining.Remove( anim.animOrig );
        }
      }

      foreach ( Animation item in animsRemaining )
        animSC.animations.Remove( item );

      objectsToImport.Add( animSC );
    }

    private void CreateMeshResource( DBID parent, AttachedSceneComponent component, MeshDesc mesh )
    {
      DBStaticSceneComponent meshSC = null;
      if ( null == mesh.componentOrig )
      {
        meshSC = new DBStaticSceneComponent();
        component.component = DataBase.Create<DBSceneComponent>( DBID.FromDBID( parent, true ), meshSC );
				meshSC.srcFileName = new SrcFile( contents.fileName );
				meshSC.selection = ( mesh.geomName == "_" ) ? "" : mesh.geomName;
				meshSC.caption = meshSC.selection;
      }
      else
      {
        meshSC = mesh.componentOrig.component.Get() as DBStaticSceneComponent;
      }

      if ( null != mesh.cycle ) 
      {
        TimeController tc = null;
        if ( component.timeController.DBId.IsEmpty )
        {
          tc = new TimeController();
          tc.cycleLength = 0;
          component.timeController = DataBase.Create( DBID.FromDBID( parent, true ), tc );
        }
        else
        {
          tc = component.timeController.Get();
        }

        if ( mesh.cycle.isChecked )
          tc.cycleCount = 0;
        else
          tc.cycleCount = mesh.cycle.Value;
      }

      List<DBPtr<Material>> materialsRemaining = new List<DBPtr<Material>>( meshSC.materialsReferences );
      foreach ( MaterialDesc mat in mesh.materials )
      {
        if ( !mat.isChecked )
          continue;

        if ( null == mat.materialOrig )
        {
          Material matRes = CreateMaterialFromType( parent, mat, false, mesh );

          if ( matRes != null )
            meshSC.materialsReferences.Add( DataBase.Create( DBID.FromDBID( parent, true ), matRes ) );
        }
        else
        {
          Material matRes = CreateMaterialFromType( parent, mat, false, mesh );
          foreach ( DBPtr<Material> item in materialsRemaining )
          {
            if ( item.Get() == mat.materialOrig )
            {
              materialsRemaining.Remove( item );
              break;
            }
          }

          if ( matRes != mat.materialOrig )
          {
            foreach ( DBPtr<Material> item in meshSC.materialsReferences )
            {
              if ( item.Get() == mat.materialOrig )
              {
                item.Set( DataBase.Create<Material>( DBID.FromDBID( parent, true ), matRes ) );
                break;
              }
            }
          }
        }
      }
      foreach ( DBPtr<Material> item in materialsRemaining )
        meshSC.materialsReferences.Remove( item );

      TryFillAnimatedTrack( mesh.translationX, component.placement.pos, 0 );
      TryFillAnimatedTrack( mesh.translationY, component.placement.pos, 1 );
      TryFillAnimatedTrack( mesh.translationZ, component.placement.pos, 2 );

      TryFillAnimatedTrack( mesh.rotationX, component.placement.rot, 0 );
      TryFillAnimatedTrack( mesh.rotationY, component.placement.rot, 1 );
      TryFillAnimatedTrack( mesh.rotationZ, component.placement.rot, 2 );
      CorrectRotationTrack( mesh.rotationX, component.placement.rot, 0 );
      CorrectRotationTrack( mesh.rotationY, component.placement.rot, 1 );
      CorrectRotationTrack( mesh.rotationZ, component.placement.rot, 2 );

      TryFillAnimatedTrack( mesh.scaleX, component.placement.scale, 0 );
      TryFillAnimatedTrack( mesh.scaleY, component.placement.scale, 1 );
      TryFillAnimatedTrack( mesh.scaleZ, component.placement.scale, 2 );

      objectsToImport.Add( meshSC );
    }

    private void CreateEffectResource( DBID parent, AttachedSceneComponent component, EffectDesc eff )
    {
      DBParticleSceneComponent effSC = null;
      if ( null == eff.componentOrig )
      {
        effSC = new DBParticleSceneComponent();
        effSC.caption = eff.name;
        effSC.selection = ( eff.name == "_" ) ? "" : eff.name;
        effSC.srcFileName = new SrcFile( contents.fileName );
        component.component = DataBase.Create<DBSceneComponent>( DBID.FromDBID( parent, true ), effSC );
      }
      else
      {
        effSC = eff.componentOrig.component.Get() as DBParticleSceneComponent;
        effSC.textures.Clear();
      }

      if ( component.timeController.IsValid )
      {
        if ( eff.cycle.isChecked )
        {
          TimeController controller = component.timeController.Get();
          controller.cycleCount = 0;
          controller.cycleLength = eff.cycle.Value;
        }
      }
      else
      {
        TimeController controller = new TimeController();
        if ( eff.cycle.isChecked )
        {
          controller.cycleCount = 0;
          controller.cycleLength = eff.cycle.Value;
        }
        else
        {
          controller.cycleCount = 1;
          controller.cycleLength = 0;
        }
        component.timeController = DataBase.Create<TimeController>( DBID.FromDBID( parent, true ), controller );
      }

      for ( int i = 0; i < eff.fileNames.Length; ++i )
      {
        effSC.textures.Add( new SrcFile( "/PFX_Textures/" + eff.fileNames[i] ) );
      }

      if ( eff.planeOrient )
        effSC.orient = EOrientType.Plane;

      objectsToImport.Add( effSC );
    }

    private void CreateCameraShakeResource( DBID parent, AttachedSceneComponent component, CameraShakeDesc cam )
    {
      CameraShakeSceneComponent camSC = null;
      if ( null == cam.componentOrig )
      {
        camSC = new CameraShakeSceneComponent();
        camSC.caption = cam.name;
        component.component = DataBase.Create<DBSceneComponent>( DBID.FromDBID( parent, true ), camSC );
      }
      else
      {
        camSC = cam.componentOrig.component.Get() as CameraShakeSceneComponent;
      }

      if ( component.timeController.IsValid )
      {
        if ( cam.cycle.isChecked )
        {
          TimeController controller = component.timeController.Get();
          controller.cycleCount = 0;
          controller.cycleLength = cam.cycle.Value;
        }
      }
      else
      {
        TimeController controller = new TimeController();
        if ( cam.cycle.isChecked )
        {
          controller.cycleCount = 0;
          controller.cycleLength = cam.cycle.Value;
        }
        else
        {
          controller.cycleCount = 1;
          controller.cycleLength = 0;
        }
        component.timeController = DataBase.Create<TimeController>( DBID.FromDBID( parent, true ), controller );
      }

      AnimatedPlacementResource disp = camSC.displacement.Get();
      if ( null == disp )
      {
        disp = new AnimatedPlacementResource();
        camSC.displacement = DataBase.Create<AnimatedPlacementResource>( DBID.FromDBID( parent, true ), disp );
      }


      TryFillAnimatedTrack( cam.translationX, disp.placement.pos, 0 );
      TryFillAnimatedTrack( cam.translationY, disp.placement.pos, 1 );
      TryFillAnimatedTrack( cam.translationZ, disp.placement.pos, 2 );

      TryFillAnimatedTrack( cam.rotationX, disp.placement.rot, 0 );
      TryFillAnimatedTrack( cam.rotationY, disp.placement.rot, 1 );
      TryFillAnimatedTrack( cam.rotationZ, disp.placement.rot, 2 );
      CorrectRotationTrack( cam.rotationX, disp.placement.rot, 0 );
      CorrectRotationTrack( cam.rotationY, disp.placement.rot, 1 );
      CorrectRotationTrack( cam.rotationZ, disp.placement.rot, 2 );

      objectsToImport.Add( camSC );
    }

    private void TryFillAnimatedTrack( AnimTrackDesc desc, IAnimated target, int trackId )
    {
      if ( null == desc || !desc.isChecked )
        return;

      IAnimatedTrack track = target.GetObjectTrack( trackId );
      if ( null == track )
        return;

      //target.Type = AnimatedType.Clamp;
      
      int n = track.KeysCount;
      if ( n > desc.times.Length )
      {
        for ( int i = 0; i < n - desc.times.Length; ++i )
          track.DeleteKey( 1 );
      }
      else
      {
        for ( int i = n; i < desc.times.Length; ++i )
          track.AddObjectKey( 0.0f, 0.0f );
      }

      for ( int i = 0; i < desc.times.Length; ++i )
      {
        track.SetObjectValue( i, desc.values[i] );
        track.SetKey( i, desc.times[i] );
      }
    }

    private void CorrectRotationTrack( AnimTrackDesc desc, AnimatedQuat target, int trackId )
    {
      if ( null == desc || !desc.isChecked )
        return;

      IAnimatedTrack track = target.GetObjectTrack( trackId );
      if ( null == track )
        return;

      int n = track.KeysCount; 
      if ( target.Type == AnimatedType.None )
        return;

      List<float> extraTimes = new List<float>();
      List<float> extraValues = new List<float>();

      for ( int i = 1; i < n; ++i )
      {
        float timeStart = track.GetKey( i - 1 );
        float timeEnd = track.GetKey( i );
        float valueStart = (float)track.GetObjectValue( i - 1 );
        float valueEnd = (float)track.GetObjectValue( i );
        if ( Math.Abs( valueEnd - valueStart ) < 160 )
          continue;

        int extraKeysNeeded = (int)Math.Abs( valueEnd - valueStart ) / 120;
        float divisor = 1.0f / ( extraKeysNeeded + 1 );

        for ( int j = 1; j <= extraKeysNeeded; ++j )
        {
          extraTimes.Add( timeStart + ( timeEnd - timeStart ) * divisor * j );
          extraValues.Add( valueStart + ( valueEnd - valueStart ) * divisor * j );
        }
      }

      for ( int i = 0; i < extraTimes.Count; ++i )
        track.AddObjectKey( extraTimes[i], extraValues[i] );
    }

    private DBTypes.Material CreateMaterialFromType( DBID parent, MaterialDesc mat, bool isSkin, MeshDesc ownerMesh )
    {
      if ( mat.materialOrig != null && !mat.materialOrig.DBId.IsInlined )
        return mat.materialOrig;

      if ( mat.result == typeof( DBTypes.BasicMaterial ) )
        return CreateBasicMaterial( parent, mat, isSkin );
      else if ( mat.result == typeof( DBTypes.BasicFXMaterial ) )
        return CreateBasicFXMaterial( parent, mat, isSkin, ownerMesh.vertexColour );
      else if ( mat.result == typeof( DBTypes.DecalMaterial ) )
        return CreateDecalMaterial( parent, mat, ownerMesh.param );
      else
        return null;
    }

    private DBTypes.Material CreateDecalMaterial( DBID parent, MaterialDesc mat, float radius )
    {
      DecalMaterial result = null;
      if ( null == mat.materialOrig || !( mat.materialOrig is DecalMaterial ) )
      {
        result = new DecalMaterial();
        result.AccessibilityPinValue = BooleanPin.None;
        result.renderState.alphaTest = OnOffState.Off;
        result.renderState.blendMode = BlendMode.LerpByAlpha;
        if ( mat.opacity != null )
          result.OpacityAndEmissiveModePinValue = OpacityAndEmissiveModePin.BlendOpacity;
      }
      else
      {
        result = mat.materialOrig as DecalMaterial;
      }
      if ( mat.fileDiffuse.isChecked ) 
        result.DiffuseMap.texture = CreateTextureCheckGFX( parent, mat.fileDiffuse.Value ).GetPtr<DBTypes.TextureBase>();
      else
        result.DiffuseMap.texture.Assign( null );

      result.radius = radius;
      result.caption = mat.name;
      TryFillAnimatedTrack( mat.opacity, result.opacity, 0 );

      return result;
    }

    private DBTypes.Material CreateBasicFXMaterial( DBID parent, MaterialDesc mat, bool isSkin, bool vertexColour )
    {
      BasicFXMaterial result = null;
      bool newlyCreated = true;
      if ( null == mat.materialOrig || !( mat.materialOrig is BasicFXMaterial ) )
      {
        result = new BasicFXMaterial();
      }
      else
      {
        result = mat.materialOrig as BasicFXMaterial;
        newlyCreated = false;
      }
      if ( mat.fileDiffuse.isChecked )
      {
        DBPtr<DBTypes.Texture> tex = CreateTextureCheckGFX( parent, mat.fileDiffuse.Value );
        result.DiffuseMap.texture = tex.GetPtr<DBTypes.TextureBase>();
        if ( newlyCreated && tex.Get().pixelFormat == EPixelFormat.DXT5 )
          result.renderState.blendMode = BlendMode.LerpByAlpha;
      }
      else
        result.DiffuseMap.texture.Assign( null );

      if ( newlyCreated )
      {
        if ( null != mat.opacity && mat.opacity.isChecked )
        {
          result.OpacityAndEmissiveModePinValue = OpacityAndEmissiveModePin.BlendOpacity;
        }
      }
      result.MultiplyVertexColorPinValue = vertexColour ? BooleanPin.Present : BooleanPin.None;
      result.SkeletalMeshPinValue = isSkin ? BooleanPin.Present : BooleanPin.None;
      result.caption = mat.name;

      TryFillAnimatedTrack( mat.offsetU, result.uOffset, 0 );
      TryFillAnimatedTrack( mat.offsetV, result.vOffset, 0 );
      TryFillAnimatedTrack( mat.opacity, result.opacity, 0 );

      TryFillAnimatedTrack( mat.colourR, result.DiffuseMul, 0 );
      TryFillAnimatedTrack( mat.colourG, result.DiffuseMul, 1 );
      TryFillAnimatedTrack( mat.colourB, result.DiffuseMul, 2 );

      return result;
    }

    private DBTypes.Material CreateBasicMaterial( DBID parent, MaterialDesc mat, bool isSkin )
    {
      BasicMaterial result = null;
      bool newlyCreated = true;
      if ( null == mat.materialOrig || !( mat.materialOrig is BasicMaterial ) )
      {
        result = new BasicMaterial();
      }
      else
      {
        result = mat.materialOrig as BasicMaterial;
        newlyCreated = false;
      }
      if ( mat.fileDiffuse.isChecked )
      {
        DBPtr<DBTypes.Texture> tex = CreateTextureCheckGFX( parent, mat.fileDiffuse.Value );
        result.DiffuseMap.texture = tex.GetPtr<DBTypes.TextureBase>();
        if ( newlyCreated && tex.Get().pixelFormat == EPixelFormat.DXT5 )
          result.renderState.alphaTest = OnOffState.On;
      }
      else
        result.DiffuseMap.texture.Assign( null );

//      if ( newlyCreated )
//        result.SkeletalMeshPinValue = isSkin ? BooleanPin.Present : BooleanPin.None;

      if ( mat.fileNormal.isChecked )
      {
        result.NormalMap.texture = CreateTextureCheckGFX( parent, mat.fileNormal.Value ).GetPtr<DBTypes.TextureBase>();
      }
      else
        result.NormalMap.texture.Assign( null );

      if ( mat.fileSpecular.isChecked )
      {
        result.SpecularMap.texture = CreateTextureCheckGFX( parent, mat.fileSpecular.Value ).GetPtr<DBTypes.TextureBase>();
//        if ( newlyCreated )
//          result.LightModePinValue = LightModePin.DiffuseSpecular;
      }
      else
        result.SpecularMap.texture.Assign( null );

      result.caption = mat.name;

      return result;
    }

    private DBPtr<Texture> CreateTextureCheckGFX( DBID parent, string fileName )
    {
      if ( fileName.Contains( "GFX_Textures" ) )
      {
        string croppedName = FileUtils.GetFileNameWithoutExtension( fileName );
        string testFilename = FileUtils.FixFileName( "/GFX_Textures/" + croppedName + ".TXTR" );
        DBID testDbid = DBID.FromFileName( testFilename, false );
        DBPtr<Texture> texPtr = null;
        if ( DataBase.IsExists( testDbid ) )
        {
          texPtr = DataBase.Get<Texture>( testDbid );
        }
        else
        {
          DBTypes.Texture tex = new DBTypes.Texture();
          tex.srcFileName = new SrcFile( "/GFX_Textures/" + FileUtils.GetFileName( fileName ) );
          objectsToImport.Add( tex );

          bool hasAlpha = CheckTextureAlpha( tex.srcFileName.FileName );
          if ( hasAlpha )
            tex.pixelFormat = EPixelFormat.DXT5;
          else
            tex.pixelFormat = EPixelFormat.DXT1;

          texPtr = DataBase.Create( DBID.GenerateUnique( "/GFX_Textures/", croppedName, typeof( Texture ) ), tex );
        }
        objectsToImport.Add( texPtr.Get() );
        return texPtr;
      }
      else
      {
        DBTypes.Texture tex = new DBTypes.Texture();
        tex.srcFileName = new SrcFile( contents.resourceFolder + "/" + fileName );
        objectsToImport.Add( tex );

        bool hasAlpha = CheckTextureAlpha( tex.srcFileName.FileName );

        if ( hasAlpha )
          tex.pixelFormat = EPixelFormat.DXT5;
        else
          tex.pixelFormat = EPixelFormat.DXT1;


        return DataBase.Create( DBID.FromDBID( parent, true ), tex );
      }
    }

    private bool CheckTextureAlpha( string fileName )
    {
      Stream textureStream = application.Application.SourceFileSystem.OpenFile( fileName );
      if ( textureStream == null )
      {
        Log.TraceWarning( "Cannot load texture \"{0}\"", fileName );
        return false;
      }

      Bitmap bmp = TgaReader.LoadImage( textureStream );
      if ( bmp == null )
      {
        Log.TraceWarning( "Cannot load texture \"{0}\"", fileName );
        return false;
      }
      PixelFormat pixFormat = bmp.PixelFormat;
      if ( pixFormat != PixelFormat.Format32bppArgb && pixFormat != PixelFormat.Format32bppPArgb )
        return false;

      BitmapData bmpData = bmp.LockBits( new Rectangle( 0, 0, bmp.Width, bmp.Height ), ImageLockMode.ReadOnly, pixFormat );
      IntPtr ptr = bmpData.Scan0;
      int bytes = bmpData.Stride * bmp.Height;
      byte[] rgbValues = new byte[bytes];
      System.Runtime.InteropServices.Marshal.Copy( ptr, rgbValues, 0, bytes );
      bool result = false;
      for ( int counter = 3; counter < rgbValues.Length; counter += 4 )
      {
        if ( rgbValues[counter] != 255 )
        {
          result = true;
          break;
        }
      }

      bmp.UnlockBits( bmpData );
      return result;
    }

#endregion

  }
}