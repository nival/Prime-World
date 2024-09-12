using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Binds;
using libdb.Animated;
using libdb.DB;
using libdb.UndoRedo;

namespace EditorPlugins.Editors.Animated
{
	public partial class AnimatedEditor : Control
	{
		private const int SNAP_DISTANCE = 10;
		private const int CATCH_DISTANCE = 7;
    private const float MIN_ZOOM = 0.001f;
    private const float MAX_ZOOM = 10000f;

		private interface IState
		{
			void Apply( bool cancel );
			void Update();
		}

		private class KeyValueStorage
		{
			private float key = 0.0f;
			private object value = null;
			private bool isValid = false;

			public void Fill( float key, object value ) { this.key = key; this.value = value; isValid = true; }

			public bool IsValid { get { return isValid; } }
			public float Key { get { return key; } }
			public object Value { get { return value; } }
		}

		public struct KeyInfo
		{
			public int keyIndex;
			public int trackIndex;

			public KeyInfo( int keyIndex, int trackIndex ) 
      { 
        this.keyIndex = keyIndex; 
        this.trackIndex = trackIndex; 
      }

			public override bool Equals( object obj )
			{
			  if ( !( obj is KeyInfo ) ) 
          return false; 
        
        return ( (KeyInfo)obj ).keyIndex == keyIndex && ( (KeyInfo)obj ).trackIndex == trackIndex;
			}

			public override int GetHashCode() 
      { 
        return keyIndex ^ trackIndex; 
      }
		}

		public enum ApplySelectionAction
		{
			Replace,
			Add,
			Invert,
		}

    private IEditorWinApplication application;

		private readonly NumberFormatInfo numFormat = new NumberFormatInfo();

		private IState activeState = null;
		private DefaultState defaultState = null;
		private SelectionState selectionState = null;
		private MoveState moveState = null;

		private readonly Dictionary<KeyInfo, KeyValueStorage> selectedKeys = new Dictionary<KeyInfo, KeyValueStorage>();
		private KeyInfo draggedKey = new KeyInfo();

		private CombinedAnimated animated = null;

	  public CombinedAnimated Animated
	  {
      get { return animated; }
	  }

		private Color[] colors = null;
		private bool[] enabledTracks = null;

		private Point mouseDownPos = new Point();

		private SizeF steps = new SizeF();

		public AnimatedEditor()
		{
			InitializeComponent();
			SetStyle( ControlStyles.ResizeRedraw, true );
			SetStyle( ControlStyles.Selectable, true );
			SetStyle( ControlStyles.AllPaintingInWmPaint, true );
			DoubleBuffered = true;
		}

		private void OnDBResourceChanged( DBID dbid )
		{
			InvalidateAndUpdate();
		}

		public void Initialize( IEditorWinApplication _application )
		{
      //init states
      application = _application;
      defaultState = new DefaultState( this, _application.BindsManager );
      selectionState = new SelectionState( this, _application.BindsManager );
      moveState = new MoveState( this, _application.BindsManager );

		  InitBinds();

      SetTrackSet( new CombinedAnimated( new IAnimated[0] ), new Color[0] );

      DataBase.ChangeDBResourceEvent += OnDBResourceChanged;
    }

    public void Deinitialize()
    {
      DataBase.ChangeDBResourceEvent -= OnDBResourceChanged;
    }

    #region Binds

    private void InitBinds()
    {
      RegisterBind( "deleteKeys", new BindConfig { keys = new List<Keys> { Keys.Delete } }, OnDeleteKeys );
      RegisterBind( "cancel", new BindConfig { mouseButtons = MouseButtons.Right }, OnCancel );
      RegisterBind( "focusAll", new BindConfig { keys = new List<Keys> { Keys.A } }, OnFocusAll );
      RegisterBind( "focusSelected", new BindConfig { keys = new List<Keys> { Keys.F } }, OnFocusSelected );
      RegisterBind( "selectAll", new BindConfig { keys = new List<Keys> { Keys.ControlKey, Keys.A } }, OnSelectAll );
    }

    public Bind RegisterBind( string bindName, BindConfig bindConfig, Operation opActivated )
    {
      string section = GetType().ToString();
      Bind result = application.BindsManager.RegisterBind( section, bindName, bindConfig );
      result.Activated += opActivated;
      return result;
    }

    #endregion

    public void SetTrackSet( CombinedAnimated animated, Color[] colors )
    {
      activeState = defaultState;

      this.animated = animated;
      this.colors = new Color[animated.TracksCount];
      enabledTracks = new bool[animated.TracksCount];
      for ( int i = 0; i < animated.TracksCount; ++i )
      {
        this.colors[i] = i < colors.Length ? colors[i] : Color.Black;
        enabledTracks[i] = true;
      }

      OnFocusAll();
    }

