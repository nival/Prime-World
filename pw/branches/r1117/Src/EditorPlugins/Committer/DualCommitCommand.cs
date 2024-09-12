using System;
using EditorPlugins.Commands;
using libdb.Diagnostics;
using SharpSvn;

namespace EditorPlugins.Committer
{
	public class DualCommitCommand : EditorLib.Menu.IEditorCommand
	{
		public override bool Enabled
		{
			get
			{
				return true;
			}
		}
		public override void Execute( EditorLib.IEditorWinApplication application )
		{
			new SaveEditorCommand().Execute( application );
      DualCommitForm form = new DualCommitForm( application );
      form.ShowDialog();

      if ( !form.Success )
        return;

      SvnClient client = new SvnClient();

      SvnCommitArgs args = new SvnCommitArgs();
      SvnCommitResult commitResult = null;
      args.LogMessage = form.LogMessage;

      if ( form.SourceAddTargets.Count > 0 )
      {
        Log.TraceMessage( "Adding non-versioned Source file(s)..." );
        foreach ( string s in form.SourceAddTargets )
        {
          if ( !client.Add( s, SvnDepth.Empty ) )
          {
            Log.TraceError( "Unable to add Source file: {0}", s );
            return;
          }
        }
      }

      if ( form.SourceTargets.Count > 0 )
      {
        Log.TraceMessage( "Committing Source file(s)..." );
        try
        {
          client.Commit( form.SourceTargets, args, out commitResult );
        }
        catch ( System.Exception ex )
        {
          Log.TraceError( "Source commit failed. Exception: {0}", ex );
          return;
        }
        if ( !string.IsNullOrEmpty( commitResult.PostCommitError ) )
        {
          Log.TraceError( "Source commit failed. Error: {0}", commitResult.PostCommitError );
          return;
        }
        Log.TraceMessage( "Source commit successful. Revision: {0}", commitResult.Revision );

        args.LogMessage += Environment.NewLine + Environment.NewLine
          + string.Format( "Respective Art Sources revision: {0}", commitResult.Revision );

        foreach ( string item in form.SourceTargets )
          args.LogMessage += Environment.NewLine + "  " + item;

        commitResult = null;
      }

      Log.TraceMessage( "Committing Data file(s)..." );
      try
      {
        client.Commit( form.DataTargets, args, out commitResult );
      }
      catch ( System.Exception ex )
      {
        Log.TraceError( "Source commit failed. Exception: {0}", ex );
        return;
      }
      if ( !string.IsNullOrEmpty( commitResult.PostCommitError ) )
      {
        Log.TraceError( "Data commit failed. Error: {0}", commitResult.PostCommitError );
        return;
      }
      Log.TraceMessage( "Data commit successful. Revision: {0}", commitResult.Revision );
    }

		public override string Name
		{
			get { return "Commit..."; }
		}

    public override string TooltipText
    {
      get { return "Save changes and launch Combined Commit"; }
    }

    public override System.Drawing.Bitmap Image
    {
      get
      {
        return EditorPluginResources.BigGreenButton;
      }
    }

	}
}
