using System;
using UnityEngine;

namespace Flash
{
  public class Timer : MonoBehaviour
  {
    // 40 ms = 25 fps
    private static float _timeDuration = 0.04F;
    private static float _timer;
    private static float _lastTick;

    public static float TimeDuration
    {
      get { return _timeDuration; }
      set { _timeDuration = value; }
    }

    private static int _framesElapsed;

    public static int FramesElapsed
    {
      get { return _framesElapsed; }
    }

    public static event EventHandler<EventArgs> HalfSecTick;

    protected void Awake()
    {
      _lastTick = 0;
    }

    protected void Update()
    {
      _framesElapsed = 0;
      _timer += Time.deltaTime;

      if (_timer > _timeDuration)
      {
        _framesElapsed = (int)(_timer / _timeDuration);
        _timer -= _framesElapsed*_timeDuration;

        if (_framesElapsed > 100)
        {
          Debug.LogError(_framesElapsed);
        }
      }

      if ((Time.time - _lastTick) >= 0.5F)
      {
        _lastTick = Time.time;
        if (HalfSecTick != null)
        {
          HalfSecTick(this, null);
        }
      }
    }
  }
}
