namespace EditorLib.Binds
{
	public interface IBind
	{
		bool IsActive { get; }
		bool IsActivated { get; }
		bool IsDeactivated { get; }
		int Delta { get; }
		string Name { get; }

		event Operation Activated;
		event Operation Deactivated;
	}
}
