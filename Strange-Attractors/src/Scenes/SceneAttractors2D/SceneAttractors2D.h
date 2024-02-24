#ifndef SCENE_ATTRACTORS_2D
#define SCENE_ATTRACTORS_2D

#include "../../SceneSystem.h"

#include <vector>
#include <raylib.h>
#include <raylib-cpp.hpp>
#include <raymath.hpp>

class SceneAttractors2D : public IScene
{
private:
	struct Point3D
	{
		raylib::Vector3 pos;
		raylib::Vector3 oldPos;
		raylib::Color color;
	};
private:
	static constexpr float TIME_STEP = 0.00015f;
	static constexpr float BETA = 10.f;
	static constexpr float RHO = 28.f;
	static constexpr float SIGMA = (8.f / 3.f);
public:
	SceneAttractors2D();
	~SceneAttractors2D();

	void Init() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Exit() override;

	inline const std::string& SceneID() override
	{
		return "Strange Attractors 2D";
	}
private:
	raylib::Vector2 WorldToScreen(float worldX, float worldY);
private:
	RenderTexture2D m_imageBuffer;

	std::vector<Point3D*> m_points;
	std::vector<raylib::Color> m_colors;
	std::vector<float> m_depthBuffer;
};

#endif