		public void SetEnabledTrack( int trackIndex, bool enabled )
		{
			enabledTracks[trackIndex] = enabled;
			if ( !enabled )
			{
				List<KeyInfo> keysToRemove = new List<KeyInfo>();
				foreach ( KeyInfo key in selectedKeys.Keys )
				{
					if ( key.trackIndex == trackIndex )
						keysToRemove.Add( key );
				}

				foreach ( KeyInfo key in keysToRemove )
					selectedKeys.Remove( key );

				OnSelectedItemsChanged();
			}

			InvalidateAndUpdate();
		}

    public void SelectTracks( IEnumerable<int> tracks )
    {
      foreach( int trackIndex in tracks )
      {
        enabledTracks[trackIndex] = true;
        OnSelectedItemsChanged();
      }

      InvalidateAndUpdate();
    }

    public void ClearSelection()
    {
      for( int i = 0; i < enabledTracks.Length; i++ )
      {
        enabledTracks[i] = false;
      }

      selectedKeys.Clear();       
      InvalidateAndUpdate();
    }

		#region Commands from hot-keys

		private void OnDeleteKeys()
		{
			DeleteKeys(selectedKeys.Keys);
      selectedKeys.Clear();
      OnSelectedItemsChanged();
			InvalidateAndUpdate();
		}

		private void DeleteKeys(IEnumerable<KeyInfo> keys)
		{
			var sortedKeys = new List<KeyInfo>(keys);
			sortedKeys.Sort((a, b) => b.keyIndex - a.keyIndex);

			using (UndoRedoTransaction trans = new UndoRedoTransaction("Delete Keys"))
			{
				foreach (KeyInfo key in sortedKeys)
				{
					IAnimatedTrack track = animated.GetObjectTrack(key.trackIndex);
					track.DeleteKey(key.keyIndex);
				}

				trans.Commit();
			}
		}

		private void OnCancel()
		{
			activeState.Apply( true );
			activeState = defaultState;
		}

		internal void OnFocusAll()
		{
			RectangleF area = new RectangleF();
			area.X = -0.3f;
			area.Width = animated.GetTotalLength() + 1.0f;

			float top = animated.TracksCount > 0 ? GetRealKeyValue( 0, 0 ) : 1;
			float bottom =  animated.TracksCount > 0 ? top : 0;

      for( int i = 0; i < animated.TracksCount; ++i )
      {
				if ( !enabledTracks[i] )
					continue;

        IAnimatedTrack track = animated.GetObjectTrack( i );
        for( int n = 0; n < track.KeysCount; ++n )
        {
          float value = GetRealValue( track.GetObjectValue( n ) );
          if( value < top )
            top = value;
          if( value > bottom )
            bottom = value;
        }
      }

		  area.Y = top - 0.3f;
      area.Height = ( bottom - top ) + 0.6f;

			VisibleArea = area;
		}

		private void OnFocusSelected()
		{
			if ( selectedKeys.Count == 0 )
			{
				OnFocusAll();
				return;
			}

			RectangleF area = new RectangleF();

      float top = MAX_ZOOM;
			float bottom = MIN_ZOOM;

      float left = MAX_ZOOM;
      float right = MIN_ZOOM;

			foreach ( KeyInfo keyInfo in selectedKeys.Keys )
			{
				float key = animated.GetObjectTrack( keyInfo.trackIndex ).GetKey( keyInfo.keyIndex );
				
        if ( key < left )
					left = key;
				
        if ( key > right )
					right = key;

				float value = GetRealKeyValue( keyInfo.keyIndex, keyInfo.trackIndex );
				
        if ( value < top )
					top = value;
				
        if ( value > bottom )
					bottom = value;
			}

			//area.X = left - 0.5f;
			//area.Width = ( right - left ) + 1.0f;
			//area.Y = top - 1.5f;
			//area.Height = ( bottom - top ) + 3.0f;

			area.X = left - 0.5f;
			area.Width = ( right - left ) + 1.0f;
			area.Y = top - 0.5f;
			area.Height = ( bottom - top ) + 1.0f;

			VisibleArea = area;
		}

    private void OnSelectAll()
    {
      OnFocusAll();

      selectedKeys.Clear();

      for( int i = 0; i < animated.TracksCount; ++i )
      {
				if ( !enabledTracks[i] )
					continue;

				IAnimatedTrack track = animated.GetObjectTrack( i );

        for( int n = 0; n < track.KeysCount; ++n )
        {
          var keyInfo = new KeyInfo( n, i );

          if( !selectedKeys.ContainsKey( keyInfo ) )
            selectedKeys.Add( keyInfo, new KeyValueStorage() );
        }
      }

      InvalidateAndUpdate();
    }

		#endregion

		#region Group of Screen <-> Point converters

		public float GetRealWidth( int width )
		{
      return width * VisibleArea.Width / ClientSize.Width;
		}

		public float GetRealX( int x )
		{
			return VisibleArea.X + GetRealWidth( x );
		}

