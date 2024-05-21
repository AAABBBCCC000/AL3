#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
class Player {
public:
	/// <summary>
	/// initialize
	/// </summary>
	
	void Initialize(Model* model,uint32_t textureHandle,ViewProjection* viewProjection);

	void Update();

	void Draw();
	
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	ViewProjection* viewProjection_ = nullptr;

};
