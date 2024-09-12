using System.Windows.Forms;
using EditorLib;

namespace EditorPlugins.Scene.Editors
{
	public interface IEditorControlDrawingExtension
	{
		string ExtensionName { get; }

		bool CanBeginDrawing { get; }
		IDrawingController BeginDrawing();

		void OnActivated();
		void OnDeactivated();
	}
}
