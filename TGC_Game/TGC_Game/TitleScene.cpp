#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
}

//eSceneType TitleScene::Update()
//{
//	// �e�N���X�̍X�V�������Ăяo��
//	return __super::Update();
//}

void TitleScene::Draw() const
{
}

void TitleScene::Finalize()
{
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}