#include "YGameSceneFactory.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"

#include "TestScene.h"
#include "DemoScene.h"

using YScene::YGameSceneFactory;
using YScene::BaseScene;

const std::string YGameSceneFactory::Title_		 = "TITLE";
const std::string YGameSceneFactory::Select_	 = "SELECT";
const std::string YGameSceneFactory::Play_		 = "PLAY";
const std::string YGameSceneFactory::Test_		 = "TEST";
const std::string YGameSceneFactory::Demo_		 = "DEMO";

BaseScene* YGameSceneFactory::CreateScene(const std::string& sceneName)
{
	// 次のシーンを生成
	BaseScene* newScene = nullptr;

	if (sceneName == Title_)	{ newScene = new TitleScene(); }
	if (sceneName == Select_)	{ newScene = new SelectScene(); }
	if (sceneName == Play_)		{ newScene = new PlayScene(); }

	if (sceneName == Test_)		{ newScene = new TestScene(); }
	if (sceneName == Demo_)		{ newScene = new DemoScene(); }

	return newScene;
}
