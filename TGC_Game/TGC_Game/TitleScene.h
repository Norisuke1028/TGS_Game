#pragma once

#include "SceneBase.h"


// �^�C�g���V�[��
class TitleScene : public SceneBase
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	//virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual eSceneType GetNowSceneType() const override;

};

