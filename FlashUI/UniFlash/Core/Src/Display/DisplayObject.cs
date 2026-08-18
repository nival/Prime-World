using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
#if UNITY_EDITOR
using System.Text;
#endif
using Flash.Utils;
using Flash.Render;
using SwfDotNet.IO.Tags;
using UnityEngine;

namespace Flash
{

  public abstract class DisplayObject : EventDispatcher, IDisposable
  {
    protected static float _currentMaskDepth = 1;
    protected static bool _banDoRender;
    public Bounds InitialBounds { get; protected set; }

    private UniBaseTag _character;
    public UniBaseTag Character
    {
      get { return _character; }
    }
    private bool _visible = true;
    public bool Visible
    {
      get { return _visible; }
      set
      {
        _visible = value;
        if ( _visible )
          _transform.ConcatenateRecursively( true, true );
      }
    }

    private List<RenderableElement> _shapes;
    public List<RenderableElement> Shapes
    {
      get
      {
        return _shapes;
      }
      set
      {
        // only once
        if ( _shapes == null )
          _shapes = value;
      }
    }
    private DisplayObjectContainer _parent;
    public DisplayObjectContainer Parent
    {
      get { return _parent; }
      set
      {
        _root = null;
        _parent = value;
        _transform.ConcatenateRecursively( true, true );
      }
    }
    private DisplayObjectContainer _root;
    public DisplayObjectContainer Root
    {
      get
      {
        if ( _root == null )
        {
          if ( Parent == null )
          {
            return (this as DisplayObjectContainer);
          }

          DisplayObjectContainer level = Parent;

          while ( level != null )
          {
            if ( level.Parent is Stage || level.IsRoot )
            {
              _root = level;
              break;
            }

            level = level.Parent;
          }

        }

        return _root;
      }
    }
    public virtual Stage Stage
    {
      get
      {
        return UniFlashPlayer.MainStage;
      }
    }
    private string _name;
    public string Name
    {
      get { return _name; }
      set { _name = value; }
    }
    private Transform _transform;
    public Transform Transform
    {
      get { return _transform; }
      set
      {
        value.Target = this;
        if ( _playable )
          _transform = value;
      }
    }

    private bool _dirtyFinalMatrix = true;
    private Matrix4x4 _finalMatrix;

