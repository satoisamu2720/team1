#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Audio.h"
class Player {

public: // メンバ関数

	void Initialize();

	void Update(); // プレイヤー更新

	void Draw();

	void Model();



private: // メンバ変数
	ViewProjection playerViewProjection_;
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
