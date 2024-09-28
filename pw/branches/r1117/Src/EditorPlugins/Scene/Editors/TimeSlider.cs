using System;
using System.Windows.Forms;
using EditorPlugins.Scene;

namespace EditorPlugins.Scene.Editors
{
	public partial class TimeSlider : UserControl
	{
    public event EventHandler<EventArgs> PausedChanged;
    public event EventHandler<EventArgs> SliderScroll;
    public event EventHandler<EventArgs> SliderValueChanged;
    public event EventHandler<EventArgs> SliderCaptureChanged;
    public event EventHandler<EventArgs> AnimationSpeedChanged;
    public event EventHandler<EventArgs> MeasureChanged;

		private bool measureInFrames;
		public bool MeasureInFrames
		{
			get 
			{
				return measureInFrames;
			}
			set 
      {
      	measureInFrames = value;
        OnMeasureInFramesChanged();
      }
		}

    public PlaySpeed AnimationSpeed 
    { 
      set
      {
      	if (value == PlaySpeed.Pause)
      		Paused = true;
      	else
      		trackBarSpeed.Value = (int) value;
      }
      get
      {
				if ( Paused )
					return PlaySpeed.Pause;

        return (PlaySpeed)trackBarSpeed.Value;
      }
    }

    public int CurrentFrame 
    { 
      get
      {
        return Math.Min((int)Math.Round(trackBarTimeSlider.Value * TimeToFramesMultiplier), trackBarTimeSlider.Maximum);
      }

      set
      {
				int currentFrame = (int)(value * FramesToTimeMultiplier);
      	//Log.Assert(currentFrame <= trackBarTimeSlider.Maximum);
      	trackBarTimeSlider.Value = currentFrame;
      }
    }

    private int frameNumbers;
    public int FrameNumbers
    {
      get
      {
        return frameNumbers;
      }
      set
      {
				if(frameNumbers == value) 
					return;

      	frameNumbers = (value <= 0) ? 0 : value;
        AdjustTickFrequency();
      }
    }

	  private bool sliderCapture;
    public bool SliderCapture 
    { 
      get { return sliderCapture;}
      private set
      {
        sliderCapture = value;
        RaiseSliderCaptureChanged();
      }
    }

    private double TimeToFramesMultiplier
		{ 
      get { return MeasureInFrames ? 1.0 : 0.03/* 1мс = .03кадра */; } 
    }

		private double FramesToTimeMultiplier
		{ 
      get { return MeasureInFrames ? 1.0 : 100.0/3.0; } 
    }

    private bool paused;
    public bool Paused
    {
      get { return paused; }
      set
      {
        paused = value;
        OnPause();
      }

    }

		public TimeSlider()
		{
			InitializeComponent();
			Paused = false;
			SetMeasureButtonText();
			trackBarTimeSlider.ScaleFactor = MeasureInFrames ? 0 : 1000;
      AnimationSpeed = PlaySpeed.X1;
      AdjustTickFrequency();
		}

	  private void AdjustTickFrequency()
		{
      trackBarTimeSlider.Maximum = (int)(frameNumbers * FramesToTimeMultiplier);

      int dist = (trackBarTimeSlider.ScaleFactor > 0
                  ? Math.Truncate(((double)trackBarTimeSlider.Maximum) / ((double)trackBarTimeSlider.ScaleFactor))
                  : trackBarTimeSlider.Maximum)
                  .ToString().Length * 7;

      trackBarTimeSlider.SmallChange = (int)FramesToTimeMultiplier;
      trackBarTimeSlider.TickFrequency = GetTickFrequency(trackBarTimeSlider.Maximum, trackBarTimeSlider.Size.Width, dist);
		}
		