    private bool _preTransformed;
    private Matrix4x4 _preTransform = Matrix4x4.identity;
    public Matrix4x4 PreTransform
    {
      get { return _preTransform; }
      set
      {
        if ( value == Matrix4x4.identity )
        {
          _preTransformed = false;
        }
        else
          _preTransformed = true;

        _preTransform = value;
      }
    }
    private Bounds _localBounds;
    public Bounds LocalBounds
    {
      get
      {
        return _localBounds;
      }
      set
      {
        if ( _localBounds == value )
          return;

        _localBounds = value;
        SetDirty();
      }
    }
    protected bool _dirtyBounds = true;
    protected Bounds _worldBounds;
    public virtual Bounds WorldBounds
    {
      get
      {
        if ( _dirtyBounds )
        {
          _dirtyBounds = false;
          UpdateWorldBounds();
        }
        return _worldBounds;
      }
      private set
      {
        _worldBounds = value;
      }
    }
    private bool _showBounds = false;
    public bool ShowBounds
    {
      get { return _showBounds; }
      set { _showBounds = value; }
    }
    public void ShowBoundsToMe()
    {
      ShowBounds = true;
      if (Parent != null)
        Parent.ShowBoundsToMe();
    }
    private DisplayObject _mask;
    public virtual DisplayObject Mask
    {
      get { return _mask; }
      set
      {
        _mask = value;
      }
    }
    private bool _isMask;
    public virtual bool IsMask
    {
      get { return _isMask; }
      set
      {
        _isMask = value;
      }
    }
    private float _maskDepth;
    public float MaskDepth
    {
      get { return _maskDepth; }
      set
      {
        if ( _maskDepth != value )
        {
          _maskDepth = value;
        }
      }
    }
    public float X
    {
      get { return Position.x; }
      set
      {
        if ( Position.x != value )
          Position = new Vector3( value, Position.y, Position.z );
      }
    }
    public float Y
    {
      get { return Position.y; }
      set
      {
        if ( Position.y != value )
          Position = new Vector3( Position.x, value, Position.z );
      }
    }
    public Vector3 Position
    {
      get
      {
        return _transform.Position;
      }
      set
      {
        SetPlayableOff();
        _transform.Position = value;
      }
    }
    public Vector3 Rotation
    {
      get
      {
        return _transform.Rotation;
      }
      set
      {
        SetPlayableOff();
        _transform.Rotation = value;
      }
    }
    public Vector3 Scale
    {
      get
      {
        return _transform.Scale;
      }
      set
      {
        SetPlayableOff();
        _transform.Scale = value;
      }
    }
    public virtual float Width
    {
      get
      {
        return WorldBounds.Width;
      }
      set
      {
        float ratio = value / Width;
        Vector3 scale = _transform.Scale;
        scale.x *= ratio;
        Scale = scale;
      }
    }
    public float Height
    {
      get
      {
        return WorldBounds.Height;
      }
      set
      {
        float ratio = value / Height;
        Vector3 scale = _transform.Scale;
        scale.y *= ratio;
        Scale = scale;
      }
    }
    public float Alpha
    {
      get { return _transform.Alpha; }
      set
      {
        _transform.Alpha = value;
      }
    }
    private bool _playable = true;
    public bool Playable
    {
      get { return _playable; }
    }
    private bool _enableColorTransform = true;
    public virtual bool EnableColorTransform
    {
      get { return _enableColorTransform; }
      set
      {
        _enableColorTransform = value;
      }
    }

    /// <summary>
    /// Using for ignore parent filters switching. If setted true - filters can be enabled/disabled only directly from EnableFilters.
    /// </summary>
    public bool IgnoreParentFiltersSwitching { get; set; }
    private bool _enableFilters = true;
    public virtual bool EnableFilters
    {
      get { return _enableFilters; }
      set
      {
        _enableFilters = value;
      }
    }

    protected Vector4 _texelHint;
    public Vector4 TexelHint
    {
      get { return _texelHint; }
    }

    private bool _activeZoneFound = false;
    public bool IsActiveZoneFound
    {
      get { return _activeZoneFound; }
      set { _activeZoneFound = value; }
    }

    private bool _activeMouseZone = false;
    public bool IsActiveMouseZone
    {
      get { return _activeMouseZone; }
      set { _activeMouseZone = value; }
    }

    private bool _serviceObject = false;
    public bool IsServiceObject
    {
      get { return _serviceObject; }
      set { _serviceObject = value; }
    }


    public event EventHandler<Event> EnterFrame;
    public event EventHandler<Event> ExitFrame;
    public event EventHandler<Event> Added;
    public event EventHandler<Event> Removed;
    public event EventHandler<Event> Render;
    public event EventHandler<Event> PostRender;

    public static T Instantiate<T>( T source ) where T : InteractiveObject, new()
    {
      T clone = new T();
      clone.Transform = (Transform)source.Transform.Clone();

      // Clone Bind Hierarchy
      ControlNode bindClone = ( (IBindable)source ).ControlNode.Instantiate();
      ( (IBindable)clone ).ControlNode = bindClone;
      bindClone.Bind = clone;

      // SET FLASH CONTENT
      clone.Push( source._character );
    //  source.Parent.AddChild( clone ); 30/09/2015 Закоммитил эту строку - добавление итема идет некорректно просто поверх всех существующих элементов
      source.Parent.AddChildAt(source.Parent.GetChildIndex(source), clone); //30/09/2015 Добавил эту строку - добавление итема идет на глубину сорс итема, а не поверх всего что есть

      clone.Name = string.Format( "{0}(Instance)", source.Name );

      clone.UpdateLocalBounds();

      // INIT
      ( (IInteractive)clone ).InitInternal();

      return clone;
    }

