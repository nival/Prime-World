using System.Collections.Generic;
using EditorNative.SceneElements.SceneObjects;

namespace EditorPlugins.Scene.Viewers
{
	internal interface IAnimationSelectionPanelExtension
		: IResourceParametersPanelExtension<DBTypes.Animation>
	{
		void StartAnimation( int animationIndex );
		void PauseAnimation( bool pause );
    IList<AnimInfo> GetAnimInfos();
	}
}
