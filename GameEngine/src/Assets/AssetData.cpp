#include "AssetData.h"
#include "AssetDataManager.h"
#include "../Rendering/Model.h"
#include "MaterialLoader.h"

#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace GameEngine {

    Material processMaterial(aiMaterial* aiMat, const aiScene* scene, const std::filesystem::path& baseFolderPath, AssetHandleIDtype ID, AssetDataManager* assetDataManager) {
        Material newMat;

        auto getTexture = [&](aiTextureType type, bool) -> AssetHandle<Texture> {
            aiString aiTexturePathStr("");

            if(aiMat->GetTextureCount(type) > 0) {
                if(aiMat->GetTexture(type, 0, &aiTexturePathStr) == aiReturn_SUCCESS) {
                    const char* texturePathStr = aiTexturePathStr.C_Str();
                    auto [embeddedTexture, textureIndex] = scene->GetEmbeddedTextureAndIndex(texturePathStr);

                    if(embeddedTexture) { // If the texture is embedded
                        return AssetHandle<Texture>(ID, textureIndex + 1, {});
                    }
                    else { // Texture is not embedded
                        return AssetHandle<Texture>(assetDataManager->importAsset<Texture>(baseFolderPath / std::string(texturePathStr)), 0, {});
                    }
                }
            }

            return AssetHandle<Texture>();
        };

        newMat.diffuseTexture = getTexture(aiTextureType::aiTextureType_DIFFUSE, true);
        newMat.normalTexture = getTexture(aiTextureType::aiTextureType_NORMALS, false);

        return newMat;
    }


    AssetData<Model>::AssetData(AssetHandleIDtype ID, AssetHandleIDtype localID, const std::string& filepath, const std::string& name, AssetDataManager* assetDataManager)
        : AssetDataBase(ID, localID, filepath, name) {

        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(filepath, 0);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cout << importer.GetErrorString() << std::endl;
            return;
        }

        std::filesystem::path baseFolderPathAbsolute = std::filesystem::absolute(filepath).parent_path();

        for(unsigned int i = 0; i < scene->mNumTextures; ++i) {
            aiTexture* aiTexture = scene->mTextures[i];
            embeddedTextures.push_back(AssetData<Texture>(ID, i + 1, filepath, std::string(aiTexture->mFilename.C_Str()), false));
        }

        for(unsigned int i = 0; i < scene->mNumMaterials; ++i) {
            aiMaterial* aiMat = scene->mMaterials[i];

            Material newMat = processMaterial(aiMat, scene, baseFolderPathAbsolute, ID, assetDataManager);
            std::string materialName = std::string(aiMat->GetName().C_Str()) + ".mat";

            MaterialLoader ml;
            ml.save(&newMat, baseFolderPathAbsolute / materialName);
            AssetHandleIDtype materialID = assetDataManager->importAsset<Material>(baseFolderPathAbsolute / materialName);
            
            materialIDs.push_back(materialID);
        }
    }

}