    public DisplayObject()
    {
      Transform = new Transform();
    }

    public virtual void Destroy()
    {
      if ( Parent != null )
        Parent.RemoveChildFromTimeline( this );
    }

    public virtual void UpdateFrame()
    {
    }

    public virtual void Push( UniBaseTag character )
    {
      _character = character;

      if ( _character is UniBaseShapeTag )
      {
        // If display object uses UniDefineBitsJpeg as shape we need generate shape once);
        if ( character is UniDefineBitsJpegTag )
          ( (UniDefineBitsJpegTag)character ).GenerateShape();

        _shapes = ( (UniBaseShapeTag)character ).Shapes;

        // Generate scale grid);
        if ( FlashEnv.CLIPPED_SCALE_GRID_ENABLED && Parent != null && Parent.ScaleGridData != null )
        {
          if ( !( this is MorphShape ) )
          {
            CloneShapes( _shapes );
            ClipShapes();
          }
        }
      }

      _localBounds = character.LocalBounds;
    }
    public virtual void PreRender()
    {
      if ( _mask != null || _isMask )
        MaskDepth = _currentMaskDepth;
      else
        MaskDepth = 1.0F;

      // Render mask
      if ( IsMask )
      {
        if ( !Parent.IsMask )
        {
          _currentMaskDepth -= 0.001F;
          MaskDepth = _currentMaskDepth;
        }

        Call();

        if ( UniFlashPlayer.ShowMasks )
        {
          DrawBounds( new Color( 0, 0, 0, 0.5F ), false );
          DrawBounds( new Color( 0, 0, 0, 1F ), true );
        }

        return;
      }

      // Focus
      bool mouseOver = false;

      if ( Parent.MouseEnabled && ( Parent.MouseChildren || Parent.Parent.MouseChildren ) )
      {
        if ( IsMouseOverQuick() )
        {
          mouseOver = true;
          FlashInput.TopmostObject = this;

          if (IsActiveMouseZone)
            Root.IsActiveZoneFound = true;

          if ( this is InteractiveObject && ( this as InteractiveObject ).MouseEnabled || !( this is InteractiveObject ) )
          {
            if ( this is TextField )
              FlashInput.MouseFocus = this as TextField;
            else
              FlashInput.MouseFocus = _parent;
          }
        }
      }

      // Render every really renderable entity	
      if ( !IsServiceObject )
        Call();


#if UNITY_EDITOR
      if ( ( mouseOver && UniFlashPlayer.ShowMouseFocus ) || _showBounds )
      {
        if ( IsActiveMouseZone )
          DrawBounds( new Color( 0, 1, 0, 1F ), true );
        else
          DrawBounds( new Color( 1, 0, 0, 1F ), true );
      }
#endif
    }

    public string GetFullPath()
    {
      if ( this != Stage )
        return string.Format( "{0}{1}{2}", _parent.GetFullPath(), Path.DirectorySeparatorChar, ( string.IsNullOrEmpty( Name ) ? "..." : Name ) );
      return string.IsNullOrEmpty( Name ) ? "..." : Name;
    }

    public Vector2 GlobalToLocal( Vector3 point )
    {
      return _transform.WorldMatrix.inverse.MultiplyPoint3x4( point );
    }

    public Vector2 LocalToGlobal( Vector3 point )
    {
      return _transform.WorldMatrix.MultiplyPoint3x4( point );
    }

    public void ResetRoot()
    {
      _root = null;
    }

