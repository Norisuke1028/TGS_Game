#include "ResultScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
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
    HighScore_SE = LoadSoundMem("Resource/sounds/");

    // 数字画像（0?9）の読み込み
    num_image = rm->GetImages("Resource/images/");

    // リザルトメインbgm再生
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    // フェードをインスタンス化
    fade = new Fade();
    // フェードの初期化処理（フェードイン）
    fade->Initialize(true);

    result_next_scene = eSceneType::eResult;
}


eSceneType ResultScene::Update()
{

    HandleNewHighScore();

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
   
   // リザルトテキストの表示（座標: x=50, y=50、色: 白）
    DrawString(50, 50, "リザルト画面です", GetColor(255, 255, 255));
    DrawString(10, 26, "A : Title", GetColor(255, 255, 255));

    // リザルトタイトル画像 (1280, 720 \ 460, 90)
    DrawExtendGraph(410, 20, 870, 130, result_title_image, TRUE);
    // 自身のスコア画像描画
    DrawExtendGraph(100, 130, 444, 211, result_player_title, TRUE);
    // ハイスコア画像描画
    DrawExtendGraph(100, 300, 381, 388, result_score_history, TRUE);

    /*/ 今回のスコアとレベルを描画
    DisplayCurrentRunScores();
    DrawFormatString(10, 58, GetColor(255, 255, 255), "Level: %d", LevelReached);
    DrawFormatString(10, 74, GetColor(255, 255, 255), "Score: %d", FinalScore);
    DrawFormatString(10, 90, GetColor(255, 255, 255), "Misinputs: %d", Misinputs);*/

    // ハイスコアを描画
    DisplayHighScores();
}

void ResultScene::Finalize()
{
    // スコアを保存
    SaveHighScores();

    // 画像を解放する
    /*for (size_t i = 0; buttons.size(); ++i)
    {
        if (buttons[i].GraphicHandle != -1)
        {
            DeleteGraph(buttons[i].GraphicHandle);
        }
    }*/
}

eSceneType ResultScene::GetNowSceneType() const
{
    return eSceneType::eResult;
}


// ハイスコアをソートする
void ResultScene::DataSortDescending(std::vector<HighScoreEntry>& arr, int n)
{
    int i, j;
    HighScoreEntry key;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j].score < key.score)  //並べ替える条件
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}


// ハイスコアのデータを取得
void ResultScene::LoadHighScores()
{
    // ファイルを開ける
    FILE* inputFile;
    fopen_s(&inputFile, HighScoreFileName, "r");

    //エラーチェック
    if (inputFile != NULL)
    {
        HighScoreEntry entry;
        int i = 0;
        int lineNumber = 1;

        // ファイルからレベル、スコア、ミス数の順番で読み込む
        while (fscanf_s(inputFile, "%d %d %d", &entry.level, &entry.score, &entry.misinputs) == 3)
        {
            if (lineNumber != 4)
            {
                HighScores.push_back(entry);
            }
            else
            {
                FinalScore = entry.score;
                LevelReached = entry.level;
                Misinputs = entry.misinputs;
            }

            i++;
            lineNumber++;
        }
        fclose(inputFile);

        // スコアをソートする
        if (HighScores.size() > 1)
        {
            DataSortDescending(HighScores, HighScores.size());
        }
    }
}

// ハイスコアを保存する
void ResultScene::SaveHighScores()
{
    // 今回のスコアがハイスコアより高いかチェック
    HandleNewHighScore();

    FILE* outputFile;
    fopen_s(&outputFile, HighScoreFileName, "w");

    // エラーチェック
    if (outputFile != NULL)
    {
        // レベル、スコア、ミス数の順番でファイルに書き込む
        for (size_t i = 0; i < HighScores.size(); ++i)
        {
            fprintf_s(outputFile, "%d %d %d\n", HighScores[i].level, HighScores[i].score, HighScores[i].misinputs);
        }

        fclose(outputFile);
    }
}


// スコアがハイスコアより高いか確認
void ResultScene::HandleNewHighScore()
{
    HighScoreEntry newEntry;
    newEntry.level = LevelReached;
    newEntry.score = FinalScore;
    newEntry.misinputs = Misinputs;

    HighScores.push_back(newEntry);

    // ランキングソート
    DataSortDescending(HighScores, HighScores.size());

    // ランキングの数が多くないかチェック
    if (HighScores.size() > MaxHighScores)
    {
        // もし多かったら、一番下のハイスコアを削除
        while (HighScores.size() > MaxHighScores)
        {
            HighScores.pop_back();
        }
    }
}

// ハイスコアの描画
void ResultScene::DisplayCurrentRunScores() const
{
    int yOffset = 180;      // y軸オフセット
    int levelX = 350;       // レベルのX座標
    int scoreX = 500;       // スコアのX座標
    int missX = 800;        // ミスのX座標
    int rowSpacing = 100;    // 行間のスペース
    int digitWidth = 32;    // 1桁の幅（使用するフォント画像に合わせる）

    // レベルを描画
    DrawNumber(levelX, yOffset, LevelReached);

    // スコアを描画
    DrawNumber(scoreX, yOffset, FinalScore);

    // ミスの回数を描画
    DrawNumber(missX, yOffset, Misinputs);
}

// ハイスコアの描画
void ResultScene::DisplayHighScores() const
{
    int yOffset = 350;      // y軸オフセット
    int rankX = 250;        // 順位のX座標
    int levelX = 350;       // レベルのX座標
    int scoreX = 500;       // スコアのX座標
    int missX = 800;        // ミスのX座標
    int rowSpacing = 100;    // 行間のスペース
    int digitWidth = 32;    // 1桁の幅（使用するフォント画像に合わせる）

    for (size_t i = 0; i < HighScores.size(); ++i)
    {
        // 順位を描画（画像で）
        DrawNumber(rankX, yOffset, i + 1);

        // レベルを描画
        DrawNumber(levelX, yOffset, HighScores[i].level);

        // スコアを描画
        DrawNumber(scoreX, yOffset, HighScores[i].score);

        // ミスの回数を描画
        DrawNumber(missX, yOffset, HighScores[i].misinputs);

        yOffset += rowSpacing; // 次の行へ
    }
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