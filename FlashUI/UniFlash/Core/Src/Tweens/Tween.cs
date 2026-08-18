using System;
using System.Linq.Expressions;
using System.Reflection;
using Flash.Utils;
using UnityEngine;

namespace Flash.Tweens
{
  //NOTE http://www.republicofcode.com/tutorials/flash/as3tweenclass/
  public class Tween<T> where T : DisplayObject
  {

    #region Nested Types

    private class TweenState
    {
      public readonly float Begin;
      public readonly float End;
      public readonly float Duration;

      public readonly Func<double, EasingType, float> EasingFunction;// returns from 0 to 1 or vice versa
      public readonly EasingType EasingType;

      public TweenState( float begin, float end, float duration, Func<double, EasingType, float> easingFunction, EasingType easingType )
      {
        Begin = begin;
        End = end;
        Duration = duration;

        EasingType = easingType;
        EasingFunction = easingFunction;
      }

      public float GetValue( float time )
      {
        return Begin + ( End - Begin ) * EasingFunction( time / Duration, EasingType );
      }
    }

    #endregion

    private readonly T _target;
    private readonly PropertyInfo _property;
    private readonly Func<double, EasingType, float> _easingFunction;
    private readonly EasingType _easingType;

    public float Begin { get; set; }
    public float End { get; set; }
    public float Duration { get; set; }

    public bool IsStarted { get; private set; }

    private float _time;
    private TweenState _currentState = null;

    #region Events
#pragma warning disable 67
    public event Action MotionFinish;	// This event is triggered when the motion finishes by reaching its end point.
    public event Action MotionStop;		// This event is triggered when the motion is stopped by the Stop() method.
    public event Action MotionStart;	// This event is triggered when the motion is started using the Start() method.
    public event Action MotionResume;	// This event is triggered when the motion is resumed by the Resume() method.
    public event Action MotionChange;	// This event is continuously triggered while the motion is running.
    //public event Action MotionLoop;		// This event is supposed to be triggered when the motion is restarted through a looping action.
#pragma warning restore 67
    #endregion

    public Tween( T target, Expression<Func<T, float>> expression, Func<double, EasingType, float> easingFunction, EasingType easingType )
      : this( target, expression, easingFunction, easingType, 0, 0, 0 ) { }

    public Tween( T target, Expression<Func<T, float>> expression, Func<double, EasingType, float> easingFunction, EasingType easingType, float begin, float end, float duration )
    {
      _target = target;
      _property = GetPropertyInfo( expression );

      _easingFunction = easingFunction;
      _easingType = easingType;

      Begin = begin;
      End = end;
      Duration = duration;
    }

    public void Start()
    {
      _time = 0;
      _currentState = new TweenState( Begin, End, Duration, _easingFunction, _easingType );

      _target.Render += OnRender;
      IsStarted = true;
      EventHelper.Invoke( MotionStart );
    }

    public void Stop()
    {
      Stop( false );
    }

    public void Stop( bool moveToEnd )
    {
      _target.Render -= OnRender;

      if ( !IsStarted )
        return;

      if (moveToEnd)
        SetPropertyValue(_currentState.End);
      
      IsStarted = false;
      EventHelper.Invoke( MotionStop );
    }

    public void Resume()
    {
      _target.Render += OnRender;
      IsStarted = true;
      EventHelper.Invoke( MotionResume );
    }

    private void MotionFinished()
    {
      _target.Render -= OnRender;
      SetPropertyValue( _currentState.End );
      IsStarted = false;
      EventHelper.Invoke( MotionFinish );
    }

    private void OnRender( object sender, Event e )
    {
      if ( _time >= _currentState.Duration )
      {
        MotionFinished();
        return;
      }

      _time += Time.deltaTime;

      _time = (float) Math.Round(_time, 2);

      _time = Mathf.Clamp( _time, 0, Duration );

      float prop = _currentState.GetValue(_time);

      SetPropertyValue(  (float) Math.Round(prop,2) );

      EventHelper.Invoke( MotionChange );
    }

    private void SetPropertyValue( float value )
    {
      _property.SetValue( _target, value, null );
    }
    /// <exception>Throws ArgumentException if invalid expression type.</exception>
    private static PropertyInfo GetPropertyInfo( Expression<Func<T, float>> expression )
    {
      Expression body = expression;
      if ( body is LambdaExpression )
      {
        body = ( (LambdaExpression)body ).Body;
      }

      if ( body.NodeType == ExpressionType.MemberAccess )
      {
        return ( (MemberExpression)body ).Member as PropertyInfo;
      }
      else
      {
        throw new ArgumentException( "Invaluid expression type" );
      }
    }
  }
}