    public void DrawBounds( Color color, bool wireframe )
    {
      UniFlashPlayer.FlashDebug.DrawMaterial.SetPass( 0 );
      GL.LoadProjectionMatrix( GL.GetGPUProjectionMatrix( UniFlashPlayer.Camera.projectionMatrix, false ) );
      GL.Color( color );
      if ( wireframe )
      {
        GL.Begin( GL.LINES );
        GL.Vertex( WorldBounds.LeftTop );
        GL.Vertex( new Vector3( WorldBounds.LeftTop.x, WorldBounds.RightBottom.y ) );
        GL.Vertex( new Vector3( WorldBounds.LeftTop.x, WorldBounds.RightBottom.y ) );
        GL.Vertex( WorldBounds.RightBottom );
        GL.Vertex( WorldBounds.RightBottom );
        GL.Vertex( new Vector3( WorldBounds.RightBottom.x, WorldBounds.LeftTop.y ) );
        GL.Vertex( new Vector3( WorldBounds.RightBottom.x, WorldBounds.LeftTop.y ) );
        GL.Vertex( WorldBounds.LeftTop );
      }
      else
      {
        GL.Vertex( WorldBounds.LeftTop );
        GL.Vertex( new Vector3( WorldBounds.RightBottom.x, WorldBounds.LeftTop.y ) );
        GL.Vertex( WorldBounds.RightBottom );
        GL.Vertex( new Vector3( WorldBounds.LeftTop.x, WorldBounds.RightBottom.y ) );
      }

      GL.End();
    }

    public virtual void UpdateLocalBounds() { }

    public virtual void UpdateLocalBounds( bool ignoreInvisibleObjects ) { }

    private bool IsMouseOverQuick()
    {
      // Check mask if under mask
      if ( !IsMask && Mask != null )
      {
        if ( !Mask.IsMouseOverQuick() )
        {
          //Profiler.EndSample();
          return false;
        }
      }

      return WorldBounds.Contains( FlashInput.MousePosition );
    }

    public bool IsMouseOver()
    {
      //Profiler.BeginSample( "MOUSE_TEST" );


      DisplayObject currentObject = this;
      while ( currentObject != null )
      {
        if ( !currentObject.Visible )
          return false;

        currentObject = currentObject.Parent;
      }

      // Check mask if under mask
      if ( !IsMask && Mask != null )
      {
        if ( !Mask.IsMouseOver() )
        {
          //Profiler.EndSample();
          return false;
        }
      }

      Vector2 mouseInLocalSpace = _transform.WorldMatrix.inverse.MultiplyPoint3x4( FlashInput.MousePosition );

      //Profiler.EndSample();

      return LocalBounds.Contains( mouseInLocalSpace );
    }

    public virtual void SetDirty()
    {
      _dirtyBounds = true;
      _dirtyFinalMatrix = true;
    }

    public virtual void Dispose()
    {
      if ( _shapes != null )
      {
        for ( int i = 0; i < _shapes.Count; i++ )
        {
          _shapes[i].Dispose();
        }
      }
    }

    public void OnEnterFrameInternal( Flash.Event args )
    {
      if ( EnterFrame != null )
        EnterFrame( this, args );
    }

    public void OnExitFrameInternal( Flash.Event args )
    {
      if ( ExitFrame != null )
        ExitFrame( this, args );
    }

    public void OnAddedInternal( Flash.Event args )
    {
      DispatchEvent( args, OnAdded, Added );
    }

    public void OnRemovedInternal( Flash.Event args )
    {
      DispatchEvent( args, OnRemoved, Removed );
    }

    private static Flash.Event _renderInternalEventArgs = new Flash.Event( EventType.RENDER, true );

    public void OnRenderInternal( Flash.Event args )
    {
      if ( Render != null )
        Render( this, _renderInternalEventArgs );
    }
    public void OnPostRenderInternal( Flash.Event args )
    {
      if ( PostRender != null )
        PostRender( this, _renderInternalEventArgs );
    }


#if UNITY_EDITOR
    public virtual void DampDisplayObject( StringBuilder builder, int offset )
    {
      builder.Append( new string( ' ', offset ) );
      builder.AppendFormat( "{0} {1} {2} \n", Name, GetType().Name, Transform.ColorTransform );
    }
#endif

