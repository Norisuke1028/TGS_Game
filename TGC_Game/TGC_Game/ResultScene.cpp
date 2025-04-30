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
    // �J�[�\���摜
    //cursor_image = LoadGraph("Resource/image/");

    result_title_image = LoadGraph("Resource/image/result_title.png");
    result_player_title = LoadGraph("Resource/image/your_score.png");
    result_score_history = LoadGraph("Resource/image/highscore_text.png");

   /* cursor_se_move = LoadSoundMem("Resource/sounds/");
    cursor_se_push = LoadSoundMem("Resource/sounds/");*/

    // �R���g���[���[�̓��̓C���X�^���X�擾
    pad_input = InputControl::GetInstance();

    // ���\�[�X�Ǘ��̃C���X�^���X���擾
    ResourceManager* rm = ResourceManager::GetInstance();

    // �w�i�摜
    background_image = LoadGraph("Resource/image/burgertitle.png");

    /*/ ���U���g���C��bgm�ǂݍ���
    result_bgm = LoadSoundMem("Resource/sounds/");

    // �n�C�X�R�A�f�[�^���擾
    LoadHighScores();

    // �n�C�X�R�ASE�̓ǂݍ���
    HighScore_SE = LoadSoundMem("Resource/sounds/");

    // �����摜�i0?9�j�̓ǂݍ���
    num_image = rm->GetImages("Resource/images/");

    // ���U���g���C��bgm�Đ�
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    // �t�F�[�h���C���X�^���X��
    fade = new Fade();
    // �t�F�[�h�̏����������i�t�F�[�h�C���j
    fade->Initialize(true);

    result_next_scene = eSceneType::eResult;
}


eSceneType ResultScene::Update()
{

    HandleNewHighScore();

    // �p�b�h���͐���̃C���X�^���X���擾
    InputControl* pad_input = InputControl::GetInstance();

    // �\���L�[����(��)
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
    {
       result_cursor--;
        PlaySoundMem(cursor_se_move, DX_PLAYTYPE_BACK);

        if (result_cursor < 0)
        {
            result_cursor = 3;
        }
    }
    // �\���L�[����(��)
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
    {
        result_cursor++;
        PlaySoundMem(cursor_se_move, DX_PLAYTYPE_BACK);

        if (result_cursor > 3)
        {
            result_cursor = 0;
        }
    }


    // �t�F�[�h�A�E�g���Ȃ�A�t�F�[�h�����𑱂���
    if (result_next_scene != eSceneType::eResult) {
        if (fade->GetEndFlag()) {
            // �t�F�[�h�A�E�g������ɃV�[���J��
            return result_next_scene;
        }
        fade->Update();
        // �t�F�[�h�A�E�g���̓^�C�g���V�[�����ێ�
        return eSceneType::eResult;
    }

    // �R���g���[���[�� A �{�^������(�ȗ���)
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress) {
        // ��������SE��点��
        PlaySoundMem(cursor_se_push, DX_PLAYTYPE_BACK);
        // BGM���~�߂�
        StopSoundMem(result_bgm);
        // �t�F�[�h������
        fade->Initialize(false);

        // �J�[�\���ʒu�ɉ����ăV�[���J�ڂ�\��
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

    // �t�F�[�h�X�V
    fade->Update();
    
    // �e�N���X�̍X�V�������Ăяo��
    return __super::Update();

    return GetNowSceneType();
}


void ResultScene::Draw() const
{

   //DrawGraph(0, 0, background_image, TRUE);
   
   // ���U���g�e�L�X�g�̕\���i���W: x=50, y=50�A�F: ���j
    DrawString(50, 50, "���U���g��ʂł�", GetColor(255, 255, 255));
    DrawString(10, 26, "A : Title", GetColor(255, 255, 255));

    // ���U���g�^�C�g���摜 (1280, 720 \ 460, 90)
    DrawExtendGraph(410, 20, 870, 130, result_title_image, TRUE);
    // ���g�̃X�R�A�摜�`��
    DrawExtendGraph(100, 130, 444, 211, result_player_title, TRUE);
    // �n�C�X�R�A�摜�`��
    DrawExtendGraph(100, 300, 381, 388, result_score_history, TRUE);

    /*/ ����̃X�R�A�ƃ��x����`��
    DisplayCurrentRunScores();
    DrawFormatString(10, 58, GetColor(255, 255, 255), "Level: %d", LevelReached);
    DrawFormatString(10, 74, GetColor(255, 255, 255), "Score: %d", FinalScore);
    DrawFormatString(10, 90, GetColor(255, 255, 255), "Misinputs: %d", Misinputs);*/

    // �n�C�X�R�A��`��
    DisplayHighScores();
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

        while (j >= 0 && arr[j].score < key.score)  //���בւ������
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