#include "ResultScene.h"
#include "InputControl.h"
#include "ResourceManager.h"
#include "DxLib.h"
#include <stdio.h>

#define UI_BUTTON_BASE_WIDTH (220)
#define UI_BUTTON_BASE_HEIGHT (70)

void ResultScene::Initialize()
{
    // �J�[�\���̏����ʒu
    cursor_pos = { 600.0f, 300.0f };
    cursorOnButton = false;
    // �J�[�\���摜
    cursor_blank_Graph = LoadGraph("Resource/Images/UI_Elements/cursor_blank.png");
    cursor_on_Graph = LoadGraph("Resource/Images/UI_Elements/cursor_on.png");
    cursor_shadow_Graph = LoadGraph("Resource/Images/UI_Elements/cursor_shadow.png");

    cursor_se_move = LoadSoundMem("Resource/Sounds/SE/cursol_move_se.mp3");
    cursor_se_push = LoadSoundMem("Resource/Sounds/SE/cursol_push_se.mp3");

    // �R���g���[���[�̓��̓C���X�^���X�擾
    pad_input = InputControl::GetInstance();

    // ���\�[�X�Ǘ��̃C���X�^���X���擾
    ResourceManager* rm = ResourceManager::GetInstance();

    // �w�i�摜
    BackgroundGraph = LoadGraph("Resource/Images/Scene/InGame/Background01.png");

    // ���U���g�V�[���摜�n���h��
    ResultTitle_Graph = LoadGraph("Resource/Images/Scene/Result/Result_Title.png");
    rank1_Graph = LoadGraph("Resource/Images/Scene/Result/Result_rank1.png");
    rank2_Graph = LoadGraph("Resource/Images/Scene/Result/Result_rank2.png");
    rank3_Graph = LoadGraph("Resource/Images/Scene/Result/Result_rank3.png");
    YourScoreGraph = LoadGraph("Resource/Images/Scene/Result/Your_Score.png");
    HighScoreHistory = LoadGraph("Resource/Images/Scene/Result/HighScore_History.png");
    ReplayButton_Graph = LoadGraph("Resource/Images/Scene/Result/Result_Replay.png");
    TitleButton_Graph = LoadGraph("Resource/Images/Scene/Result/Result_returnTitle.png");

    // �w�i�摜
    backgroundWaves[0] = LoadGraph("Resource/Images/Scene/Result/Backgrounds/BackgroundCloud_1.png");
    backgroundWaves[1] = LoadGraph("Resource/Images/Scene/Result/Backgrounds/BackgroundCloud_2.png");
    backgroundWaves[2] = LoadGraph("Resource/Images/Scene/Result/Backgrounds/BackgroundCloud_3.png");
    backgroundWaves[3] = LoadGraph("Resource/Images/Scene/Result/Backgrounds/BackgroundCloud_4.png");
    // �w�i�摜�̍��W
    backgroundY[0] = 0;
    backgroundY[1] = -screenHeight;
    backgroundY[2] = -screenHeight * 2;
    backgroundY[3] = -screenHeight * 3;

    // ���U���g���C��bgm�ǂݍ���
    result_bgm = LoadSoundMem("Resource/Sounds/BGM/Result.mp3");

    // �n�C�X�R�A�f�[�^���擾
    LoadHighScores();

    // �n�C�X�R�ASE�̓ǂݍ���
    HighScore_SE = LoadSoundMem("Resource/Sounds/BGM/HighScore.mp3");

    // �����摜�i0?9�j�̓ǂݍ���
    num_image = rm->GetImages("Resource/Images/Scene/InGame/Text/NumWhite.png");

    /************ UI�{�^�� ************/
    // ���g���C�{�^��
    Button RetryButton;
    RetryButton.GraphicHandle = ReplayButton_Graph;
    RetryButton.x = 1030;
    RetryButton.y = 520;
    RetryButton.Width = UI_BUTTON_BASE_WIDTH;
    RetryButton.Height = UI_BUTTON_BASE_HEIGHT;
    RetryButton.TargetScene = eSceneType::eInGame;
    buttons.push_back(RetryButton);

    // �^�C�g���{�^��
    Button TitleButton;
    TitleButton.GraphicHandle = TitleButton_Graph;
    TitleButton.x = 1030;
    TitleButton.y = 620;
    TitleButton.Width = UI_BUTTON_BASE_WIDTH;
    TitleButton.Height = UI_BUTTON_BASE_HEIGHT;
    TitleButton.TargetScene = eSceneType::eTitle;
    buttons.push_back(TitleButton);
    /***********************************/

    // ���U���g���C��bgm�Đ�
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);
}