    private void Call()
    {
      if ( _dirtyFinalMatrix )
      {
        _dirtyFinalMatrix = false;

        Matrix4x4 texelMatrix = Matrix4x4.identity;
        UpdateTexelHint();

        if ( _parent.ScaleGridData == null )
        {
          texelMatrix.m03 = -_texelHint.x;
          texelMatrix.m13 = -_texelHint.y;
        }

        _finalMatrix = texelMatrix * _transform.WorldMatrix;
      }

      _finalMatrix.m23 = MaskDepth;

      for ( int i = 0; i < Shapes.Count; i++ )
      {
        RenderableElement shape = Shapes[i];

        if ( shape.FillMesh != null )
        {
          if ( ( shape.FillMesh.vertexCount > 0 ) && ( !shape.Transparent || IsMask ) )
          {
            if ( this is MorphShape )
            {
              var morphShape = this as MorphShape;
              var morphElem = shape as MorphElement;
              var morphTag = this._character as UniDefineMorphShapeTag;
              
              var morphOut = new UniDefineMorphShapeTag.MorphLerped();
              if (morphTag.LerpMesh(morphElem, morphShape.Transform.Ratio, ref morphOut))
              {
                morphElem.FillMaterial.RenderMaterial.SetColor("_Color", morphOut.fillColor);
                SetupMaterialProperty(shape.FillMaterial, shape);
                DoRender(shape.FillMaterial, morphOut.mesh);
              }
            }
            else
            {
              SetupMaterialProperty(shape.FillMaterial, shape);
              DoRender(shape.FillMaterial, shape.FillMesh);
            }
          }
        }

        if ( shape.LineMesh != null )
        {
          if ( this is MorphShape && shape.LineMesh.name.IndexOf( "select" ) == -1)
          {
            var morphShape = this as MorphShape;
            var morphElem = shape as MorphElement;
            var morphTag = this._character as UniDefineMorphShapeTag;

            var morphOut = new UniDefineMorphShapeTag.MorphLerped();
            if ( morphTag.LerpLine( morphElem, morphShape.Transform.Ratio, 2.0f, ref morphOut ) )
            {
              SetupMaterialProperty( shape.LineMaterial, shape );
              DoRender( shape.LineMaterial, morphOut.mesh );
            }
          }
          else
          {
            if ( ( shape.LineMesh.vertexCount > 0 ) && ( !shape.TransparentLine || IsMask ) )
            {
              SetupMaterialProperty( shape.LineMaterial, shape );
              DoRender( shape.LineMaterial, shape.LineMesh );
            }
          }
        }
      }
      /**/

      /*
      foreach ( var shape in Shapes )
      {
        if ((shape.FillMesh.vertexCount > 0) && (!shape.Transparent || IsMask ))
        {
//          SetupMaterialProperty(shape.FillMaterial, shape);
//          DoRender(shape.FillMaterial, shape.FillMesh);
        }
      }
      /**/
    }

    protected virtual void SetupMaterialProperty( FlashMaterial material, RenderableElement element )
    {
      if ( material.ConcatenatedAlpha != _transform.ConcatenatedAlpha )
      {
        material.RenderMaterial.SetFloat( "_Alpha", _transform.ConcatenatedAlpha );
        material.ConcatenatedAlpha = _transform.ConcatenatedAlpha;
      }

      if ( EnableColorTransform && _transform.HasFinalColorTransform )
      {
        material.RenderMaterial.SetColor( "_Color", _transform.ConcatenatedColorTransform.MultColor );
        material.RenderMaterial.SetColor( "_AddColor", _transform.ConcatenatedColorTransform.AddColor );
        material.HasColorTransform = true;
      }
      else
      {
        if ( material.HasColorTransform )
        {
          material.RenderMaterial.SetColor( "_Color", Color.white );
          material.RenderMaterial.SetColor( "_AddColor", Color.clear );
          material.HasColorTransform = false;
        }
      }

      if ( EnableFilters && _transform.HasFinalColorMatrix )
      {
        material.RenderMaterial.SetMatrix( "_colorMatrix_mul", _transform.ConcatenatedColorMatrix_mul );
        material.RenderMaterial.SetVector( "_colorMatrix_add", _transform.ConcatenatedColorMatrix_add );
        material.Pin_HasColorMatrix = BooleanPin.Present;
      }
      else
      {
        if ( material.Pin_HasColorMatrix == BooleanPin.Present )
        {
          material.RenderMaterial.SetMatrix( "_colorMatrix_mul", Matrix4x4.identity );
          material.RenderMaterial.SetVector( "_colorMatrix_add", Vector4.zero );
          material.Pin_HasColorMatrix = BooleanPin.None;
        }
      }

      material.Pin_HasScaleGrid = ( _parent.ScaleGridData != null ) ? BooleanPin.Present : BooleanPin.None;
    }

