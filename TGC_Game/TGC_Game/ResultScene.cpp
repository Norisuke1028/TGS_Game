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
    HighScore_SE = LoadSoundMem("Resource/sounds/");*/

   // �����摜�i0?9�j�̓ǂݍ���
	num_image = rm->GetImages("Resource/image/number.png");

    /*/ ���U���g���C��bgm�Đ�
    PlaySoundMem(result_bgm, DX_PLAYTYPE_BACK);*/

    // �t�F�[�h���C���X�^���X��
    fade = new Fade();
    // �t�F�[�h�̏����������i�t�F�[�h�C���j
    fade->Initialize(true);

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
   
   // ���U���g�e�L�X�g�̕\���i���W: x=50, y=50�A�F: ���j(��������폜�\��)
    DrawString(50, 50, "���U���g��ʂł�", GetColor(255, 255, 255));
    DrawString(10, 26, "A : Title", GetColor(255, 255, 255));

    // ���U���g�^�C�g���摜 (1280, 720 \ 460, 90)
    DrawExtendGraph(410, 20, 870, 130, result_title_image, TRUE);
    // ���g�̃X�R�A�摜�`��
    DrawExtendGraph(100, 130, 444, 211, result_player_title, TRUE);
    // �n�C�X�R�A�摜�`��
    DrawExtendGraph(100, 300, 381, 388, result_score_history, TRUE);

    // �f�[�^
    int correct = GameDataManager::GetInstance().GetCorrect();
    int sales = GameDataManager::GetInstance().GetSales();


    DrawFormatString(100, 100, GetColor(255, 255, 255), "�ڋq�l��: %d", correct);
    DrawFormatString(100, 140, GetColor(255, 255, 255), "����: %d �~", sales);
}

void ResultScene::Finalize()
{
    
}

eSceneType ResultScene::GetNowSceneType() const
{
    return eSceneType::eResult;
}