eSceneType ResultScene::Update()
{
    cursorOnButton = false;

    // �w�i�摜�̍��W�X�V
    for (int i = 0; i < 4; ++i)
    {
        backgroundY[i] -= scrollSpeedY;

        // �����摜����ʊO�ɍs���΍��W��������
        if (backgroundY[i] < 0)
        {
            backgroundY[i] += screenHeight * 4;
        }
    }

    HandleNewHighScore();

    // �{�^���������ꂽ���`�F�b�N
    for (size_t i = 0; i < buttons.size(); i++)
    {
        Button& button = buttons[i];
        bool cursorOverButton = (cursor_pos.x >= button.x && cursor_pos.x <= button.x + button.Width &&
            cursor_pos.y >= button.y && cursor_pos.y <= button.y + button.Height);

        if (cursorOverButton)
        {
            cursorOnButton = true;
        }

        if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::eRelease && cursorOverButton)
        {

            // �{�^���������ꂽ�Ƃ���SE
            PlaySoundMem(cursor_se_push, DX_PLAYTYPE_BACK);
            // ���C��BGM���~�߂�
            StopSoundMem(result_bgm);
            return button.TargetScene;

        }
    }

    /*/ �L�[�{�[�h���͐���̃C���X�^���X���擾
    InputManager* key_input = InputManager::GetInstance();
    if (key_input->GetKeyInputState(KEY_INPUT_Z) == eInputState::ePress)
    {
        // ���C��BGM���~�߂�
        StopSoundMem(result_bgm);
        // Z�L�[�������ꂽ��C���Q�[����ʂɑJ��
        return eSceneType::eInGame;
    }
    if (key_input->GetKeyInputState(KEY_INPUT_X) == eInputState::ePress)
    {
        // ���C��BGM���~�߂�
        StopSoundMem(result_bgm);
        // X�L�[�������ꂽ��^�C�g����ʂɑJ��
        return eSceneType::eTitle;
    }*/
    // ���X�e�B�b�N���͒l�擾
    LeftStickTilt = pad_input->GetLeftStickTiltPercentage();

    // ���X�e�B�b�N���͂�����΃J�[�\���ʒu���X�V
    if (LeftStickTilt.x != 0.0f || LeftStickTilt.y != 0.0f)
    {
        cursor_pos.x += LeftStickTilt.x * 10;
        cursor_pos.y -= LeftStickTilt.y * 10;
    }

    return GetNowSceneType();
}


void ResultScene::Draw() const
{
    ////// �w�i�`��
    //for (int i = 0; i < 4; ++i) 
    //{
    //    DrawExtendGraph(0, backgroundY[i], 1280, backgroundY[i] + 720, backgroundWaves[i], TRUE);
    //}

    DrawGraph(0, 0, BackgroundGraph, TRUE);

    DrawString(10, 10, "Result", GetColor(255, 255, 255));
    DrawString(10, 26, "Z : InGame\nX : Title", GetColor(255, 255, 255));

    // ���U���g�V�[���摜 (1280, 720 \ 460, 90)
    DrawExtendGraph(410, 20, 870, 110, ResultTitle_Graph, TRUE);

    // ���Ȃ��̃X�R�A�摜�`��
    DrawExtendGraph(100, 130, 444, 181, YourScoreGraph, TRUE);
    // �n�C�X�R�A���摜�`��
    DrawExtendGraph(100, 300, 381, 348, HighScoreHistory, TRUE);

    // ����̃X�R�A�ƃ��x����`��
    DisplayCurrentRunScores();
    DrawFormatString(10, 58, GetColor(255, 255, 255), "Level: %d", LevelReached);
    DrawFormatString(10, 74, GetColor(255, 255, 255), "Score: %d", FinalScore);
    DrawFormatString(10, 90, GetColor(255, 255, 255), "Misinputs: %d", Misinputs);

    // �n�C�X�R�A��`��
    DisplayHighScores();

    // UI�{�^����`��
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        DrawExtendGraph(buttons[i].x, buttons[i].y, buttons[i].x + buttons[i].Width, buttons[i].y + buttons[i].Height, buttons[i].GraphicHandle, TRUE);
    }

    // �J�[�\���`��
    DrawCursor();
}

void ResultScene::Finalize()
{
    // �X�R�A��ۑ�
    SaveHighScores();

    // �摜���������
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


// �n�C�X�R�A���\�[�g����
void ResultScene::DataSortDescending(std::vector<HighScoreEntry>& arr, int n)
{
    int i, j;
    HighScoreEntry key;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j].score < key.score)  /***** ���בւ������ *****/
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}


// �n�C�X�R�A�̃f�[�^���擾
void ResultScene::LoadHighScores()
{
    // �t�@�C�����J����
    FILE* inputFile;
    fopen_s(&inputFile, HighScoreFileName, "r");

    //�G���[�`�F�b�N
    if (inputFile != NULL)
    {
        HighScoreEntry entry;
        int i = 0;
        int lineNumber = 1;

        // �t�@�C�����烌�x���A�X�R�A�A�~�X���̏��Ԃœǂݍ���
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

        // �X�R�A���\�[�g����
        if (HighScores.size() > 1)
        {
            DataSortDescending(HighScores, HighScores.size());
        }
    }
}

