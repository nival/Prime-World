#include "../Sound/SoundScene.h"

namespace NScene
{
	struct SoundItem
	{
		NSoundScene::SoundDescription soundDesc;
		int soundIdx;
		float time;
		bool isPlay;
	};
}
