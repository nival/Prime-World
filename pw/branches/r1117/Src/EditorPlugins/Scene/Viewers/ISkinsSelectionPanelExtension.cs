namespace EditorPlugins.Scene.Viewers
{
	public interface ISkinsSelectionPanelExtension
		: IResourceParametersPanelExtension<DBTypes.SkinPart>
	{
		void ShowSkin( int skinName, bool show );
	}
}
