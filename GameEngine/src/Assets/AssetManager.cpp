#include "AssetManager.h"
#include <entt/core/hashed_string.hpp>

namespace GameEngine {

	template<typename T>
	AssetHandle<T> AssetManager::load(const std::string& filepath) {
		// Error: T does not have a loader
		assert(0);
		return AssetHandle<T>();
	}

	template<typename T>
	AssetHandle<T> AssetManager::reload(const std::string& filepath) {
		// Error: T does not have a loader
		assert(0);
		return AssetHandle<T>();
	}

	template<typename T>
	AssetHandle<T> AssetManager::getHandle(const std::string& filepath) {
		return getResourceCache<T>().handle(entt::hashed_string{filepath.c_str()});
	}

	template<typename T>
	bool AssetManager::exists(const std::string& filepath) {
		return getResourceCache<T>().contains(entt::hashed_string{filepath.c_str()});
	}

	template<typename T>
	void AssetManager::clearAssets() {
		getResourceCache<T>().clear();
	}

	template<typename T>
	size_t AssetManager::numberOfAssets() {
		return getResourceCache<T>().size();
	}

	template<typename T>
	entt::resource_cache<T>& AssetManager::getResourceCache() {
		assert(false);
		return 0;
	}

	// Model
	template<>
	entt::resource_cache<Model>& AssetManager::getResourceCache() {
		return m_modelCache;
	}

	template<>
	AssetHandle<Model> AssetManager::load<Model>(const std::string& filepath) {
		return getResourceCache<Model>().load<ModelLoader>(entt::hashed_string{filepath.c_str()}, filepath);
	}

	template<>
	AssetHandle<Model> AssetManager::reload<Model>(const std::string& filepath) {
		return getResourceCache<Model>().reload<ModelLoader>(entt::hashed_string{filepath.c_str()}, filepath);
	}

	template AssetHandle<Model> AssetManager::getHandle<Model>(const std::string& filepath);
	template bool AssetManager::exists<Model>(const std::string& filepath);
	template void AssetManager::clearAssets<Model>();
	template size_t AssetManager::numberOfAssets<Model>();

	// Shader
	template<>
	entt::resource_cache<Shader>& AssetManager::getResourceCache() {
		return m_shaderCache;
	}

	template<>
	AssetHandle<Shader> AssetManager::load<Shader>(const std::string& filepath) {
		return getResourceCache<Shader>().load<ShaderLoader>(entt::hashed_string{filepath.c_str()}, filepath);
	}

	template<>
	AssetHandle<Shader> AssetManager::reload<Shader>(const std::string& filepath) {
		return getResourceCache<Shader>().reload<ShaderLoader>(entt::hashed_string{filepath.c_str()}, filepath);
	}

	template AssetHandle<Shader> AssetManager::getHandle<Shader>(const std::string& filepath);
	template bool AssetManager::exists<Shader>(const std::string& filepath);
	template void AssetManager::clearAssets<Shader>();
	template size_t AssetManager::numberOfAssets<Shader>();

	// ----

}