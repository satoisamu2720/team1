#include "Player.h"

void Player::Initialize() {
// �v���C���[�r���[�v���W�F�N�V�����̏�����
	playerViewProjection_.translation_.y = 1;
	playerViewProjection_.translation_.z = -6;
	playerViewProjection_.Initialize();
}

void Player::Update() {}

void Player::Draw() {}

void Player::Model() {}
