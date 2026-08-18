using System;
using System.Collections.Generic;
using UnityEngine;

namespace Flash
{
  public abstract class Sprite : DisplayObjectContainer
  {
    // for mask setup
    private DisplayObject _currentMask;
    public DisplayObject CurrentMask
    {
      get { return _currentMask; }
      set { _currentMask = value; }
    }
    private int _targetMaskDepth;
    public int TargetMaskDepth
    {
      get { return _targetMaskDepth; }
      set { _targetMaskDepth = value; }
    }
    private bool _isPlaying = true;
    protected bool IsPlaying
    {
      get { return _isPlaying; }
      set { _isPlaying = value; }
    }
    private bool _reciveStopFromParent = true;
    public bool ReciveStopFromParent
    {
      get { return _reciveStopFromParent; }
      set { _reciveStopFromParent = value; }
    }
    private int _currentFrame = 1;
    public int CurrentFrame
    {
      get { return _currentFrame; }
      protected set
      {
        if ( value < 1 || value > TimeLine.Count )
        {
          Debug.LogError( string.Format( "Wrong frame number {0} in {1} less than 1 or more than framesCount = {2}", value, Name, TimeLine.Count ) );
        }
        _currentFrame = value;
        _currentFrame = Mathf.Clamp( _currentFrame, 1, TimeLine.Count );

        //Frame prevFrame = Children;
        Children = TimeLine[_currentFrame - 1];
      }
    }
    private WrapMode _wrapMode = WrapMode.Loop;
    public WrapMode WrapMode
    {
      get { return _wrapMode; }
      set { _wrapMode = value; }
    }
    protected SortedList<string, int> _labelToFrameMap;
    private SortedList<int, UniDoActionTag> _doActionsTags;

    public override void Push( UniBaseTag character )
    {
      base.Push( character );

      // Splitter
      if ( ( (UniDefineSpriteTag)character ).Scale9Grid != null )
        ScaleGridData = new ScaleGridData( this, ( (UniDefineSpriteTag)character ).Scale9Grid );

      // MediaPlayer has one frame in .ctor
      Frame frame = null;
      if ( this is MediaPlayer )
        frame = TimeLine[0];
      else
        frame = new Frame();

      List<IDisplayTag> tags = ( (UniDefineSpriteTag)character ).Tags;

      int i = 1;

      foreach ( IDisplayTag tag in tags )
      {
        tag.Execute( frame, this );

        if ( tag is UniFrameLabelTag )
        {
          if ( _labelToFrameMap == null )
            _labelToFrameMap = new SortedList<string, int>( 1 );

          _labelToFrameMap[( (UniFrameLabelTag)tag ).Label] = i;
        }

        if ( tag is UniShowFrameTag )
        {
          TimeLine.Add( frame );
          frame.ApplyInternal();
          frame = frame.CloneInternal();
          i++;
        }

        if ( tag is UniDoActionTag )
        {
          if ( _doActionsTags == null )
          {
            _doActionsTags = new SortedList<int, UniDoActionTag>( 1 );
          }

          _doActionsTags[i] = (UniDoActionTag)tag;
        }
      }

      Children = TimeLine[_currentFrame - 1];
    }

    public void DoActions()
    {
      // Do Actions
      if ( _doActionsTags != null )
      {
        for ( int frame = 0; frame < Timer.FramesElapsed; ++frame )
        {
          UniDoActionTag tag;
          if ( _doActionsTags.TryGetValue( _currentFrame + frame, out tag ) )
          {
            tag.DoActions( this );
          }
        }
      }
    }

    private static Event _exitFrameArgs = new Event( EventType.EXIT_FRAME, true );
    private static Event _enterFrameArgs = new Event( EventType.ENTER_FRAME, true );

    public void OnUpdateFrame()
    {
      ////Profiler.BeginSample( "INVOKE_NEXT_FRAME" );

      // On Exit Frame
      OnExitFrameInternal( _exitFrameArgs );

      if ( _isPlaying )
      {
        _currentFrame += Timer.FramesElapsed;

        if ( _currentFrame > TimeLine.Count )
        {
          if ( _wrapMode == WrapMode.Loop )
          {
            if ( Root == this )
              RewindRecursively();
            else
              Rewind();
          }
          if ( _wrapMode == WrapMode.Clamp )
            _currentFrame = TimeLine.Count;
        }

        Children = TimeLine[_currentFrame - 1];
      }

      // On Enter Frame
      OnEnterFrameInternal( _enterFrameArgs );

      ////Profiler.EndSample();
    }

    private void Rewind()
    {
      CurrentFrame = 1;
    }

    private void RewindRecursively()
    {
      CurrentFrame = 1;

      for ( int i = 0; i < TimeLine.Count; i++ )
      {
        for ( int j = 0; j < TimeLine[i].Count; j++ )
        {
          if ( TimeLine[i][j].DisplayObject is Sprite )
          {
            ( (Sprite)TimeLine[i][j].DisplayObject ).RewindRecursively();
          }
        }
      }
    }
  }
  public enum WrapMode
  {
    Loop,
    Clamp
  }
}