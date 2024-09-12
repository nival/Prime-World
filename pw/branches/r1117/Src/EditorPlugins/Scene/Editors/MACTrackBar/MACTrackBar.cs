using System;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Text;
using System.Windows.Forms;
using EConTech.Windows.MACUI.Designer;

namespace EConTech.Windows.MACUI
{

	#region Declaration

	/// <summary>
	/// Represents the method that will handle a change in value.
	/// </summary>
	public delegate void ValueChangedHandler(object sender, decimal value);

	public enum MACBorderStyle
	{
		/// <summary>
		/// No border.
		/// </summary>
		None,
		/// <summary>
		/// A dashed border.
		/// </summary>
		Dashed, //from ButtonBorderStyle Enumeration
		/// <summary>
		/// A dotted-line border.
		/// </summary>
		Dotted, //from ButtonBorderStyle Enumeration
		/// <summary>
		/// A sunken border.
		/// </summary>
		Inset, //from ButtonBorderStyle Enumeration
		/// <summary>
		/// A raised border.
		/// </summary>
		Outset, //from ButtonBorderStyle Enumeration
		/// <summary>
		/// A solid border.
		/// </summary>
		Solid, //from ButtonBorderStyle Enumeration

		/// <summary>
		/// The border is drawn outside the specified rectangle, preserving the dimensions of the rectangle for drawing.
		/// </summary>
		Adjust, //from Border3DStyle Enumeration
		/// <summary>
		/// The inner and outer edges of the border have a raised appearance.
		/// </summary>
		Bump, //from Border3DStyle Enumeration
		/// <summary>
		/// The inner and outer edges of the border have an etched appearance.
		/// </summary>
		Etched, //from Border3DStyle Enumeration
		/// <summary>
		/// The border has no three-dimensional effects.
		/// </summary>
		Flat, //from Border3DStyle Enumeration
		/// <summary>
		/// The border has raised inner and outer edges.
		/// </summary>
		Raised, //from Border3DStyle Enumeration
		/// <summary>
		/// The border has a raised inner edge and no outer edge.
		/// </summary>
		RaisedInner, //from Border3DStyle Enumeration
		/// <summary>
		/// The border has a raised outer edge and no inner edge.
		/// </summary>
		RaisedOuter, //from Border3DStyle Enumeration
		/// <summary>
		/// The border has sunken inner and outer edges.
		/// </summary>
		Sunken, //from Border3DStyle Enumeration
		/// <summary>
		/// The border has a sunken inner edge and no outer edge.
		/// </summary>
		SunkenInner, //from Border3DStyle Enumeration
		/// <summary>
		/// The border has a sunken outer edge and no inner edge.
		/// </summary>
		SunkenOuter //from Border3DStyle Enumeration
	}

	#endregion

	/// <summary>
	///	  <para>
	///		MACTrackBar represents an advanced track bar that is very better than the 
	///		standard trackbar.
	///   </para>
	///   <para>
	///   MACTrackBar supports the following features:
	///   <list type="bullet">
	///     <item><c>MAC style, Office2003 style, IDE2003 style and Plain style.</c></item>
	///     <item><c>Vertical and Horizontal trackbar.</c></item>
	///     <item><c>Supports many Text Tick styles: None, TopLeft, BottomRight, Both. You can change Text Font, ForeColor.</c></item> 
	///     <item><c>Supports many Tick styles: None, TopLeft, BottomRight, Both.</c></item> 
	///     <item><c>You can change <see cref="MACTrackBar.TickColor"/>, <see cref="MACTrackBar.TickFrequency"/>, <see cref="MACTrackBar.TickHeight"/>.</c></item> 
	///     <item><c>You can change <see cref="MACTrackBar.TrackerColor"/> and <see cref="MACTrackBar.TrackerSize"/>.</c></item> 
	///     <item><c>You can change <see cref="MACTrackBar.TrackLineColor"/> and <see cref="MACTrackBar.TrackLineHeight"/>.</c></item> 	
	///     <item><c>Easy to Use and Integrate in Visual Studio .NET.</c></item> 
	///     <item><c>100% compatible to the standard control in VS.NET.</c></item> 
	///     <item><c>100% managed code.</c></item> 
	///     <item><c>No coding RAD component.</c></item> 
	///   </list>
	///   </para>
	/// </summary>
	[Description("MACTrackBar represents an advanced track bar that is very better than the standard trackbar.")]
	[ToolboxBitmap(typeof (MACTrackBar), "Editors.MACTrackBar.MACTrackBar.bmp")]
	[Designer(typeof (MACTrackBarDesigner))]
	[DefaultProperty("Maximum")]
	[DefaultEvent("ValueChanged")]
	public class MACTrackBar : Control
	{
		// Instance fields
		private bool _autoSize = true;
		private Color _borderColor = SystemColors.ActiveBorder;
		private MACBorderStyle _borderStyle = MACBorderStyle.None;

		private int _indentHeight = 6;
		private int _indentWidth = 6;
		private int _largeChange = 2;
		private int _maximum = 10;
		private int _minimum = 0;
		private Orientation _orientation = Orientation.Horizontal;
		private int _smallChange = 1;
		private TickStyle _textTickStyle = TickStyle.BottomRight;

		private Color _tickColor = Color.Black;
		private int _tickFrequency = 1;
		private int _tickHeight = 2;
		private TickStyle _tickStyle = TickStyle.BottomRight;

		private Color _trackerColor = SystemColors.Control;
		public RectangleF _trackerRect = RectangleF.Empty;
		private Size _trackerSize = new Size( 10, 20 );
		private Color _trackLineColor = SystemColors.Control;
		private int _trackLineHeight = 3;
		private int _value = 0;

		private bool leftButtonDown = false;
		private float mouseStartPos = -1;

		/// <summary>
		/// Occurs when the property Value has been changed.
		/// </summary>
		public event ValueChangedHandler ValueChanged;

		/// <summary>
		/// Occurs when either a mouse or keyboard action moves the slider.
		/// </summary>
		public event EventHandler Scroll;

		#region Public Contruction