		public float GetRealHeight( int height )
		{
			return height * VisibleArea.Height / ClientSize.Height;
		}

		public float GetRealY( int y )
		{
			return VisibleArea.Y + GetRealHeight( ClientSize.Height - y );
		}

		public int GetScreenWidth( float width )
		{
      return (int)( width * ClientSize.Width / VisibleArea.Width );
		}

		public int GetScreenX( float x )
		{
			return GetScreenWidth( x - VisibleArea.X );
		}

		public int GetScreenHeight( float height )
		{
      return (int)( height * ClientSize.Height / VisibleArea.Height );
		}

		public int GetScreenY( float y )
		{
			return ClientSize.Height - GetScreenHeight( y - VisibleArea.Y );
		}

		#endregion

		private int GetScreenValue( object value )
		{
			if ( animated.TrackValueType == typeof( float ) )
				return GetScreenY( (float)value );
			else if ( animated.TrackValueType == typeof( int ) )
				return GetScreenY( (float)(int)value );
			else
				return GetScreenY( 0.0f ); 
		}

		private int GetScreenKeyValue( int keyIndex, int trackIndex )
		{
			return GetScreenValue( animated.GetObjectTrack( trackIndex ).GetObjectValue( keyIndex ) );
		}

		private int GetScreenValue( float time, int trackIndex )
		{
			return GetScreenValue( animated.GetObjectTrackValue( time, trackIndex ) );
		}

		private float GetRealValue( object value )
		{
			if ( animated.TrackValueType == typeof( float ) )
				return (float)value;
			else if ( animated.TrackValueType == typeof( int ) )
				return (float)(int)value;
			else
				return 0.0f; 
		}

		private float GetRealKeyValue( int keyIndex, int trackIndex )
		{
			return GetRealValue( animated.GetObjectTrack( trackIndex ).GetObjectValue( keyIndex ) );
		}

		private object GetTrackValue( int y )
		{
			if ( animated.TrackValueType == typeof( float ) )
				return GetRealY( y );
			else if ( animated.TrackValueType == typeof( int ) )
				return (int)Math.Round( GetRealY( y ) );
			else
				return null; //@Ivn@TODO: Write here some code for discrete support
		}

		#region OnPaint and some stuff for it

		private float GetStepX( out int digitsCount )
		{
			digitsCount = Math.Max( -3, (int)( Math.Floor( Math.Log10( GetRealWidth( minGridDisctance ) ) ) ) );
			float mult = (float)Math.Pow( 10.0, digitsCount );
			digitsCount = Math.Max( 0, -digitsCount );
			if ( GetScreenWidth( 2.0f * mult ) >= minGridDisctance )
				return 2.0f * mult;
			else if ( GetScreenWidth( 5.0f * mult ) >= minGridDisctance )
				return 5.0f * mult;
			else
				return 10.0f * mult;
		}

		private float GetStepY( out int digitsCount )
		{
			digitsCount = Math.Max( -3, (int)( Math.Floor( Math.Log10( GetRealHeight( minGridDisctance ) ) ) ) );
			float mult = (float)Math.Pow( 10.0, digitsCount );
			digitsCount = Math.Max( 0, -digitsCount );
			if ( GetScreenHeight( 2.0f * mult ) >= minGridDisctance )
				return 2.0f * mult;
			else if ( GetScreenHeight( 5.0f * mult ) >= minGridDisctance )
				return 5.0f * mult;
			else
				return 10.0f * mult;
		}

		private int DrawVerticalGrid( PaintEventArgs e )
		{
			int result = -1;

			float x = GetRealX( e.ClipRectangle.X );
			float width = GetRealWidth( e.ClipRectangle.Width );
			int digitsCount = 0;
			steps.Width = GetStepX( out digitsCount );

			for ( float x0 = (float)Math.Floor( x / steps.Width ) * steps.Width; x0 <= x + width; x0 += steps.Width )
			{
				int pos = GetScreenX( x0 );
				if ( Math.Abs( x0 ) < 0.0001f )
					result = pos;
				else
					e.Graphics.DrawLine( gridPen, pos, e.ClipRectangle.Top, pos, e.ClipRectangle.Bottom );
			}

			numFormat.NumberDecimalDigits = digitsCount;
			for ( float x0 = (float)Math.Floor( GetRealX( 0 ) / steps.Width ) * steps.Width; x0 <= x + VisibleArea.Width; x0 += steps.Width )
			{
				int pos = GetScreenX( x0 );
				if ( pos < 2 )
					continue;
				e.Graphics.DrawString( x0.ToString( "F", numFormat ), Font, Math.Abs( x0 ) < 0.0001f ? axisBrush : gridBrush, pos + 2.0f, ClientSize.Height - Font.Height - 2.0f );
			}

			return result;
		}

