using System;
using System.Collections.Generic;
using libdb.Animated;

namespace EditorPlugins.Editors.AnimatedCurves
{
	public class AnimatedCurvesItem
	{
		public string Text { get; set; }
		public IAnimated Animated { get; set; }
		//public int TrackNo { get; set; }
		public int TrackAbsNo { get; set; }
		public System.Drawing.Color Color { get; set; }

		private int indent;
		public int Indent
		{
			get
			{
				return indent;
			}
			private set
			{
				indent = value;
				childrenList.ForEach( x => x.Indent = Indent + 1 );
			}
		}

		private bool selected;
		public bool Selected
		{
			get { return selected; }
			set
			{
				selected = value;
				childrenList.ForEach( item => item.Selected = selected );
			}
		}

		private readonly List<AnimatedCurvesItem> childrenList;

		#region Constructors

		public AnimatedCurvesItem( string _text )
			: this( _text, new List<AnimatedCurvesItem>() )
		{
		}

		public AnimatedCurvesItem( string _text, List<AnimatedCurvesItem> _children )
		{
			Text = _text;
			Animated = null;
			childrenList = _children;
			Color = System.Drawing.Color.Cyan;
			childrenList.ForEach( x => x.Indent = Indent + 1 );
		}

		public AnimatedCurvesItem( string _text, IAnimated _animated, int _trackNo, int _trackAbsNo )
		{
			Text = _text;
			Animated = _animated;
			//TrackNo = _trackNo;
			TrackAbsNo = _trackAbsNo;
			childrenList = new List<AnimatedCurvesItem>();
			Color = GetColorByName( Text );
		}

		#endregion

		public override string ToString()
		{
			return Text;
		}

		public void ForEach( Action<AnimatedCurvesItem> _action )
		{
			_action( this );

			foreach ( var item in childrenList )
			{
				item.ForEach( _action );
			}
		}

		public void ForEachAnimated( Action<AnimatedCurvesItem> _action )
		{
			if ( Animated != null )
				_action( this );

			foreach ( var item in childrenList )
			{
				item.ForEachAnimated( _action );
			}
		}

		private System.Drawing.Color GetColorByName( string name )
		{
			switch ( name.Trim().ToUpper() )
			{
			case "X":
			case "R":
			case "TRANSLATEX":
			case "SCALEX":
			case "ROTATEX":
				return System.Drawing.Color.Red;

			case "Y":
			case "G":
			case "TRANSLATEY":
			case "SCALEY":
			case "ROTATEY":
				return System.Drawing.Color.Lime;

			case "Z":
			case "B":
			case "TRANSLATEZ":
			case "SCALEZ":
			case "ROTATEZ":
				return System.Drawing.Color.Blue;

			case "A":
				return System.Drawing.Color.Orange;
			}

			return System.Drawing.Color.Purple;
		}

		public AnimatedCurvesItem[] GetChildrenList()
		{
			return childrenList.ToArray();
		}

		public AnimatedCurvesItem AddChild( AnimatedCurvesItem child )
		{
			child.Indent = Indent + 1;
			childrenList.Add( child );
			return child;
		}

		public bool RemoveChild( AnimatedCurvesItem child )
		{
			return childrenList.Remove( child );
		}
	}
}
