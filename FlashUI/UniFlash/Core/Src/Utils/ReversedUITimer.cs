using System;

namespace Flash.Utils
{
	public class ReversedUITimer : UITimer
	{
		private readonly TimeSpan _minValue = new TimeSpan( 0, 0, 0 );

		public TimeSpan StartValue { get; set; }

		/// <summary>
		/// Таймер с обратным отсчетом
		/// </summary>
		public ReversedUITimer()
		{
			StartValue = new TimeSpan( 0, 0, 60 );
		}

		/// <summary>
		/// Таймер с обратным отсчетом
		/// </summary>
		/// <param name="startSeconds">Стартовое значение в секундах</param>
		public ReversedUITimer( float startSeconds )
		{
			StartValue = new TimeSpan( 0, 0, (int)startSeconds );
		}

		public override TimeSpan SpentTime
		{
			get
			{
				TimeSpan time = StartValue - base.SpentTime;

				if ( time <= _minValue )
					return _minValue;

				return time;
			}
		}
	}
}
