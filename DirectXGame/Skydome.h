
#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class WorldTransform;
class Skydome {
public:
	
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
};

/*
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Skydome {
public:
	void Initialize(Model* model, ViewProjection* viewProjection);

	void Update();

	void Draw();

private:
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
    Model* model_ = nullptr;

};
*/