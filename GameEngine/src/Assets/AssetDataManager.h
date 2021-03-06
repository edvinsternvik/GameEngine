#pragma once
#include "AssetData.h"
#include <string>
#include <unordered_map>
#include <functional>

namespace GameEngine {

    class AssetManager;

    class AssetDataManager {
    private:
        template<typename T>
        class AssetDataMap {
        public:
            std::unordered_map<AssetHandleIDtype, std::unordered_map<AssetHandleIDtype, AssetData<T>>> map;
        };

    public:
        AssetDataManager(const std::string& assetFolderPath, AssetManager* assetManager);

        void reloadAssetData();
        void clearRegisteredAssets();

        template <typename T>
        AssetHandleIDtype importAsset(const std::string& assetPath, ImportSettings<T> importSettings);

        template <typename T>
        AssetData<T>* getAssetData(AssetHandleIDtype ID, AssetHandleIDtype localID = 0);

        template <typename T>
        bool exists(AssetHandleIDtype ID, AssetHandleIDtype localID = 0);

        template <typename T>
        void each(std::function<void(AssetData<T>&)> func) {
            for(auto& e : getAssetDataMap<T>().map) {
                for(auto& a : e.second) func(a.second);
            }
        }

        AssetHandleIDtype nextID();

        std::string getAssetFolderPath() const { return m_assetFolderPath; }

    private:
        template <typename T>
        AssetDataMap<T>& getAssetDataMap();

        template <typename T>
        void registerAssetData(const AssetData<T>& assetData);

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