		private int DrawHorizontalGrid( PaintEventArgs e )
		{
			int result = -1;

			float y = GetRealY( e.ClipRectangle.Bottom );
			float height = GetRealHeight( e.ClipRectangle.Height );
			int digitsCount = 0;
			steps.Height = GetStepY( out digitsCount );

			for ( float y0 = (float)Math.Floor( y / steps.Height ) * steps.Height; y0 <= y + height; y0 += steps.Height )
			{
				int pos = GetScreenY( y0 );
				if ( Math.Abs( y0 ) < 0.0001f )
					result = pos;
				else
					e.Graphics.DrawLine( gridPen, e.ClipRectangle.Left, pos, e.ClipRectangle.Right, pos );
			}

			numFormat.NumberDecimalDigits = digitsCount;
			for ( float y0 = (float)Math.Floor( GetRealY( ClientSize.Height ) / steps.Height ) * steps.Height; y0 <= y + VisibleArea.Height; y0 += steps.Height )
			{
				int pos = GetScreenY( y0 );
				if ( pos > ClientSize.Height - Font.Height - 2 )
					continue;
				e.Graphics.DrawString( y0.ToString( "F", numFormat ), Font, Math.Abs( y0 ) < 0.0001f ? axisBrush : gridBrush, 2.0f, pos + 2.0f );
			}

			return result;
		}

		private void DrawGraph( int index, PaintEventArgs e )
		{
			if ( !enabledTracks[index] )
				return;

			
			IAnimatedTrack track = animated.GetObjectTrack( index );
      float x0 = GetRealX( e.ClipRectangle.Left );
      float xLength = GetRealX( e.ClipRectangle.Right );
			float step = Math.Max( 0.0001f, GetRealWidth( 1 ) );
			int keyIndex = track.FindKey( x0 );
			if ( keyIndex < 0 )
				keyIndex = 0;
			else if ( keyIndex >= track.KeysCount )
				return;

			Pen pen = new Pen( colors[index] );

			Brush brush = new SolidBrush( colors[index] );
			x0 = track.GetKey( keyIndex );
			float xKey = track.GetKey( keyIndex );
			int y0 = GetScreenKeyValue( keyIndex, index );

      e.Graphics.DrawLine( pen, e.ClipRectangle.Left, y0, GetScreenX( x0 ), y0 );

			while ( x0 <= xLength )
			{
				if ( x0 == xKey )
				{
					int radius = enabledTracks[index] ? 4 : 2;
					e.Graphics.FillEllipse( brush, GetScreenX( x0 ) - radius + 1, y0 - radius + 1, 2 * radius - 1, 2 * radius - 1 );
					if ( selectedKeys.ContainsKey( new KeyInfo( keyIndex, index ) ) )
						e.Graphics.DrawEllipse( new Pen( Color.White ), GetScreenX( x0 ) - radius, y0 - radius, 2 * radius + 1, 2 * radius + 1 );
					++keyIndex;
					if ( keyIndex >= track.KeysCount )
						break;
					xKey = track.GetKey( keyIndex );
				}

				int y1 = 0;
				float x1 = x0 + step;
				if ( x1 > xKey )
				{
					x1 = xKey;
					y1 = GetScreenKeyValue( keyIndex, index );
				}
				else
					y1 = GetScreenValue( x1, index );
        e.Graphics.DrawLine( pen, GetScreenX( x0 ), y0, GetScreenX( x1 ), y1 );
				x0 = x1;
				y0 = y1;
			}

      e.Graphics.DrawLine( pen, GetScreenX( x0 ), y0, e.ClipRectangle.Right, y0 );
		}

		protected override void OnPaint( PaintEventArgs e )
		{
      e.Graphics.FillRectangle( backBrush, e.ClipRectangle );

			//draw grid
			int zeroVerticalPos = DrawVerticalGrid( e );
			int zeroHorizontalPos = DrawHorizontalGrid( e );
			if ( zeroHorizontalPos > 0 )
				e.Graphics.DrawLine( axisPen, e.ClipRectangle.Left, zeroHorizontalPos, e.ClipRectangle.Right, zeroHorizontalPos );
			if ( zeroVerticalPos > 0 )
				e.Graphics.DrawLine( axisPen, zeroVerticalPos, e.ClipRectangle.Top, zeroVerticalPos, e.ClipRectangle.Bottom );
			if ( animated != null )
			{
				int lengthAxis = GetScreenX( animated.GetTotalLength() );
				if ( lengthAxis >= e.ClipRectangle.Left && lengthAxis <= e.ClipRectangle.Right )
				{
					axisPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
					e.Graphics.DrawLine( axisPen, lengthAxis, e.ClipRectangle.Top, lengthAxis, e.ClipRectangle.Bottom );
					axisPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
				}
			}

			// draw grahics
			if ( animated != null )
			{
				for ( int i = 0; i < animated.TracksCount; ++i )
					DrawGraph( i, e );
			}

			// draw selection
			if ( SelectionArea.IntersectsWith( e.ClipRectangle ) )
			{
				Rectangle clipped = SelectionArea;
				clipped.Intersect( e.ClipRectangle );
				e.Graphics.FillRectangle( selectionBrush, clipped );
				e.Graphics.DrawRectangle( selectionPen, SelectionArea );
			}
		}

