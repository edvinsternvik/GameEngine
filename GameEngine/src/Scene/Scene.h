#pragma once
#include "../Entity.h"
#include <functional>

namespace GameEngine {
	
	class ScriptComponentManager;
	class Camera;

	class Scene {
	public:
        Scene(const std::string& name);

		Entity createEntity(const std::string& name);
		void destroyEntity(const Entity& entity);

        void each(std::function<void(Entity)> callback) {
            m_entityRegistry.each([&](auto entity){
                callback(Entity(&m_entityRegistry, entity));
            });
        }

        template <class ComponentType>
        void each(std::function<void(Entity, ComponentType&)> callback) {
            m_entityRegistry.view<ComponentType>().each([&](auto entity, auto& component){
                callback(Entity(&m_entityRegistry, entity), component);
            });
        }

        template <class ComponentType>
        void each(std::function<void(ComponentType&)> callback) {
            m_entityRegistry.view<ComponentType>().each([&](auto& component){
                callback(component);
            });
        }

        template <class... Components>
        void eachInGroup(typename entt::type_identity<std::function<void(Entity, Components&...)>>::type callback) {
            m_entityRegistry.group<Components...>().each([&](auto entity, Components&... components){
                callback(Entity(&m_entityRegistry, entity), components...);
            });
        }

        template <class... Components>
        void eachInGroup(typename entt::type_identity<std::function<void(Components&...)>>::type callback) {
            m_entityRegistry.group<Components...>().each([&](Components&... components){
                callback(components...);
            });
        }

		Camera* getActiveCamera();
        const std::string& getName() const;

	private:
		void update();
		void updateCameras(float windowWidth, float windowHeight);

	private:
		entt::registry m_entityRegistry;
        std::string m_sceneName;

		friend class Application;
	};

}
