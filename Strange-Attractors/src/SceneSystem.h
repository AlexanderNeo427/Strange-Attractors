#ifndef SCENE_SYSTEM
#define SCENE_SYSTEM

#include <string>

struct IScene
{
	virtual void Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	const virtual std::string& SceneID() = 0;
};

class SceneManager
{
public: 
	static SceneManager* Instance()
	{
		static SceneManager* instance;

		if (instance == nullptr)
			instance = new SceneManager();

		return instance;
	}
public: 
	void Update(float deltaTime)
	{
		if (m_scene != m_nextScene)
		{
			m_scene->Exit();

			delete m_scene;
			m_scene = nullptr;

			m_scene = m_nextScene;
			m_scene->Init();
		}
		m_scene->Update(deltaTime);
	}
	void Render() { m_scene->Render(); }
	void Exit()   { m_scene->Exit(); }

	template<typename T>
	void LoadScene()
	{
		static_assert(std::is_base_of<IScene, T>::value, "T must implement IScene");

		if (m_scene == nullptr)
		{
			m_nextScene = m_scene = new T();
			m_scene->Init();
			return;
		}
		m_nextScene = new T();
	}
private:
	SceneManager()
		:
		m_scene(nullptr),
		m_nextScene(nullptr)
	{}
	~SceneManager()
	{
		delete m_scene;
		delete m_nextScene;
	}
private:
	IScene *m_scene, *m_nextScene;
};

#endif