		private void InvalidateAndUpdate()
		{
			Invalidate();
			Update();
		}

		#endregion

		private bool GetTracksOnPoint( int x, int y, List<int> tracks )
		{
			bool found = false;

			float x0 = GetRealX( x - 2 );
			float x1 = GetRealX( x + 2 );
			for ( int i = 0; i < animated.TracksCount; ++i )
			{
				if ( !enabledTracks[i] )
					continue;

				int y0 = GetScreenValue( x0, i );
				int y1 = GetScreenValue( x1, i );

				if ( Math.Abs( y - y0 ) < CATCH_DISTANCE || Math.Abs( y - y1 ) < CATCH_DISTANCE )
				{
					tracks.Add( i );
					found = true;
				}
			}

			return found;
		}

		private bool TryFindKey( int x, int y, IAnimatedTrack track, out int key )
		{
			key = track.FindKey( GetRealX( x ) );
			if ( key >= 0 && Math.Abs( x - GetScreenX( track.GetKey( key ) ) ) < CATCH_DISTANCE && Math.Abs( y - GetScreenValue( track.GetObjectValue( key ) ) ) < CATCH_DISTANCE )
				return true;
			++key;
			if ( key < track.KeysCount && Math.Abs( x - GetScreenX( track.GetKey( key ) ) ) < CATCH_DISTANCE && Math.Abs( y - GetScreenValue( track.GetObjectValue( key ) ) ) < CATCH_DISTANCE )
				return true;

			key = -1;
			return false;
		}

		private bool GetKeysOnPoint( int x, int y, List<KeyInfo> keys )
		{
			bool found = false;
			for ( int i = 0; i < animated.TracksCount; ++i )
			{
				if ( !enabledTracks[i] )
					continue;

				IAnimatedTrack track = animated.GetObjectTrack( i );
				int key = -1;
				if ( TryFindKey( x, y, track, out key ) )
				{
					keys.Add( new KeyInfo( key, i ) );
					found = true;
				}
			}

			return found;
		}

		private bool GetKeysInSelection( List<KeyInfo> keys )
		{
			bool found = false;

			float rx = GetRealX( SelectionArea.Left );
			for ( int i = 0; i < animated.TracksCount; ++i )
			{
				if ( !enabledTracks[i] )
					continue;

				IAnimatedTrack track = animated.GetObjectTrack( i );

				int key = Math.Max( 0, track.FindKey( rx ) );
				while ( key < track.KeysCount && track.GetKey( key ) <= SelectionArea.Right )
				{
					int sx = GetScreenX( track.GetKey( key ) );
					int sy = GetScreenKeyValue( key, i );
					if ( SelectionArea.Left <= sx && sx <= SelectionArea.Right && SelectionArea.Top <= sy && sy <= SelectionArea.Bottom )
					{
						keys.Add( new KeyInfo( key, i ) );
						found = true;
					}
					++key;
				}
			}

			return found;
		}

		private bool IsSmallShift( int x, int y )
		{
			return Math.Abs( x - mouseDownPos.X ) < 3 && Math.Abs( y - mouseDownPos.Y ) < 3;
		}

		#region Helpers for states

		public void Pan( int x, int y )
		{
			if ( x == 0 && y == 0 )
				return;

			float xShift = GetRealWidth( x );
			float yShift = GetRealWidth( y );
			VisibleArea = new RectangleF( VisibleArea.X + xShift, VisibleArea.Y + yShift, VisibleArea.Width, VisibleArea.Height );
		}

		public void Zoom( float factor )
		{
			if ( factor == 1.0f )
				return;

		  float x = VisibleArea.X + VisibleArea.Width*0.5f*( 1.0f - factor );
		  float y = VisibleArea.Y + VisibleArea.Height*0.5f*( 1.0f - factor );
		  float width = VisibleArea.Width*factor;
		  float height = VisibleArea.Height*factor;

      // ограничение на zoom
      if( width < MIN_ZOOM || width >= MAX_ZOOM || height < MIN_ZOOM || height >= MAX_ZOOM )
        return;

      // center based zoom
			VisibleArea = new RectangleF( x, y, width, height);
		}

		public void StoreValuesForSelectedKeys()
		{
			foreach ( KeyValuePair<KeyInfo, KeyValueStorage> key in selectedKeys )
				key.Value.Fill( animated.GetObjectTrack( key.Key.trackIndex ).GetKey( key.Key.keyIndex ), animated.GetObjectTrack( key.Key.trackIndex ).GetObjectValue( key.Key.keyIndex ) );
		}

