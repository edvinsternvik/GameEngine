#pragma once
#include "../Math/Vector.h"
#include "Gui.h"
#include "../Entity.h"
#include "../Assets/AssetHandle.h"
#include <entt/entity/registry.hpp>

namespace GameEngine {

	class Camera;
    class Texture;
    class Event;
    class Application;

	class Editor {
	public:
		Editor(Application* application);
		~Editor();

		void update();
        void render();

		Camera* getEditorCamera();
        Entity getSelectedEntity();
        AssetVariant getSelectedAsset();

		void setEventFunction(std::function<void(Event*)> eventFunction);
        void setViewportTexture(std::shared_ptr<Texture> viewportTexture);
		void updateEditorCameraViewportSize(Vector2 viewportSize);
        void selectEntity(Entity entity);
        void selectAsset(AssetVariant asset);

	private:
		entt::registry m_editorEntityRegistry;
        Application* m_application;
        Gui m_editorGui;
        std::variant<Entity, AssetVariant> m_selected;
	};

}
