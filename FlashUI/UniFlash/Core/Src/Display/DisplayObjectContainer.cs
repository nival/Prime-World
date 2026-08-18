#define ENABLE_POST_PROCESS
using System;
using System.Collections.Generic;
#if UNITY_EDITOR
using System.Text;
#endif
using Flash.Controls;
using SwfDotNet.IO.Tags;
using UnityEngine;

namespace Flash
{
  public abstract class DisplayObjectContainer : InteractiveObject
  {
#if ENABLE_POST_PROCESS
    private static Stack<RenderTexture> _rtStack = new Stack<RenderTexture>();
#endif
    private Frame _children;
    public Frame Children
    {
      get
      {
        if ( _children == null )
          _children = new Frame();
        return _children;
      }
      protected set
      {
        _children = value;
        _children.UpdateTransforms();
      }
    }
    private List<Frame> _timeLine = new List<Frame>( 1 );
    public List<Frame> TimeLine
    {
      get { return _timeLine; }
      protected set { _timeLine = value; }
    }
    private bool _allowInBoundsCalculation = true;
    public bool AllowInBoundsCalculation
    {
      get { return _allowInBoundsCalculation; }
      set { _allowInBoundsCalculation = value; }
    }
    private bool _dirtyScaleGridData;
    public bool DirtyScaleGridData
    {
      get { return _dirtyScaleGridData; }
    }
    private ScaleGridData _scaleGridData;
    public ScaleGridData ScaleGridData
    {
      get
      {
        return _scaleGridData;
      }
      protected set { _scaleGridData = value; }
    }
    public int NumChildren
    {
      get
      {
        if ( _children == null )
          return 0;

        return _children.Count;
      }
    }
    private bool _isRoot;
    public bool IsRoot
    {
      get { return _isRoot; }
    }
    public override DisplayObject Mask
    {
      get { return base.Mask; }
      set
      {
        if ( Mask == value )
          return;

        if ( Parent != null && Parent.Mask != null && value == null )
          return;

        base.Mask = value;

        for ( int i = 0; i < _timeLine.Count; i++ )
        {
          for ( int j = 0; j < _timeLine[i].Count; j++ )
            _timeLine[i][j].DisplayObject.Mask = value;
        }
      }
    }
    public override bool IsMask
    {
      get
      {
        return base.IsMask;
      }
      set
      {
        if ( IsMask == value )
          return;

        if ( Parent != null && Parent.IsMask && value == false )
          return;

        base.IsMask = value;

        for ( int i = 0; i < _timeLine.Count; i++ )
        {
          for ( int j = 0; j < _timeLine[i].Count; j++ )
          {
            _timeLine[i][j].DisplayObject.IsMask = value;
          }
        }
      }
    }
    private bool _mouseChildren = true;
    public bool MouseChildren
    {
      get { return _mouseChildren; }
      set
      {
        // if set same value then discard
        if ( _mouseChildren == value )
          return;
        // if parent has false then discard
        if ( !Parent.MouseChildren && value )
          return;

        _mouseChildren = value;

        for ( int i = 0; i < _timeLine.Count; i++ )
          for ( int j = 0; j < _timeLine[i].Count; j++ )
            if ( _timeLine[i][j].DisplayObject is DisplayObjectContainer )
              ( (DisplayObjectContainer)_timeLine[i][j].DisplayObject ).MouseChildren = value;

      }
    }
    public override bool EnableColorTransform
    {
      get
      {
        return base.EnableColorTransform;
      }
      set
      {
        if ( base.EnableColorTransform == value )
          return;

        if ( !Parent.EnableColorTransform && value )
          return;

        base.EnableColorTransform = value;

        for ( int i = 0; i < TimeLine.Count; i++ )
          for ( int j = 0; j < _timeLine[i].Count; j++ )
            _timeLine[i][j].DisplayObject.EnableColorTransform = value;
      }
    }

