#pragma once
#include <entt/resource/handle.hpp>

namespace GameEngine {

	class Model;
	class Shader;
	class Texture;
	class Material;

	template<typename T>
	using AssetHandle = entt::resource_handle<T>;

	using ModelAsset = AssetHandle<Model>;
	using ShaderAsset = AssetHandle<Shader>;
	using TextureAsset = AssetHandle<Texture>;
	using MaterialAsset = AssetHandle<Material>;

}