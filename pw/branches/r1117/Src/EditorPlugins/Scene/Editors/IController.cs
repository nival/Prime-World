namespace EditorPlugins.Scene.Editors
{
	public interface IController<TResource>
	{
		void Unsubscribe();
    TResource Resource { get; }
	}
}