    public override bool EnableFilters
    {
      get
      {
        return base.EnableFilters;
      }
      set
      {
        if ( base.EnableFilters == value )
          return;

        if ( !IgnoreParentFiltersSwitching && !Parent.EnableFilters && value )
          return;

        base.EnableFilters = value;

        for ( int i = 0; i < TimeLine.Count; i++ )
          for ( int j = 0; j < _timeLine[i].Count; j++ )
            if ( !_timeLine[i][j].DisplayObject.IgnoreParentFiltersSwitching )
              _timeLine[i][j].DisplayObject.EnableFilters = value;
      }
    }
    public override Bounds WorldBounds
    {
      get
      {
        if ( _dirtyBounds )
        {
          _dirtyBounds = false;
          _worldBounds = Transform.WorldMatrix * LocalBounds;
        }
        return _worldBounds;
      }
    }

#if ENABLE_POST_PROCESS
    private Material _blendMaterial;
    public Material BlendMaterial
    {
      get
      {
        if ( _blendMaterial == null )
          _blendMaterial = new Material( Shader.Find( "Flash/Blend" ) );
        return _blendMaterial;
      }
    }
    private RenderTexture _rt = null;
#endif

#if ENABLE_POST_PROCESS
    static DisplayObjectContainer()
    {
      _rtStack.Push( null );
    }
    private void PushRT()
    {
      _rt = RenderTexture.GetTemporary( UniFlashPlayer.Width, UniFlashPlayer.Height, 16, RenderTextureFormat.ARGB32 );
      RenderTexture.active = _rt;
      _rtStack.Push( _rt );
      GL.Clear( true, true, new Color( 0, 0, 0, 0 ) );
    }
    private void PopRT()
    {
      _rtStack.Pop();
      RenderTexture.active = _rtStack.Peek();

      if ( RenderTexture.active == null )
      {
        BlendMaterial.SetFloat( "_grab", 1 );
        Graphics.Blit( _rt, RenderTexture.active, BlendMaterial, -1 );
      }
      else
      {
        BlendMaterial.SetFloat( "_grab", 0 );
        BlendMaterial.SetTexture( "_FrameTex", RenderTexture.active );
        Graphics.Blit( _rt, RenderTexture.active, BlendMaterial, 1 );
      }
      RenderTexture.ReleaseTemporary( _rt );
    }
#endif

    public override void Destroy()
    {
      base.Destroy();

      for ( int i = 0; i < TimeLine.Count; i++ )
      {
        for ( int j = TimeLine[i].Count - 1; j > -1; j-- )
        {
          TimeLine[i][j].DisplayObject.Destroy();
        }
      }
    }


    public override void PreRender()
    {
#if ENABLE_POST_PROCESS
      // TODO : _cacheAsBitmap не работает правильно при анимации
      if ( Transform.BlendMode == BlendMode.Layer )
      {
        PushRT();
      }
#endif
      if ( IsMask && !Parent.IsMask )
      {
        _currentMaskDepth -= 0.001F;
        MaskDepth = _currentMaskDepth;
      }

      // update scalegrid
      if ( _scaleGridData != null && _dirtyScaleGridData )
      {
        UpdateTexelHint();
        _scaleGridData.UpdateScaleGrid();
        _dirtyScaleGridData = false;
      }

      if ( _scaleGridData != null )
      {
        Shader.SetGlobalMatrix( "_scaleGridData", _scaleGridData.ScaleGridSummary );
      }


      RenderChildren();

#if ENABLE_POST_PROCESS
      if ( Transform.BlendMode == BlendMode.Layer )
        PopRT();
#endif

      //if (ScaleGridData != null)
      //ScaleGridData.DrawScaleGrid();

      if ( ShowBounds )
      {
        DrawBounds( new Color( 1, 0, 0, 0.2F ), false );
        DrawBounds( new Color( 1, 0, 0, 1 ), true );
      }
    }
    public virtual void RenderChildren()
    {
      // Event (invers order)
      for ( int i = Children.Count - 1; i >= 0; --i )
      {
        Children[i].DisplayObject.OnRenderInternal( null );
      }

      // Render children
      for ( int i = 0; i < Children.Count; i++ )
      {
        DisplayObject child = Children[i].DisplayObject;

        if ( child.Visible )
        {
          // Mask culling
          if ( child.Mask != null )
          {
            if ( !child.Mask.WorldBounds.Intersects( child.WorldBounds ) )
              continue;
          }

          child.PreRender();
        }
      }
    }

