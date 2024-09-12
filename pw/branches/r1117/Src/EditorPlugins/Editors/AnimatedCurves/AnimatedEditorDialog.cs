using System;
using System.Windows.Forms;
using EditorLib;
using libdb.Animated;
using libdb.DB;

namespace EditorPlugins.Editors.AnimatedCurves
{
	public partial class AnimatedEditorDialog : Form
	{
		private readonly IAnimated animated;
		private object[] backup = null;

		public AnimatedEditorDialog()
		{
			InitializeComponent();
		}

		public AnimatedEditorDialog( IEditorWinApplication _app, IAnimated _animated )
		{
			InitializeComponent();
	
			animated = _animated;
			
			Backup();

			animatedCurvesControl.Initialize( _app );
			animatedCurvesControl.SetRoot( BuildRoot() );
		}

    protected override void OnClosed( EventArgs e )
    {
      base.OnClosed( e );
      animatedCurvesControl.Deinitialize();
    }

		private void Backup()
		{
			backup = new object[animated.TracksCount];

			for ( int i = 0; i < animated.TracksCount; ++i )
			{
				backup[i] = animated.GetObjectTrack( i ).Serialize();
			}
		}

		private void Restore()
		{
			for ( int i = 0; i < animated.TracksCount; ++i )
			{
				animated.GetObjectTrack( i ).Deserialize( backup[i] );
			}
		}

		private AnimatedCurvesItem BuildRoot()
		{
			AnimatedCurvesItem result = new AnimatedCurvesItem(animated.GetType().Name);
			AnimatedComplexConverterAttribute complexConverter = TypeUtils.GetAttribute<AnimatedComplexConverterAttribute>( animated.GetType(), true );

			for ( int i = 0; i < animated.TracksCount; ++i )
			{
				string trackName = complexConverter != null ? complexConverter.Args[i] : "track " + i;

				AnimatedCurvesItem leaf = new AnimatedCurvesItem( trackName, animated, i, i );
				result.AddChild( leaf );
			}	
			
			return result;
		}

		private void btnCancel_Click( object sender, EventArgs e )
		{
			DialogResult = DialogResult.Cancel;
			Restore();
		}
	}
}
