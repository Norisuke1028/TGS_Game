#include "ResultScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "GameDataManager.h"
#include "RankingManager.h"
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
    result_sum_title = LoadGraph("Resource/image/sum_score_font.png");

    //result_score_history = LoadGraph("Resource/image/highscore_text.png");
    result_collect_font = LoadGraph("Resource/image/collect.png");
    result_sales_font = LoadGraph("Resource/image/sales.png");
    result_button_image = LoadGraph("Resource/image/result_button.png");
    sum_background = LoadSoundMem("Resource/sounds/drum03.mp3");
    result_se = LoadSoundMem("Resource/sounds/result.mp3");

    result_bronze_font = LoadGraph("Resource/image/result_burger_bronze.png");
    result_bronze_badge = LoadGraph("Resource/image/brondze_badge.png");
    
    result_gold_font = LoadGraph("Resource/image/result_burger_gold.png");
    result_gold_badge = LoadGraph("Resource/image/gold_badge.png");

    result_diamond_font = LoadGraph("Resource/image/result_burger_god.png");
    result_diamond_badge = LoadGraph("Resource/image/diamond_badge.png");

   //cursor_se_move = LoadSoundMem("Resource/sounds/");
    cursor_se_push = LoadSoundMem("Resource/sounds/SE/ranking/ranking_button_se.mp3");
    result_badge_se = LoadSoundMem("Resource/sounds/Award.mp3");
    // コントローラーの入力インスタンス取得
    pad_input = InputControl::GetInstance();

    // リソース管理のインスタンスを取得
    ResourceManager* rm = ResourceManager::GetInstance();

    // 背景画像
    background_image = LoadGraph("Resource/image/r_background.png");

    //リザルトのスコアボード画像
    sb_result_image = LoadGraph("Resource/image/result_S.png");

    /*/ リザルトメインbgm読み込み
    result_bgm = LoadSoundMem("Resource/sounds/");*/

   // 数字画像（0?9）の読み込み
	num_image = rm->GetImages("Resource/image/number2.png");

    /*/ リザルトメインbgm再生
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    result_score_time = 0;

    result_next_scene = eSceneType::eResult;
}


eSceneType ResultScene::Update()
{
    // パッド入力制御のインスタンスを取得
    InputControl* pad_input = InputControl::GetInstance();

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

    if (result_score_time >= 1300) {
        // コントローラーの A ボタン処理(簡略化)
        if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress) {
            // 押したらSEを鳴らせる
            PlaySoundMem(cursor_se_push, DX_PLAYTYPE_BACK);
            // BGMを止める
            StopSoundMem(result_bgm);
            // フェード初期化
            fade->Initialize(false);
            // ランキングシーンに遷移
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
    // データ
    int correct = GameDataManager::GetInstance().GetCorrect();
    int sales = GameDataManager::GetInstance().GetSales();
    int sum = 0;
    
    // リザルトタイトル画像 (1280, 720 \ 460, 90)
    DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

    if (result_score_time >= 100)DrawGraph(0, -10, sb_result_image, TRUE);  //リザルトスコアボードの描画


    // 数字フォント用変数
    int yOffset = 290;      // y軸オフセット
    int rankX = 25;        // 順位のX座標
    int correctX = 400;       //  接客数のX座標
    int salesX = 930;       // 売上のX座標
    int sumX = 380;
    int rowSpacing = 100;    // 行間のスペース
    int digitWidth = 32;    // 1桁の幅（使用するフォント画像に合わせる）

    if (result_score_time >= 200)
    {
        // 接客数の数字（少し拡大）
        if (correct >= 10) {
            DrawNumber(750, 220, correct, 0.6f);
        }
        else {
            DrawNumber(800, 220, correct, 0.6f);
        }
        if (result_score_time == 203) {
            ChangeVolumeSoundMem(120, result_se);
            PlaySoundMem(result_se, DX_PLAYTYPE_NORMAL);
        }
    }
    if (result_score_time >= 203)  // 売上の数字（同じく拡大）
    {
        if (result_score_time == 204) {
            PlaySoundMem(result_se, DX_PLAYTYPE_NORMAL);
        }
        //売上が4桁の時のスコアの位置調整
        if (sales >= 1000) {
            DrawNumber(630, 300, sales, 0.6f);
        }
        //売上が4桁以下の時のスコアの位置調整
        else if(sales > 0){
            DrawNumber(690, 300, sales, 0.6f);
        }
        else {
            DrawNumber(800, 300, sales, 0.6f);
        }
    }
    if (result_score_time == 300)
    {
        PlaySoundMem(sum_background, DX_PLAYTYPE_BACK);
    }
    if (result_score_time >= 800)
    {
        sum = (correct * 50) + sales;

        // 合計スコアの数字（中央表示）
        int sum_width = std::to_string(sum).length() * 32 * 1.0f;  // 32は1桁の幅
        int centerX = (1280 - sum_width) / 2;
        if (sum >= 1000) {
            DrawNumber(centerX - 140, 520, sum, 0.9f);
        }
        else if(sum > 0){
            DrawNumber(centerX - 90, 520, sum, 0.9f);  // 大きめに表示
        }
        else {
            DrawNumber(centerX - 40, 520, sum, 0.9f);  // 大きめに表示
        }
    }

    //バッジ表示時SE
    if (result_score_time == 999)
    {
        PlaySoundMem(result_badge_se, DX_PLAYTYPE_BACK);
    }

    // バッジと等級表示
    if (result_score_time >= 1000)
    {
        if (sum <= 1000) {
            DrawExtendGraph(800, 540, 960, 700, result_bronze_badge, TRUE);
        }
        else if (sum <= 3600) {
            DrawExtendGraph(800, 540, 960, 700, result_gold_badge, TRUE);
            
        }
        else {
            DrawExtendGraph(800, 540, 960, 700, result_diamond_badge, TRUE);
        }
    } 

    if (result_score_time >= 1100)DrawRotaGraph(1125, 690, 1.15, 0, result_button_image, TRUE);

    // フェード描画
    fade->Draw();
}

void ResultScene::Finalize()
{
    int correct = GameDataManager::GetInstance().GetCorrect();
    int sales = GameDataManager::GetInstance().GetSales();

    RankingManager::GetInstance().WriteScore(correct, sales);
}

eSceneType ResultScene::GetNowSceneType() const
{
    return eSceneType::eResult;
}

// 指定位置に数値を画像で描画する
void ResultScene::DrawNumber(int x, int y, int number, float scale) const
{
    if (num_image.empty()) return;

    int image_width, image_height;
    GetGraphSize(num_image[0], &image_width, &image_height);

    int digit_width = image_width / 10;
    int digit_height = image_height;

    std::string numStr = std::to_string(number);

    for (size_t i = 0; i < numStr.length(); ++i)
    {
        int digit = numStr[i] - '0';
        int srcX = digit * digit_width;
        int srcY = 0;

        int drawX = x + static_cast<int>(i * digit_width * scale);
        int drawY = y;

        // ここがポイント！
        DrawRectExtendGraph(
            drawX, drawY,
            drawX + static_cast<int>(digit_width * scale),
            drawY + static_cast<int>(digit_height * scale),
            srcX, srcY, digit_width, digit_height,
            num_image[0],
            TRUE
        );
    }
}
