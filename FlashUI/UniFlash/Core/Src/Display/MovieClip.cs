using System;
using System.Collections.Generic;
using System.Reflection;

namespace Flash
{
  public class MovieClip : Sprite
  {
    public int TotalFrames
    {
      get { return TimeLine.Count; }
    }

    public void Stop()
    {
      IsPlaying = false;
    }

    public void StopChildren()
    {
      Stop();
      for ( int i =0; i < Children.Count; i++ )
      {
        if ( Children[i].DisplayObject is MovieClip )
        {
          if ( ( (MovieClip)Children[i].DisplayObject ).ReciveStopFromParent )
            ( (MovieClip)Children[i].DisplayObject ).StopChildren();
        }
      }
    }

    public void Play()
    {
      IsPlaying = true;
    }

    public void PlayChildren()
    {
        Play();

        for (int i = 0; i < Children.Count; i++)
        {
            if (Children[i].DisplayObject is MovieClip)
            {
                ((MovieClip)Children[i].DisplayObject).Play();
                ((MovieClip)Children[i].DisplayObject).PlayChildren();
            }
        }
    }

    public void GotoPlayChildren(int frame = 1)
    {
        CurrentFrame = frame;
      Play();

      for ( int i = 0; i < Children.Count; i++ )
      {
        if ( Children[i].DisplayObject is MovieClip )
        {
          ( (MovieClip)Children[i].DisplayObject ).Play();
          ( (MovieClip)Children[i].DisplayObject ).PlayChildren();
        }
      }
    }

    public void GotoAndStop( int frame )
    {
      CurrentFrame = frame;
      Stop();
    }

    public void NextFrame()
    {
      if ( CurrentFrame < TotalFrames )
        GotoAndStop( CurrentFrame + 1 );
    }

    public void PrevFrame()
    {
      if ( CurrentFrame > 1 )
        GotoAndStop( CurrentFrame - 1 );
    }

    public void GotoAndPlay( int frame )
    {
      CurrentFrame = frame;
      Play();
    }

    public int GetFrameByName( string name )
    {
      int i;
      if ( _labelToFrameMap != null && _labelToFrameMap.TryGetValue( name, out i ) )
        return i;
      return -1;
    }

    public override void UpdateFrame()
    {
      if (Visible)
      {
        base.UpdateFrame();

        DoActions();

        if (TotalFrames > 1)
          OnUpdateFrame();
      }
    }
  }
}
