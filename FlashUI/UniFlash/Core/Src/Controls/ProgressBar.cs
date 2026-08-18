using UnityEngine;

namespace Flash.Controls
{
	public class ProgressBar : SystemTooltipControl
	{
		private int _value;
		
		public virtual int Value
		{
			get { return _value; }
			set
			{
				_value = Mathf.Clamp(value, 0, 100);
				SetFrame(_value);
			}
		}

		/// <summary>
		/// Выставляет frame
		/// </summary>
		/// <param name="value">value должен быть от 0 до 100</param>
		private void SetFrame(int value)
		{
			#if UNITY_EDITOR

			bool hasError = false;

			if ( value < 0 )
			{
				Debug.LogError( this.Name + ": value cant' be less 0" );
				hasError = true;
			}
			
			if ( value > 100 )
			{
				Debug.LogError( this.Name + ": value cant' be greater 100" );
				hasError = true;
			}
				
			
			if ( TotalFrames == 0 )
			{
				Debug.LogError( this.Name + ": TotalFrames is 0" );
				hasError = true;
			}

			if(hasError)
				return;

			#endif

      int currentFrame = (int)((TotalFrames - 1) * value / 100f) + 1;
			GotoAndStop(currentFrame);
		}
	}
}
