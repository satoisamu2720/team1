#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

	// プレイヤー
	uint32_t textureHandlePlayer_ = 0;
	Model* modelPlayer_ = nullptr;
	WorldTransform worldTransformPlayer_;

	int playerLife_ = 3;
	int playerTimer_ = 0;
	float playerSpeed_ = 0.05f;
	// プレイヤー更新
	void PlayerUpdate();

	// ビーム
	uint32_t textureHandleBeam_ = 0;
	Model* modelBeam_ = {};
	WorldTransform worldTransformBeam_[10];

	void BeamMove();
	void BeamUpdate();
	void BeamBorn();

	int beamFlag_[10] = {};
	int beamTimer_ = 0;

	void Collision();
	void CollisionPlayerEnemy();
	void CollisionBeamEnemy();

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();
	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	void GamePlayUpdete();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void GamePlayDraw3D();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/*uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;

	float inputFloat3[3] = {0, 0, 0};

	DebugCamera* debugCamera_ = nullptr;

	bool isDebugcameraActive_ = false;*/
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
