#pragma once
#include "AssetData.h"
#include <string>
#include <unordered_map>

namespace GameEngine {

    class AssetManager;

    class AssetDataManager {
    private:
        template<typename T>
        class AssetDataMap {
        public:
            AssetHandleIDtype nextID();

            std::unordered_map<AssetHandleIDtype, AssetData<T>> map;

        private:
            AssetHandleIDtype m_nextID = 1;
        };

    public:
        AssetDataManager(const std::string& assetFolderPath, AssetManager* assetManager);

        void reloadAssetData();
        void clearRegisteredAssets();

        template <typename T>
        AssetHandleIDtype importAsset(const std::string& assetPath);

        template <typename T>
        AssetData<T>* getAssetData(AssetHandleIDtype ID);

        template <typename T>
        bool exists(AssetHandleIDtype ID);

        template <typename T>
        bool isValidFileExtensionForAssetType(const std::string& ext);

    private:
        template <typename T>
        AssetDataMap<T>& getAssetDataMap();

    private:
        const std::string m_assetFolderPath;
        AssetManager* m_assetManager;

        AssetDataMap<Model> m_modelAssetDataMap;
        AssetDataMap<Shader> m_shaderAssetDataMap;
        AssetDataMap<Texture> m_textureAssetDataMap;
        AssetDataMap<Material> m_materialAssetDataMap;

        AssetHandleIDtype m_nextID = 1;
    };

}