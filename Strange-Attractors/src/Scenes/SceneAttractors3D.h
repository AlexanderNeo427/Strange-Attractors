#ifndef SCENE_ATTRACTOR_3D
#define SCENE_ATTRACTOR_3D

#include "../SceneSystem.h"

#include <ECS/Coordinator.h>

class SceneAttractors3D : public IScene
{
public:
	SceneAttractors3D();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;
private:
};

#endif

