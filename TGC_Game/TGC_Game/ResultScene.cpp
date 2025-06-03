#include "ResultScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "Fade.h"
#include "DxLib.h"
#include <stdio.h>

#define UI_BUTTON_BASE_WIDTH (220)
#define UI_BUTTON_BASE_HEIGHT (70)

void ResultScene::Initialize()
{
    // カーソル画像
    //cursor_image = LoadGraph("Resource/image/");

    result_title_image = LoadGraph("Resource/image/result_title.png");
    result_player_title = LoadGraph("Resource/image/your_score.png");
    result_score_history = LoadGraph("Resource/image/highscore_text.png");

   /* cursor_se_move = LoadSoundMem("Resource/sounds/");
    cursor_se_push = LoadSoundMem("Resource/sounds/");*/

    // コントローラーの入力インスタンス取得
    pad_input = InputControl::GetInstance();

    // リソース管理のインスタンスを取得
    ResourceManager* rm = ResourceManager::GetInstance();

    // 背景画像
    background_image = LoadGraph("Resource/image/burgertitle.png");

    /*/ リザルトメインbgm読み込み
    result_bgm = LoadSoundMem("Resource/sounds/");

    // ハイスコアデータを取得
    LoadHighScores();

    // ハイスコアSEの読み込み
    HighScore_SE = LoadSoundMem("Resource/sounds/");*/

   // 数字画像（0?9）の読み込み
	num_image = rm->GetImages("Resource/image/number.png");

    /*/ リザルトメインbgm再生
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    // フェードをインスタンス化
    fade = new Fade();
    // フェードの初期化処理（フェードイン）
    fade->Initialize(true);

    result_next_scene = eSceneType::eResult;
}


eSceneType ResultScene::Update()
{

    

    // パッド入力制御のインスタンスを取得
    InputControl* pad_input = InputControl::GetInstance();

    // 十字キー操作(上)
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
    {
       result_cursor--;
        PlaySoundMem(cursor_se_move, DX_PLAYTYPE_BACK);

        if (result_cursor < 0)
        {
            result_cursor = 3;
        }
    }
    // 十字キー操作(下)
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
    {
        result_cursor++;
        PlaySoundMem(cursor_se_move, DX_PLAYTYPE_BACK);

        if (result_cursor > 3)
        {
            result_cursor = 0;
        }
    }


    // フェードアウト中なら、フェード処理を続ける
    if (result_next_scene != eSceneType::eResult) {
        if (fade->GetEndFlag()) {
            // フェードアウト完了後にシーン遷移
            return result_next_scene;
        }
        fade->Update();
        // フェードアウト中はタイトルシーンを維持
        return eSceneType::eResult;
    }

    // コントローラーの A ボタン処理(簡略化)
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress) {
        // 押したらSEを鳴らせる
        PlaySoundMem(cursor_se_push, DX_PLAYTYPE_BACK);
        // BGMを止める
        StopSoundMem(result_bgm);
        // フェード初期化
        fade->Initialize(false);

        // カーソル位置に応じてシーン遷移を予約
        if (result_cursor == 0) {
            result_next_scene = eSceneType::eTitle;
        }
        else if (result_cursor == 1) {
            result_next_scene = eSceneType::eInGame;
        }
        else if (result_cursor == 2) {
            result_next_scene = eSceneType::eRanking;
        }
    }

    // フェード更新
    fade->Update();
    
    // 親クラスの更新処理を呼び出す
    return __super::Update();

    return GetNowSceneType();
}


void ResultScene::Draw() const
{

   //DrawGraph(0, 0, background_image, TRUE);
   
   // リザルトテキストの表示（座標: x=50, y=50、色: 白）(完成次第削除予定)
    DrawString(50, 50, "リザルト画面です", GetColor(255, 255, 255));
    DrawString(10, 26, "A : Title", GetColor(255, 255, 255));

    // リザルトタイトル画像 (1280, 720 \ 460, 90)
    DrawExtendGraph(410, 20, 870, 130, result_title_image, TRUE);
    // 自身のスコア画像描画
    DrawExtendGraph(100, 130, 444, 211, result_player_title, TRUE);
    // ハイスコア画像描画
    DrawExtendGraph(100, 300, 381, 388, result_score_history, TRUE);

    // データ
    int correct = GameDataManager::GetInstance().GetCorrect();
    int sales = GameDataManager::GetInstance().GetSales();


    DrawFormatString(100, 100, GetColor(255, 255, 255), "接客人数: %d", correct);
    DrawFormatString(100, 140, GetColor(255, 255, 255), "売上: %d 円", sales);
}

void ResultScene::Finalize()
{
    
}

eSceneType ResultScene::GetNowSceneType() const
{
    return eSceneType::eResult;
}



