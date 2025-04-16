#include "InGameScene.h"
#include "DxLib.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
}

//eSceneType InGameScene::Update()
//{
//	// 親クラスの更新処理を呼び出す
//	return __super::Update();
//}

void InGameScene::Draw() const
{
}

void InGameScene::Finalize()
{
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}