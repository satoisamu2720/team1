#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

	uint32_t textureHandle_ = 0;
	WorldTransform worldTransformEnemy_[10];
	Model* modelEnemy_ = nullptr;

	int EnemyFlag_[10] = {};
	float enemySpeed_[10] = {};

	void EnemyMove();
	void EnemyUpdate();
	void EnemyBorn();

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	// ビュープロジェクション(共通)
	ViewProjection viewProjection_;

	int sceneMode_ = 0;

	void GamePlayUpdate();
	void GamePlayDraw3D();

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

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	

};