		/// <summary>
		/// Constructor method of <see cref="MACTrackBar"/> class
		/// </summary>
		public MACTrackBar()
		{
			base.MouseDown += new MouseEventHandler( OnMouseDownSlider );
			base.MouseUp += new MouseEventHandler( OnMouseUpSlider );
			base.MouseMove += new MouseEventHandler( OnMouseMoveSlider );

			SetStyle( ControlStyles.AllPaintingInWmPaint |
			          ControlStyles.ResizeRedraw |
			          ControlStyles.DoubleBuffer |
			          ControlStyles.SupportsTransparentBackColor,
			          true );

			Font = new Font( "Verdana", 8.25F, FontStyle.Bold, GraphicsUnit.Point, (byte) 0 );
			ForeColor = Color.FromArgb( 123, 125, 123 );
			BackColor = Color.Transparent;

			_tickColor = Color.FromArgb( 148, 146, 148 );
			_tickHeight = 4;

			_trackerColor = Color.FromArgb( 24, 130, 198 );
			_trackerSize = new Size( 16, 16 );
			_indentWidth = 6;
			_indentHeight = 6;

			_trackLineColor = Color.FromArgb( 90, 93, 90 );
			_trackLineHeight = 3;

			_borderStyle = MACBorderStyle.None;
			_borderColor = SystemColors.ActiveBorder;

			_autoSize = true;
			Height = FitSize.Height;
		}

		#endregion

		#region Public Properties

		/// <summary>
		/// Gets or sets the height and width of the control.
		/// </summary>
		/// <remarks>You can see <see cref="Control.Size"/> for more detail.</remarks>
		/// <value>The <see cref="Size"/> object that represents the height and width of the control in pixels.</value>
		[Description("Gets or sets the height and width of the control.")]
		[Category("Layout")]
		public new Size Size
		{
			get { return base.Size; }
			set
			{
				// Calculate the Position for children controls
				if ( _orientation == Orientation.Horizontal )
				{
					Width = value.Width;
					Height = FitSize.Height;
				}
				else
				{
					Width = FitSize.Width;
					Height = value.Height;
				}
				//=================================================
			}
		}

		/// <summary>
		/// Gets or sets a value indicating whether the height or width of the track bar is being automatically sized.
		/// </summary>
		/// <remarks>You can set the AutoSize property to true to cause the track bar to adjust either its height or width, depending on orientation, to ensure that the control uses only the required amount of space.</remarks>
		/// <value>true if the track bar is being automatically sized; otherwise, false. The default is true.</value>
		[Category("Behavior")]
		[Description("Gets or sets the height of track line.")]
		[DefaultValue(4)]
		public new bool AutoSize
		{
			get { return _autoSize; }

			set
			{
				if ( _autoSize != value )
				{
					_autoSize = value;
					if ( _autoSize == true )
						Size = FitSize;
				}
			}
		}

		/// <summary>
		/// Gets or sets a value to be added to or subtracted from the <see cref="Value"/> property when the slider is moved a large distance.
		/// </summary>
		/// <remarks>
		/// When the user presses the PAGE UP or PAGE DOWN key or clicks the track bar on either side of the slider, the <see cref="Value"/> 
		/// property changes according to the value set in the <see cref="LargeChange"/> property. 
		/// You might consider setting the <see cref="LargeChange"/> value to a percentage of the <see cref="Control.Height"/> (for a vertically oriented track bar) or 
		/// <see cref="Control.Width"/> (for a horizontally oriented track bar) values. This keeps the distance your track bar moves proportionate to its size.
		/// </remarks>
		/// <value>A numeric value. The default value is 2.</value>
		[Category("Behavior")]
		[Description(
			"Gets or sets a value to be added to or subtracted from the Value property when the slider is moved a large distance.")]
		[DefaultValue(2)]
		public int LargeChange
		{
			get { return _largeChange; }

			set
			{
				_largeChange = value;
				if ( _largeChange < 1 )
					_largeChange = 1;
			}
		}

		/// <summary>
		/// Gets or sets a value to be added to or subtracted from the <see cref="Value"/> property when the slider is moved a small distance.
		/// </summary>
		/// <remarks>
		/// When the user presses one of the arrow keys, the <see cref="Value"/> property changes according to the value set in the SmallChange property.
		/// You might consider setting the <see cref="SmallChange"/> value to a percentage of the <see cref="Control.Height"/> (for a vertically oriented track bar) or 
		/// <see cref="Control.Width"/> (for a horizontally oriented track bar) values. This keeps the distance your track bar moves proportionate to its size.
		/// </remarks>
		/// <value>A numeric value. The default value is 1.</value>
		[Category("Behavior")]
		[Description(
			"Gets or sets a value to be added to or subtracted from the Value property when the slider is moved a small distance.")]
		[DefaultValue(1)]
		public int SmallChange
		{
			get { return _smallChange; }

			set
			{
				_smallChange = value;
				if ( _smallChange < 1 )
					_smallChange = 1;
			}
		}

