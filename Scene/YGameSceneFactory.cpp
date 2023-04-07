#include "YGameSceneFactory.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "EditScene.h"
#include "ResultScene.h"

using YScene::YGameSceneFactory;
using YScene::BaseScene;

BaseScene* YGameSceneFactory::CreateScene(const std::string& sceneName)
{
	// 次のシーンを生成
	BaseScene* newScene = nullptr;

	if (sceneName == Title_)	{ newScene = new TitleScene(); }
	if (sceneName == Select_)	{ newScene = new SelectScene(); }
	if (sceneName == Play_)		{ newScene = new PlayScene(); }
	if (sceneName == Result_)	{ newScene = new ResultScene(); }

	if (sceneName == Edit_)		{ newScene = new EditScene(); }

	return newScene;
}