		public void RestoreValuesForSelectedKeys()
		{
			foreach ( KeyValuePair<KeyInfo, KeyValueStorage> key in selectedKeys )
			{
				animated.GetObjectTrack( key.Key.trackIndex ).SetKey( key.Key.keyIndex, key.Value.Key );
				animated.GetObjectTrack( key.Key.trackIndex ).SetObjectValue( key.Key.keyIndex, key.Value.Value );
			}

			InvalidateAndUpdate();
		}

		public void MoveSelectedKeys( int x, int y, bool snapToGrid )
		{
			float keyShift = GetRealWidth( x );

			if ( keyShift != 0.0f )
			{
				foreach ( KeyValuePair<KeyInfo, KeyValueStorage> key in selectedKeys )
				{
				  IAnimatedTrack track = animated.GetObjectTrack( key.Key.trackIndex );

          if ( key.Key.keyIndex == 0)
          {
            keyShift = 0;
          }
          else if( keyShift < 0 )
          {
            float boundLeft = ( key.Key.keyIndex > 0 ) ? track.GetKey( key.Key.keyIndex - 1 ) : 0.0f;
            keyShift = Math.Min( Math.Max( keyShift, boundLeft - key.Value.Key ), 0.0f );
          }
          else
          {
            float boundRight = ( key.Key.keyIndex < track.KeysCount - 1 )
                                 ? track.GetKey( key.Key.keyIndex + 1 )
                                 : float.MaxValue;
            keyShift = Math.Max( Math.Min( keyShift, boundRight - key.Value.Key ), 0.0f );
          }
				}
			}

			KeyValueStorage selectedDraggedKey = null;
			if ( snapToGrid && selectedKeys.TryGetValue( draggedKey, out selectedDraggedKey ) && 
        selectedDraggedKey != null && selectedDraggedKey.IsValid )
			{
				float key = selectedDraggedKey.Key + keyShift;
				float nearestKey = (float)Math.Round( key / steps.Width ) * steps.Width;
				if ( Math.Abs( GetScreenWidth( nearestKey - key ) ) < SNAP_DISTANCE )
					keyShift = nearestKey - selectedDraggedKey.Key;

				int screenValue = GetScreenValue( selectedDraggedKey.Value );
				float value = GetRealY( screenValue + y );
				float nearestValue = (float)Math.Round( value / steps.Height ) * steps.Height;
				if ( Math.Abs( GetScreenHeight( nearestValue - value ) ) < SNAP_DISTANCE )
					y = GetScreenY( nearestValue ) - screenValue;
			}

			foreach ( KeyValuePair<KeyInfo, KeyValueStorage> key in selectedKeys )
			{
				animated.GetObjectTrack( key.Key.trackIndex ).SetKey( key.Key.keyIndex, key.Value.Key + keyShift );
				object value = GetTrackValue( GetScreenValue( key.Value.Value ) + y );
				if ( animated.GetObjectTrack( key.Key.trackIndex ).GetObjectValue( key.Key.keyIndex ) != value )
					animated.GetObjectTrack( key.Key.trackIndex ).SetObjectValue( key.Key.keyIndex, value );
			}

			if ( SelectedItemsMoved != null )
				SelectedItemsMoved( this, EventArgs.Empty );

			InvalidateAndUpdate();
		}

		public void ApplySelection( ApplySelectionAction action )
		{
			List<KeyInfo> keys = new List<KeyInfo>();
			bool smallSelection = GetScreenWidth( SelectionArea.Width ) < 3 && GetScreenHeight( SelectionArea.Height ) < 3;
			if ( smallSelection )
				GetKeysOnPoint( SelectionArea.X + SelectionArea.Width / 2, SelectionArea.Y + SelectionArea.Height / 2, keys );
			else
				GetKeysInSelection( keys );

			switch ( action )
			{
			case ApplySelectionAction.Replace:
				selectedKeys.Clear();
				foreach ( KeyInfo key in keys )
				{
					if ( !selectedKeys.ContainsKey( key ) )
						selectedKeys.Add( key, new KeyValueStorage() );
				}
				break;
			case ApplySelectionAction.Add:
				foreach ( KeyInfo key in keys )
				{
					if ( !selectedKeys.ContainsKey( key ) )
						selectedKeys.Add( key, new KeyValueStorage() );
				}
				break;
			case ApplySelectionAction.Invert:
				foreach ( KeyInfo key in keys )
				{
					if ( selectedKeys.ContainsKey( key ) )
						selectedKeys.Remove( key );
					else
						selectedKeys.Add( key, new KeyValueStorage() );
				}
				break;
			}

			OnSelectedItemsChanged();
			InvalidateAndUpdate();
		}

		private void OnSelectedItemsChanged()
		{
			if ( SelectedItemsChanged != null )
				SelectedItemsChanged( this, EventArgs.Empty );
		}

