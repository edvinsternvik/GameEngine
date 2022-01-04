#pragma once
#include <memory>
#include <string>

namespace GameEngine {

	class Window;
	class Renderer;
	class Event;
	class Scene;
	class AssetManager;
	class Editor;

	class Application {
	public:
		Application(const std::string& name);
		virtual ~Application();

		void run();

		virtual void onUpdate() = 0;
		virtual void onRender() = 0;

		Window* getWindow() const;
		Scene* getScene() const;
		AssetManager* getAssetManager() const;
		
	private:
		void eventHandler(Event* event);

	private:
		std::unique_ptr<Window> m_window;
		std::unique_ptr<Renderer> m_renderer;
		std::shared_ptr<Scene> m_scene;
		std::unique_ptr<AssetManager> m_assetManager;

		std::unique_ptr<Editor> m_editor;

		bool m_running = true;
	};

}
