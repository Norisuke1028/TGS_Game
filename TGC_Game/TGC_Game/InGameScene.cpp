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
//	// �e�N���X�̍X�V�������Ăяo��
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