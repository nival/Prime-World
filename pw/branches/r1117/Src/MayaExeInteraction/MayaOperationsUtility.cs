using System;
using System.IO;
using libdb.Diagnostics;

namespace Tools.MayaExeInteraction
{
  public static class MayaOperationsUtility
  {
  	private static IMayaLauncher maya;
		private static IMayaLauncher Maya
		{
			get
			{
				if(maya == null)
					maya = new MayaLauncher( PathToMaya, Path.GetFullPath(@"..\Tools\MayaPlugins\") );

				return maya;
			}
		}

  	public static string PathToMaya { get; set; }

    public static bool LaunchAnimationImportScript( string skelSrcFileName, string selection, string animSrcFileName, string tempFileName, float compression )
    {
      try
      {
        var command = new MayaImportCommand();
        command.Name = "H6_exportAnim";
				command.Script = Path.GetFullPath( @"..\Tools\MayaScripts\H6_exportAnim.mel" );
        command.Scene = skelSrcFileName;
        command.OutFile = tempFileName;
        command.IsCrcRequired = true;
        command.ParametersOrder = "selection|animSrcFileName|compression";
        command.Parameters.Add( "selection", selection );
        command.Parameters.Add( "animSrcFileName", animSrcFileName );
        command.Parameters.Add( "compression", compression.ToString() );

				//команда сама должна сохранить файл
      	return Maya.ExecuteCommand( command );
      }
      catch( Exception err)
      {
        Log.TraceError( err.Message );
      }

      return false;
    }

		public static bool LaunchStaticMeshImportScript( string srcFileName, string selection, string tempFileName )
		{
			try
			{
				var command = new MayaImportCommand();
				command.Name = "H6_exportStat";
				command.Script = Path.GetFullPath( @"..\Tools\MayaScripts\H6_exportStat.mel" );
				command.Scene = srcFileName;
				command.OutFile = tempFileName;
				command.IsCrcRequired = true;
				command.Parameters.Add( "selection", selection );

				return Maya.ExecuteCommand(command);
			}
			catch ( Exception err )
			{
				Log.TraceError( err.Message );
			}

			return false;
		}

		public static bool LaunchSkinPartImportScript( string skelSrcFileName, string skinSrcFileName, string selection, string tempFileName, string rootJoint )
		{
			try
			{
				var command = new MayaImportCommand();
				command.Name = "H6_exportSkin";
				command.Script = Path.GetFullPath( @"..\Tools\MayaScripts\H6_exportSkin.mel" );
				command.Scene = skelSrcFileName;
				command.OutFile = tempFileName;
				command.IsCrcRequired = true;
				command.ParametersOrder = "skinSrcFileName|selection|root";
				command.Parameters.Add( "skinSrcFileName", skinSrcFileName );
				command.Parameters.Add( "selection", selection );
				command.Parameters.Add( "root", rootJoint );

				return Maya.ExecuteCommand( command );
			}
			catch ( Exception err )
			{
				Log.TraceError( err.Message );
			}

			return false;
		}

		public static bool LaunchParticleFxImportScript( string srcFileName, string selection, string tempFileName, float compression )
		{
			try
			{
				var command = new MayaImportCommand();
				command.Name = "H6_exportPart";
				command.Script = Path.GetFullPath( @"..\Tools\MayaScripts\H6_exportPart.mel" );
				command.Scene = srcFileName;
				command.OutFile = tempFileName;
				command.IsCrcRequired = true;
				command.ParametersOrder = "selection|compression";
				command.Parameters.Add( "selection", selection );
				command.Parameters.Add( "compression", compression.ToString() );

				return Maya.ExecuteCommand( command );
			}
			catch ( Exception err )
			{
				Log.TraceError( err.Message );
			}

			return false;
		}

		public static bool LaunchSkeletonImportScript( string srcFileName, string selection, string tempFileName )
		{
			try
			{
				var command = new MayaImportCommand();
				command.Name = "H6_exportSkel";
				command.Script = Path.GetFullPath( @"..\Tools\MayaScripts\H6_exportSkel.mel" );
				command.Scene = srcFileName;
				command.OutFile = tempFileName;
				command.IsCrcRequired = true;
				command.Parameters.Add( "selection", selection );

				return Maya.ExecuteCommand( command );
			}
			catch ( Exception err )
			{
				Log.TraceError( err.Message );
			}

			return false;
		}

		public static bool LaunchCollisionGeometryImportScript( string srcFileName, string selection, string tempFileName )
		{
			return LaunchStaticMeshImportScript( srcFileName, selection, tempFileName );
		}

		public static bool LaunchSceneContentsScript( string srcFileName )
		{
			try
			{
				string tempFileName = srcFileName + ".desc";

				var command = new MayaImportCommand();
				command.Name = "natSceneAnalizer";
				command.Script = Path.GetFullPath( @"..\Tools\MayaScripts\natSceneAnalizer.mel" );
				command.Scene = srcFileName;
				command.OutFile = tempFileName;
				command.IsCrcRequired = false;

				return Maya.ExecuteCommand( command );
			}
			catch ( Exception err )
			{
				Log.TraceError( err.Message );
			}

			return false;
		}

    public static void Terminate()
    {
			Maya.Terminate();
    }
  }
}
