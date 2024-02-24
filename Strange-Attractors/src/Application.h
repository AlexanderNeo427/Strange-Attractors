#ifndef APPLICATION
#define APPLICATION

#include <ECS/Coordinator.h>

class Application
{
public:
	Application() {}
	void Init()
	{
		// Initialize window
		m_window = new raylib::Window(1800, 1350, "Strange Attractors");
		m_window->SetTargetFPS(INT_MAX);
		SetConfigFlags(FLAG_MSAA_4X_HINT);

		// Initialize initial scene
		SceneManager::Instance()->LoadScene<SceneAttractors2D>();

		// Initialize systems
	}
	void Run(float deltaTime)
	{
		SceneManager::Instance()->Update(deltaTime);
		SceneManager::Instance()->Render();
	}
	void Exit()
	{
		SceneManager::Instance()->Exit();
	}
	const bool ShouldClose() const { return m_window->ShouldClose(); }
private:
	raylib::Window *m_window;
};

#endif
