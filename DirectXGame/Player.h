#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Audio.h"
#include "ImGuiManager.h"
#include "MathUtilityForText.h"

class Player {

public: // �����o�֐�

	void Initialize();

	void Update(); // �v���C���[�X�V

	void Draw();

	Player();
	ViewProjection playerViewProjection_;
	 ~Player();


private: // �����o�ϐ�
	
	WorldTransform worldTransformPlayer_;
	Model* modelPlayer_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	int playerLife_ = 3;
	int playerTimer_ = 0;
	float playerSpeed_ = 0.02f;
	int playerMoveFlag_ = 0;
};