    //max - максимальное значение
		//size - размер control'а в пикселях
		//minDist - минимальный интервал между засечками в пикселях
		//return - интервал, через который рисовать засечки, т.е. 0, return, 2*return, ...
		private static int GetTickFrequency( int max, int size, int minDist )
		{
			double[] multipliers = new double[] { 1.0, 2.0, 2.5, 5.0, 10.0 };

			if ( max == 0 )
				return 1;

			double tickWidth = (double)size / (double)max;
			if ( tickWidth > minDist )
				return 1;

			double m = Math.Pow( 10.0, Math.Floor( Math.Log10( (double)minDist / tickWidth ) ) );
			foreach ( double x in multipliers )
			{
				if ( x * m * tickWidth > minDist )
					return (int)( Math.Ceiling( x * m ) );
			}

			return (int)( Math.Ceiling( multipliers[multipliers.Length - 1] * m ) );
		}

		private void SetMeasureButtonText()
		{
			llMeasure.Text = MeasureInFrames ? "frames" : "seconds";
		}

    private void SetScaleFactor()
    {
      trackBarTimeSlider.ScaleFactor = MeasureInFrames ? 0 : 1000;
    }

    private void OnPause()
    {
      btnPlay.Text = paused ? "Play" : "Pause";
      RaisePausedChanged();
    }

    private void OnMeasureInFramesChanged()
    {
      SetMeasureButtonText();

      SetScaleFactor();

      AdjustTickFrequency();

      RaiseMeasureChanged();
    }

	  #region Event Senders

    private void RaisePausedChanged()
    {
      EventHandler<EventArgs> temp = PausedChanged;
      if (temp != null)
        temp(this, EventArgs.Empty);
    }

    private void RaiseSliderScroll()
    {
      EventHandler<EventArgs> temp = SliderScroll;
      if (temp != null)
        temp(this, EventArgs.Empty);
    }

    private void RaiseAnimationSpeedChanged()
    {
      EventHandler<EventArgs> temp = AnimationSpeedChanged;
      if (temp != null)
        temp(this, EventArgs.Empty);
    }

    private void RaiseSliderCaptureChanged()
    {
      EventHandler<EventArgs> temp = SliderCaptureChanged;
      if (temp != null)
        temp(this, EventArgs.Empty);
    }

    private void RaiseMeasureChanged()
    {
      EventHandler<EventArgs> temp = MeasureChanged;
      if (temp != null)
        temp(this, EventArgs.Empty);
    }

    #endregion

    #region Event Handlers

    private void llMeasure_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
    {
      MeasureInFrames = !MeasureInFrames;
    }

    private void btnPlay_Click(object sender, EventArgs e)
    {
      Paused = !Paused;
    }

    private void trackBarTimeSlider_Scroll(object sender, EventArgs e)
    {
      RaiseSliderScroll();
    }

    private void trackBarTimeSlider_ValueChanged(object sender, decimal value)
    {
      lblCurrentValue.Text = MeasureInFrames ? value.ToString() : ( value / 1000 ).ToString( "F1" );

      EventHandler<EventArgs> temp = SliderValueChanged;
      if (temp != null)
        temp(this, EventArgs.Empty);
    }

    private void trackBarTimeSlider_MouseDown(object sender, MouseEventArgs e)
    {
      SliderCapture = true;
    }

    private void trackBarTimeSlider_MouseUp(object sender, MouseEventArgs e)
    {
      SliderCapture = false;
    }

    private void OnInternalKeyDown(object sender, KeyEventArgs e)
    {
      this.OnKeyDown(e);
    }

    private void llMeasure_PreviewKeyDown(object sender, PreviewKeyDownEventArgs e)
    {
      if (e.KeyCode == Keys.Space)
      {
        OnKeyDown(new KeyEventArgs(e.KeyData));
      }
    }

    private void trackBarTimeSlider_ClientSizeChanged(object sender, EventArgs e)
    {
      AdjustTickFrequency();
    }

    private void trackBarSpeed_ValueChanged(object sender, EventArgs e)
    {
      RaiseAnimationSpeedChanged();
    }

    #endregion
  }
}