    private void DoRender( FlashMaterial material, Mesh mesh )
    {
      if ( _banDoRender )
      {
        return;
      }

      material.Pin_IsMask = IsMask ? BooleanPin.Present : BooleanPin.None;

      switch ( Parent.Transform.BlendMode )
      {
      case BlendMode.Add: material.Pin_BlendMode = BlendModePin.Add; break;
      case BlendMode.Alpha: material.Pin_BlendMode = BlendModePin.Alpha; break;
      default: material.Pin_BlendMode = BlendModePin.Normal; break;
      }

      material.SetPass();

      Graphics.DrawMeshNow( mesh, _preTransformed ? _finalMatrix * _preTransform : _finalMatrix );

      // Uncomment next line to draw line/fill shapes in wireframe mode
      //DrawMesh(Shapes);
    }

    private void DrawMesh( IEnumerable renderable )
    {
      GL.LoadProjectionMatrix( GL.GetGPUProjectionMatrix( UniFlashPlayer.Camera.projectionMatrix, false ) );
      //for(int i = 0 ;  i < renderable)
      foreach ( RenderableElement element in renderable )
      {
        bool fillMesh = true;
        var mesh = fillMesh ? element.FillMesh : element.LineMesh;
        if ( mesh )
        {
          UniFlashPlayer.FlashDebug.DrawMaterial.SetPass( 0 );
          Vector3[] vertex = mesh.vertices;
          int[] triangles = mesh.triangles;
          Vector2[] uvs = mesh.uv;

          //Draw Vertexes
          GL.Begin( GL.QUADS );
          GL.Color( new Color( 0, 0, 0, 1F ) );
          for ( int i = 0; i < vertex.Length; ++i )
          {
            GL.Color( new Color( 0, 0, 0, 1F ) * ( ( (float)i / vertex.Length ) + 0.2F ) );
            Vector3 v = _transform.WorldMatrix.MultiplyPoint3x4( vertex[i] );
            v.z = 0;
            float s = 1;
            if ( i == 0 )
            {
              GL.Color( new Color( 1, 0, 0, 1F ) );
              s = 1.5F;
            }
            else if ( i == vertex.Length - 1 )
            {
              GL.Color( new Color( 0, 1, 0, 1F ) );
              s = 1.5F;
            }
            GL.Vertex( v + new Vector3( -2, 2 ) * s );
            GL.Vertex( v + new Vector3( 2, 2 ) * s );
            GL.Vertex( v + new Vector3( 2, -2 ) * s );
            GL.Vertex( v + new Vector3( -2, -2 ) * s );
          }
          GL.End();

          // Draw Mesh Shape
          GL.Begin( GL.LINES );
          GL.Color( new Color( 0, 0, 0, 1F ) );
          for ( int i = 0; i < triangles.Length; i += 3 )
          {
            Vector3 v0 = _transform.WorldMatrix.MultiplyPoint3x4( vertex[triangles[i]] + new Vector3( uvs[triangles[i]].x, uvs[triangles[i]].y, 0 ) );
            Vector3 v1 = _transform.WorldMatrix.MultiplyPoint3x4( vertex[triangles[i + 1]] + new Vector3( uvs[triangles[i + 1]].x, uvs[triangles[i + 1]].y, 0 ) );
            Vector3 v2 = _transform.WorldMatrix.MultiplyPoint3x4( vertex[triangles[i + 2]] + new Vector3( uvs[triangles[i + 2]].x, uvs[triangles[i + 2]].y, 0 ) );
            v0.z = 0;
            v1.z = 0;
            v2.z = 0;
            GL.Vertex( v0 );
            GL.Vertex( v1 );
            GL.Vertex( v1 );
            GL.Vertex( v2 );
            GL.Vertex( v2 );
            GL.Vertex( v0 );
          }
          GL.End();
        }
      }

    }
    protected void DispatchEvent<T>( T args, Action<T> method, EventHandler<T> ev ) where T : Flash.Event
    {
      // Method
      method( args );
      // Event
      if ( args.PropogateAcrossNode )
      {
        if ( ev != null )
          ev( this, args );
      }
    }
    protected override void PropagateToParent<T>( T evt )
    {
      if ( _parent != null && _parent != Stage )
        _parent.DispatchEvent( evt );
    }
    protected bool CanRiseEvent( Event args )
    {
      return args.PropogateAcrossHierarchy && _parent != null;// && _parent != stage;
    }
    private void SetPlayableOff()
    {
      if ( _playable )
      {
        _playable = false;
        _transform = (Transform)_transform.Clone();
      }
    }
    protected virtual void OnAdded( Event args )
    {

    }
    protected virtual void OnRemoved( Event args )
    {

    }
    protected void CloneShapes( List<RenderableElement> sharedShapes )
    {
      _shapes = new List<RenderableElement>( sharedShapes.Count );
      for ( int i = 0; i < sharedShapes.Count; i++ )
      {
        RenderableElement clone = (RenderableElement)sharedShapes[i].Clone();
        _shapes.Add( clone );
      }
    }