// �n�C�X�R�A��ۑ�����
void ResultScene::SaveHighScores()
{
    // ����̃X�R�A���n�C�X�R�A��荂�����`�F�b�N
    HandleNewHighScore();

    FILE* outputFile;
    fopen_s(&outputFile, HighScoreFileName, "w");

    // �G���[�`�F�b�N
    if (outputFile != NULL)
    {
        // ���x���A�X�R�A�A�~�X���̏��ԂŃt�@�C���ɏ�������
        for (size_t i = 0; i < HighScores.size(); ++i)
        {
            fprintf_s(outputFile, "%d %d %d\n", HighScores[i].level, HighScores[i].score, HighScores[i].misinputs);
        }

        fclose(outputFile);
    }
}


// �X�R�A���n�C�X�R�A��荂�����m�F
void ResultScene::HandleNewHighScore()
{
    HighScoreEntry newEntry;
    newEntry.level = LevelReached;
    newEntry.score = FinalScore;
    newEntry.misinputs = Misinputs;

    HighScores.push_back(newEntry);

    // �����L���O�\�[�g
    DataSortDescending(HighScores, HighScores.size());

    // �����L���O�̐��������Ȃ����`�F�b�N
    if (HighScores.size() > MaxHighScores)
    {
        // ��������������A��ԉ��̃n�C�X�R�A���폜
        while (HighScores.size() > MaxHighScores)
        {
            HighScores.pop_back();
        }
    }
}

// �n�C�X�R�A�̕`��
void ResultScene::DisplayCurrentRunScores() const
{
    int yOffset = 180;      // y���I�t�Z�b�g
    int levelX = 350;       // ���x����X���W
    int scoreX = 500;       // �X�R�A��X���W
    int missX = 800;        // �~�X��X���W
    int rowSpacing = 100;    // �s�Ԃ̃X�y�[�X
    int digitWidth = 32;    // 1���̕��i�g�p����t�H���g�摜�ɍ��킹��j

    // ���x����`��
    DrawNumber(levelX, yOffset, LevelReached);

    // �X�R�A��`��
    DrawNumber(scoreX, yOffset, FinalScore);

    // �~�X�̉񐔂�`��
    DrawNumber(missX, yOffset, Misinputs);
}

// �n�C�X�R�A�̕`��
void ResultScene::DisplayHighScores() const
{
    int yOffset = 350;      // y���I�t�Z�b�g
    int rankX = 250;        // ���ʂ�X���W
    int levelX = 350;       // ���x����X���W
    int scoreX = 500;       // �X�R�A��X���W
    int missX = 800;        // �~�X��X���W
    int rowSpacing = 100;    // �s�Ԃ̃X�y�[�X
    int digitWidth = 32;    // 1���̕��i�g�p����t�H���g�摜�ɍ��킹��j

    for (size_t i = 0; i < HighScores.size(); ++i)
    {
        // ���ʂ�`��i�摜�Łj
        DrawNumber(rankX, yOffset, i + 1);

        // ���x����`��
        DrawNumber(levelX, yOffset, HighScores[i].level);

        // �X�R�A��`��
        DrawNumber(scoreX, yOffset, HighScores[i].score);

        // �~�X�̉񐔂�`��
        DrawNumber(missX, yOffset, HighScores[i].misinputs);

        yOffset += rowSpacing; // ���̍s��
    }
}

// �w��ʒu�ɐ��l���摜�ŕ`�悷��
void ResultScene::DrawNumber(int x, int y, int number) const
{
    if (num_image.empty()) return;  // �摜�������[�h�Ȃ�`�悵�Ȃ�

    int image_width, image_height;
    GetGraphSize(num_image[0], &image_width, &image_height);  // �摜�̃T�C�Y�擾

    int digit_width = image_width / 10;  // �e�����̕��i10���ɕ����j
    int digit_height = image_height;  // �摜�̍���

    std::string numStr = std::to_string(number); // �����𕶎���ɕϊ�

    for (size_t i = 0; i < numStr.length(); ++i)
    {
        int digit = numStr[i] - '0';  // �������琔�l�֕ϊ�
        int srcX = digit * digit_width;  // �摜����X���W
        int srcY = 0;  // Y���W�i1�s�̉摜�Ȃ�0�j

        // �摜�̈ꕔ��؂����ĕ`��
        DrawRectGraph(x + i * digit_width, y, srcX, srcY, digit_width, digit_height, num_image[0], TRUE, FALSE);
    }
}

// �J�[�\���`�揈��
void ResultScene::DrawCursor() const
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // �摜�𔼓����ɂ���
    DrawExtendGraph(cursor_pos.x - 9, cursor_pos.y - 2, cursor_pos.x + 25, cursor_pos.y + 30, cursor_shadow_Graph, true);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);  // �����x�����ɖ߂�

    if (cursorOnButton)
    {
        DrawExtendGraph(cursor_pos.x - 20, cursor_pos.y - 20, cursor_pos.x + 20, cursor_pos.y + 20, cursor_on_Graph, true);
    }
    else
    {
        DrawExtendGraph(cursor_pos.x - 20, cursor_pos.y - 20, cursor_pos.x + 20, cursor_pos.y + 20, cursor_blank_Graph, true);
    }
}

void ResultScene::DrawBackground()
{
    DrawExtendGraph(cursor_pos.x - 20, cursor_pos.y - 20, cursor_pos.x + 20, cursor_pos.y + 20, cursor_blank_Graph, true);
}