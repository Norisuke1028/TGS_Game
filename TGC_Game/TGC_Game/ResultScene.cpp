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
    // �t�F�[�h���C���X�^���X��
    fade = new Fade();
    // �t�F�[�h�̏����������i�t�F�[�h�C���j
    fade->Initialize(true);

    // �J�[�\���摜
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

   /* cursor_se_move = LoadSoundMem("Resource/sounds/");
    cursor_se_push = LoadSoundMem("Resource/sounds/");*/

    // �R���g���[���[�̓��̓C���X�^���X�擾
    pad_input = InputControl::GetInstance();

    // ���\�[�X�Ǘ��̃C���X�^���X���擾
    ResourceManager* rm = ResourceManager::GetInstance();

    // �w�i�摜
    background_image = LoadGraph("Resource/image/r_background.png");

    //���U���g�̃X�R�A�{�[�h�摜
    sb_result_image = LoadGraph("Resource/image/result_S.png");

    /*/ ���U���g���C��bgm�ǂݍ���
    result_bgm = LoadSoundMem("Resource/sounds/");*/

   // �����摜�i0?9�j�̓ǂݍ���
	num_image = rm->GetImages("Resource/image/number.png");

    /*/ ���U���g���C��bgm�Đ�
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    result_score_time = 0;

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

    if (result_score_time >= 1100) {
        // �R���g���[���[�� A �{�^������(�ȗ���)
        if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress) {
            // ��������SE��点��
            PlaySoundMem(cursor_se_push, DX_PLAYTYPE_BACK);
            // BGM���~�߂�
            StopSoundMem(result_bgm);
            // �t�F�[�h������
            fade->Initialize(false);
            // �����L���O�V�[���ɑJ��
            result_next_scene = eSceneType::eRanking;
        }
    }

    // �t�F�[�h�X�V
    fade->Update();

    result_score_time++;
    
    // �e�N���X�̍X�V�������Ăяo��
    return __super::Update();

    return GetNowSceneType();
}


void ResultScene::Draw() const
{  
    // �f�[�^
    int correct = GameDataManager::GetInstance().GetCorrect();
    int sales = GameDataManager::GetInstance().GetSales();
    int sum = 0;
    
    // ���U���g�^�C�g���摜 (1280, 720 \ 460, 90)
    DrawExtendGraph(0, 0, 1280, 720, background_image, FALSE);

    DrawGraph(0, -10, sb_result_image, TRUE);  //���U���g�X�R�A�{�[�h�̕`��

    // �ڋq����`��i�����F�^�C�g���������j
    //DrawGraph(150, 250, result_collect_font, TRUE);      // �ڋq���̃^�C�g���摜

    // �����`��i�E���F�^�C�g���������j
    //DrawGraph(730, 250, result_sales_font, TRUE);         // ����̃^�C�g���摜

    // ���v�X�R�A�^�C�g��
    //DrawGraph(150, 400, result_sum_title, TRUE);

    DrawFormatString(20, 600, 0x000000, "%d", result_score_time);

    // �����t�H���g�p�ϐ�
    int yOffset = 290;      // y���I�t�Z�b�g
    int rankX = 25;        // ���ʂ�X���W
    int correctX = 400;       //  �ڋq����X���W
    int salesX = 930;       // �����X���W
    int sumX = 380;
    int rowSpacing = 100;    // �s�Ԃ̃X�y�[�X
    int digitWidth = 32;    // 1���̕��i�g�p����t�H���g�摜�ɍ��킹��j

    if (result_score_time >= 50)
    {
        // �ڋq���̐����i�����g��j
        if (correct >= 10) {
            DrawNumber(760, 220, correct, 1.0f);
        }
        else {
            DrawNumber(800, 220, correct, 1.0f);
        }
        if (result_score_time == 53) {
            ChangeVolumeSoundMem(120, result_se);
            PlaySoundMem(result_se, DX_PLAYTYPE_NORMAL);
        }
    }
    if (result_score_time >= 53)  // ����̐����i�������g��j
    {
        if (result_score_time == 54) {
            PlaySoundMem(result_se, DX_PLAYTYPE_NORMAL);
        }
        //���オ4���̎��̃X�R�A�̈ʒu����
        if (sales >= 1000) {
            DrawNumber(660, 300, sales, 1.0f);
        }
        //���オ4���ȉ��̎��̃X�R�A�̈ʒu����
        else {
            DrawNumber(700, 300, sales, 1.0f);
        }
    }
    if (result_score_time == 200)
    {
        PlaySoundMem(sum_background, DX_PLAYTYPE_BACK);
    }
    if (result_score_time >= 700)
    {
        sum = (correct * 50) + sales;

        // ���v�X�R�A�̐����i�����\���j
        int sum_width = std::to_string(sum).length() * 32 * 1.5f;  // 32��1���̕�
        int centerX = (1280 - sum_width) / 2;
        if (sum >= 1000) {
            DrawNumber(centerX-80, 520, sum, 1.5f);
        }
        else {
            DrawNumber(centerX, 520, sum, 1.5f);  // �傫�߂ɕ\��
        }
    }
    // �o�b�W�Ɠ����\��
    if (result_score_time >= 900)
    {

        if (sum <= 1000) {
            DrawExtendGraph(800, 500, 960, 660, result_bronze_badge, TRUE);
            //DrawExtendGraph(1000, 460,1300,660, result_bronze_font, TRUE);
        }
        else if (sum <= 3600) {
            DrawExtendGraph(800, 500, 960, 660, result_gold_badge, TRUE);
            //DrawGraph(400, 480, result_gold_font, TRUE);
        }
        else {
            DrawExtendGraph(800, 500, 960, 660, result_diamond_badge, TRUE);
            //DrawGraph(400, 480, result_diamond_font, TRUE);
        }
    } 

    if (result_score_time >= 1000)DrawRotaGraph(1125, 690, 1.15, 0, result_button_image, TRUE);

    // �t�F�[�h�`��
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

// �w��ʒu�ɐ��l���摜�ŕ`�悷��
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

        // �������|�C���g�I
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