		#endregion

		private void UpdateBinds()
		{
			activeState.Update();
			application.BindsManager.Update();
		}

		#region Overrided mouse and keyboard handlers for BindsManager

		//Mouse Down:
		//  Empty: Start Selection
		//  On Curve: Start Selection
		//  On Non Selected Key:
		//    Selection modifiers present: Start Selection
		//    Just mouse down: Select Key, Start Move
		//  On Selected Key: Start Move
		protected override void OnMouseDown( MouseEventArgs e )
		{
		  EnterDBOperation();

			base.OnMouseDown( e );
			Select();
      application.BindsManager.OnMouseDown( e );

			if ( e.Button == MouseButtons.Left )
			{
				mouseDownPos.X = e.X;
				mouseDownPos.Y = e.Y;

				List<KeyInfo> keys = new List<KeyInfo>();
        List<int> tracks = new List<int>();
        if ( GetKeysOnPoint( e.X, e.Y, keys ) )
				{
          if( selectionState.HasModifiers )
          {
            activeState = selectionState.Activate( e.X, e.Y );
          }
          else
					{
						bool hasSelectedKey = false;
						foreach ( KeyInfo key in keys )
						{
							if ( selectedKeys.ContainsKey( key ) )
							{
								draggedKey = key;
								hasSelectedKey = true;
								break;
							}
						}

						if ( !hasSelectedKey )
						{
							selectedKeys.Clear();
							draggedKey = keys[0];
							foreach ( KeyInfo key in keys )
							{
                selectedKeys.Add( key, new KeyValueStorage() );
							}

							OnSelectedItemsChanged();
						}

						activeState = moveState.Activate();
					}
				}
        else if ( GetTracksOnPoint( e.X, e.Y, tracks ) )
        {
          activeState.Apply( true );
          selectedKeys.Clear();
          float key = GetRealX( e.X );

          if(key < 0)
          {
            UpdateBinds();
            return;
          }

          object value = GetTrackValue( e.Y );
          foreach ( int track in tracks )
            animated.GetObjectTrack( track ).AddObjectKey( key, value );

          GetKeysOnPoint( e.X, e.Y, keys );
          foreach ( KeyInfo keyItem in keys )
            selectedKeys.Add( keyItem, new KeyValueStorage() );

          OnSelectedItemsChanged();
          activeState = moveState.Activate();
        }
				else
					activeState = selectionState.Activate( e.X, e.Y );
			}
			UpdateBinds();
		}

		//Mouse Up:
		//  Empty:
		//    Small Shift: Clear Selection
		//    Normal Shift: Apply Selection/Stop Move
		//  On Curve:
		//    Small Shift: Add Key
		//    Normal Shift: Apply Selection/Stop Move
		//  On Key: Apply Selection/Stop Move
		protected override void OnMouseUp( MouseEventArgs e )
		{     
      base.OnMouseUp( e );
      application.BindsManager.OnMouseUp( e );

			if ( e.Button == MouseButtons.Left )
			{
				List<KeyInfo> keys = new List<KeyInfo>();
				List<int> tracks = new List<int>();
				if ( GetKeysOnPoint( e.X, e.Y, keys ) )
					activeState.Apply( false );
				else if ( GetTracksOnPoint( e.X, e.Y, tracks ) )
				{
					if ( IsSmallShift( e.X, e.Y ) )
					{
						activeState.Apply( true );
						selectedKeys.Clear();
						float key = GetRealX( e.X );

            if( key < 0 )
            {
              activeState = defaultState;
              UpdateBinds();

              LeaveDBOperation();
              return;
            }

						object value = GetTrackValue( e.Y );
						foreach ( int track in tracks )
							animated.GetObjectTrack( track ).AddObjectKey( key, value );

						OnSelectedItemsChanged();
						InvalidateAndUpdate();
					}
					else
						activeState.Apply( false );
				}
				else if ( IsSmallShift( e.X, e.Y ) )
				{
					activeState.Apply( true );
					selectedKeys.Clear();

					OnSelectedItemsChanged();
					InvalidateAndUpdate();
				}
				else
					activeState.Apply( false );
			}
      else if ( e.Button == MouseButtons.Right )
      {
        selectedKeys.Clear();
        OnSelectedItemsChanged();
        List<KeyInfo> keys = new List<KeyInfo>();
        if ( GetKeysOnPoint( e.X, e.Y, keys ) )
        {
					DeleteKeys(keys);
          InvalidateAndUpdate();
        }
      }

			activeState = defaultState;
			UpdateBinds();

		  LeaveDBOperation();
		}

		protected override void OnMouseMove( MouseEventArgs e )
		{
			base.OnMouseMove( e );
      application.BindsManager.OnMouseMove( e );
			UpdateBinds();
		}