    public void CallPostRender()
    {
      for ( int i = Children.Count - 1; i >= 0; --i )
      {
        Children[i].DisplayObject.OnPostRenderInternal(null);
      }

      for ( int i = 0; i < Children.Count; i++ )
      {
        var child = Children[i].DisplayObject as DisplayObjectContainer;

        if (child!=null && child.Visible )
        {
          // Mask culling
          if ( child.Mask != null )
          {
            if ( !child.Mask.WorldBounds.Intersects( child.WorldBounds ) )
              continue;
          }

          child.CallPostRender();
        }
      }
    }


    public DisplayObject GetChildByName( string name )
    {
      for ( int i = 0; i < _children.Count; i++ )
      {
        if ( _children[i] != null && _children[i].DisplayObject.Name == name )
          return _children[i].DisplayObject;
      }

      return null;
    }

    public T GetChildByName<T>( string name ) where T : DisplayObject
    {
      for ( int i = 0; i < _children.Count; i++ )
      {
        if ( _children[i] != null && _children[i].DisplayObject.Name == name )
          return _children[i].DisplayObject as T;
      }

      return null;
    }

    public DisplayObject FindChildInHierarchy( string name )
    {
      for ( int i = 0; i < _timeLine.Count; i++ )
      {
        for ( int j = 0; j < _timeLine[i].Count; j++ )
        {
          if ( _timeLine[i][j] != null && _timeLine[i][j].DisplayObject.Name == name )
            return _timeLine[i][j].DisplayObject;

          if ( _timeLine[i][j].DisplayObject is DisplayObjectContainer )
          {
            DisplayObject result = ( _timeLine[i][j].DisplayObject as DisplayObjectContainer ).FindChildInHierarchy( name );
            if ( result != null )
              return result;
          }
        }
      }

      return null;
    }

    public DisplayObject GetChildAt( int index )
    {
      return _children[index].DisplayObject;
    }

    public int GetChildIndex( DisplayObject obj )
    {
      int index = -1;
      if ( _children.Contains( ref index, obj ) )
        return index;

      return -1;
    }

    public void SetChildIndex( DisplayObject obj, int index )
    {
      _children.SetIndex( obj, index );
    }

    public void SwapChildrenAt( int index1, int index2 )
    {
      _children.SwapAt( index1, index2 );
    }

    public void SwapChildren( DisplayObject child1, DisplayObject child2 )
    {
      _children.Swap( child1, child2 );
    }

    public void AddChild( DisplayObject obj )
    {
      AddChildAt( _children.Count, obj );
    }
    public void AddChildAt( int depth, DisplayObject obj )
    {
      DisplayInstance instance = new DisplayInstance( obj, ( obj.Transform ?? new Transform() ) );
      _children.Add( depth, instance, this );
      obj.ResetRoot();

      // mask setup
      obj.Mask = Mask;
      // is mask setup
      obj.IsMask = IsMask;
      // mouse children setup
      if ( obj is DisplayObjectContainer )
      {
        DisplayObjectContainer dc = obj as DisplayObjectContainer;
        if ( _mouseChildren != dc.MouseChildren )
          dc.MouseChildren = _mouseChildren;
      }
      // Filters and Color Transform
      if ( !EnableFilters )
        obj.EnableFilters = EnableFilters;
      if ( !EnableColorTransform )
        obj.EnableColorTransform = EnableColorTransform;

      //if (!(this is Stage))
      //    UpdateLocalBounds();

      Event args = new Event( EventType.ADDED, true );
      obj.OnAddedInternal( args );
    }

