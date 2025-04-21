#include "InGameScene.h"
#include "InputControl.h"
#include "DxLib.h"

InGameScene::InGameScene()
{
	ingame_cursol = 0;
	counter_time = 0;
	next_scene = eSceneType::eInGame;
}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
}

eSceneType InGameScene::Update()
{
	//制限時間処理
	if (counter_time <= 3000)
	{
		counter_time++;
	}

	// パッド入力制御のインスタンスを取得
	InputControl* pad_input = InputControl::GetInstance();
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		ingame_cursol--;
		if (ingame_cursol < 0)
		{
			ingame_cursol = 3;
		}
	}

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		ingame_cursol++;
		if (ingame_cursol >3)
		{
			ingame_cursol = 0;
		}
	}

	// 親クラスの更新処理を呼び出す
	return GetNowSceneType();
}

//描画処理
void InGameScene::Draw() const
{

	DrawString(50,50,"InGameSceneです",GetColor(255,255,255));
	DrawFormatString(1200, 20, 0xffffff, "%d", counter_time/100);
	DrawBox(200 + (ingame_cursol * 100), 500, 300 + (ingame_cursol * 100), 600, 0xffffff, true);
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}