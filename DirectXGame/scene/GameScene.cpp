#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {

}

GameScene::~GameScene() {

	delete blockModel_;
	for (auto& worldTransformBlockLine : worldTransformBlocks_) {
		for (auto worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
		
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	blockModel_ = Model::Create();
	viewProjection_.Initialize();
	const uint8_t kNumBlockVirtical = 10;
	const uint8_t kNumBlockHorizontal = 20;
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;
	worldTransformBlocks_.resize(kNumBlockHorizontal);
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint8_t i = 0; i < kNumBlockVirtical; i++) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	
	}
	for (uint8_t i = 0; i < kNumBlockVirtical; i++) {
		for (uint8_t j = 0; j < kNumBlockHorizontal; j++) {
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
		
		}
	
	}
	

}

void GameScene::Update() {

	for (auto& worldTransformBlockLine : worldTransformBlocks_) {
		for (auto worldTransformBlock : worldTransformBlockLine) {
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			worldTransformBlock->TransferMatrix();
		}
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>


	for (auto& worldTransformBlockLine : worldTransformBlocks_) {
		for (auto worldTransformBlock : worldTransformBlockLine) {
			blockModel_->Draw(*worldTransformBlock, viewProjection_);
		}
	}


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
