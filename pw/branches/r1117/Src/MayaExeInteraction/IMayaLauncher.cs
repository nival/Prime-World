namespace Tools.MayaExeInteraction
{
	interface IMayaLauncher
	{
		bool ExecuteCommand(MayaCommand _command);
		void Terminate();
	}
}