    public void RemoveChild( DisplayObject obj )
    {
      _children.Remove( obj );
      obj.ResetRoot();

      Event args = new Event( EventType.REMOVED, true );
      obj.OnRemovedInternal( args );
    }

    public void RemoveChildFromTimeline( DisplayObject obj )
    {
      for ( int i = 0; i < TimeLine.Count; i++ )
        TimeLine[i].Remove( obj );

      obj.ResetRoot();
      Event args = new Event( EventType.REMOVED, true );
      obj.OnRemovedInternal( args );
    }
    public void RemoveChildAt( int depth )
    {
      DisplayObject removed = _children.Remove( depth );

      if ( removed != null )
      {
        removed.ResetRoot();
        Event args = new Event( EventType.REMOVED, true );
        removed.OnRemovedInternal( args );
      }
    }

    public override void UpdateLocalBounds()
    {
      UpdateLocalBounds( false );
    }

    public override void UpdateLocalBounds( bool ignoreInvisibleObjects )
    {
      if ( _children == null || _children.Count == 0 )
        return;

      SetDirty();

      int index = 0;
      Bounds bounds = new Bounds();
      for ( int i = 0; i < _children.Count; i++ )
      {
        if ( _children[i] != null ) // mask is in ignor
        {
          if ( ignoreInvisibleObjects && !_children[i].DisplayObject.Visible || !AllowInBoundsCalculation )
            continue;

          _children[i].DisplayObject.UpdateLocalBounds( ignoreInvisibleObjects );

          Bounds tansformedBounds = _children[i].DisplayObject.Transform.Matrix * _children[i].DisplayObject.LocalBounds;

          if ( index == 0 )
            bounds = tansformedBounds;
          else
            bounds.ExtendToBounds( tansformedBounds );

          LocalBounds = bounds;
          ++index;
        }
      }

      //Profiler.EndSample();
    }

    public void SetAsRoot()
    {
      _isRoot = true;
    }

    public override void UpdateFrame()
    {
      for ( int i = 0; i < Children.Count; i++ )
      {
        Children[i].DisplayObject.UpdateFrame();
      }
    }

    public override void SetDirty()
    {
      base.SetDirty();
      if ( _scaleGridData != null )
        _dirtyScaleGridData = true;
    }

    public override void Dispose()
    {
      for ( int i = 0; i < _timeLine.Count; i++ )
      {
        for ( int j = 0; j < _timeLine[i].Count; j++ )
        {
          _timeLine[i][j].DisplayObject.Dispose();
        }
      }
    }

    public void ClearChildren()
    {
      for ( int i = 0; i < TimeLine.Count; i++ )
      {
        for ( int j = TimeLine[i].Count - 1; j >= 0; --j )
        {
          TimeLine[i].Remove( j );
        }
      }
    }

    /// <summary>
    /// Проходит по всем вышестоящим элементам и определяет, действительно ли текущий элемент виден
    /// </summary>
    /// <returns>true если элемент видим, false в противном случае</returns>
    public bool IsVisibleThroughHierarchy()
    {
      DisplayObjectContainer current = this;

      while ( current != null )
      {
        if ( !current.Visible )
          return false;

        current = current.Parent;
      }

      return true;
    }

#if UNITY_EDITOR
    public void DampHierarchyForFrame( StringBuilder builder, int frame )
    {
      builder.AppendFormat( "{0} {1}\n", Name, GetType().Name );
      Frame fr = TimeLine[frame];
      foreach ( DisplayInstance displayInstance in fr )
      {
        displayInstance.DisplayObject.DampDisplayObject( builder, 4 );
      }
    }
    public override void DampDisplayObject( StringBuilder builder, int offset )
    {
      base.DampDisplayObject( builder, offset += 4 );

      foreach ( DisplayInstance displayInstance in Children )
      {
        displayInstance.DisplayObject.DampDisplayObject( builder, offset += 4 );
      }
    }
#endif
  }
}
