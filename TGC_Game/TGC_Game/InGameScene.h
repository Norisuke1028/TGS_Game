#pragma once

#include "SceneBase.h"


// �C���Q�[���V�[��
class InGameScene : public SceneBase
{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	//virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

};

