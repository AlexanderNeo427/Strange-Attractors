#include "SceneAttractors2D.h"

SceneAttractors2D::SceneAttractors2D()
{
}

SceneAttractors2D::~SceneAttractors2D()
{
}

void SceneAttractors2D::Init()
{
	m_colors = std::vector<raylib::Color>
	{
		raylib::Color::Red(),
		raylib::Color::Orange(),
		raylib::Color::Yellow(),
		raylib::Color::DarkGreen(),
		raylib::Color::Green(),
		raylib::Color::Lime(),
		raylib::Color::Blue(),
		raylib::Color::DarkBlue(),
		raylib::Color::Violet(),
		raylib::Color::SkyBlue(),
		raylib::Color::Purple(),
		raylib::Color::DarkPurple(),
	};

	auto RandFloat = [](float min, float max) {
		return min + static_cast<float>(rand()) /
					(static_cast<float>(RAND_MAX / (max - min)));
	};

	auto RandInt = [](int min, int max) {
		return min + rand() % ((max + 1) - min);
	};

	raylib::Vector3 pos = raylib::Vector3(0.01f, 0.f, 0.f);
	for (int i = 0; i < m_colors.size(); i++)
	{
		m_points.emplace_back(new Point3D { pos, pos, m_colors[i] });
		pos += raylib::Vector3(1.f, 1.f, 1.f);
	}

	m_imageBuffer = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

	// Initialize depth buffer
	m_depthBuffer.resize(GetScreenWidth() * GetScreenHeight());
	std::fill(m_depthBuffer.begin(), m_depthBuffer.end(), -999999.f);
}

void SceneAttractors2D::Update(float deltaTime)
{
	for (Point3D *p3D : m_points)
	{
		p3D->oldPos = p3D->pos;

		float dxdt = BETA * (p3D->pos.y - p3D->pos.x);
		float dydt = p3D->pos.x * (RHO - p3D->pos.z) - p3D->pos.y;
		float dzdt = (p3D->pos.x * p3D->pos.y) - (SIGMA * p3D->pos.z);

		p3D->pos.x += dxdt * TIME_STEP;
		p3D->pos.y += dydt * TIME_STEP;
		p3D->pos.z += dzdt * TIME_STEP;
	}
}

void SceneAttractors2D::Render()
{
	BeginTextureMode(m_imageBuffer);
	{
		for (Point3D* p3D : m_points)
		{
			raylib::Vector2 scrCoords = WorldToScreen(p3D->pos.x, p3D->pos.z);
			raylib::Vector2 scrCoordsOld = WorldToScreen(p3D->oldPos.x, p3D->oldPos.z);
			int idx = (int)scrCoords.y * GetScreenWidth() + (int)scrCoords.x;

			if (p3D->pos.y > m_depthBuffer[idx])
			{
				DrawLine(scrCoords.x, scrCoords.y,
						 scrCoordsOld.x, scrCoordsOld.y,
						 p3D->color);

				m_depthBuffer[idx] = p3D->pos.y;
			}
		}
	}
	EndTextureMode();

	BeginDrawing();
	ClearBackground(BLACK);
	DrawTextureRec(
		m_imageBuffer.texture, 
		Rectangle { 
			0, 0, 
			static_cast<float>(m_imageBuffer.texture.width),
			static_cast<float>(-m_imageBuffer.texture.height)
		}, 
		raylib::Vector2(0, 0), WHITE);
		
	EndDrawing();
}

void SceneAttractors2D::Exit()
{
	UnloadRenderTexture(m_imageBuffer);
}

raylib::Vector2 SceneAttractors2D::WorldToScreen(float worldX, float worldY)
{
	const float MIN_X = -22.f;
	const float MAX_X = 22.f;

	const float MIN_Y = -2.f;
	const float MAX_Y = 52.f;

	float normX = (worldX - MIN_X) / (MAX_X - MIN_X);
	float normY = (worldY - MIN_Y) / (MAX_Y - MIN_Y);

	float screenX = normX * (float)GetScreenWidth();
	float screenY = (float)GetScreenHeight() - (normY * (float)GetScreenHeight());

	return raylib::Vector2(screenX, screenY);
}