		protected override void OnMouseWheel( MouseEventArgs e )
		{
			base.OnMouseWheel( e );
      application.BindsManager.OnMouseWheel( e );
			UpdateBinds();
		}

		protected override void OnKeyDown( KeyEventArgs e )
		{
			base.OnKeyDown( e );
      application.BindsManager.OnKeyDown( e );
			UpdateBinds();
			e.Handled = true;
		}

		protected override void OnKeyUp( KeyEventArgs e )
		{
			base.OnKeyUp( e );
      application.BindsManager.OnKeyUp( e );
			UpdateBinds();
			e.Handled = true;
		}

    protected override void OnLostFocus( EventArgs e )
    {
      base.OnLostFocus( e );
      LeaveDBOperation();
      application.BindsManager.ResetPressedKeys();
    }

    #endregion

    #region DB Operations Optimization

    bool isDBOperationStarted = false;

    private void EnterDBOperation()
    {
      if( isDBOperationStarted )
        return;

      DataBase.UndoRedoManager.Start( "Move Track Point" );
      isDBOperationStarted = true;
      System.Diagnostics.Debug.Print( "1.EnterDBOperation" );
    }

    private void LeaveDBOperation()
    {
      if( !isDBOperationStarted )
        return;

      DataBase.UndoRedoManager.Commit();
      isDBOperationStarted = false;
      System.Diagnostics.Debug.Print( "2.LeaveDBOperation" );
    }

		#endregion

		#region Control design properties and depended variables (pens and brushes)

		private Color gridColor = Color.FromKnownColor( KnownColor.DarkGray );
		private Pen gridPen = new Pen( Color.FromKnownColor( KnownColor.DarkGray ) );
		private Brush gridBrush = new SolidBrush( Color.FromKnownColor( KnownColor.DarkGray ) );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "DarkGray" )]
		public Color GridColor { get { return gridColor; } set { gridColor = value; gridPen = new Pen( gridColor ); gridBrush = new SolidBrush( gridColor ); InvalidateAndUpdate(); } }

		private Color axisColor = Color.FromKnownColor( KnownColor.White );
		private Pen axisPen = new Pen( Color.FromKnownColor( KnownColor.White ) );
		private Brush axisBrush = new SolidBrush( Color.FromKnownColor( KnownColor.White ) );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "White" )]
		public Color AxisColor { get { return axisColor; } set { axisColor = value; axisPen = new Pen( axisColor ); axisBrush = new SolidBrush( axisColor ); InvalidateAndUpdate(); } }

		private Color selectionColor = Color.FromKnownColor( KnownColor.Highlight );
		private Pen selectionPen = new Pen( Color.FromKnownColor( KnownColor.Highlight ) );
		private Brush selectionBrush = new SolidBrush( Color.FromArgb( 32, Color.FromKnownColor( KnownColor.Highlight ) ) );
		[Category( "Appearance" )]
		[DefaultValue( typeof( Color ), "Highlight" )]
		public Color SelectionColor { get { return selectionColor; } set { selectionColor = value; selectionPen = new Pen( selectionColor ); selectionBrush = new SolidBrush( Color.FromArgb( 32, selectionColor ) ); InvalidateAndUpdate(); } }

		private Brush backBrush = new SolidBrush( Color.FromKnownColor( KnownColor.Gray ) );
		[Category( "Appearance" )]
		public new Color BackColor { get { return base.BackColor; } set { base.BackColor = value; backBrush = new SolidBrush( base.BackColor ); InvalidateAndUpdate(); } }

		private int minGridDisctance = 50;
		[Category( "Appearance" )]
		[DefaultValue( 50 )]
		public int MinGridDistance { get { return minGridDisctance; } set { minGridDisctance = value; InvalidateAndUpdate(); } }

		#endregion

		#region Control additional events

		[Category( "Behaviour" )]
		public event EventHandler SelectedItemsChanged = null;

		[Category( "Behaviour" )]
		public event EventHandler SelectedItemsMoved = null;

		#endregion

		#region Control properties

		private RectangleF visibleArea = new RectangleF( -0.5f, -0.5f, 11.0f, 11.0f );
		[Browsable( false )]
		public RectangleF VisibleArea 
    { 
      get { return visibleArea; } 
      set
      {
        visibleArea = value; 
        InvalidateAndUpdate();
      } 
    }

		private Rectangle selectionArea = new Rectangle();
	  [Browsable( false )]
	  public Rectangle SelectionArea
	  {
	    get { return selectionArea; } 
      set
      {
        selectionArea = value; 
        InvalidateAndUpdate();
      }
	  }

		[Browsable( false )]
		public IEnumerable<KeyInfo> SelectedItems 
    { 
      get { return selectedKeys.Keys; } 
    }

		[Browsable( false )]
		public bool HasSelectedItems 
    { 
      get { return selectedKeys.Count > 0; } 
    }

		#endregion
  }
}