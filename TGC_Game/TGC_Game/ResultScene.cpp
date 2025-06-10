#include "ResultScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "Fade.h"
#include "DxLib.h"
#include <stdio.h>
#include <fstream>

#define UI_BUTTON_BASE_WIDTH (220)
#define UI_BUTTON_BASE_HEIGHT (70)

void ResultScene::Initialize()
{
    // フェードをインスタンス化
    fade = new Fade();
    // フェードの初期化処理（フェードイン）
    fade->Initialize(true);

    // カーソル画像
    //cursor_image = LoadGraph("Resource/image/");

    result_title_image = LoadGraph("Resource/image/result_title.png");
    result_player_title = LoadGraph("Resource/image/your_score.png");
    //result_score_history = LoadGraph("Resource/image/highscore_text.png");
    result_collect_font = LoadGraph("Resource/image/collect.png");
    result_sales_font = LoadGraph("Resource/image/sales.png");

   /* cursor_se_move = LoadSoundMem("Resource/sounds/");
    cursor_se_push = LoadSoundMem("Resource/sounds/");*/

    // コントローラーの入力インスタンス取得
    pad_input = InputControl::GetInstance();

    // リソース管理のインスタンスを取得
    ResourceManager* rm = ResourceManager::GetInstance();

    // 背景画像
    background_image = LoadGraph("Resource/image/result_background.png");

    /*/ リザルトメインbgm読み込み
    result_bgm = LoadSoundMem("Resource/sounds/");*/

   // 数字画像（0?9）の読み込み
	num_image = rm->GetImages("Resource/image/number.png");

    /*/ リザルトメインbgm再生
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    result_score_time = 0;

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
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress) {
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

    result_score_time++;
    
    // 親クラスの更新処理を呼び出す
    return __super::Update();

    return GetNowSceneType();
}


void ResultScene::Draw() const
{
    // リザルトタイトル画像 (1280, 720 \ 460, 90)
    DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

    // 自身のスコア画像描画
    DrawGraph(50, 200, result_player_title, TRUE);

    // ハイスコア画像描画
    DrawExtendGraph(100, 300, 381, 388, result_score_history, TRUE);

    DrawGraph(60, 295, result_collect_font, TRUE);

    DrawGraph(850, 290, result_sales_font, TRUE);

    // データ
    int correct = GameDataManager::GetInstance().GetCorrect();
    int sales = GameDataManager::GetInstance().GetSales();
    

    DrawFormatString(100, 100, GetColor(255, 255, 255), "接客人数: %d", correct);
    //DrawFormatString(100, 140, GetColor(255, 255, 255), "売上: %d 円", sales);

    DrawFormatString(100, 140, GetColor(0, 0, 0), "時間: %d 円", result_score_time);


    int yOffset = 290;      // y軸オフセット
    int rankX = 25;        // 順位のX座標
    int correctX = 350;       //  接客数のX座標
    int salesX = 800;       // 売上のX座標
    int sumX = 500;
    int rowSpacing = 100;    // 行間のスペース
    int digitWidth = 32;    // 1桁の幅（使用するフォント画像に合わせる）

    if (result_score_time >= 50)
    {
        // 接客数を描画
        DrawNumber(correctX, yOffset, correct);
    }
    if (result_score_time >= 100)
    {
        // 売上を描画
        DrawNumber(salesX, yOffset, sales);
    }
    if (result_score_time >= 300)
    {
        int sum = (sales * 2) + correct;
        DrawNumber(sumX, yOffset, sum);
    }
    if (result_score_time >= 350)
    {
        DrawGraph(850, 490, result_sales_font, TRUE);
    }

    // フェード描画
    fade->Draw();
}

void ResultScene::Finalize()
{
    
}

eSceneType ResultScene::GetNowSceneType() const
{
    return eSceneType::eResult;
}

// 指定位置に数値を画像で描画する
void ResultScene::DrawNumber(int x, int y, int number) const
{
    if (num_image.empty()) return;  // 画像が未ロードなら描画しない

    int image_width, image_height;
    GetGraphSize(num_image[0], &image_width, &image_height);  // 画像のサイズ取得

    int digit_width = image_width / 10;  // 各数字の幅（10桁に分割）
    int digit_height = image_height;  // 画像の高さ

    std::string numStr = std::to_string(number); // 数字を文字列に変換

    for (size_t i = 0; i < numStr.length(); ++i)
    {
        int digit = numStr[i] - '0';  // 文字から数値へ変換
        int srcX = digit * digit_width;  // 画像内のX座標
        int srcY = 0;  // Y座標（1行の画像なら0）

        // 画像の一部を切り取って描画
        DrawRectGraph(x + i * digit_width, y, srcX, srcY, digit_width, digit_height, num_image[0], TRUE, FALSE);
    }
}

void ResultScene::SaveScore(int correct, int sales) {
    std::ofstream file("Resource/ScoreData/ranking.txt", std::ios::app); // appendモードで追記
    if (file.is_open()) {
        file << correct << " " << sales << std::endl;
        file.close();
    }
}
