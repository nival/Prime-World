using System;
using FlashView.Utils;

namespace Flash.Utils
{
	public class UITimer
	{
		private DateTime _dt = DateTime.MinValue;

		public void StartTimer()
		{
			_dt = DateTime.Now;
		}

		public void StopTimer()
		{
			_dt = DateTime.MinValue;
		}

		public virtual TimeSpan SpentTime
		{
			get
			{
				if ( _dt != DateTime.MinValue )//timer is started
				{
					return DateTime.Now - _dt;
				}

				return new TimeSpan( 0, 0, 0 );				
			}
		}

		public virtual string FormattedTime
		{
			get { return TimeFormat.ConvertSecondsToHoursMinutes(SpentTime); }
		}
	}
}
