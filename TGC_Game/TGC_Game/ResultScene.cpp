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
    // �t�F�[�h���C���X�^���X��
    fade = new Fade();
    // �t�F�[�h�̏����������i�t�F�[�h�C���j
    fade->Initialize(true);

    // �J�[�\���摜
    //cursor_image = LoadGraph("Resource/image/");

    result_title_image = LoadGraph("Resource/image/result_title.png");
    result_player_title = LoadGraph("Resource/image/your_score.png");
    //result_score_history = LoadGraph("Resource/image/highscore_text.png");

   /* cursor_se_move = LoadSoundMem("Resource/sounds/");
    cursor_se_push = LoadSoundMem("Resource/sounds/");*/

    // �R���g���[���[�̓��̓C���X�^���X�擾
    pad_input = InputControl::GetInstance();

    // ���\�[�X�Ǘ��̃C���X�^���X���擾
    ResourceManager* rm = ResourceManager::GetInstance();

    // �w�i�摜
    background_image = LoadGraph("Resource/image/result_background.png");

    /*/ ���U���g���C��bgm�ǂݍ���
    result_bgm = LoadSoundMem("Resource/sounds/");*/

   // �����摜�i0?9�j�̓ǂݍ���
	num_image = rm->GetImages("Resource/image/number.png");

    /*/ ���U���g���C��bgm�Đ�
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    result_next_scene = eSceneType::eResult;
}


eSceneType ResultScene::Update()
{
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
    if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress) {
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
    // ���U���g�^�C�g���摜 (1280, 720 \ 460, 90)
    DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);
    
    // ���g�̃X�R�A�摜�`��
    DrawGraph(50, 200, result_player_title, TRUE);
    
    /*/ �n�C�X�R�A�摜�`��
    DrawExtendGraph(100, 300, 381, 388, result_score_history, TRUE);*/

    // �f�[�^
    int correct = GameDataManager::GetInstance().GetCorrect();
    int sales = GameDataManager::GetInstance().GetSales();


    DrawFormatString(100, 100, GetColor(255, 255, 255), "�ڋq�l��: %d", correct);
    DrawFormatString(100, 140, GetColor(255, 255, 255), "����: %d �~", sales);


    int yOffset = 290;      // y���I�t�Z�b�g
    int rankX = 25;        // ���ʂ�X���W
    int correctX = 350;       //  �ڋq����X���W
    int salesX = 500;       // �����X���W
    int rowSpacing = 100;    // �s�Ԃ̃X�y�[�X
    int digitWidth = 32;    // 1���̕��i�g�p����t�H���g�摜�ɍ��킹��j

    // �ڋq����`��
    DrawNumber(correctX, yOffset, correct);

    // �����`��
    DrawNumber(salesX, yOffset, sales);

    // �t�F�[�h�`��
    fade->Draw();
}

void ResultScene::Finalize()
{
    
}

eSceneType ResultScene::GetNowSceneType() const
{
    return eSceneType::eResult;
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

void ResultScene::SaveScore(int correct, int sales) {
    std::ofstream file("Resource/ScoreData/ranking.txt", std::ios::app); // append���[�h�ŒǋL
    if (file.is_open()) {
        file << correct << " " << sales << std::endl;
        file.close();
    }
}