		/// <summary>
		/// Gets or sets the height of track line.
		/// </summary>
		/// <value>The default value is 4.</value>
		[Category("Appearance")]
		[Description("Gets or sets the height of track line.")]
		[DefaultValue(4)]
		public int TrackLineHeight
		{
			get { return _trackLineHeight; }

			set
			{
				if ( _trackLineHeight != value )
				{
					_trackLineHeight = value;
					if ( _trackLineHeight < 1 )
						_trackLineHeight = 1;

					if ( _trackLineHeight > _trackerSize.Height )
						_trackLineHeight = _trackerSize.Height;

					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the tick's <see cref="Color"/> of the control.
		/// </summary>
		[Category("Appearance")]
		[Description("Gets or sets the tick's color of the control.")]
		public Color TickColor
		{
			get { return _tickColor; }

			set
			{
				if ( _tickColor != value )
				{
					_tickColor = value;
					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets a value that specifies the delta between ticks drawn on the control.
		/// </summary>
		/// <remarks>
		/// For a <see cref="MACTrackBar"/> with a large range of values between the <see cref="Minimum"/> and the 
		/// <see cref="Maximum"/>, it might be impractical to draw all the ticks for values on the control. 
		/// For example, if you have a control with a range of 100, passing in a value of 
		/// five here causes the control to draw 20 ticks. In this case, each tick 
		/// represents five units in the range of values.
		/// </remarks>
		/// <value>The numeric value representing the delta between ticks. The default is 1.</value>
		[Category("Appearance")]
		[Description("Gets or sets a value that specifies the delta between ticks drawn on the control.")]
		[DefaultValue(1)]
		public int TickFrequency
		{
			get { return _tickFrequency; }

			set
			{
				if ( _tickFrequency != value )
				{
					_tickFrequency = value;
					if ( _tickFrequency < 1 )
						_tickFrequency = 1;
					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the height of tick.
		/// </summary>
		/// <value>The height of tick in pixels. The default value is 2.</value>
		[Category("Appearance")]
		[Description("Gets or sets the height of tick.")]
		[DefaultValue(6)]
		public int TickHeight
		{
			get { return _tickHeight; }

			set
			{
				if ( _tickHeight != value )
				{
					_tickHeight = value;

					if ( _tickHeight < 1 )
						_tickHeight = 1;

					if ( _autoSize == true )
						Size = FitSize;

					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the height of indent (or Padding-Y).
		/// </summary>
		/// <value>The height of indent in pixels. The default value is 6.</value>
		[Category("Appearance")]
		[Description("Gets or sets the height of indent.")]
		[DefaultValue(2)]
		public int IndentHeight
		{
			get { return _indentHeight; }

			set
			{
				if ( _indentHeight != value )
				{
					_indentHeight = value;
					if ( _indentHeight < 0 )
						_indentHeight = 0;

					if ( _autoSize == true )
						Size = FitSize;

					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the width of indent (or Padding-Y).
		/// </summary>
		/// <value>The width of indent in pixels. The default value is 6.</value>
		[Category("Appearance")]
		[Description("Gets or sets the width of indent.")]
		[DefaultValue(6)]
		public int IndentWidth
		{
			get { return _indentWidth; }

			set
			{
				if ( _indentWidth != value )
				{
					_indentWidth = value;
					if ( _indentWidth < 0 )
						_indentWidth = 0;

					if ( _autoSize == true )
						Size = FitSize;

					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the tracker's size. 
		/// The tracker's width must be greater or equal to tracker's height.
		/// </summary>
		/// <value>The <see cref="Size"/> object that represents the height and width of the tracker in pixels.</value>
		[Category("Appearance")]
		[Description("Gets or sets the tracker's size.")]
		public Size TrackerSize
		{
			get { return _trackerSize; }

			set
			{
				if ( _trackerSize != value )
				{
					_trackerSize = value;
					if ( _trackerSize.Width > _trackerSize.Height )
						_trackerSize.Height = _trackerSize.Width;

					if ( _autoSize == true )
						Size = FitSize;

					Invalidate();
				}
			}
		}

    public Image TrackerImage { get; set; }

		/// <summary>
		/// Gets or sets the text tick style of the trackbar.
		/// There are 4 styles for selection: None, TopLeft, BottomRight, Both. 
		/// </summary>
		/// <remarks>You can use the <see cref="Control.Font"/>, <see cref="Control.ForeColor"/>
		/// properties to customize the tick text.</remarks>
		/// <value>One of the <see cref="TickStyle"/> values. The default is <b>BottomRight</b>.</value>
		[Category("Appearance")]
		[Description("Gets or sets the text tick style.")]
		[DefaultValue(TickStyle.BottomRight)]
		public TickStyle TextTickStyle
		{
			get { return _textTickStyle; }

			set
			{
				if ( _textTickStyle != value )
				{
					_textTickStyle = value;

					if ( _autoSize == true )
						Size = FitSize;

					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the tick style of the trackbar.
		/// There are 4 styles for selection: None, TopLeft, BottomRight, Both. 
		/// </summary>
		/// <remarks>You can use the <see cref="TickColor"/>, <see cref="TickFrequency"/>, 
		/// <see cref="TickHeight"/> properties to customize the trackbar's ticks.</remarks>
		/// <value>One of the <see cref="TickStyle"/> values. The default is <b>BottomRight</b>.</value>
		[Category("Appearance")]
		[Description("Gets or sets the tick style.")]
		[DefaultValue(TickStyle.BottomRight)]
		public TickStyle TickStyle
		{
			get { return _tickStyle; }

			set
			{
				if ( _tickStyle != value )
				{
					_tickStyle = value;

					if ( _autoSize == true )
						Size = FitSize;

					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or set tracker's color.
		/// </summary>
		/// <value>
		/// <remarks>You can change size of tracker by <see cref="TrackerSize"/> property.</remarks>
		/// A <see cref="Color"/> that represents the color of the tracker. 
		/// </value>
		[Description("Gets or set tracker's color.")]
		[Category("Appearance")]
		public Color TrackerColor
		{
			get { return _trackerColor; }
			set
			{
				if ( _trackerColor != value )
				{
					_trackerColor = value;
					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets a numeric value that represents the current position of the slider on the track bar.
		/// </summary>
		/// <remarks>The Value property contains the number that represents the current position of the slider on the track bar.</remarks>
		/// <value>A numeric value that is within the <see cref="Minimum"/> and <see cref="Maximum"/> range. 
		/// The default value is 0.</value>
		[Description("The current value for the MACTrackBar, in the range specified by the Minimum and Maximum properties.")]
		[Category("Behavior")]
		public int Value
		{
			get { return _value; }
			set
			{
				if ( _value != value )
				{
					if ( value < _minimum )
						_value = _minimum;
					else if ( value > _maximum )
						_value = _maximum;
					else
						_value = value;

					OnValueChanged( _value );

					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the lower limit of the range this <see cref="MACTrackBar"/> is working with.
		/// </summary>
		/// <remarks>You can use the <see cref="SetRange"/> method to set both the <see cref="Maximum"/> and <see cref="Minimum"/> properties at the same time.</remarks>
		/// <value>The minimum value for the <see cref="MACTrackBar"/>. The default value is 0.</value>
		[Description("The lower bound of the range this MACTrackBar is working with.")]
		[Category("Behavior")]
		public int Minimum
		{
			get { return _minimum; }
			set
			{
				_minimum = value;

				if ( _minimum > _maximum )
					_maximum = _minimum;
				if ( _minimum > _value )
					_value = _minimum;

				Invalidate();
			}
		}

		/// <summary>
		/// Gets or sets the upper limit of the range this <see cref="MACTrackBar"/> is working with.
		/// </summary>
		/// <remarks>You can use the <see cref="SetRange"/> method to set both the <see cref="Maximum"/> and <see cref="Minimum"/> properties at the same time.</remarks>
		/// <value>The maximum value for the <see cref="MACTrackBar"/>. The default value is 10.</value>
		[Description("The uppper bound of the range this MACTrackBar is working with.")]
		[Category("Behavior")]
		public int Maximum
		{
			get { return _maximum; }
			set
			{
				_maximum = value;

				if ( _maximum < _value )
					_value = _maximum;
				if ( _maximum < _minimum )
					_minimum = _maximum;

				Invalidate();
			}
		}

		/// <summary>
		/// Gets or sets a value indicating the horizontal or vertical orientation of the track bar.
		/// </summary>
		/// <remarks>
		/// When the <b>Orientation</b> property is set to <b>Orientation.Horizontal</b>, 
		/// the slider moves from left to right as the <see cref="Value"/> increases. 
		/// When the <b>Orientation</b> property is set to <b>Orientation.Vertical</b>, the slider moves 
		/// from bottom to top as the <see cref="Value"/> increases.
		/// </remarks>
		/// <value>One of the <see cref="Orientation"/> values. The default value is <b>Horizontal</b>.</value>
		[Description("Gets or sets a value indicating the horizontal or vertical orientation of the track bar.")]
		[Category("Behavior")]
		[DefaultValue(Orientation.Horizontal)]
		public Orientation Orientation
		{
			get { return _orientation; }
			set
			{
				if ( value != _orientation )
				{
					_orientation = value;
					if ( _orientation == Orientation.Horizontal )
					{
						if ( Width < Height )
						{
							int temp = Width;
							Width = Height;
							Height = temp;
						}
					}
					else //Vertical 
						if ( Width > Height )
						{
							int temp = Width;
							Width = Height;
							Height = temp;
						}
					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the border type of the trackbar control.
		/// </summary>
		/// <value>A <see cref="MACBorderStyle"/> that represents the border type of the trackbar control. 
		/// The default is <b>MACBorderStyle.None</b>.</value>
		[Description("Gets or sets the border type of the trackbar control.")]
		[Category("Appearance"), DefaultValue(typeof (MACBorderStyle), "None")]
		[DesignerSerializationVisibility(DesignerSerializationVisibility.Visible)]
		public MACBorderStyle BorderStyle
		{
			get { return _borderStyle; }
			set
			{
				if ( _borderStyle != value )
				{
					_borderStyle = value;
					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the border color of the control.
		/// </summary>
		/// <value>A <see cref="Color"/> object that represents the border color of the control.</value>
		[Category("Appearance")]
		[Description("Gets or sets the border color of the control.")]
		public Color BorderColor
		{
			get { return _borderColor; }
			set
			{
				if ( value != _borderColor )
				{
					_borderColor = value;
					Invalidate();
				}
			}
		}

		/// <summary>
		/// Gets or sets the color of the track line.
		/// </summary>
		/// <value>A <see cref="Color"/> object that represents the color of the track line.</value>
		[Category("Appearance")]
		[Description("Gets or sets the color of the track line.")]
		public Color TrackLineColor
		{
			get { return _trackLineColor; }
			set
			{
				if ( value != _trackLineColor )
				{
					_trackLineColor = value;
					Invalidate();
				}
			}
		}

		#endregion

		#region Private Properties

		/// <summary>
		/// Gets the Size of area need for drawing.
		/// </summary>
		[Description("Gets the Size of area need for drawing.")]
		[Browsable(false)]
		private Size FitSize
		{
			get
			{
				Size fitSize;
				float textAreaSize;

				// Create a Graphics object for the Control.
				Graphics g = CreateGraphics();

				Rectangle workingRect = Rectangle.Inflate( ClientRectangle, - _indentWidth, - _indentHeight );
				float currentUsedPos = 0;

				if ( _orientation == Orientation.Horizontal )
				{
					currentUsedPos = _indentHeight;
					//==========================================================================

					// Get Height of Text Area
					textAreaSize = g.MeasureString( _maximum.ToString(), Font ).Height;

					if ( _textTickStyle == TickStyle.TopLeft || _textTickStyle == TickStyle.Both )
						currentUsedPos += textAreaSize;

					if ( _tickStyle == TickStyle.TopLeft || _tickStyle == TickStyle.Both )
						currentUsedPos += _tickHeight + 1;

					currentUsedPos += _trackerSize.Height;

					if ( _tickStyle == TickStyle.BottomRight || _tickStyle == TickStyle.Both )
					{
						currentUsedPos += 1;
						currentUsedPos += _tickHeight;
					}

					if ( _textTickStyle == TickStyle.BottomRight || _textTickStyle == TickStyle.Both )
						currentUsedPos += textAreaSize;

					currentUsedPos += _indentHeight;

					fitSize = new Size( ClientRectangle.Width, (int) currentUsedPos );
				}
				else //_orientation == Orientation.Vertical
				{
					currentUsedPos = _indentWidth;
					//==========================================================================

					// Get Width of Text Area
					textAreaSize = g.MeasureString( _maximum.ToString(), Font ).Width;

					if ( _textTickStyle == TickStyle.TopLeft || _textTickStyle == TickStyle.Both )
						currentUsedPos += textAreaSize;

					if ( _tickStyle == TickStyle.TopLeft || _tickStyle == TickStyle.Both )
						currentUsedPos += _tickHeight + 1;

					currentUsedPos += _trackerSize.Height;

					if ( _tickStyle == TickStyle.BottomRight || _tickStyle == TickStyle.Both )
					{
						currentUsedPos += 1;
						currentUsedPos += _tickHeight;
					}

					if ( _textTickStyle == TickStyle.BottomRight || _textTickStyle == TickStyle.Both )
						currentUsedPos += textAreaSize;

					currentUsedPos += _indentWidth;

					fitSize = new Size( (int) currentUsedPos, ClientRectangle.Height );
				}

				// Clean up the Graphics object.
				g.Dispose();

				return fitSize;
			}
		}


		/// <summary>
		/// Gets the rectangle containing the tracker.
		/// </summary>
		[Description("Gets the rectangle containing the tracker.")]
		private RectangleF TrackerRect
		{
			get
			{
				RectangleF trackerRect;
				float textAreaSize;

				// Create a Graphics object for the Control.
				Graphics g = CreateGraphics();

				Rectangle workingRect = Rectangle.Inflate( ClientRectangle, - _indentWidth, - _indentHeight );
				float currentUsedPos = 0;

				if ( _orientation == Orientation.Horizontal )
				{
					currentUsedPos = _indentHeight;
					//==========================================================================

					// Get Height of Text Area
					textAreaSize = g.MeasureString( _maximum.ToString(), Font ).Height;

					if ( _textTickStyle == TickStyle.TopLeft || _textTickStyle == TickStyle.Both )
						currentUsedPos += textAreaSize;

					if ( _tickStyle == TickStyle.TopLeft || _tickStyle == TickStyle.Both )
						currentUsedPos += _tickHeight + 1;


					//==========================================================================
					// Caculate the Tracker's rectangle
					//==========================================================================
					float currentTrackerPos;
					if ( _maximum == _minimum )
						currentTrackerPos = workingRect.Left;
					else
						currentTrackerPos = (workingRect.Width - _trackerSize.Width) * (_value - _minimum) / (_maximum - _minimum)
						                    + workingRect.Left;
					trackerRect = new RectangleF( currentTrackerPos, currentUsedPos, _trackerSize.Width, _trackerSize.Height );
						// Remember this for drawing the Tracker later
					trackerRect.Inflate( 0, -1 );
				}
				else //_orientation == Orientation.Vertical
				{
					currentUsedPos = _indentWidth;
					//==========================================================================

					// Get Width of Text Area
					textAreaSize = g.MeasureString( _maximum.ToString(), Font ).Width;

					if ( _textTickStyle == TickStyle.TopLeft || _textTickStyle == TickStyle.Both )
						currentUsedPos += textAreaSize;

					if ( _tickStyle == TickStyle.TopLeft || _tickStyle == TickStyle.Both )
						currentUsedPos += _tickHeight + 1;

					//==========================================================================
					// Caculate the Tracker's rectangle
					//==========================================================================
					float currentTrackerPos;
					if ( _maximum == _minimum )
						currentTrackerPos = workingRect.Top;
					else
						currentTrackerPos = (workingRect.Height - _trackerSize.Width) * (_value - _minimum) / (_maximum - _minimum);

					trackerRect = new RectangleF( currentUsedPos,
					                              workingRect.Bottom - currentTrackerPos - _trackerSize.Width,
					                              _trackerSize.Height,
					                              _trackerSize.Width ); // Remember this for drawing the Tracker later
					trackerRect.Inflate( -1, 0 );
				}

				// Clean up the Graphics object.
				g.Dispose();

				return trackerRect;
			}
		}

		#endregion

		#region Public Methods

		/// <summary>
		/// Raises the ValueChanged event.
		/// </summary>
		/// <param name="value">The new value</param>
		public virtual void OnValueChanged(int value)
		{
			// Any attached event handlers?
			if ( ValueChanged != null )
				ValueChanged( this, value );
		}

		/// <summary>
		/// Raises the Scroll event.
		/// </summary>
		public virtual void OnScroll()
		{
			try
			{
				// Any attached event handlers?
				if ( Scroll != null )
					Scroll( this, new EventArgs() );
			}
			catch (Exception Err)
			{
				MessageBox.Show( "OnScroll Exception: " + Err.Message );
			}
		}


		/// <summary>
		/// Call the Increment() method to increase the value displayed by an integer you specify 
		/// </summary>
		/// <param name="value"></param>
		public void Increment(int value)
		{
			if ( _value < _maximum )
			{
				_value += value;
				if ( _value > _maximum )
					_value = _maximum;
			}
			else
				_value = _maximum;

			OnValueChanged( _value );
			Invalidate();
		}

		/// <summary>
		/// Call the Decrement() method to decrease the value displayed by an integer you specify 
		/// </summary>
		/// <param name="value"> The value to decrement</param>
		public void Decrement(int value)
		{
			if ( _value > _minimum )
			{
				_value -= value;
				if ( _value < _minimum )
					_value = _minimum;
			}
			else
				_value = _minimum;

			OnValueChanged( _value );
			Invalidate();
		}

		/// <summary>
		/// Sets the minimum and maximum values for a TrackBar.
		/// </summary>
		/// <param name="minValue">The lower limit of the range of the track bar.</param>
		/// <param name="maxValue">The upper limit of the range of the track bar.</param>
		public void SetRange(int minValue, int maxValue)
		{
			_minimum = minValue;

			if ( _minimum > _value )
				_value = _minimum;

			_maximum = maxValue;

			if ( _maximum < _value )
				_value = _maximum;
			if ( _maximum < _minimum )
				_minimum = _maximum;

			Invalidate();
		}

		/// <summary>
		/// Reset the appearance properties.
		/// </summary>
		public void ResetAppearance()
		{
			Font = new Font( "Verdana", 8.25F, FontStyle.Bold, GraphicsUnit.Point, (byte) 0 );
			ForeColor = Color.FromArgb( 123, 125, 123 );
			BackColor = Color.Transparent;

			_tickColor = Color.FromArgb( 148, 146, 148 );
			_tickHeight = 4;

			_trackerColor = Color.FromArgb( 24, 130, 198 );
			_trackerSize = new Size( 16, 16 );
			//_trackerRect.Size = _trackerSize;

			_indentWidth = 6;
			_indentHeight = 6;

			_trackLineColor = Color.FromArgb( 90, 93, 90 );
			_trackLineHeight = 3;

			_borderStyle = MACBorderStyle.None;
			_borderColor = SystemColors.ActiveBorder;

			//==========================================================================

			if ( _autoSize == true )
				Size = FitSize;
			Invalidate();
		}

		#endregion

		#region Protected Methods

		/// <summary>
		/// The OnCreateControl method is called when the control is first created.
		/// </summary>
		protected override void OnCreateControl() { }

		/// <summary>
		/// This member overrides <see cref="Control.OnLostFocus">Control.OnLostFocus</see>.
		/// </summary>
		protected override void OnLostFocus(EventArgs e)
		{
			Invalidate();
			base.OnLostFocus( e );
		}

		/// <summary>
		/// This member overrides <see cref="Control.OnGotFocus">Control.OnGotFocus</see>.
		/// </summary>
		protected override void OnGotFocus(EventArgs e)
		{
			Invalidate();
			base.OnGotFocus( e );
		}

		/// <summary>
		/// This member overrides <see cref="Control.OnClick">Control.OnClick</see>.
		/// </summary>
		protected override void OnClick(EventArgs e)
		{
			Focus();
			Invalidate();
			base.OnClick( e );
		}

		/// <summary>
		/// This member overrides <see cref="Control.ProcessCmdKey">Control.ProcessCmdKey</see>.
		/// </summary>
		protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
		{
			bool blResult = true;

			/// <summary>
			/// Specified WM_KEYDOWN enumeration value.
			/// </summary>
			const int WM_KEYDOWN = 0x0100;

			/// <summary>
			/// Specified WM_SYSKEYDOWN enumeration value.
			/// </summary>
			const int WM_SYSKEYDOWN = 0x0104;


			if ( (msg.Msg == WM_KEYDOWN) || (msg.Msg == WM_SYSKEYDOWN) )
				switch (keyData)
				{
					case Keys.Left:
					case Keys.Down:
						Decrement( _smallChange );
						break;
					case Keys.Right:
					case Keys.Up:
						Increment( _smallChange );
						break;

					case Keys.PageUp:
						Increment( _largeChange );
						break;
					case Keys.PageDown:
						Decrement( _largeChange );
						break;

					case Keys.Home:
						Value = _maximum;
						break;
					case Keys.End:
						Value = _minimum;
						break;

					default:
						blResult = base.ProcessCmdKey( ref msg, keyData );
						break;
				}

			return blResult;
		}

		/// <summary>
		/// Dispose of instance resources.
		/// </summary>
		/// <param name="disposing">true to release both managed and unmanaged resources; false to release only unmanaged resources.</param>
		protected override void Dispose(bool disposing) { base.Dispose( disposing ); }

		#endregion

		#region Painting Methods

		/// <summary>
		/// This member overrides <see cref="Control.OnPaint">Control.OnPaint</see>.
		/// </summary>
		protected override void OnPaint(PaintEventArgs e)
		{
			Brush brush;
			RectangleF rectTemp, drawRect;
			float textAreaSize;

			Rectangle workingRect = Rectangle.Inflate( ClientRectangle, - _indentWidth, - _indentHeight );
			float currentUsedPos = 0;

			//==========================================================================
			// Draw the background of the ProgressBar control.
			//==========================================================================
			brush = new SolidBrush( BackColor );
			rectTemp = ClientRectangle;
			e.Graphics.FillRectangle( brush, rectTemp );
			brush.Dispose();
			//==========================================================================

			//==========================================================================
			if ( _orientation == Orientation.Horizontal )
			{
				currentUsedPos = _indentHeight;
				//==========================================================================

				// Get Height of Text Area
				textAreaSize = e.Graphics.MeasureString( _maximum.ToString(), Font ).Height;

				if ( _textTickStyle == TickStyle.TopLeft || _textTickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 1st Text Line.
					//==========================================================================
					drawRect = new RectangleF( workingRect.Left, currentUsedPos, workingRect.Width, textAreaSize );
					drawRect.Inflate( - _trackerSize.Width / 2, 0 );
					currentUsedPos += textAreaSize;

					DrawTickTextLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, ForeColor, Font, _orientation );
					//==========================================================================
				}

				if ( _tickStyle == TickStyle.TopLeft || _tickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 1st Tick Line.
					//==========================================================================
					drawRect = new RectangleF( workingRect.Left, currentUsedPos, workingRect.Width, _tickHeight );
					drawRect.Inflate( - _trackerSize.Width / 2, 0 );
					currentUsedPos += _tickHeight + 1;

					DrawTickLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, _tickColor, _orientation );
					//==========================================================================
				}

				//==========================================================================
				// Caculate the Tracker's rectangle
				//==========================================================================
				float currentTrackerPos;
				if ( _maximum == _minimum )
					currentTrackerPos = workingRect.Left;
				else
					currentTrackerPos = (workingRect.Width - _trackerSize.Width) * (_value - _minimum) / (_maximum - _minimum) + workingRect.Left;
				_trackerRect = new RectangleF( currentTrackerPos, currentUsedPos, _trackerSize.Width, _trackerSize.Height );
					// Remember this for drawing the Tracker later
				//_trackerRect.Inflate(0,-1);

				//==========================================================================
				// Draw the Track Line
				//==========================================================================
				drawRect = new RectangleF( workingRect.Left,
				                           currentUsedPos + _trackerSize.Height / 2 - _trackLineHeight / 2,
				                           workingRect.Width,
				                           _trackLineHeight );
				DrawTrackLine( e.Graphics, drawRect );
				currentUsedPos += _trackerSize.Height;


				//==========================================================================

				if ( _tickStyle == TickStyle.BottomRight || _tickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 2st Tick Line.
					//==========================================================================
					currentUsedPos += 1;
					drawRect = new RectangleF( workingRect.Left, currentUsedPos, workingRect.Width, _tickHeight );
					drawRect.Inflate( - _trackerSize.Width / 2, 0 );
					currentUsedPos += _tickHeight;

					DrawTickLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, _tickColor, _orientation );
					//==========================================================================
				}

				if ( _textTickStyle == TickStyle.BottomRight || _textTickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 2st Text Line.
					//==========================================================================
					// Get Height of Text Area
					drawRect = new RectangleF( workingRect.Left, currentUsedPos, workingRect.Width, textAreaSize );
					drawRect.Inflate( - _trackerSize.Width / 2, 0 );
					currentUsedPos += textAreaSize;

					DrawTickTextLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, ForeColor, Font, _orientation );
					//==========================================================================
				}
			}
			else //_orientation == Orientation.Vertical
			{
				currentUsedPos = _indentWidth;
				//==========================================================================

				// Get Width of Text Area
				textAreaSize = e.Graphics.MeasureString( _maximum.ToString(), Font ).Width;

				if ( _textTickStyle == TickStyle.TopLeft || _textTickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 1st Text Line.
					//==========================================================================
					// Get Height of Text Area
					drawRect = new RectangleF( currentUsedPos, workingRect.Top, textAreaSize, workingRect.Height );
					drawRect.Inflate( 0, - _trackerSize.Width / 2 );
					currentUsedPos += textAreaSize;

					DrawTickTextLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, ForeColor, Font, _orientation );
					//==========================================================================
				}

				if ( _tickStyle == TickStyle.TopLeft || _tickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 1st Tick Line.
					//==========================================================================
					drawRect = new RectangleF( currentUsedPos, workingRect.Top, _tickHeight, workingRect.Height );
					drawRect.Inflate( 0, - _trackerSize.Width / 2 );
					currentUsedPos += _tickHeight + 1;

					DrawTickLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, _tickColor, _orientation );
					//==========================================================================
				}

				//==========================================================================
				// Caculate the Tracker's rectangle
				//==========================================================================
				float currentTrackerPos;
				if ( _maximum == _minimum )
					currentTrackerPos = workingRect.Top;
				else
					currentTrackerPos = (workingRect.Height - _trackerSize.Width) * (_value - _minimum) / (_maximum - _minimum);

				_trackerRect = new RectangleF( currentUsedPos,
				                               workingRect.Bottom - currentTrackerPos - _trackerSize.Width,
				                               _trackerSize.Height,
				                               _trackerSize.Width ); // Remember this for drawing the Tracker later
				//_trackerRect.Inflate(-1,0);

				rectTemp = _trackerRect; //Testing

				//==========================================================================
				// Draw the Track Line
				//==========================================================================
				drawRect = new RectangleF( currentUsedPos + _trackerSize.Height / 2 - _trackLineHeight / 2,
				                           workingRect.Top,
				                           _trackLineHeight,
				                           workingRect.Height );
				DrawTrackLine( e.Graphics, drawRect );
				currentUsedPos += _trackerSize.Height;
				//==========================================================================

				if ( _tickStyle == TickStyle.BottomRight || _tickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 2st Tick Line.
					//==========================================================================
					currentUsedPos += 1;
					drawRect = new RectangleF( currentUsedPos, workingRect.Top, _tickHeight, workingRect.Height );
					drawRect.Inflate( 0, - _trackerSize.Width / 2 );
					currentUsedPos += _tickHeight;

					DrawTickLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, _tickColor, _orientation );
					//==========================================================================
				}

				if ( _textTickStyle == TickStyle.BottomRight || _textTickStyle == TickStyle.Both )
				{
					//==========================================================================
					// Draw the 2st Text Line.
					//==========================================================================
					// Get Height of Text Area
					drawRect = new RectangleF( currentUsedPos, workingRect.Top, textAreaSize, workingRect.Height );
					drawRect.Inflate( 0, - _trackerSize.Width / 2 );
					currentUsedPos += textAreaSize;

					DrawTickTextLine( e.Graphics, drawRect, _tickFrequency, _minimum, _maximum, ForeColor, Font, _orientation );
					//==========================================================================
				}
			}

			//==========================================================================
			// Check for special values of Max, Min & Value
			if ( _maximum == _minimum )
			{
				// Draw border only and exit;
				DrawBorder( e.Graphics );
				return;
			}
			//==========================================================================

			//==========================================================================
			// Draw the Tracker
			//==========================================================================
			DrawTracker( e.Graphics, _trackerRect );
			//==========================================================================

			// Draw border
			DrawBorder( e.Graphics );
			//==========================================================================

			// Draws a focus rectangle
			//if(this.Focused && this.BackColor != Color.Transparent)
			if ( Focused )
				ControlPaint.DrawFocusRectangle( e.Graphics, Rectangle.Inflate( ClientRectangle, -2, -2 ) );
			//==========================================================================
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="g"></param>
		/// <param name="drawRect"></param>
		private void DrawTrackLine(Graphics g, RectangleF drawRect) { DrawMACStyleHelper.DrawAquaPillSingleLayer( g, drawRect, _trackLineColor, _orientation ); }

		/// <summary>
		/// 
		/// </summary>
		/// <param name="g"></param>
		/// <param name="trackerRect"></param>
		private void DrawTracker(Graphics g, RectangleF trackerRect) 
    {
      if( TrackerImage != null )
        g.DrawImage( TrackerImage, trackerRect.Location );
      else
        DrawMACStyleHelper.DrawAquaPill( g, trackerRect, _trackerColor, _orientation ); 
    }

		public int ScaleFactor=0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="g"></param>
		/// <param name="drawRect"></param>
		/// <param name="tickFrequency"></param>
		/// <param name="minimum"></param>
		/// <param name="maximum"></param>
		/// <param name="foreColor"></param>
		/// <param name="font"></param>
		/// <param name="orientation"></param>
		private void DrawTickTextLine(Graphics g,
		                              RectangleF drawRect,
		                              int tickFrequency,
		                              int minimum,
		                              int maximum,
		                              Color foreColor,
		                              Font font,
		                              Orientation orientation)
		{
			//Check input value
			if ( maximum == minimum )
				return;

			//Caculate tick number
			int tickCount = (int) ((maximum - minimum) / tickFrequency);
			if ( (maximum - minimum) % tickFrequency == 0 )
				tickCount -= 1;

			if ( tickCount > 2 )
				tickCount -= 1;

			//Prepare for drawing Text
			//===============================================================
			StringFormat stringFormat;
			stringFormat = new StringFormat();
			stringFormat.FormatFlags = StringFormatFlags.NoWrap;
			stringFormat.LineAlignment = StringAlignment.Center;
			stringFormat.Alignment = StringAlignment.Center;
			stringFormat.Trimming = StringTrimming.EllipsisCharacter;
			stringFormat.HotkeyPrefix = HotkeyPrefix.Show;

			Brush brush = new SolidBrush( foreColor );
			string text;
			float tickFrequencySize;
			//===============================================================

			if ( _orientation == Orientation.Horizontal )
			{
				// Calculate tick's setting
				tickFrequencySize = drawRect.Width * tickFrequency / (maximum - minimum);

				//===============================================================

				// Draw each tick text
				for ( int i = 0; i <= tickCount; i++ )
				{
					int val = _minimum + tickFrequency * i;
					if(ScaleFactor>0)
					{
						int rem = int.MaxValue;
						val = Math.DivRem( val, ScaleFactor, out rem );
						if ( rem != 0 )continue;
					}
					text = Convert.ToString( val, 10 );
					g.DrawString( text, font, brush, drawRect.Left + tickFrequencySize * i, drawRect.Top + drawRect.Height / 2, stringFormat );
				}
				// Draw last tick text at Maximum
				float lval= ScaleFactor > 0
					?
						lval = (float) Math.Round( ((float) _maximum) / ((float) ScaleFactor), 1 )
					: _maximum;
				
				text = Convert.ToString( lval );
				g.DrawString( text, font, brush, drawRect.Right, drawRect.Top + drawRect.Height / 2, stringFormat );

				//===============================================================
			}
			else //Orientation.Vertical
			{
				// Calculate tick's setting
				tickFrequencySize = drawRect.Height * tickFrequency / (maximum - minimum);
				//===============================================================

				// Draw each tick text
				for ( int i = 0; i <= tickCount; i++ )
				{
					text = Convert.ToString( _minimum + tickFrequency * i, 10 );
					g.DrawString( text, font, brush, drawRect.Left + drawRect.Width / 2, drawRect.Bottom - tickFrequencySize * i, stringFormat );
				}
				// Draw last tick text at Maximum
				text = Convert.ToString( _maximum, 10 );
				g.DrawString( text, font, brush, drawRect.Left + drawRect.Width / 2, drawRect.Top, stringFormat );
				//===============================================================
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="g"></param>
		/// <param name="drawRect"></param>
		/// <param name="tickFrequency"></param>
		/// <param name="minimum"></param>
		/// <param name="maximum"></param>
		/// <param name="tickColor"></param>
		/// <param name="orientation"></param>
		private void DrawTickLine(Graphics g,
		                          RectangleF drawRect,
		                          int tickFrequency,
		                          int minimum,
		                          int maximum,
		                          Color tickColor,
		                          Orientation orientation)
		{
			//Check input value
			if ( maximum == minimum )
				return;

			//Create the Pen for drawing Ticks
			Pen pen = new Pen( tickColor, 1 );
			float tickFrequencySize;

			//Caculate tick number
			int tickCount = (int) ((maximum - minimum) / tickFrequency);
			if ( (maximum - minimum) % tickFrequency == 0 )
				tickCount -= 1;

			if ( tickCount > 2 )
				tickCount -= 1;

			if ( _orientation == Orientation.Horizontal )
			{
				// Calculate tick's setting
				tickFrequencySize = drawRect.Width * tickFrequency / (maximum - minimum);

				//===============================================================

				// Draw each tick
				for ( int i = 0; i <= tickCount; i++ )
					g.DrawLine( pen, drawRect.Left + tickFrequencySize * i, drawRect.Top, drawRect.Left + tickFrequencySize * i, drawRect.Bottom );
				// Draw last tick at Maximum
				g.DrawLine( pen, drawRect.Right, drawRect.Top, drawRect.Right, drawRect.Bottom );
				//===============================================================
			}
			else //Orientation.Vertical
			{
				// Calculate tick's setting
				tickFrequencySize = drawRect.Height * tickFrequency / (maximum - minimum);
				//===============================================================

				// Draw each tick
				for ( int i = 0; i <= tickCount; i++ )
					g.DrawLine( pen,
					            drawRect.Left,
					            drawRect.Bottom - tickFrequencySize * i,
					            drawRect.Right,
					            drawRect.Bottom - tickFrequencySize * i );
				// Draw last tick at Maximum
				g.DrawLine( pen, drawRect.Left, drawRect.Top, drawRect.Right, drawRect.Top );
				//===============================================================
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="g"></param>
		private void DrawBorder(Graphics g)
		{
			switch (_borderStyle)
			{
				case MACBorderStyle.Dashed: //from ButtonBorderStyle Enumeration
					ControlPaint.DrawBorder( g, ClientRectangle, _borderColor, ButtonBorderStyle.Dashed );
					break;
				case MACBorderStyle.Dotted: //from ButtonBorderStyle Enumeration
					ControlPaint.DrawBorder( g, ClientRectangle, _borderColor, ButtonBorderStyle.Dotted );
					break;
				case MACBorderStyle.Inset: //from ButtonBorderStyle Enumeration
					ControlPaint.DrawBorder( g, ClientRectangle, _borderColor, ButtonBorderStyle.Inset );
					break;
				case MACBorderStyle.Outset: //from ButtonBorderStyle Enumeration
					ControlPaint.DrawBorder( g, ClientRectangle, _borderColor, ButtonBorderStyle.Outset );
					break;
				case MACBorderStyle.Solid: //from ButtonBorderStyle Enumeration
					ControlPaint.DrawBorder( g, ClientRectangle, _borderColor, ButtonBorderStyle.Solid );
					break;

				case MACBorderStyle.Adjust: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.Adjust );
					break;
				case MACBorderStyle.Bump: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.Bump );
					break;
				case MACBorderStyle.Etched: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.Etched );
					break;
				case MACBorderStyle.Flat: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.Flat );
					break;
				case MACBorderStyle.Raised: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.Raised );
					break;
				case MACBorderStyle.RaisedInner: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.RaisedInner );
					break;
				case MACBorderStyle.RaisedOuter: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.RaisedOuter );
					break;
				case MACBorderStyle.Sunken: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.Sunken );
					break;
				case MACBorderStyle.SunkenInner: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.SunkenInner );
					break;
				case MACBorderStyle.SunkenOuter: //from Border3DStyle Enumeration
					ControlPaint.DrawBorder3D( g, ClientRectangle, Border3DStyle.SunkenOuter );
					break;
				case MACBorderStyle.None:
				default:
					break;
			}
		}

		#endregion

		#region Private Methods

		private void OnMouseDownSlider(object sender, MouseEventArgs e)
		{
			int offsetValue = 0;
			int oldValue = 0;
			PointF currentPoint;

			currentPoint = new PointF( e.X, e.Y );
//			if ( _trackerRect.Contains( currentPoint ) )
//			{
				if ( !leftButtonDown )
				{
					leftButtonDown = true;
					Capture = true;
					switch (_orientation)
					{
						case Orientation.Horizontal:
							mouseStartPos = _trackerRect.Width / 2;
						//	mouseStartPos = currentPoint.X - _trackerRect.X;
							break;

						case Orientation.Vertical:
							//mouseStartPos = currentPoint.Y - _trackerRect.Y;
							break;
					}
				}
//			}
//			else
//			{
				switch (_orientation)
				{
					case Orientation.Horizontal:
						if ( currentPoint.X + _trackerSize.Width / 2 >= Width - _indentWidth )
							offsetValue = _maximum - _minimum;
						else if ( currentPoint.X - _trackerSize.Width / 2 <= _indentWidth )
							offsetValue = 0;
						else
							offsetValue =
								(int)
								(((currentPoint.X - _indentWidth - _trackerSize.Width / 2) * (_maximum - _minimum))
								 / (Width - 2 * _indentWidth - _trackerSize.Width) + 0.5);

						break;

					case Orientation.Vertical:
						if ( currentPoint.Y + _trackerSize.Width / 2 >= Height - _indentHeight )
							offsetValue = 0;
						else if ( currentPoint.Y - _trackerSize.Width / 2 <= _indentHeight )
							offsetValue = _maximum - _minimum;
						else
							offsetValue =
								(int)
								(((Height - currentPoint.Y - _indentHeight - _trackerSize.Width / 2) * (_maximum - _minimum))
								 / (Height - 2 * _indentHeight - _trackerSize.Width) + 0.5);

						break;

					default:
						break;
				}

				oldValue = _value;
				_value = _minimum + offsetValue;
				Invalidate();

				if ( oldValue != _value )
				{
					OnScroll();
					OnValueChanged( _value );
				}
//			}
		}

		private void OnMouseUpSlider(object sender, MouseEventArgs e)
		{
			leftButtonDown = false;
			Capture = false;
		}

		private void OnMouseMoveSlider(object sender, MouseEventArgs e)
		{
			int offsetValue = 0;
			int oldValue = 0;
			PointF currentPoint;

			currentPoint = new PointF( e.X, e.Y );

			if ( leftButtonDown )
				try
				{
					switch (_orientation)
					{
						case Orientation.Horizontal:
							if ( (currentPoint.X + _trackerSize.Width - mouseStartPos) >= Width - _indentWidth )
								offsetValue = _maximum - _minimum;
							else if ( currentPoint.X - mouseStartPos <= _indentWidth )
								offsetValue = 0;
							else
								offsetValue =
									(int)
									(((currentPoint.X - mouseStartPos - _indentWidth) * (_maximum - _minimum))
									 / (Width - 2 * _indentWidth - _trackerSize.Width) + 0.5);

							break;

						case Orientation.Vertical:
							if ( currentPoint.Y + _trackerSize.Width / 2 >= Height - _indentHeight )
								offsetValue = 0;
							else if ( currentPoint.Y + _trackerSize.Width / 2 <= _indentHeight )
								offsetValue = _maximum - _minimum;
							else
								offsetValue =
									(int)
									(((Height - currentPoint.Y + _trackerSize.Width / 2 - mouseStartPos - _indentHeight) * (_maximum - _minimum))
									 / (Height - 2 * _indentHeight) + 0.5);

							break;
					}
				}
				catch (Exception)
				{
				}
				finally
				{
					oldValue = _value;
					_value = _minimum + offsetValue;
					Invalidate();

					if ( oldValue != _value )
					{
						OnScroll();
						OnValueChanged( _value );
					}
				}
		}

		#endregion
	}
}