using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Flash
{

  public class Frame : IEnumerable<DisplayInstance>
  {
    private SortedDictionary<int, DisplayInstance> _flashDisplayList;
    private List<DisplayInstance> _displayList;

    public int Count
    {
      get { return _displayList.Count; }
    }

    public Frame()
    {
      _flashDisplayList = new SortedDictionary<int, DisplayInstance>();
      _displayList = new List<DisplayInstance>(1);
    }

    public Frame( SortedDictionary<int, DisplayInstance> displayList )
    {
      _flashDisplayList = displayList;
      _displayList = new List<DisplayInstance>(1);
    }

    public void UpdateTransforms()
    {
      for ( int i =0; i < _displayList.Count; i++ )
        {
          _displayList[i].DisplayObject.Transform = _displayList[i].Transform;
          _displayList[i].DisplayObject.Transform.ConcatenateRecursively( true, true );
        }
    }

    public Frame CloneInternal()
    {
      SortedDictionary<int, DisplayInstance> newChildren = new SortedDictionary<int, DisplayInstance>();
      foreach ( int depth in _flashDisplayList.Keys )
        newChildren.Add( depth, new DisplayInstance( _flashDisplayList[depth].DisplayObject, _flashDisplayList[depth].Transform ) );
      Frame clone = new Frame( newChildren );
      return clone;
    }

    public void AddInternal( int depth, DisplayInstance instance, DisplayObjectContainer parent )
    {
      instance.DisplayObject.Transform = instance.Transform;
      instance.DisplayObject.Parent = parent;
      
      _flashDisplayList.Add( depth, instance );
    }
    public DisplayInstance RemoveInternal( int depth )
    {
      DisplayInstance result = null;

      if ( _flashDisplayList.ContainsKey( depth ) )
      {
        result = _flashDisplayList[depth];
        _flashDisplayList.Remove( depth );
      }

      return result;
    }
    public void RemoveInternal( DisplayObject obj )
    {
      int depth = -1;
      if ( Contains( ref depth, obj ) )
      {
        RemoveInternal( depth );
      }
    }
    public void ReplaceTransformAtInternal( int depth, Transform data )
    {
      if ( !data.HasCxForm )
      {
        data.ColorTransform = _flashDisplayList[depth].Transform.ColorTransform;
        data.HasCxForm = _flashDisplayList[depth].Transform.HasCxForm;
      }
      if ( !data.HasTransform )
        data.Matrix = _flashDisplayList[depth].Transform.Matrix;
      if ( !data.HasBlendMode )
        data.BlendMode = _flashDisplayList[depth].Transform.BlendMode;

      _flashDisplayList[depth].Transform = data;
    }
    public void ApplyInternal()
    {
      foreach ( DisplayInstance instance in _flashDisplayList.Values )
        _displayList.Add( instance );
    }
    public void Add( int index, DisplayInstance instance, DisplayObjectContainer parent )
    {
      if ( instance.DisplayObject.Parent != null )
      {
        if ( parent == instance.DisplayObject.Parent )
          index--;
        instance.DisplayObject.Parent.RemoveChild( instance.DisplayObject );
      }

      instance.DisplayObject.Transform = instance.Transform;
      instance.DisplayObject.Parent = parent;

      _displayList.Insert( index, instance );
    }
    public DisplayObject Remove( int index )
    {
      DisplayObject result = _displayList[index].DisplayObject;
      _displayList.RemoveAt( index );
      return result;
    }
    public void Remove( DisplayObject obj )
    {
      int index = -1;
      if ( Contains( ref index, obj ) )
        _displayList.RemoveAt( index );
    }
    public IEnumerator<DisplayInstance> GetEnumerator()
    {
      return _displayList.GetEnumerator();
    }
    IEnumerator IEnumerable.GetEnumerator()
    {
      return GetEnumerator();
    }
    public DisplayInstance this[int index]
    {
      get { return _displayList[index]; }
      set { _displayList[index] = value; }
    }
    public void SwapAt( int index1, int index2 )
    {
      DisplayInstance instance1 = _displayList[index1];
      DisplayInstance instance2 = _displayList[index2];
      _displayList[index2] = instance1;
      _displayList[index1] = instance2;
    }
    public void Swap( DisplayObject child1, DisplayObject child2 )
    {
      int index1 = -1;
      int index2 = -1;
      if ( Contains( ref index1, child1 ) && Contains( ref index2, child2 ) )
      {
        DisplayInstance instance1 = _displayList[index1];
        DisplayInstance instance2 = _displayList[index2];
        _displayList[index2] = instance1;
        _displayList[index1] = instance2;
      }
    }
    public void SetIndex( DisplayObject obj, int index )
    {
      int oldIndex = -1;
      if ( Contains( ref oldIndex, obj ) )
      {
        DisplayInstance instance = _displayList[oldIndex];
        _displayList.RemoveAt( oldIndex );
        _displayList.Insert( index, instance );
      }
    }

    public bool Contains( ref int index, DisplayObject obj )
    {
      for ( int i = 0; i < _displayList.Count; ++i )
      {
        if ( obj == _displayList[i].DisplayObject )
        {
          index = i;
          return true;
        }
      }

      return false;
    }

  }
}
