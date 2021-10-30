#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

namespace GameEngine {

	std::shared_ptr<Texture> TextureLoader::load(const std::string& filepath) const {
		stbi_set_flip_vertically_on_load(true);

		int imageWidth;
		int imageHeight;
		int channels;
		unsigned char* data = stbi_load(filepath.c_str(), &imageWidth, &imageHeight, &channels, 0);
		if(!data) {
			std::cout << "Could not load texture: " << filepath << std::endl;
			return std::shared_ptr<Texture>();
		}

		TextureFormat textureFormat;
		switch(channels) {
		case 1: textureFormat = TextureFormat::R; break;
		case 2: textureFormat = TextureFormat::RG; break;
		case 3: textureFormat = TextureFormat::SRGB; break;
		case 4: textureFormat = TextureFormat::SRGBA; break;
		default:
			std::cout << "Number of texture channels unsuported for texture: " << filepath << std::endl;
			stbi_image_free(data);
			return std::shared_ptr<Texture>();
		}

		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		texture->textureImage2D(textureFormat, imageWidth, imageHeight, data);

		texture->setFilterMode(TextureFilterMode::LINEAR);
		texture->setWrapModeS(TextureWrapMode::REPEAT);
		texture->setWrapModeT(TextureWrapMode::REPEAT);

		stbi_image_free(data);

		return texture;		
	}

}