    private static Vector2 _lt = new Vector2( 10000, 10000 );
    private static Vector2 _rb = new Vector2( -10000, -10000 );

    private void UpdateWorldBounds()
    {
      if ( Shapes == null )
        return;

      if ( _transform.Right == Vector3.right ) // no rotate
      {
        _worldBounds = _transform.WorldMatrix * _localBounds;
      }
      else
      {
        _worldBounds.LeftTop = _lt;
        _worldBounds.RightBottom = _rb;

        for ( int i = 0; i < Shapes.Count; i++ )
        {
          if ( Shapes[i].FillMesh != null )
            _worldBounds.ExtendToMesh( Shapes[i].FillMesh, _transform.WorldMatrix );
        }
      }

      UpdateTexelHint();
    }

    protected void UpdateTexelHint()
    {
      if ( Rotation.z != 0 )
        return;

      if ( Application.platform == RuntimePlatform.OSXEditor || Application.platform == RuntimePlatform.OSXPlayer )
      {
        _texelHint.x = WorldBounds.LeftTop.x - (int)WorldBounds.LeftTop.x;
        _texelHint.y = WorldBounds.LeftTop.y - (int)WorldBounds.LeftTop.y;
      }
      else
      {
        _texelHint.x = WorldBounds.LeftTop.x - (int)WorldBounds.LeftTop.x - 0.5F;
        _texelHint.y = WorldBounds.LeftTop.y - (int)WorldBounds.LeftTop.y - 0.5F;
      }
    }

    protected void ClipShapes()
    {
      if ( Shapes == null )
        return;

      try
      {
        ////Profiler.BeginSample( "CLIP_SHAPES" );
        for ( int i = 0; i < Shapes.Count; i++ )
        {
          if ( Shapes[i].FillMesh != null )
          {
            Mesh newMesh = Mesh2DGen.GetClippedMesh( Parent.ScaleGridData.LocalSplitterBounds.LeftTop, Parent.ScaleGridData.LocalSplitterBounds.RightBottom, Shapes[i] );
            Shapes[i].FillMesh = newMesh;
          }
        }
        ////Profiler.EndSample();
        UpdateLocalBounds();
      }
      catch ( Exception err )
      {
        Debug.LogError( err.Message + "\n" + err.StackTrace );

      }
    }
  }
}
